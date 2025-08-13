#pragma once
#include "ProgramInstallStatus.h"

struct OfferProgram
{
	int nIDS_OFFER_PROGRAM_NAME;
	int nIDS_PATH_LOGO;
	int nIDS_LICENSE_URL;
	int nIDS_DESCRIPTION;
	int nIDS_PATH_REGISTER_KEY;
	int nIDS_REGISTER_VALUE;
	int nIDS_INSTALLER_URL;
	int nIDS_EXE_INSTALLER_PARAMS;
	bool doesInstallerRequiresAdmin;
	ProgramInstallStatus installStatus;

	OfferProgram();

	OfferProgram
	(
		const int nIDS_OFFER_PROGRAM_NAME,
		const int nIDS_PATH_LOGO,
		const int nIDS_LICENSE_URL,
		const int nIDS_DESCRIPTION,
		const int nIDS_PATH_REGISTER_KEY,
		const int nIDS_REGISTER_VALUE,
		const int nIDS_INSTALLER_URL,
		const int nIDS_EXE_INSTALLER_PARAMS,
		const bool doesInstallerRequiresAdmin = false,
		const ProgramInstallStatus installStatus = ProgramInstallStatus::Error
	);
};