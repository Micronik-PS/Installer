#include "pch.h"
#include "Installer.h"
#include "afxdialogex.h"
#include "FinishPage.h"

IMPLEMENT_DYNAMIC(CFinishPage, CBaseDialog)

CFinishPage::CFinishPage(CWnd* pParent /*=nullptr*/)
	: CBaseDialog(IDD_DIALOG_FINISH_PAGE, pParent)
{

}

CFinishPage::~CFinishPage()
{
}

void CFinishPage::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FINISH_PAGE_PICTURE_CONTROL_ZIP, m_logoZip);
	DDX_Control(pDX, IDC_FINISH_PAGE_PICTURE_CONTROL_XNVIEW, m_logoXnView);
}

BEGIN_MESSAGE_MAP(CFinishPage, CBaseDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_FINISH_PAGE_BUTTON_EXIT, &CFinishPage::OnBnClickedFinishPageButtonExit)
END_MESSAGE_MAP()

BOOL CFinishPage::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	theApp.OnOpenPage();

	SetDialogHead(IDI_APP, IDS_FINISH_PAGE_HEAD);

	// Лого приложений
	SetPictureForControl(IDB_LOGO_ZIP, m_logoZip);
	SetPictureForControl(IDB_LOGO_XNVIEW, m_logoXnView);

	// Текст
	SetTextForControl(IDC_FINISH_PAGE_STATIC_TEXT_TITLE, IDS_FINISH_PAGE_TITLE, &m_titleFont);
	SetTextForControl(IDC_FINISH_PAGE_BUTTON_EXIT, IDS_FINISH_PAGE_BUTTON_EXIT, &m_bodyFont);

	OutputInstallResults(IDC_FINISH_PAGE_STATIC_TEXT_BODY);

	return TRUE;
}

void CFinishPage::OnClose()
{
	DestroyWindow();
}

void CFinishPage::PostNcDestroy()
{
	CBaseDialog::PostNcDestroy();
	delete this;
}

void CFinishPage::OnBnClickedFinishPageButtonExit()
{
	DestroyWindow();
}

void CFinishPage::OutputInstallResults(const int nIDC_staticText)
{
	CString emptyString(_T('\0'));
	SetTextForControl(nIDC_staticText, emptyString, &m_bodyFont);

	CArray<OfferProgram*> installedPrograms;
	CArray<OfferProgram*> beforeInstalledPrograms;
	CArray<OfferProgram*> canceledPrograms;
	CArray<OfferProgram*> errorInstalledPrograms;

	for (int indexOfferProgram = 0; indexOfferProgram < theApp.m_offerPrograms.GetSize(); ++indexOfferProgram)
	{
		OfferProgram& offerProgram = theApp.m_offerPrograms[indexOfferProgram];

		switch (offerProgram.installStatus)
		{
		case ProgramInstallStatus::Installed :
		{
			installedPrograms.Add(&offerProgram);
			break;
		}
		case ProgramInstallStatus::BeforeInstalled :
		{
			beforeInstalledPrograms.Add(&offerProgram);
			break;
		}
		case ProgramInstallStatus::Canceled :
		{
			canceledPrograms.Add(&offerProgram);
			break;
		}
		default:
		{
			errorInstalledPrograms.Add(&offerProgram);
			break;
		}
		}
	}

	OutputInstallResultsCategory(installedPrograms, nIDC_staticText, IDS_FINISH_PAGE_BODY_INSTALLED_PROGRAMS);
	OutputInstallResultsCategory(beforeInstalledPrograms, nIDC_staticText, IDS_FINISH_PAGE_BODY_BEFORE_INSTALLED_PROGRAMS);
	OutputInstallResultsCategory(canceledPrograms, nIDC_staticText, IDS_FINISH_PAGE_BODY_CANCELED_PROGRAMS);
	OutputInstallResultsCategory(errorInstalledPrograms, nIDC_staticText, IDS_FINISH_PAGE_BODY_ERROR_INSTALLED_PROGRAMS);
}

void CFinishPage::OutputInstallResultsCategory
(
	CArray<OfferProgram*>& installResultsCategory, 
	const int nIDC_staticText,
	const int nIDS_staticTextCategory
)
{
	if (installResultsCategory.GetSize() != NULL)
	{
		AddTextInControl(nIDC_staticText, nIDS_staticTextCategory);
		for (int indexInstalledProgram = 0; indexInstalledProgram < installResultsCategory.GetSize(); ++indexInstalledProgram)
		{
			OfferProgram* offerProgram = installResultsCategory.GetAt(indexInstalledProgram);

			CString offerProgramName;
			offerProgramName.LoadString(offerProgram->nIDS_OFFER_PROGRAM_NAME);

			CString punctuationMark(_T('\0'));
			if (indexInstalledProgram == installResultsCategory.GetSize() - 1)
			{
				punctuationMark = _T('.');
			}
			else if (indexInstalledProgram >= 0)
			{
				punctuationMark = _T(", ");
			}

			AddTextInControl(nIDC_staticText, offerProgramName + punctuationMark);
		}

		AddTextInControl(nIDC_staticText, _T("\r\n\r\n"));
	}
}