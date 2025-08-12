#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"
#include "ProgramInstallStatus.h"

class CWelcomePage;

class CInstallerApp : public CWinApp
{
public:
	CInstallerApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

public:
	void OnCloseWelcomePage(bool canceled);
	void OnCloseOfferPage(bool canceled, ProgramInstallStatus& offerApp);
	void OnOpenPage();

private:
	bool IsProgramInstalled(const int nIDS_PATH_REGISTER_KEY, const int nIDS_REGISTER_VALUE_ZIP);
	void OpenWelcomePage();
	bool CInstallerApp::TryOpenOfferPage();
	bool CInstallerApp::TryOpenProgressPage();

	CWnd* pastPage;

	ProgramInstallStatus m_sevenZip;
	ProgramInstallStatus m_xnView;

};

extern CInstallerApp theApp;
