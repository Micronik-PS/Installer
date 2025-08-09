#pragma once
#include "afxdialogex.h"


// Диалоговое окно CWelcomePage

class CWelcomePage : public CDialogEx
{
	DECLARE_DYNAMIC(CWelcomePage)

public:
	CWelcomePage(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CWelcomePage();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WELCOME_PAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
