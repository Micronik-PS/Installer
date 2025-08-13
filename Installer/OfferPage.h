#pragma once
#include "afxdialogex.h"
#include "PictureCtrl.h"
#include "BaseDialog.h"


class COfferPage : public CBaseDialog
{
	DECLARE_DYNAMIC(COfferPage)

public:
	
	COfferPage(OfferProgram& offerProgram, CWnd* pParent = nullptr);

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
	OfferProgram& m_offerProgram;
	CPictureCtrl m_offerLogo;
	CMFCLinkCtrl m_licenseUrl;

	CString GetHeadText(int nIDS_OFFER_PROGRAM_NAME);
	CString GetTitleText(int nIDS_OFFER_PROGRAM_NAME);

public:
	afx_msg void OnBnClickedOfferPageButtonAccept();
	afx_msg void OnBnClickedOfferPageButtonCancel();
	virtual void PostNcDestroy();
};
