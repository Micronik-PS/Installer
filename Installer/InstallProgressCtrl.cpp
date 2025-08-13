#include "pch.h"
#include "Installer.h"
#include "InstallProgressCtrl.h"
#include "ProgressBarUpdateData.h"
#include "ProgressPage.h"

IMPLEMENT_DYNAMIC(CInstallProgressCtrl, CProgressCtrl)

CInstallProgressCtrl::CInstallProgressCtrl():
	m_stopped {true},
	m_downloadSpeed {500},
	m_installSpeed {300},
	m_lowerRange{0},
	m_upperRange{100}
{

}

CInstallProgressCtrl::~CInstallProgressCtrl()
{
}

void CInstallProgressCtrl::Setup()
{
	SetRange(m_lowerRange, m_upperRange);
	SetPos(m_lowerRange);
}

UINT CInstallProgressCtrl::StartProgressBarThread(LPVOID pParam)
{
	ProgressBarUpdateData*const updateData = static_cast<ProgressBarUpdateData*>(pParam);
	CInstallProgressCtrl*const progressBar = updateData->progressBar;
	OfferProgram*const offerProgram = updateData->offerProgram;
	CProgressPage* const progressPage = static_cast<CProgressPage*>(progressBar->GetParent());

	progressBar->m_stopped = false;

	progressPage->UpdateStatus(offerProgram->nIDS_OFFER_PROGRAM_NAME, offerProgram->installStatus);
	
	while(!progressBar->m_stopped && progressBar->GetPos() < updateData->destinationValue)
	{
		progressBar->SetPos(progressBar->GetPos() + 1);
		Sleep(updateData->destinationSpeed);
	}
	progressBar->SetPos(updateData->destinationValue);

	int progressBarLowerRange;
	int progressBarUpperRange;
	progressBar->GetRange(progressBarLowerRange, progressBarUpperRange);
	if (progressBar->GetPos() == progressBarUpperRange)
	{
		progressPage->UpdateStatus(true);
	}

	progressBar->StopProgressBar();
	return 0;
}

void CInstallProgressCtrl::StopProgressBar()
{
	m_stopped = true;
}

UINT CInstallProgressCtrl::GetProgressBarDestinationValueForOneProgram() const
{
	int lowerProgressBarRangeValue;
	int upperProgressBarRangeValue;
	this->GetRange(lowerProgressBarRangeValue, upperProgressBarRangeValue);

	const UINT countOfferProgramMarkedForInstall = theApp.GetCountOfferProgramMarkedForInstall();
	return upperProgressBarRangeValue / countOfferProgramMarkedForInstall;
}


BEGIN_MESSAGE_MAP(CInstallProgressCtrl, CProgressCtrl)
END_MESSAGE_MAP()