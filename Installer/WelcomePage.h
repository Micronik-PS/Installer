#pragma once
#include "afxdialogex.h"
#include "BaseDialog.h"

class CWelcomePage : public CBaseDialog
{
	DECLARE_DYNAMIC(CWelcomePage)

public:
	CWelcomePage(CWnd* pParent = nullptr);
	virtual ~CWelcomePage();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WELCOME_PAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedWelcomePageButtonNext();
	afx_msg void OnBnClickedWelcomePageButtonCancel();
	virtual BOOL OnInitDialog();

private:
	CStatic m_logoZip;
	CStatic m_logoXnView;

	virtual void PostNcDestroy();
};
