#include "pch.h"
#include "Installer.h"
#include "afxdialogex.h"
#include "WelcomePage.h"

IMPLEMENT_DYNAMIC(CWelcomePage, CDialogEx)

CWelcomePage::CWelcomePage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_WELCOME_PAGE, pParent)
{
	InitTitleFont();
	InitBodyFont();
}

CWelcomePage::~CWelcomePage()
{
}

void CWelcomePage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
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
	CDialogEx::OnClose();
	delete this;
}

BOOL CWelcomePage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Заголовок диалогового окна
	CString windowText;
	if (windowText.LoadString(IDS_WELCOME_PAGE_HEAD) != NULL)
	{
		SetWindowText(windowText);
	}

	// Лого приложений
	SetLogo(IDS_PATH_LOGO_ZIP, m_logoZip);
	SetLogo(IDS_PATH_LOGO_XNVIEW, m_logoXnView);
	
	// Текст
	SetText(IDC_WELCOME_PAGE_STATIC_TEXT_TITLE, IDS_WELCOME_PAGE_TITLE, &m_titleFont);
	SetText(IDC_WELCOME_PAGE_STATIC_TEXT_BODY, IDS_WELCOME_PAGE_BODY, &m_bodyFont);
	SetText(IDC_WELCOME_PAGE_BUTTON_NEXT, IDS_WELCOME_PAGE_BUTTON_NEXT, &m_bodyFont);
	SetText(IDC_WELCOME_PAGE_BUTTON_CANCEL, IDS_WELCOME_PAGE_BUTTON_CANCEL, &m_bodyFont);

	// Иконка установщика
	auto icon = theApp.LoadIcon(IDI_APP);
	SetIcon(icon, TRUE);
	SetIcon(icon, FALSE);

	return TRUE;
}

void CWelcomePage::SetText(const int nIDC_staticText, const int nIDS_text, CFont* const font)
{
	auto titleTextControl = GetDlgItem(nIDC_staticText);

	titleTextControl->SetFont(font);

	CString titleText;
	if (titleText.LoadString(nIDS_text) != NULL)
	{
		titleTextControl->SetWindowText(titleText);
	}
}

void CWelcomePage::InitTitleFont()
{
	m_titleFont.CreateFontW
	(
		40, // размер
		0,
		0,
		0,
		FW_BOLD, // толщина
		FALSE, // курсив
		FALSE, // подчеркнутый
		FALSE, // зачеркнутый
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("Segoe UI") // шрифт
	);
}

void CWelcomePage::InitBodyFont()
{
	m_bodyFont.CreateFontW
	(
		17, // размер
		0,
		0,
		0,
		FW_DONTCARE, // толщина
		FALSE, // курсив
		FALSE, // подчеркнутый
		FALSE, // зачеркнутый
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("Segoe UI") // шрифт
	);
}

void CWelcomePage::SetLogo(const int nIDS_filePathToLogo, CPictureCtrl& placement)
{
	CString pathToLogo;

	if (pathToLogo.LoadString(nIDS_filePathToLogo) != NULL)
	{
		placement.LoadFromFile(pathToLogo);
	}
}

void CWelcomePage::OnBnClickedWelcomePageButtonNext()
{
	
}

void CWelcomePage::OnBnClickedWelcomePageButtonCancel()
{
	PostMessage(WM_CLOSE);
}
