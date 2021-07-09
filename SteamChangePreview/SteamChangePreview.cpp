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

	printf("Writing appid to steam_appid.txt\n");
	std::ofstream myfile;
	myfile.open("steam_appid.txt");
	myfile << appid;
	myfile.close();

	printf("Initialising SteamAPI\n");
	if (!SteamAPI_Init())
	{
		printf("SteamAPI_Init() failed\n");
		return 1;
	}

	printf("Starting item update\n");
	UGCUpdateHandle_t hUpdate = SteamUGC()->StartItemUpdate(appid, publishedfileid);

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

	// TODO: Callback https://partner.steamgames.com/doc/api/ISteamUGC#SubmitItemUpdateResult_t

	printf("Shutting down SteamAPI\n");
	SteamAPI_Shutdown();

	return 0;
}

