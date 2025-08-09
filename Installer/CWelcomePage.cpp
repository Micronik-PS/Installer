// CWelcomePage.cpp: файл реализации
//

#include "pch.h"
#include "Installer.h"
#include "afxdialogex.h"
#include "CWelcomePage.h"


// Диалоговое окно CWelcomePage

IMPLEMENT_DYNAMIC(CWelcomePage, CDialogEx)

CWelcomePage::CWelcomePage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_WELCOME_PAGE, pParent)
{

}

CWelcomePage::~CWelcomePage()
{
}

void CWelcomePage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWelcomePage, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений CWelcomePage
