#pragma once
#include "afxdialogex.h"

class CPictureCtrl;

class CBaseDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CBaseDialog)

public:
	CBaseDialog(UINT nIDTemplate, CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CBaseDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()

protected:
	CFont m_titleFont;
	CFont m_bodyFont;

	void InitTitleFont();
	void InitBodyFont();

	void SetPictureForControl(const int nIDB, CStatic& placement, const int pictureWidth = 150, const int pictureHeight = 150);

	void SetTextForControl(const int nIDC_staticText, const int nIDS_text, CFont* const font);
	void SetTextForControl(const int nIDC_staticText, const CString& text, CFont* const font);

	void SetDialogHead(const int nIDI_applicationIcon, const int nIDS_headText);
	void SetDialogHead(const int nIDI_applicationIcon, const CString& headText);
};
