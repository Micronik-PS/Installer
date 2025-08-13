#pragma once
#include "afxdialogex.h"
#include "BaseDialog.h"

class CFinishPage : public CBaseDialog
{
	DECLARE_DYNAMIC(CFinishPage)

public:
	CFinishPage(CWnd* pParent = nullptr);
	virtual ~CFinishPage();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FINISH_PAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedFinishPageButtonExit();

private:
	CStatic m_logoZip;
	CStatic m_logoXnView;
};
