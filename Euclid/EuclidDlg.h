// EuclidDlg.h : header file
//

#if !defined(AFX_EUCLIDDLG_H__9B9A4207_8530_11D5_A253_80542EFCACA3__INCLUDED_)
#define AFX_EUCLIDDLG_H__9B9A4207_8530_11D5_A253_80542EFCACA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PROGRESS_RANGE 1000
//сложность деления многочленов через степени 
#define DIV_(A,B) (((A)-(B))*((B)+2))

#include "FindPrimitiveDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CEuclidDlg dialog

UINT process_find_irred(void * pParam);//поиск неприводимых
UINT process_check_irred(void * pParam);//проверка непривод
	
class CEuclidDlg : public CDialog
{
private:
	CWinThread *thread;
	int ch_edit1, ch_edit2, ch_module;//флаги отредактир
	void EnableButtons(BOOL);//управляет кнопками
	FindPrimitiveDlg *fpd;//окно для поиска примитивных, чтобы
		//оно не было модальным
public:
	static BOOL m_StopVal;
	CEuclidDlg(CWnd* pParent = NULL);	// standard constructor
	~CEuclidDlg();
	static void showProgress();//отобразить прогресс
// Dialog Data
	//{{AFX_DATA(CEuclidDlg)
	enum { IDD = IDD_EUCLID_DIALOG };
	CButton	m_Stop;
	CProgressCtrl	m_MainProgress; 
	static CStatic m_What; //static 
	static CProgressCtrl m_Progress; //static  
	CEdit	m_EditPolyMod;
	CButton	m_reset;
	CEdit	m_Edit3;
	CEdit	m_Edit2;
	CEdit	m_Edit1;
	CEdit	m_Mod;
	CButton	m_plus;
	CButton	m_mult;
	CButton	m_minus;
	CButton	m_eucl;
	CButton	m_div;
	static BOOL m_NoLog; //static 
	BOOL	m_Endian;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEuclidDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	
// Implementation
protected:
	HICON m_hIcon;
	CToolTipCtrl *m_ToolTipCtrl;//всплыв. подсказки

	// Generated message map functions
	//{{AFX_MSG(CEuclidDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDIV();
	afx_msg void OnEUCL();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEditMod();
	afx_msg void OnMINUS();
	afx_msg void OnMULT();
	afx_msg void OnPLUS();
	afx_msg void OnReset();
	afx_msg void OnFileE1();
	afx_msg void OnFileE2();
	afx_msg void OnFileE3();
	afx_msg void OnCii();
	afx_msg void OnFilePolyMod();
	afx_msg void OnChangeNolog();
	afx_msg void OnFpp();
	afx_msg void OnEndian();
	afx_msg void OnStop();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EUCLIDDLG_H__9B9A4207_8530_11D5_A253_80542EFCACA3__INCLUDED_)
