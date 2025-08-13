#include "pch.h"
#include "OfferProgram.h"

OfferProgram::OfferProgram
(
	const int nIDS_OFFER_PROGRAM_NAME, 
	const int nIDB_LOGO,
	const int nIDS_LICENSE_URL, 
	const int nIDS_DESCRIPTION, 
	const int nIDS_PATH_REGISTER_KEY, 
	const int nIDS_REGISTER_VALUE, 
	const int nIDS_INSTALLER_URL,
	const int nIDS_EXE_INSTALLER_PARAMS,
	const bool doesInstallerRequiresAdmin, /* = false*/
	const ProgramInstallStatus installStatus /* = ProgramInstallStatus::Error*/
)
	: nIDS_OFFER_PROGRAM_NAME { nIDS_OFFER_PROGRAM_NAME }
	, nIDB_LOGO{ nIDB_LOGO }
	, nIDS_LICENSE_URL { nIDS_LICENSE_URL }
	, nIDS_DESCRIPTION { nIDS_DESCRIPTION }
	, nIDS_PATH_REGISTER_KEY { nIDS_PATH_REGISTER_KEY }
	, nIDS_REGISTER_VALUE { nIDS_REGISTER_VALUE }
	, nIDS_INSTALLER_URL { nIDS_INSTALLER_URL }
	, nIDS_EXE_INSTALLER_PARAMS { nIDS_EXE_INSTALLER_PARAMS }
	, doesInstallerRequiresAdmin { doesInstallerRequiresAdmin }
	, installStatus{ installStatus }
{
}

OfferProgram::OfferProgram() 
	: nIDS_OFFER_PROGRAM_NAME{ 0 }
	, nIDB_LOGO{ 0 }
	, nIDS_LICENSE_URL{ 0 }
	, nIDS_DESCRIPTION{ 0 }
	, nIDS_PATH_REGISTER_KEY{ 0 }
	, nIDS_REGISTER_VALUE{ 0 }
	, nIDS_INSTALLER_URL{ 0 }
	, nIDS_EXE_INSTALLER_PARAMS { 0 }
{
}