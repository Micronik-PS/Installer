#pragma once

class CInstallProgressCtrl;
struct OfferProgram;

struct ProgressBarUpdateData
{
	const UINT destinationValue;
	const UINT destinationSpeed; // 1000 = 1 секунда
	CInstallProgressCtrl*const progressBar;
	OfferProgram*const offerProgram;

	ProgressBarUpdateData
	(
		const UINT destinationValue, 
		const UINT destinationSpeed, 
		CInstallProgressCtrl*const progressBar,
		OfferProgram*const offerProgram
	);
};