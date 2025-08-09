
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

	CWelcomePage dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

