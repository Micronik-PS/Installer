#include "pch.h"
#include "framework.h"
#include "Installer.h"

#include "WelcomePage.h"
#include "OfferPage.h"
#include "ProgressPage.h"
#include "ProgressBarUpdateData.h"
#include "OfferProgram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CInstallerApp, CWinApp)
	
END_MESSAGE_MAP()

CInstallerApp::CInstallerApp()
    : pastPage{ nullptr }
{ 
    const OfferProgram SevenZip
    (
        IDS_OFFER_PROGRAM_NAME_ZIP,
        IDS_PATH_LOGO_ZIP,
        IDS_LICENSE_URL_ZIP,
        IDS_DESCRIPTION_ZIP,
        IDS_PATH_REGISTER_KEY_ZIP,
        IDS_REGISTER_VALUE_ZIP,
        IDS_INSTALLER_URL_ZIP,
        IDS_EXE_INSTALLER_PARAMS_ZIP,
        true
    );
    const OfferProgram XnView
    (
        IDS_OFFER_PROGRAM_NAME_XNVIEW,
        IDS_PATH_LOGO_XNVIEW,
        IDS_LICENSE_URL_XNVIEW,
        IDS_DESCRIPTION_XNVIEW,
        IDS_PATH_REGISTER_KEY_XNVIEW,
        IDS_REGISTER_VALUE_XNVIEW,
        IDS_INSTALLER_URL_XNVIEW,
        IDS_EXE_INSTALLER_PARAMS_XNVIEW,
        true
    );

    m_offerPrograms.Add(SevenZip);
    m_offerPrograms.Add(XnView);
}

CInstallerApp theApp;

BOOL CInstallerApp::InitInstance()
{
	CWinApp::InitInstance();

    for (int indexOfferProgram = 0; indexOfferProgram < m_offerPrograms.GetSize(); ++indexOfferProgram)
    {
        OfferProgram& offerProgram = m_offerPrograms[indexOfferProgram];
        offerProgram.installStatus = IsProgramInstalled(offerProgram.nIDS_PATH_REGISTER_KEY, offerProgram.nIDS_REGISTER_VALUE) ?
            ProgramInstallStatus::BeforeInstalled : ProgramInstallStatus::None;
    }

    OpenWelcomePage();

	return TRUE;
}

bool CInstallerApp::TryOpenOfferPage()
{
    COfferPage* offerPage = nullptr;

    bool IsCreatedOfferPage = false;

    for (int indexOfferProgram = 0; indexOfferProgram < m_offerPrograms.GetSize(); ++indexOfferProgram)
    {
        OfferProgram& offerProgram = m_offerPrograms[indexOfferProgram];

        if (offerProgram.installStatus == ProgramInstallStatus::None)
        {
            offerPage = new COfferPage(offerProgram); // очищается в COfferPage::PostNcDestroy()
            IsCreatedOfferPage = true;
            break;
        }
    }

    if (IsCreatedOfferPage)
    {
        m_pMainWnd = offerPage;
        offerPage->Create(IDD_DIALOG_OFFER_PAGE);
        offerPage->ShowWindow(SW_SHOW);
    }

    return IsCreatedOfferPage;
}

bool CInstallerApp::TryOpenProgressPage()
{
    bool someoneIsMarkedForInstall = false;

    for (int indexOfferProgram = 0; indexOfferProgram < m_offerPrograms.GetSize(); ++indexOfferProgram)
    {
        OfferProgram& offerProgram = m_offerPrograms[indexOfferProgram];
        if(offerProgram.installStatus == ProgramInstallStatus::MarkedForInstall)
        {
            someoneIsMarkedForInstall = true;
        }
    }

    if (someoneIsMarkedForInstall)
    {
        CProgressPage* offerPage = new CProgressPage;
        m_pMainWnd = offerPage;
        offerPage->Create(IDD_DIALOG_PROGRESS_PAGE);
        offerPage->ShowWindow(SW_SHOW);
    }

    return someoneIsMarkedForInstall;
}

CString CInstallerApp::GetExeInstallerPath() const
{
    TCHAR tempPath[MAX_PATH] = { 0 };
    if (GetTempPath(MAX_PATH, tempPath) == 0)
    {
        return CString();
    }
    CString exeInstallerName;
    exeInstallerName.LoadString(IDS_EXE_INSTALLER_NAME);

    return tempPath + exeInstallerName;
}

UINT CInstallerApp::GetCountOfferProgramMarkedForInstall()
{
    UINT countOfferProgramMarkedForInstall = 0;
    for (int indexOfferProgram = 0; indexOfferProgram < theApp.m_offerPrograms.GetSize(); ++indexOfferProgram)
    {
        OfferProgram& offerProgram = theApp.m_offerPrograms[indexOfferProgram];
        if (offerProgram.installStatus == ProgramInstallStatus::MarkedForInstall)
        {
            ++countOfferProgramMarkedForInstall;
        }
    }

    return countOfferProgramMarkedForInstall;
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
            if (!TryOpenProgressPage())
            {
                // Finish Page
            }
        }
    }
}

void CInstallerApp::OnCloseOfferPage(bool canceled, ProgramInstallStatus& offerProgramInstallStatus)
{
    offerProgramInstallStatus = canceled ?
        ProgramInstallStatus::Canceled : 
        ProgramInstallStatus::MarkedForInstall;

    pastPage = AfxGetMainWnd();
    if (!TryOpenOfferPage())
    {
        if (!TryOpenProgressPage())
        {
            // Finish Page
        }
    }
}

