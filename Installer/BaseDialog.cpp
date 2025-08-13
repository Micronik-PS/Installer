#include "pch.h"
#include "Installer.h"
#include "afxdialogex.h"
#include "BaseDialog.h"
#include "PictureCtrl.h"

IMPLEMENT_DYNAMIC(CBaseDialog, CDialogEx)

CBaseDialog::CBaseDialog(UINT nIDTemplate, CWnd* pParent /*=nullptr*/):
	CDialogEx(nIDTemplate, pParent)
{
	InitTitleFont();
	InitBodyFont();
}

CBaseDialog::~CBaseDialog()
{
}

void CBaseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBaseDialog, CDialogEx)
END_MESSAGE_MAP()


void CBaseDialog::InitTitleFont()
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

void CBaseDialog::InitBodyFont()
{
	m_bodyFont.CreateFontW
	(
		17, // размер
		0,
		0,
		0,
		FW_NORMAL, // толщина
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

void CBaseDialog::SetPictureForControl(const int nIDS_filePathToPicture, CPictureCtrl& placement)
{
	CString pathToPicture;

	if (pathToPicture.LoadString(nIDS_filePathToPicture) != NULL)
	{
		placement.LoadFromFile(pathToPicture);
	}
}

void CBaseDialog::SetTextForControl(const int nIDC_staticText, const int nIDS_text, CFont* const font)
{
	CString text;
	if (text.LoadString(nIDS_text) != NULL)
	{
		SetTextForControl(nIDC_staticText, text, font);
	}
}

void CBaseDialog::SetTextForControl(const int nIDC_staticText, const CString& text, CFont* const font)
{
	auto textControl = GetDlgItem(nIDC_staticText);

	textControl->SetFont(font);

	textControl->SetWindowText(text);
}

void CBaseDialog::SetDialogHead(const int nIDI_applicationIcon, const int nIDS_headText)
{
	CString headText;
	if (headText.LoadString(nIDS_headText) != NULL)
	{
		SetDialogHead(nIDI_applicationIcon, headText);
	}
}

void CBaseDialog::SetDialogHead(const int nIDI_applicationIcon, const CString& headText)
{
	// Иконка
	auto icon = theApp.LoadIcon(nIDI_applicationIcon);
	SetIcon(icon, TRUE);
	SetIcon(icon, FALSE);

	SetWindowText(headText);
}