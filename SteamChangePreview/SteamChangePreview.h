#pragma once

#include <iostream>
#include <string>
#include "InputParser.h"
#include "ExecCmd.h"

int enterAll();
int enterIds(const char* file);
int changePreview(int appid, uint64 publishedfileid, const char* file);