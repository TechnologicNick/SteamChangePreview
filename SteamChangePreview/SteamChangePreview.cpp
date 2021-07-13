#include "pch.h"
#include "SteamChangePreview.h"

bool g_hidemessagebox = false;

int main(int argc, char* argv[])
{
	InputParser input(argc, argv);
	if (input.cmdOptionExists("-h") || input.cmdOptionExists("--help") || input.cmdOptionExists("/?")) {
		printf("Usage: %s IMAGE_PATH PUBLISHEDFILEID [APPID]\n\n", argv[0]);

		printf("Run with -h or --help to show this usage\n");
		printf("Run with --hidemessagebox to prevent the message box from being shown.\n");
		printf("It is possible to drag and drop an image onto the executable.\n");
		printf("Fields that are not filled in will be taken from stdin.\n");
		return 0;
	}

	g_hidemessagebox = input.cmdOptionExists("--hidemessagebox");

	int nonOptionCount = input.getNonOptionCount();

	if (nonOptionCount == 0) {
		return enterAll();
	} else if (nonOptionCount == 1) {
		char fullFilename[MAX_PATH];

		int result = processFile(input.getNthNonOption(0).c_str(), fullFilename);
		if (result != 0) {
			return result;
		}

		return enterIds(fullFilename);
	} else if (nonOptionCount == 2) {
		char fullFilename[MAX_PATH];

		int result = processFile(input.getNthNonOption(0).c_str(), fullFilename);
		if (result != 0) {
			return result;
		}

		PublishedFileId_t publishedfileid = strtoull(input.getNthNonOption(1).c_str(), NULL, 10);
		
		printf("Looking for the correct appid online...\n");
		AppId_t appid = getAppid(publishedfileid);
		
		if (appid == 0) {
			std::cerr << "Failed getting appid of workshop item" << std::endl;

			std::ifstream fAppid("steam_appid.txt");
			if (fAppid.is_open()) {
				fAppid >> appid;
				printf("Falling back to using previous appid = %d\n", appid);
			}
			else {
				printf("No previous appid found to fall back to\n");
				return 1;
			}
		} else {
			printf("Found appid = %d\n", appid);
		}

		return changePreview(appid, publishedfileid, fullFilename, g_hidemessagebox);
	} else if (nonOptionCount >= 3) {
		char fullFilename[MAX_PATH];

		int result = processFile(input.getNthNonOption(0).c_str(), fullFilename);
		if (result != 0) {
			return result;
		}

		PublishedFileId_t publishedfileid = strtoull(argv[2], NULL, 10);
		AppId_t appid = (AppId_t) strtoull(argv[3], NULL, 10);

		return changePreview(appid, publishedfileid, fullFilename, g_hidemessagebox);
	}
}

int enterAll() {
	char filename[MAX_PATH];
	char fullFilename[MAX_PATH];

	printf("Enter the path to your preview image: ");
	fgets(filename, sizeof(filename), stdin);

	filename[strcspn(filename, "\n")] = 0;

	int result = processFile(filename, fullFilename);
	if (result != 0) {
		return result;
	}

	return enterIds(fullFilename);
}

int processFile(const char* filename, LPSTR fullFilename) {
	//char fullFilename[MAX_PATH];
	GetFullPathNameA(filename, MAX_PATH, fullFilename, nullptr);

	std::ifstream f(fullFilename);

	if (f.fail()) {
		std::cerr << "Failed reading \"" << fullFilename << "\": " << strerror(errno) << std::endl;
		return errno;
	}

	return 0;
}

uint64 getInt(const char* message, bool required) {
	char *p, s[100];
	uint64 n;

	printf(message);

	while (fgets(s, sizeof(s), stdin)) {
		n = strtoull(s, &p, 10);
		if ((required && p == s) || *p != '\n') {
			printf("ERROR: Please enter an integer: ");
		}
		else break;
	}

	return n;
}

int enterIds(const char* file) {
	PublishedFileId_t publishedfileid = getInt("Enter the publishedfileid: ", true);
	AppId_t appid = (AppId_t) getInt("Enter the appid: ", false);

	if (appid == 0) {
		printf("Looking for the correct appid online...\n");

		appid = getAppid(publishedfileid);

		if (appid == 0) {
			std::cerr << "Failed getting appid of workshop item" << std::endl;
			
			std::ifstream fAppid("steam_appid.txt");
			if (fAppid.is_open()) {
				fAppid >> appid;
				printf("Falling back to using previous appid = %d\n", appid);
			}
			else {
				printf("No previous appid found to fall back to\n");
				return 1;
			}
		} else {
			printf("Found appid = %d\n", appid);
		}
	}

	return changePreview(appid, publishedfileid, file, g_hidemessagebox);
}

AppId_t getAppid(PublishedFileId_t publishedfileid) {
	// This sucks
	std::wstring str(L"powershell -c \"[regex]::Matches((Invoke-WebRequest -Uri \\\"https://steamcommunity.com/sharedfiles/filedetails/?id=");
	str += std::to_wstring(publishedfileid);
	str += std::wstring(L"\\\" ).Content, 'data-appid=\\\"(\\d+?)\\\">').Groups[1].Value\"");

	//wprintf(L"Executing: %s\n", str.c_str());

	auto out = ExecCmd(str.c_str());
	//printf("out=%s\n", out);

	return strtoul(out, NULL, 10);
}

