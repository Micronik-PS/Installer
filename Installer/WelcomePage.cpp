#include "pch.h"
#include "Installer.h"
#include "afxdialogex.h"
#include "WelcomePage.h"

IMPLEMENT_DYNAMIC(CWelcomePage, CBaseDialog)

CWelcomePage::CWelcomePage(CWnd* pParent /*=nullptr*/)
	: CBaseDialog(IDD_DIALOG_WELCOME_PAGE, pParent)
{

}

CWelcomePage::~CWelcomePage()
{
}

void CWelcomePage::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WELCOME_PAGE_PICTURE_ZIP, m_logoZip);
	DDX_Control(pDX, IDC_WELCOME_PAGE_PICTURE_XNVIEW, m_logoXnView);
}


BEGIN_MESSAGE_MAP(CWelcomePage, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_WELCOME_PAGE_BUTTON_NEXT, &CWelcomePage::OnBnClickedWelcomePageButtonNext)
	ON_BN_CLICKED(IDC_WELCOME_PAGE_BUTTON_CANCEL, &CWelcomePage::OnBnClickedWelcomePageButtonCancel)
END_MESSAGE_MAP()


void CWelcomePage::OnClose()
{
	CBaseDialog::OnClose();
	delete this;
}

BOOL CWelcomePage::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	SetDialogHead(IDI_APP, IDS_WELCOME_PAGE_HEAD);

	// Лого приложений
	SetPictureForControl(IDS_PATH_LOGO_ZIP, m_logoZip);
	SetPictureForControl(IDS_PATH_LOGO_XNVIEW, m_logoXnView);
	
	// Текст
	SetTextForControl(IDC_WELCOME_PAGE_STATIC_TEXT_TITLE, IDS_WELCOME_PAGE_TITLE, &m_titleFont);
	SetTextForControl(IDC_WELCOME_PAGE_STATIC_TEXT_BODY, IDS_WELCOME_PAGE_BODY, &m_bodyFont);
	SetTextForControl(IDC_WELCOME_PAGE_BUTTON_NEXT, IDS_WELCOME_PAGE_BUTTON_NEXT, &m_bodyFont);
	SetTextForControl(IDC_WELCOME_PAGE_BUTTON_CANCEL, IDS_WELCOME_PAGE_BUTTON_CANCEL, &m_bodyFont);

	return TRUE;
}

void CWelcomePage::OnBnClickedWelcomePageButtonNext()
{
	
}

void CWelcomePage::OnBnClickedWelcomePageButtonCancel()
{
	PostMessage(WM_CLOSE);
}
