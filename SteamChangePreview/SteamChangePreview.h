#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "InputParser.h"
#include "ExecCmd.h"

int enterAll();
int enterIds(const char* file);
AppId_t getAppid(PublishedFileId_t publishedfileid);
int changePreview(AppId_t appid, PublishedFileId_t publishedfileid, const char* file);