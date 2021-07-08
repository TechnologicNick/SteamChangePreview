#include "pch.h"
#include <iostream>

int main()
{
	if (!SteamAPI_Init())
	{
		printf("SteamAPI_Init() failed\n");
	}
}

