#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "InputParser.h"
#include "ExecCmd.h"

int enterAll();
int enterIds(const char* file);
AppId_t getAppid(PublishedFileId_t publishedfileid);
int changePreview(AppId_t appid, PublishedFileId_t publishedfileid, const char* file);

class CPreviewChanger {
public:
	CPreviewChanger(AppId_t appid);

	void SetAppId(AppId_t appid);

	bool Init();
	void Shutdown();

	bool m_LoopRunning = false;
	void LoopRunCallbacks();

	int ChangePreview(PublishedFileId_t publishedfileid, const char* file);

private:
	CPreviewChanger *m_pPreviewChanger;
	AppId_t m_appid;

	//STEAM_CALLBACK(CPreviewChanger, OnSubmitItemUpdateResult, SubmitItemUpdateResult_t);

	void OnSubmitItemUpdate(SubmitItemUpdateResult_t *pCallback, bool bUserNeedsToAcceptWorkshopLegalAgreement);
	CCallResult<CPreviewChanger, SubmitItemUpdateResult_t> m_SubmitItemUpdateCallResult;
};
