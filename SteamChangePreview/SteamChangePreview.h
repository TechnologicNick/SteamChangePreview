#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <Windows.h>
#include "InputParser.h"
#include "ExecCmd.h"
#include "EResult.h"

int enterAll();
int onEnterFile(const char* filename);
int enterIds(const char* file);
AppId_t getAppid(PublishedFileId_t publishedfileid);
int changePreview(AppId_t appid, PublishedFileId_t publishedfileid, const char* file, bool hidemessagebox);

class CPreviewChanger {
public:
	CPreviewChanger(AppId_t appid, bool hidemessagebox);

	void SetAppId(AppId_t appid);

	bool Init();
	void Shutdown();

	bool m_LoopRunning = false;
	void LoopRunCallbacks();

	int ChangePreview(PublishedFileId_t publishedfileid, const char* file);

private:
	CPreviewChanger *m_pPreviewChanger;
	AppId_t m_appid;
	bool m_hidemessagebox;

	void OnSubmitItemUpdate(SubmitItemUpdateResult_t *pCallback, bool bUserNeedsToAcceptWorkshopLegalAgreement);
	CCallResult<CPreviewChanger, SubmitItemUpdateResult_t> m_SubmitItemUpdateCallResult;
};
