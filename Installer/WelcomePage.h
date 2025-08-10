#pragma once
#include "afxdialogex.h"
#include "PictureCtrl.h"


class CWelcomePage : public CDialogEx
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
	CFont m_titleFont;
	CFont m_bodyFont;

	CPictureCtrl m_logoZip;
	CPictureCtrl m_logoXnView;

	void InitTitleFont();
	void InitBodyFont();
	void SetLogo(const int nIDS_filePathToLogo, CPictureCtrl& placement);
	void SetText(const int nIDC_staticText, const int nIDS_text, CFont* const font);
};
