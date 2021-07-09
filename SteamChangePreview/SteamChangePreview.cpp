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

long getInt(const char* message, bool required) {
	char *p, s[100];
	long n;

	printf(message);

	while (fgets(s, sizeof(s), stdin)) {
		n = strtol(s, &p, 10);
		if ((required && p == s) || *p != '\n') {
			printf("ERROR: Please enter an integer: ");
		}
		else break;
	}

	return n;
}

int enterIds(const char* file) {
	int publishedfileid = getInt("Enter the publishedfileid: ", true);
	int appid = getInt("Enter the appid: ", false);

	return changePreview(appid, publishedfileid, file);
}

int changePreview(int appid, int publishedfileid, const char* file) {
	printf("appid=%d\n", appid);
	printf("publishedfileid=%d\n", publishedfileid);
	printf("file=%s\n", file);

	return 0;
}

