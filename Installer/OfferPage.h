#pragma once
#include "afxdialogex.h"
#include "PictureCtrl.h"
#include "BaseDialog.h"


class COfferPage : public CBaseDialog
{
	DECLARE_DYNAMIC(COfferPage)

public:
	COfferPage(CWnd* pParent = nullptr);
	virtual ~COfferPage();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OFFER_PAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClose();
private:
	CPictureCtrl m_offerLogo;

};
