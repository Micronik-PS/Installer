#pragma once

enum class ProgramInstallStatus
{
	None,
	Canceled,
	BeforeInstalled,
	MarkedForInstall,
	StartedInstall,
	StartedDownload,
	Installed,
	Error
};