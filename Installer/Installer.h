
// Installer.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CInstallerApp:
// Сведения о реализации этого класса: Installer.cpp
//

class CInstallerApp : public CWinApp
{
public:
	CInstallerApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CInstallerApp theApp;
