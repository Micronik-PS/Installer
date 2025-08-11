#include "pch.h"
#include "Installer.h"
#include "afxdialogex.h"
#include "OfferPage.h"


IMPLEMENT_DYNAMIC(COfferPage, CBaseDialog)

COfferPage::COfferPage(CWnd* pParent /*=nullptr*/)
	: CBaseDialog(IDD_DIALOG_OFFER_PAGE, pParent)
{

}

COfferPage::~COfferPage()
{
}

void COfferPage::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OFFER_PAGE_PICTURE, m_offerLogo);
}


BEGIN_MESSAGE_MAP(COfferPage, CBaseDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


void COfferPage::OnClose()
{
	CBaseDialog::OnClose();
	delete this;
}