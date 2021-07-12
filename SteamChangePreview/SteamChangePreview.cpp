#include "pch.h"
#include "SteamChangePreview.h"

int main(int argc, char* argv[])
{
	InputParser input(argc, argv);
	if (input.cmdOptionExists("-h") || input.cmdOptionExists("--help") || input.cmdOptionExists("/?")) {
		printf("Usage: %s IMAGE_PATH PUBLISHEDFILEID [APPID]\n\n", argv[0]);

		printf("Run with -h or --help to show this usage\n");
		printf("It is possible to drag and drop an image onto the executable.\n");
		printf("Fields that are not filled in will be taken from stdin.\n");
		return 0;
	}

	if (argc == 1) {
		return enterAll();
	} else if (argc == 2) {
		return enterIds(argv[1]);
	}
}

int enterAll() {
	char file[260];

	printf("Enter the path to your preview image: ");
	fgets(file, sizeof(file), stdin);

	return enterIds(file);
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
		printf("Found appid=%d\n", appid);

		if (appid == 0) {
			std::cerr << "Failed getting appid of workshop item" << std::endl;
			return 1;
		}
	}

	return changePreview(appid, publishedfileid, file);
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

int changePreview(AppId_t appid, PublishedFileId_t publishedfileid, const char* file) {
	printf("appid=%lu\n", appid);
	printf("publishedfileid=%llu\n", publishedfileid);
	printf("file=%s\n", file);

	CPreviewChanger pc(appid);

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



CPreviewChanger::CPreviewChanger(AppId_t appid) {
	this->m_appid = appid;

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
	printf("OnSubmitItemUpdateResult\n");
	printf("m_bUserNeedsToAcceptWorkshopLegalAgreement = %s\n", pCallback->m_bUserNeedsToAcceptWorkshopLegalAgreement ? "true" : "false");
	printf("m_eResult = %d\n", pCallback->m_eResult);
	printf("m_nPublishedFileId = %llu\n", pCallback->m_nPublishedFileId);

	this->m_LoopRunning = false;
}