void CInstallerApp::OnOpenPage()
{
    pastPage->DestroyWindow();
    pastPage = nullptr;
}

bool CInstallerApp::IsProgramInstalled(const int nIDS_PATH_REGISTER_KEY, const int nIDS_REGISTER_VALUE)
{
    CString subKeyPath;
    subKeyPath.LoadString(nIDS_PATH_REGISTER_KEY);

    CString valueName;
    valueName.LoadString(nIDS_REGISTER_VALUE);

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

bool CInstallerApp::TryDownloadExeInstaller(OfferProgram& offerProgram, ProgressBarUpdateData& progressBarUpdateDownloadData)
{
    CInstallProgressCtrl*const progressBar = progressBarUpdateDownloadData.progressBar;

    CWinThread* progressDownloadBarThread = AfxBeginThread
    (
        CInstallProgressCtrl::StartProgressBarThread,
        &progressBarUpdateDownloadData
    );

    CString exeInstallerUrl;
    exeInstallerUrl.LoadString(offerProgram.nIDS_INSTALLER_URL);

    const HRESULT downloadResult = URLDownloadToFile
    (
        NULL,
        exeInstallerUrl,
        theApp.GetExeInstallerPath(),
        NULL,
        NULL
    );

    progressBar->StopProgressBar();
    WaitForSingleObject(progressDownloadBarThread->m_hThread, INFINITE);
    return !(FAILED(downloadResult));
}

bool CInstallerApp::TryInstallOfferProgram(OfferProgram& offerProgram, ProgressBarUpdateData& progressBarUpdateInstallData)
{
    CInstallProgressCtrl* const progressBar = progressBarUpdateInstallData.progressBar;

    CWinThread* progressInstallBarThread = AfxBeginThread
    (
        CInstallProgressCtrl::StartProgressBarThread,
        &progressBarUpdateInstallData
    );

    CString exeInstallerVerb;
    exeInstallerVerb.LoadString
    (
        offerProgram.doesInstallerRequiresAdmin ? IDS_EXECUTE_ADMIN_FLAG : IDS_EXECUTE_OPEN_FLAG
    );

    CString exeInstallerParams;
    exeInstallerParams.LoadString(offerProgram.nIDS_EXE_INSTALLER_PARAMS);

    CString exeInstallerPath = theApp.GetExeInstallerPath();

    SHELLEXECUTEINFOW sei = { 0 };
    sei.cbSize = sizeof(sei);
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    sei.hwnd = nullptr;
    sei.lpVerb = exeInstallerVerb;
    sei.lpFile = exeInstallerPath;
    sei.lpParameters = exeInstallerParams;
    sei.nShow = SW_HIDE;

    bool hasError = false;
    if (!ShellExecuteExW(&sei))
    {
        hasError = true;
    }

    if (sei.hProcess)
    {
        WaitForSingleObject(sei.hProcess, INFINITE);
        CloseHandle(sei.hProcess);
    }

    progressBar->StopProgressBar();
    WaitForSingleObject(progressInstallBarThread->m_hThread, INFINITE);

    return !hasError;
}

UINT CInstallerApp::StartDeploy(LPVOID pParam)
{
    CInstallProgressCtrl*const progressBar = static_cast<CInstallProgressCtrl*>(pParam);
    
    const UINT progressBarDestinationValueForOneProgram = progressBar->GetProgressBarDestinationValueForOneProgram();

    for (int indexOfferProgram = 0; indexOfferProgram < theApp.m_offerPrograms.GetSize(); ++indexOfferProgram)
    {
        OfferProgram& offerProgram = theApp.m_offerPrograms[indexOfferProgram];
        if (offerProgram.installStatus != ProgramInstallStatus::MarkedForInstall) { continue; }

        offerProgram.installStatus = ProgramInstallStatus::StartedDownload;
        ProgressBarUpdateData progressBarUpdateDownloadData
        (
            progressBar->GetPos() + progressBarDestinationValueForOneProgram / 2,
            progressBar->m_downloadSpeed,
            progressBar,
            &offerProgram
        );
        if(!theApp.TryDownloadExeInstaller(offerProgram, progressBarUpdateDownloadData))
        {
            offerProgram.installStatus = ProgramInstallStatus::Error;
            continue;
        }

        offerProgram.installStatus = ProgramInstallStatus::StartedInstall;
        ProgressBarUpdateData progressBarUpdateInstallData
        (
            progressBar->GetPos() + progressBarDestinationValueForOneProgram / 2,
            progressBar->m_installSpeed,
            progressBar,
            &offerProgram
        );
        if(!theApp.TryInstallOfferProgram(offerProgram,progressBarUpdateInstallData))
        {
            offerProgram.installStatus = ProgramInstallStatus::Error;
            continue;
        }

        offerProgram.installStatus = theApp.IsProgramInstalled
        (
            offerProgram.nIDS_PATH_REGISTER_KEY, 
            offerProgram.nIDS_REGISTER_VALUE
        ) ? ProgramInstallStatus::Installed : ProgramInstallStatus::Error;
    }

    // Finish Page
    return 0;
}

void CInstallerApp::OpenWelcomePage()
{
    CWelcomePage* welcomePage = new CWelcomePage; // очищается в CWelcomePage::PostNcDestroy()
    welcomePage->Create(IDD_DIALOG_WELCOME_PAGE);
    welcomePage->ShowWindow(SW_SHOW);
    m_pMainWnd = welcomePage;
}