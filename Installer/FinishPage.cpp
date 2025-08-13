#include "pch.h"
#include "Installer.h"
#include "afxdialogex.h"
#include "FinishPage.h"

IMPLEMENT_DYNAMIC(CFinishPage, CBaseDialog)

CFinishPage::CFinishPage(CWnd* pParent /*=nullptr*/)
	: CBaseDialog(IDD_DIALOG_FINISH_PAGE, pParent)
{

}

CFinishPage::~CFinishPage()
{
}

void CFinishPage::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FINISH_PAGE_PICTURE_CONTROL_ZIP, m_logoZip);
	DDX_Control(pDX, IDC_FINISH_PAGE_PICTURE_CONTROL_XNVIEW, m_logoXnView);
}

BEGIN_MESSAGE_MAP(CFinishPage, CBaseDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_FINISH_PAGE_BUTTON_EXIT, &CFinishPage::OnBnClickedFinishPageButtonExit)
END_MESSAGE_MAP()

BOOL CFinishPage::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	theApp.OnOpenPage();

	SetDialogHead(IDI_APP, IDS_FINISH_PAGE_HEAD);

	// Лого приложений
	SetPictureForControl(IDB_LOGO_ZIP, m_logoZip);
	SetPictureForControl(IDB_LOGO_XNVIEW, m_logoXnView);

	// Текст
	SetTextForControl(IDC_FINISH_PAGE_STATIC_TEXT_TITLE, IDS_FINISH_PAGE_TITLE, &m_titleFont);
	SetTextForControl(IDC_FINISH_PAGE_BUTTON_EXIT, IDS_FINISH_PAGE_BUTTON_EXIT, &m_bodyFont);

	return TRUE;
}

void CFinishPage::OnClose()
{
	DestroyWindow();
}

void CFinishPage::PostNcDestroy()
{
	CBaseDialog::PostNcDestroy();
	delete this;
}

void CFinishPage::OnBnClickedFinishPageButtonExit()
{
	DestroyWindow();
}