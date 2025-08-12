#pragma once
#include "afxdialogex.h"
#include "PictureCtrl.h"
#include "BaseDialog.h"


class COfferPage : public CBaseDialog
{
	DECLARE_DYNAMIC(COfferPage)

public:
	
	COfferPage
	(
		ProgramInstallStatus& offerApp,
		const int nIDS_OFFER_PAGE_HEAD, 
		const int nIDS_OFFER_PAGE_TITLE, 
		const int nIDS_PATH_LOGO, 
		const int nIDS_OFFER_PAGE_DESCRIPTION, 
		const int nIDS_OFFER_PAGE_LICENSE_URL,
		CWnd* pParent = nullptr
	);

	virtual ~COfferPage();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OFFER_PAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();

private:
	ProgramInstallStatus& m_offerApp;
	CPictureCtrl m_offerLogo;
	CMFCLinkCtrl m_licenseUrl;

	const int m_nIDS_OFFER_PAGE_HEAD;
	const int m_nIDS_OFFER_PAGE_TITLE;
	const int m_nIDS_PATH_LOGO;
	const int m_nIDS_OFFER_PAGE_DESCRIPTION;
	const int m_nIDS_OFFER_PAGE_LICENSE_URL;
public:
	afx_msg void OnBnClickedOfferPageButtonAccept();
	afx_msg void OnBnClickedOfferPageButtonCancel();
	virtual void PostNcDestroy();
};
