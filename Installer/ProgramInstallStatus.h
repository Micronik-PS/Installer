#pragma once

enum class ProgramInstallStatus
{
	None,
	Installed,
	Canceled,
	BeforeInstalled,
	Error,
	MarkedForInstall
};