// DegSelect.cpp : implementation file
//

#include "stdafx.h"
#include "Euclid.h"
#include "DegSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DegSelect dialog


DegSelect::DegSelect(CWnd* pParent /*=NULL*/)
	: CDialog(DegSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(DegSelect)
	m_Deg = 0;
	//}}AFX_DATA_INIT
}


void DegSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DegSelect)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Text(pDX, IDC_EDIT, m_Deg);
	DDV_MinMaxInt(pDX, m_Deg, 0, 65000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DegSelect, CDialog)
	//{{AFX_MSG_MAP(DegSelect)
	ON_EN_CHANGE(IDC_EDIT, OnChangeEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DegSelect message handlers

void DegSelect::OnChangeEdit() 
{
	this->m_OK.EnableWindow(TRUE);		
}
