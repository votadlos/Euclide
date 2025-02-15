// ErrorDlg.cpp : implementation file
//
#include "stdafx.h"
#include "Euclid.h"
#include "ErrorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ErrorDlg dialog

ErrorDlg::ErrorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ErrorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ErrorDlg)
	//}}AFX_DATA_INIT
}
////////////////////////////////////////////////////////////
void ErrorDlg::setERRNO(int err_no){
	this->ERR_NO = err_no;
}
////////////////////////////////////////////////////////////
void ErrorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ErrorDlg)
	DDX_Control(pDX, IDC_ERR_TEXT, m_Static);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ErrorDlg, CDialog)
	//{{AFX_MSG_MAP(ErrorDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ErrorDlg message handlers
void ErrorDlg::OnOK() 
{
	CDialog::OnCancel();
	EndDialog(0);
}
//////////////////////////////////////////////////////////////
void ErrorDlg::showErrorText(){
	char *str = new char[1000];
	switch(ERR_NO){
		case 1 : strcpy(str," Wrong module. Module MUST be an integer greater then 1.");
			break;
		case 2 : strcpy(str," Empty coefficient or module field. To compose a polynomial you MUST specify module and coefficients in appropriate text field.\n If you define some coefficients greater then module, program will construct right coefficients itself, i.e. if module is 2 and you specify one of coefficients as 3, in calculations and output it will become 1.");
			break;
		case 3 : strcpy(str," Wrong degree. The degree of each polynomial MUST be greater or equal then 0.\n This is rather programmer's fault, so refer to developers for details.");
			break;
		case 4 : strcpy(str," Polynomial is not irreducible. To compose each field you should specify irreducible polynomial. If you define divisible polynomial, not all elements in composed 'field' will have inverse element, so it will be not field.");
			break;
		case 5 : strcpy(str," Degree of dividend MUST be greater or equal then that of divisor. Otherwise the result of devision is not defined and may lead to halting of OS.");
			break;
		case 6 : strcpy(str," To calculate prime polynomials you should specify their degrees ");
			break;
		case 7 : strcpy(str, " Please specify an integer between 1 and 65000");
			break;
	}
	m_Static.SetWindowText(str);
	delete [] str;

}
/////////////////////////////////////////////////////////////
BOOL ErrorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	showErrorText();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
