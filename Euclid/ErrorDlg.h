#if !defined(AFX_ERRORDLG_H__597B8EEE_A3DC_11D5_A253_9EBBE132BFA3__INCLUDED_)
#define AFX_ERRORDLG_H__597B8EEE_A3DC_11D5_A253_9EBBE132BFA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ErrorDlg dialog

class ErrorDlg : public CDialog
{
// Construction
public:
	ErrorDlg(CWnd* pParent = NULL);// standard constructor
	void setERRNO(int);
private:
	int ERR_NO;//код ошибки
	void ErrorDlg::OnOK();
	void showErrorText();//показать текст ошибки в окне
// Dialog Data
	//{{AFX_DATA(ErrorDlg)
	enum { IDD = IDD_ERROR };
	CStatic	m_Static;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ErrorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ErrorDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORDLG_H__597B8EEE_A3DC_11D5_A253_9EBBE132BFA3__INCLUDED_)
