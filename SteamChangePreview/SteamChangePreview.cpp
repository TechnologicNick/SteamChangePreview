#include "pch.h"
#include "SteamChangePreview.h"

int main(int argc, char* argv[])
{
	if (argc == 1) {
		return enterAll();
	} else if (argc == 2) {
		return enterIds(argv[1]);
	}

	InputParser input(argc, argv);
	if (input.cmdOptionExists("-h") || input.cmdOptionExists("--help") || input.cmdOptionExists("/?")) {
		printf("Usage: SteamChangePreview.exe IMAGE_PATH [PUBLISHEDFILEID] [APPID]\n\n");

		printf("Run with -h or --help to show this usage\n");
		printf("It is possible to drag and drop an image onto the executable.\n");
		printf("Fields that are not filled in will be taken from stdin.\n");
		return 0;
	}

	if (!SteamAPI_Init())
	{
		printf("SteamAPI_Init() failed\n");
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
	uint64 publishedfileid = getInt("Enter the publishedfileid: ", true);
	int appid = getInt("Enter the appid: ", false);

	return changePreview(appid, publishedfileid, file);
}

int getAppid(uint64 publishedfileid) {
	// This sucks
	std::wstring str(L"powershell -c \"[regex]::Matches((Invoke-WebRequest -Uri \\\"https://steamcommunity.com/sharedfiles/filedetails/?id=");
	str += std::to_wstring(publishedfileid);
	str += std::wstring(L"\\\" ).Content, 'data-appid=\\\"(\\d+?)\\\">').Groups[1].Value\"");

	wprintf(L"Executing: %s\n", str.c_str());
	
	auto out = ExecCmd(str.c_str());
	printf("out=%s\n", out);

	return strtol(out, NULL, 10);
}

int changePreview(int appid, uint64 publishedfileid, const char* file) {
	printf("appid=%d\n", appid);
	printf("publishedfileid=%llu\n", publishedfileid);
	printf("file=%s\n", file);

	if (appid == 0) {
		printf("Looking for the correct appid online...\n");

		appid = getAppid(publishedfileid);
		printf("Found appid=%d\n", appid);

		if (appid == 0) {
			std::cerr << "Failed getting appid of workshop item" << std::endl;
			return 1;
		}
	}

	return 0;
}

