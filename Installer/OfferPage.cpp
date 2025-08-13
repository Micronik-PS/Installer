#include "pch.h"
#include "Installer.h"
#include "afxdialogex.h"
#include "OfferPage.h"


IMPLEMENT_DYNAMIC(COfferPage, CBaseDialog)


COfferPage::COfferPage(OfferProgram& offerProgram, CWnd* pParent)
	: CBaseDialog(IDD_DIALOG_OFFER_PAGE, pParent)
	, m_offerProgram{ offerProgram }
{
}

COfferPage::~COfferPage()
{
}

void COfferPage::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OFFER_PAGE_PICTURE, m_offerLogo);
	DDX_Control(pDX, IDC_OFFER_PAGE_MFCLINK_LICENSE, m_licenseUrl);
}


BEGIN_MESSAGE_MAP(COfferPage, CBaseDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_OFFER_PAGE_BUTTON_ACCEPT, &COfferPage::OnBnClickedOfferPageButtonAccept)
	ON_BN_CLICKED(IDC_OFFER_PAGE_BUTTON_CANCEL, &COfferPage::OnBnClickedOfferPageButtonCancel)
END_MESSAGE_MAP()


void COfferPage::OnClose()
{
	DestroyWindow();
}

BOOL COfferPage::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	theApp.OnOpenPage();

	SetDialogHead(IDI_APP, GetHeadText(m_offerProgram.nIDS_OFFER_PROGRAM_NAME));

	SetTextForControl(IDC_OFFER_PAGE_STATIC_TEXT_TITLE, GetTitleText(m_offerProgram.nIDS_OFFER_PROGRAM_NAME), &m_titleFont);
	SetTextForControl(IDC_OFFER_PAGE_STATIC_TEXT_DESCRIPTION, m_offerProgram.nIDS_DESCRIPTION, &m_bodyFont);
	SetTextForControl(IDC_OFFER_PAGE_BUTTON_ACCEPT, IDS_OFFER_PAGE_BUTTON_ACCEPT, &m_bodyFont);
	SetTextForControl(IDC_OFFER_PAGE_BUTTON_CANCEL, IDS_OFFER_PAGE_BUTTON_CANCEL, &m_bodyFont);
	SetTextForControl(IDC_OFFER_PAGE_MFCLINK_LICENSE, IDS_OFFER_PAGE_LICENSE, &m_bodyFont);

	SetPictureForControl(m_offerProgram.nIDS_PATH_LOGO, m_offerLogo);

	CString url;
	if (url.LoadString(m_offerProgram.nIDS_LICENSE_URL) != NULL)
	{
		m_licenseUrl.SetURL(url);
	}

	return TRUE;
}

CString COfferPage::GetHeadText(int nIDS_OFFER_PROGRAM_NAME)
{
	CString staticOfferPageHead;
	staticOfferPageHead.LoadString(IDS_OFFER_PAGE_HEAD);

	CString offerProgramName;
	offerProgramName.LoadString(nIDS_OFFER_PROGRAM_NAME);

	return staticOfferPageHead + offerProgramName;
}

CString COfferPage::GetTitleText(int nIDS_OFFER_PROGRAM_NAME)
{
	CString staticTitle;
	staticTitle.LoadString(IDS_OFFER_PAGE_TITLE);

	CString offerProgramName;
	offerProgramName.LoadString(nIDS_OFFER_PROGRAM_NAME);

	return staticTitle + offerProgramName;
}

void COfferPage::OnBnClickedOfferPageButtonAccept()
{
	theApp.OnCloseOfferPage(false, m_offerProgram.installStatus);
}

void COfferPage::OnBnClickedOfferPageButtonCancel()
{
	theApp.OnCloseOfferPage(true, m_offerProgram.installStatus);
}

void COfferPage::PostNcDestroy()
{
	CBaseDialog::PostNcDestroy();
	delete this;
}
