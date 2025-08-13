#include "pch.h"
#include "Installer.h"
#include "afxdialogex.h"
#include "ProgressPage.h"
#include "BaseDialog.h"
#include "ProgramInstallStatus.h"

IMPLEMENT_DYNAMIC(CProgressPage, CBaseDialog)

CProgressPage::CProgressPage(CWnd* pParent /*=nullptr*/)
	: CBaseDialog(IDD_DIALOG_PROGRESS_PAGE, pParent)
{

}

CProgressPage::~CProgressPage()
{
}

void CProgressPage::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_PAGE_BAR, m_progressBar);
}


BEGIN_MESSAGE_MAP(CProgressPage, CBaseDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

void CProgressPage::OnClose()
{
	
}

void CProgressPage::PostNcDestroy()
{
	CBaseDialog::PostNcDestroy();
	delete this;
}

BOOL CProgressPage::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	theApp.OnOpenPage();

	SetDialogHead(IDI_APP, IDS_PROGRESS_PAGE_HEAD);

	SetTextForControl(IDC_PROGRESS_PAGE_STATIC_TEXT_TITLE, IDS_PROGRESS_PAGE_TITLE, &m_titleFont);
	SetTextForControl(IDC_PROGRESS_PAGE_STATIC_TEXT_BODY, IDS_PROGRESS_PAGE_BODY, &m_bodyFont);
	UpdateStatus(false);

	m_progressBar.Setup();

	AfxBeginThread(CInstallerApp::StartDeploy,&m_progressBar);

	return TRUE;
}

void CProgressPage::UpdateStatus(const int nIDS_OFFER_PROGRAM_NAME, const ProgramInstallStatus& installStatus)
{
	int nIDS_PROGRESS_PAGE_STATUS;

	switch (installStatus)
	{
		case ProgramInstallStatus::StartedDownload : 
		{
			nIDS_PROGRESS_PAGE_STATUS = IDS_PROGRESS_PAGE_STATUS_DOWNLOAD;
			break;
		}
		case ProgramInstallStatus::StartedInstall :
		{
			nIDS_PROGRESS_PAGE_STATUS = IDS_PROGRESS_PAGE_STATUS_INSTALL;
			break;
		}
		default:
		{
			return;
		}
	}

	CString staticStatus;
	staticStatus.LoadString(nIDS_PROGRESS_PAGE_STATUS);

	CString programName;
	programName.LoadString(nIDS_OFFER_PROGRAM_NAME);

	SetTextForControl(IDC_PROGRESS_PAGE_STATIC_TEXT_STATUS, staticStatus + programName, &m_bodyFont);
}

void CProgressPage::UpdateStatus(bool doesDeployCompleted)
{
	SetTextForControl
	(
		IDC_PROGRESS_PAGE_STATIC_TEXT_STATUS, 
		doesDeployCompleted ? IDS_PROGRESS_PAGE_STATUS_END : IDS_PROGRESS_PAGE_STATUS_START, 
		&m_bodyFont
	);
}