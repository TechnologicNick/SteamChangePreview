#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "InputParser.h"
#include "ExecCmd.h"

int enterAll();
int enterIds(const char* file);
int getAppid(uint64 publishedfileid);
int changePreview(int appid, uint64 publishedfileid, const char* file);