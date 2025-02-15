#if !defined(AFX_DEGSELECT_H__8E8173E5_AEC0_11D5_A253_D13208B91CA0__INCLUDED_)
#define AFX_DEGSELECT_H__8E8173E5_AEC0_11D5_A253_D13208B91CA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DegSelect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DegSelect dialog

class DegSelect : public CDialog
{
// Construction
public:
	DegSelect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DegSelect)
	enum { IDD = IDD_DEG_ENT };
	CButton	m_OK;
	int		m_Deg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DegSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DegSelect)
	afx_msg void OnChangeEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEGSELECT_H__8E8173E5_AEC0_11D5_A253_D13208B91CA0__INCLUDED_)
