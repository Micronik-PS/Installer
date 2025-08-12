#include "pch.h"
#include "Installer.h"
#include "afxdialogex.h"
#include "OfferPage.h"


IMPLEMENT_DYNAMIC(COfferPage, CBaseDialog)


COfferPage::COfferPage
(
	ProgramInstallStatus& offerApp,
	const int nIDS_OFFER_PAGE_HEAD,
	const int nIDS_OFFER_PAGE_TITLE, 
	const int nIDS_PATH_LOGO, 
	const int nIDS_OFFER_PAGE_DESCRIPTION, 
	const int nIDS_OFFER_PAGE_LICENSE_URL, 
	CWnd* pParent
)	: CBaseDialog(IDD_DIALOG_OFFER_PAGE, pParent)
	, m_offerApp{ offerApp }
	, m_nIDS_OFFER_PAGE_HEAD { nIDS_OFFER_PAGE_HEAD }
	, m_nIDS_OFFER_PAGE_TITLE { nIDS_OFFER_PAGE_TITLE }
	, m_nIDS_PATH_LOGO { nIDS_PATH_LOGO }
	, m_nIDS_OFFER_PAGE_DESCRIPTION { nIDS_OFFER_PAGE_DESCRIPTION }
	, m_nIDS_OFFER_PAGE_LICENSE_URL { nIDS_OFFER_PAGE_LICENSE_URL }
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

	SetDialogHead(IDI_APP, m_nIDS_OFFER_PAGE_HEAD);

	SetTextForControl(IDC_OFFER_PAGE_STATIC_TEXT_TITLE, m_nIDS_OFFER_PAGE_TITLE, &m_titleFont);
	SetTextForControl(IDC_OFFER_PAGE_STATIC_TEXT_DESCRIPTION, m_nIDS_OFFER_PAGE_DESCRIPTION, &m_bodyFont);
	SetTextForControl(IDC_OFFER_PAGE_BUTTON_ACCEPT, IDS_OFFER_PAGE_BUTTON_ACCEPT, &m_bodyFont);
	SetTextForControl(IDC_OFFER_PAGE_BUTTON_CANCEL, IDS_OFFER_PAGE_BUTTON_CANCEL, &m_bodyFont);
	SetTextForControl(IDC_OFFER_PAGE_MFCLINK_LICENSE, IDS_OFFER_PAGE_LICENSE, &m_bodyFont);

	SetPictureForControl(m_nIDS_PATH_LOGO, m_offerLogo);

	CString url;
	if (url.LoadString(m_nIDS_OFFER_PAGE_LICENSE_URL) != NULL)
	{
		m_licenseUrl.SetURL(url);
	}

	return TRUE;
}

void COfferPage::OnBnClickedOfferPageButtonAccept()
{
	theApp.OnCloseOfferPage(false, m_offerApp);
}

void COfferPage::OnBnClickedOfferPageButtonCancel()
{
	theApp.OnCloseOfferPage(true, m_offerApp);
}

void COfferPage::PostNcDestroy()
{
	CBaseDialog::PostNcDestroy();
	delete this;
}
