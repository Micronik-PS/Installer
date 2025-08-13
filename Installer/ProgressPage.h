#pragma once
#include "afxdialogex.h"
#include "BaseDialog.h"
#include "InstallProgressCtrl.h"
#include "ProgramInstallStatus.h"


class CProgressPage : public CBaseDialog
{
	DECLARE_DYNAMIC(CProgressPage)

public:
	CProgressPage(CWnd* pParent = nullptr);
	virtual ~CProgressPage();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROGRESS_PAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
	void UpdateStatus(const int nIDS_OFFER_PROGRAM_NAME, const ProgramInstallStatus& installStatus);
	void UpdateStatus(bool doesDeployCompleted);

private:
	CInstallProgressCtrl m_progressBar;
};