int changePreview(AppId_t appid, PublishedFileId_t publishedfileid, const char* file, bool hidemessagebox) {
	printf("Changing preview with data:\n");
	printf("  appid = %lu\n", appid);
	printf("  publishedfileid = %llu\n", publishedfileid);
	printf("  file = %s\n", file);

	CPreviewChanger pc(appid, hidemessagebox);

	if (!pc.Init()) {
		return 1;
	}

	int result = pc.ChangePreview(publishedfileid, file);
	if (result) {
		pc.Shutdown();
		return result;
	}

	pc.LoopRunCallbacks();

	pc.Shutdown();

	return 0;
}



CPreviewChanger::CPreviewChanger(AppId_t appid, bool hidemessagebox) {
	this->m_appid = appid;
	this->m_hidemessagebox = hidemessagebox;

	this->SetAppId(appid);
}

void CPreviewChanger::SetAppId(AppId_t appid) {
	printf("Writing appid to steam_appid.txt\n");
	std::ofstream myfile;
	myfile.open("steam_appid.txt");
	myfile << appid;
	myfile.close();
}

bool CPreviewChanger::Init() {
	printf("Initialising SteamAPI\n");
	if (!SteamAPI_Init())
	{
		printf("SteamAPI_Init() failed\n");
		printf("Make sure Steam is running, you're logged in and used the correct appid\n");
		return false;
	}

	return true;
}

void CPreviewChanger::Shutdown() {
	printf("Shutting down SteamAPI");
	SteamAPI_Shutdown();
}

int CPreviewChanger::ChangePreview(PublishedFileId_t publishedfileid, const char* file) {

	printf("Starting item update\n");
	UGCUpdateHandle_t hUpdate = SteamUGC()->StartItemUpdate(this->m_appid, publishedfileid);

	printf("Setting item preview\n");
	if (!SteamUGC()->SetItemPreview(hUpdate, file)) {
		printf("SteamUGC()->SetItemPreview() failed\n");
		return 1;
	}

	printf("Submitting update\n");
	SteamAPICall_t hSteamAPICall = SteamUGC()->SubmitItemUpdate(hUpdate, "Update preview image");
	if (hSteamAPICall == k_UGCQueryHandleInvalid) {
		printf("SteamUGC()->SubmitItemUpdate failed\n");
		return 1;
	}

	m_SubmitItemUpdateCallResult.Set(hSteamAPICall, this, &CPreviewChanger::OnSubmitItemUpdate);

	// TODO: Callback https://partner.steamgames.com/doc/api/ISteamUGC#SubmitItemUpdateResult_t

	return 0;
}

void CPreviewChanger::LoopRunCallbacks() {
	this->m_LoopRunning = true;

	while (m_LoopRunning) {
		SteamAPI_RunCallbacks();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void CPreviewChanger::OnSubmitItemUpdate(SubmitItemUpdateResult_t *pCallback, bool bUserNeedsToAcceptWorkshopLegalAgreement) {
	printf("OnSubmitItemUpdate callback triggered:\n");
	printf("  m_bUserNeedsToAcceptWorkshopLegalAgreement = %s\n", pCallback->m_bUserNeedsToAcceptWorkshopLegalAgreement ? "true" : "false");
	printf("  m_eResult = %d\n", pCallback->m_eResult);
	printf("  m_nPublishedFileId = %llu\n", pCallback->m_nPublishedFileId);

	const char* caption = pCallback->m_eResult == k_EResultOK ? "Successfully updated preview image" : "Failed to update preview image";


	std::string conclusion;

	if (bUserNeedsToAcceptWorkshopLegalAgreement || pCallback->m_bUserNeedsToAcceptWorkshopLegalAgreement) {
		conclusion += "You need to accept the Steam Workshop Legal agreement\n";
		conclusion += "https://steamcommunity.com/sharedfiles/workshoplegalagreement\n\n";
	}

	// Add more information about errors
	switch (pCallback->m_eResult) {
	case k_EResultInvalidParam:
		conclusion += "Either the provided app ID is invalid or doesn't match the consumer app ID of the item, ISteamUGC is not enabled for the provided app ID on the Steam Workshop Configuration App Admin page, or the preview file is smaller than 16 bytes.\n\n";
		break;
	case k_EResultAccessDenied:
		conclusion += "You don't own a license for the provided app ID.\n\n";
		break;
	case k_EResultFileNotFound:
		conclusion += "Failed to get the workshop info for the item or failed to read the preview file.\n\n";
		break;
	case k_EResultLockingFailed: 
		conclusion += "Failed to aquire UGC Lock.\n\n";
		break;
	case k_EResultLimitExceeded:
		conclusion += "The preview image is too large, it must be less than 1 Megabyte; or there is not enough space available on your Steam Cloud.\n\n";
		break;
	}

	conclusion += "Result:\n";
	conclusion += "  Code: " + std::to_string(pCallback->m_eResult) + std::string("\n");
	conclusion += "  Name: " + std::string(GetEResultName(pCallback->m_eResult)) + std::string("\n");
	conclusion += "  Description: " + std::string(GetEResultDescription(pCallback->m_eResult)) + std::string("\n");


	printf("\n\n%s\n\n%s", caption, conclusion.c_str());

	if (!this->m_hidemessagebox) {
		MessageBoxA(
			NULL,
			conclusion.c_str(),
			caption,
			MB_OK | (pCallback->m_eResult != k_EResultOK ? MB_ICONERROR : 0)
		);
	}

	this->m_LoopRunning = false;
}


