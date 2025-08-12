#include "pch.h"
#include "framework.h"
#include "Installer.h"

#include "WelcomePage.h"
#include "OfferPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CInstallerApp, CWinApp)
	
END_MESSAGE_MAP()

CInstallerApp::CInstallerApp():
     m_sevenZip {ProgramInstallStatus::Error}
    ,m_xnView {ProgramInstallStatus::Error}
    ,pastPage {nullptr}
{
}

CInstallerApp theApp;

BOOL CInstallerApp::InitInstance()
{
	CWinApp::InitInstance();

    m_sevenZip = IsProgramInstalled(IDS_PATH_REGISTER_KEY_ZIP, IDS_REGISTER_VALUE_ZIP) ? 
        ProgramInstallStatus::BeforeInstalled : ProgramInstallStatus::None;
    m_xnView = IsProgramInstalled(IDS_PATH_REGISTER_KEY_XNVIEW, IDS_REGISTER_VALUE_XNVIEW) ? 
        ProgramInstallStatus::BeforeInstalled : ProgramInstallStatus::None;

    OpenWelcomePage();

	return TRUE;
}

bool CInstallerApp::TryOpenOfferPage()
{
    COfferPage* pDlg = nullptr;

    if (m_sevenZip == ProgramInstallStatus::None)
    {
        pDlg = new COfferPage // очищается в COfferPage::PostNcDestroy()
        (
            m_sevenZip,
            IDS_OFFER_PAGE_HEAD_ZIP,
            IDS_OFFER_PAGE_TITLE_ZIP,
            IDS_PATH_LOGO_ZIP,
            IDS_OFFER_PAGE_DESCRIPTION_ZIP,
            IDS_OFFER_PAGE_LICENSE_URL_ZIP
        );
    }
    else if (m_xnView == ProgramInstallStatus::None)
    {
        pDlg = new COfferPage // очищается в COfferPage::PostNcDestroy()
        (
            m_xnView,
            IDS_OFFER_PAGE_HEAD_XNVIEW,
            IDS_OFFER_PAGE_TITLE_XNVIEW,
            IDS_PATH_LOGO_XNVIEW,
            IDS_OFFER_PAGE_DESCRIPTION_XNVIEW,
            IDS_OFFER_PAGE_LICENSE_URL_XNVIEW
        );
    }
    else
    {
        return false;
    }

    m_pMainWnd = pDlg;
    pDlg->Create(IDD_DIALOG_OFFER_PAGE);
    pDlg->ShowWindow(SW_SHOW);

    return true;
}

void CInstallerApp::OnCloseWelcomePage(bool canceled)
{
    if (canceled)
    {
        AfxGetMainWnd()->DestroyWindow();
    }
    else
    {
        pastPage = AfxGetMainWnd();
        if (!TryOpenOfferPage())
        {
            //Progress Page
        }
    }
}

void CInstallerApp::OnCloseOfferPage(bool canceled, ProgramInstallStatus& offerApp)
{
    pastPage = AfxGetMainWnd();
    offerApp = canceled ? ProgramInstallStatus::Canceled : ProgramInstallStatus::MarkedForInstall;
    if (!TryOpenOfferPage())
    {
        //Progress Page
    }
}

void CInstallerApp::OnOpenPage()
{
    pastPage->DestroyWindow();
    pastPage = nullptr;
}

bool CInstallerApp::IsProgramInstalled(const int nIDS_PATH_REGISTER_KEY, const int nIDS_REGISTER_VALUE_ZIP)
{
    CString subKeyPath;
    subKeyPath.LoadString(nIDS_PATH_REGISTER_KEY);

    CString valueName;
    valueName.LoadString(nIDS_REGISTER_VALUE_ZIP);

    const ULONG accessFlags[] = { KEY_READ | KEY_WOW64_64KEY, KEY_READ | KEY_WOW64_32KEY };
    const HKEY rootKeys[] = { HKEY_LOCAL_MACHINE, HKEY_CURRENT_USER };

    for (HKEY rootKey : rootKeys)
    {
        for (ULONG flags : accessFlags)
        {
            CRegKey regKey;
            LONG result = regKey.Open(rootKey, subKeyPath, flags);
            if (result == ERROR_SUCCESS)
            {
                TCHAR buffer[256];
                ULONG size = 256;
                result = regKey.QueryStringValue(valueName, buffer, &size);
                if (result == ERROR_SUCCESS)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void CInstallerApp::OpenWelcomePage()
{
    CWelcomePage* welcomePage = new CWelcomePage; // очищается в CWelcomePage::PostNcDestroy()
    welcomePage->Create(IDD_DIALOG_WELCOME_PAGE);
    welcomePage->ShowWindow(SW_SHOW);
    m_pMainWnd = welcomePage;
}