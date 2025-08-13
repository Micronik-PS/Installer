#include "pch.h"
#include "ProgressBarUpdateData.h"

ProgressBarUpdateData::ProgressBarUpdateData
(
	const UINT destinationValue, 
	const UINT destinationSpeed, 
	CInstallProgressCtrl* const progressBar,
	OfferProgram* const offerProgram
)
	: destinationValue { destinationValue }
	, destinationSpeed { destinationSpeed }
	, progressBar { progressBar }
	, offerProgram { offerProgram }
{
}
