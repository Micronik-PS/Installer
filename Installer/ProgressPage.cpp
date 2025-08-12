#include "pch.h"
#include "Installer.h"
#include "afxdialogex.h"
#include "ProgressPage.h"
#include "BaseDialog.h"

IMPLEMENT_DYNAMIC(CProgressPage, CBaseDialog)

CProgressPage::CProgressPage(CWnd* pParent /*=nullptr*/)
	: CBaseDialog(IDD_DIALOG_PROGRESS_PAGE, pParent)
{

}

CProgressPage::~CProgressPage()
{
}

void CProgressPage::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProgressPage, CBaseDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

void CProgressPage::OnClose()
{
	
}

void CProgressPage::PostNcDestroy()
{
	CBaseDialog::PostNcDestroy();
	this;
}

BOOL CProgressPage::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	theApp.OnOpenPage();

	SetDialogHead(IDI_APP, IDS_PROGRESS_PAGE_HEAD);

	SetTextForControl(IDC_PROGRESS_PAGE_STATIC_TEXT_TITLE, IDS_PROGRESS_PAGE_TITLE, &m_titleFont);
	SetTextForControl(IDC_PROGRESS_PAGE_STATIC_TEXT_BODY, IDS_PROGRESS_PAGE_BODY, &m_bodyFont);

	return TRUE;
}
