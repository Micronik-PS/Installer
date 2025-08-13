#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"
#include "ProgramInstallStatus.h"
#include "OfferProgram.h"
#include "ProgressBarUpdateData.h"

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
	void OnCloseOfferPage(bool canceled, ProgramInstallStatus& offerProgramInstallStatus);
	void OnOpenPage();
	static UINT StartDeploy(LPVOID pParam);
	UINT GetCountOfferProgramMarkedForInstall();

private:
	CWnd* pastPage;
	CArray<OfferProgram> m_offerPrograms;

	bool IsProgramInstalled(const int nIDS_PATH_REGISTER_KEY, const int nIDS_REGISTER_VALUE);
	void OpenWelcomePage();
	bool TryOpenOfferPage();
	bool TryOpenProgressPage();
	bool TryDownloadExeInstaller(OfferProgram& offerProgram, ProgressBarUpdateData& progressBarUpdateDownloadData);
	bool TryInstallOfferProgram(OfferProgram& offerProgram, ProgressBarUpdateData& progressBarUpdateInstallData);
	CString GetExeInstallerPath() const;
};

extern CInstallerApp theApp;
