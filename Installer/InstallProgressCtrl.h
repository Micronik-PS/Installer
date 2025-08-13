#pragma once
#include <afxwin.h>

class CInstallProgressCtrl : public CProgressCtrl
{
	DECLARE_DYNAMIC(CInstallProgressCtrl)

public:
	CInstallProgressCtrl();
	virtual ~CInstallProgressCtrl();

protected:
	DECLARE_MESSAGE_MAP()

public:
	const UINT m_downloadSpeed;
	const UINT m_installSpeed;

	void Setup();
	static UINT StartProgressBarThread(LPVOID pParam);
	void StopProgressBar();
	UINT GetProgressBarDestinationValueForOneProgram() const;

private:
	bool m_stopped;
	const UINT m_lowerRange;
	const UINT m_upperRange;
};


