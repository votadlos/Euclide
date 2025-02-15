#if !defined(AFX_FINDPRIMITIVEDLG_H__7680F981_B723_11D5_A253_D4334B5B93A3__INCLUDED_)
#define AFX_FINDPRIMITIVEDLG_H__7680F981_B723_11D5_A253_D4334B5B93A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindPrimitiveDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FindPrimitiveDlg dialog

UINT process_calc_prime(void * pParam);//поиск примитивных

class FindPrimitiveDlg : public CDialog
{
private:
	CWinThread *thread;
public:
	FindPrimitiveDlg(CWnd* pParent = NULL);   // standard constructor
	long Mod;
	BOOL Endian;
	CProgressCtrl *fpp_progress;
// Dialog Data
	//{{AFX_DATA(FindPrimitiveDlg)
	enum { IDD = IDD_PRIMITIVE_DIALOG };
	CEdit	m_Deg;
	CEdit	m_Output;
	BOOL	m_Irred;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FindPrimitiveDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FindPrimitiveDlg)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDPRIMITIVEDLG_H__7680F981_B723_11D5_A253_D4334B5B93A3__INCLUDED_)
