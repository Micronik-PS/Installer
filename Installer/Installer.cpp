
// Installer.cpp: определяет поведение классов для приложения.
//

#include "pch.h"
#include "framework.h"
#include "Installer.h"

#include "CWelcomePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CInstallerApp

BEGIN_MESSAGE_MAP(CInstallerApp, CWinApp)
	
END_MESSAGE_MAP()


// Создание CInstallerApp

CInstallerApp::CInstallerApp()
{

}


// Единственный объект CInstallerApp

CInstallerApp theApp;


// Инициализация CInstallerApp

BOOL CInstallerApp::InitInstance()
{
	CWinApp::InitInstance();

	CWelcomePage* pDlg = new CWelcomePage;
	pDlg->Create(IDD_DIALOG_WELCOME_PAGE);
	pDlg->ShowWindow(SW_SHOW);
	m_pMainWnd = pDlg;

	return TRUE;
}

