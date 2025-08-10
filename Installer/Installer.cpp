#include "pch.h"
#include "framework.h"
#include "Installer.h"

#include "WelcomePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CInstallerApp, CWinApp)
	
END_MESSAGE_MAP()

CInstallerApp::CInstallerApp()
{

}

CInstallerApp theApp;

BOOL CInstallerApp::InitInstance()
{
	CWinApp::InitInstance();

	CWelcomePage* pDlg = new CWelcomePage; // очищается в CWelcomePage::OnClose()
	pDlg->Create(IDD_DIALOG_WELCOME_PAGE);
	pDlg->ShowWindow(SW_SHOW);
	m_pMainWnd = pDlg;

	return TRUE;
}

