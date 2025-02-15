// EuclidDlg.cpp : implementation file
//
#include <ctype.h>
#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
//#include <process.h>
////////////////////
#include "Euclid.h"
#include "EuclidDlg.h"
#include "ErrorDlg.h"
#include "Euclid_return.h"
#include "DegSelect.h"
#include "Polynomial.h"
#include "Field.h"
#include "Period.h"
#include "PCIParam.h"
#include "PFIParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//globals
PCIParam pcip;
PFIParam pfip;
BOOL CEuclidDlg::m_StopVal;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEuclidDlg dialog

CEuclidDlg::CEuclidDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEuclidDlg::IDD, pParent)
{
	this->thread = NULL;
	CEuclidDlg::m_StopVal = FALSE;
	m_ToolTipCtrl = NULL;
	fpd = NULL;
	ch_edit1=0; ch_edit2=0; ch_module=0;
		//{{AFX_DATA_INIT(CEuclidDlg)
	m_Endian = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
////////////////////////////////////////////////////////////
CEuclidDlg::~CEuclidDlg(){
	delete m_ToolTipCtrl;
	delete fpd;
}
////////////////////////////////////////////////////////////
void CEuclidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEuclidDlg)
	DDX_Control(pDX, IDC_STOP, m_Stop);
	DDX_Control(pDX, IDC_MAIN_PROGRESS, m_MainProgress);
	DDX_Control(pDX, IDC_STATIC_WHAT, m_What);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_POLY_MOD, m_EditPolyMod);
	DDX_Control(pDX, IDC_RESET, m_reset);
	DDX_Control(pDX, IDC_EDIT3, m_Edit3);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_EDIT_MOD, m_Mod);
	DDX_Control(pDX, PLUS, m_plus);
	DDX_Control(pDX, MULT, m_mult);
	DDX_Control(pDX, MINUS, m_minus);
	DDX_Control(pDX, EUCL, m_eucl);
	DDX_Control(pDX, DIV, m_div);
	DDX_Check(pDX, IDC_NOLOG, m_NoLog);
	DDX_Check(pDX, IDC_ENDIAN, m_Endian);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEuclidDlg, CDialog)
	//{{AFX_MSG_MAP(CEuclidDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(DIV, OnDIV)
	ON_BN_CLICKED(EUCL, OnEUCL)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT_MOD, OnChangeEditMod)
	ON_BN_CLICKED(MINUS, OnMINUS)
	ON_BN_CLICKED(MULT, OnMULT)
	ON_BN_CLICKED(PLUS, OnPLUS)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_BN_CLICKED(IDC_FILE_E1, OnFileE1)
	ON_BN_CLICKED(IDC_FILE_E2, OnFileE2)
	ON_BN_CLICKED(IDC_FILE_E3, OnFileE3)
	ON_BN_CLICKED(IDC_CII, OnCii)
	ON_BN_CLICKED(IDC_FILE_POLY_MOD, OnFilePolyMod)
	ON_BN_CLICKED(IDC_NOLOG, OnChangeNolog)
	ON_BN_CLICKED(IDC_FPP, OnFpp)
	ON_BN_CLICKED(IDC_ENDIAN, OnEndian)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEuclidDlg message handlers

BOOL CEuclidDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Добавить CToolTipCtrl
	EnableToolTips();
	m_ToolTipCtrl = new CToolTipCtrl();
	m_ToolTipCtrl->Create(this);
	m_ToolTipCtrl->AddTool(GetDlgItem(MINUS), MINUS);
	m_ToolTipCtrl->AddTool(GetDlgItem(PLUS), PLUS);
	m_ToolTipCtrl->AddTool(GetDlgItem(MULT), MULT);
	m_ToolTipCtrl->AddTool(GetDlgItem(DIV), DIV);
	m_ToolTipCtrl->AddTool(GetDlgItem(EUCL), EUCL);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_STATIC_WHAT), IDC_STATIC_WHAT);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_EDIT_MOD), IDC_EDIT_MOD);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_NOLOG), IDC_NOLOG);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_PROGRESS1), IDC_PROGRESS1);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_FILE_POLY_MOD), IDC_FILE_POLY_MOD);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_FILE_E1), IDC_FILE_E1);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_FILE_E2), IDC_FILE_E2);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_FILE_E3), IDC_FILE_E3);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_RESET), IDC_RESET);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_EDIT1), IDC_EDIT1);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_EDIT2), IDC_EDIT2);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_EDIT3), IDC_EDIT3);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_POLY_MOD), IDC_POLY_MOD);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_CII), IDC_CII);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_FPP), IDC_FPP);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_ENDIAN), IDC_ENDIAN);
	m_ToolTipCtrl->AddTool(GetDlgItem(IDC_MAIN_PROGRESS), IDC_MAIN_PROGRESS);


	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//настроить прогресс
	CEuclidDlg::m_Progress.SetRange(0,PROGRESS_RANGE);
	CEuclidDlg::m_Progress.SetStep(1);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
//////////////////////////////////////////////////////////////
void CEuclidDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

//////////////////////////////////////////////////////////////
void CEuclidDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEuclidDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//////////////////////////////////////////////////////////////
void CEuclidDlg::OnDIV() 
{
	//если не задан образующий полином, реализует обычное деление многочленов,
	//выводит частное и остаток
	CEuclidDlg::m_What.SetWindowText("Calculating division...");
	ErrorDlg error;
	time_t newt, oldt = time(NULL);
	int el1 = m_Edit1.LineLength();
	int el2 = m_Edit2.LineLength();
	int ml = m_Mod.LineLength();
	int epml = m_EditPolyMod.LineLength();
	if ((el1==0)||(el2==0)||(ml==0)){
		error.setERRNO(2);
		error.DoModal();
		return;
	}

	int not_errors, err_no;
	char *edit1 = new char[el1+1];
	char *edit2 = new char[el2+1];
	char *mod = new char[ml+1];

	m_Mod.GetLine(0,mod,ml);
	m_Edit1.GetLine(0,edit1,el1);
	m_Edit2.GetLine(0,edit2,el2);

	long module = atol(mod);
	Polynomial poly1(edit1,el1,module,m_Endian);
  	Polynomial poly2(edit2,el2,module,m_Endian);
	Polynomial *poly_mod;
	CString res;//строка результата
	not_errors=1;//были ли ошибки при создании полиномов
	if (epml>0){
		char *editPolyMod = new char[epml+1];
		m_EditPolyMod.GetLine(0,editPolyMod,epml);
		poly_mod = new Polynomial(editPolyMod,epml,module,m_Endian);
		delete [] editPolyMod;
		if(poly_mod->Err == 1){
			err_no = 1; not_errors = 0;
		}
		if(poly_mod->Err == 2){
			err_no = 2; not_errors = 0;
		}
	}
	delete [] mod;
	delete [] edit1;
	delete [] edit2;
	if ((poly1.Err == 1)||(poly2.Err == 1)){
		err_no = 1; not_errors=0;
	}
	if ((poly1.Err == 2)||(poly2.Err == 2)){
		err_no = 2; not_errors=0;
	}
	if ((poly1.Deg < poly2.Deg)&&(epml<=0)){
		err_no = 5; not_errors=0;
	}

	if (not_errors){
		if (epml>0){
			/* задан образующий многочлен
			 * поиск обратного и умножение на него
			 */
			//поиск обратного по алгоритму Евклида
			Euclid_return *er = new Euclid_return(poly2,*poly_mod);
			res = ((poly1 * *(er->A)).div(*poly_mod)).remToString(m_Endian);
			delete er;
		}
		else{
			/* образующий многочлен не задан
			 * обычное деление
			 */
			Div_poly &dp = poly1.div(poly2);
			CString rem = dp.remToString(m_Endian);
			CString quot = dp.quotToString(m_Endian);
			res = "quot = " + quot + "; rem = " + rem;
		}
		m_Edit3.SetWindowText(LPCTSTR(res));
		newt = time(NULL);
	}
	else{
		newt = time(NULL);
		error.setERRNO(err_no);
		error.DoModal();
	}
	if (epml>0) delete poly_mod;
	//вывести время, очистить прогресс
	Period pr(oldt, newt);
	CEuclidDlg::m_Progress.SetPos(0);
	CEuclidDlg::m_What.SetWindowText(LPCTSTR(pr.toString()));
		
}
//////////////////////////////////////////////////////////////
void CEuclidDlg::OnEUCL()
{
	//то, что на интерфейсе называется "/"
	//если не задан образующий полином, реализует алг. Евклида.
	CEuclidDlg::m_What.SetWindowText("Calculating inversion...");
	ErrorDlg error;
	time_t newt, oldt = time(NULL);
	int el1 = m_Edit1.LineLength();
	int el2 = m_Edit2.LineLength();
	int ml = m_Mod.LineLength();
	int epml = m_EditPolyMod.LineLength();

	if(epml<=0){
		//если не задан образующий многочлен, должен быть задан 
		//второй многочлен для расчета Евклида
		if ((el1==0)||(el2==0)||(ml==0)){
			error.setERRNO(2);
			error.DoModal();
			return;
		}
	}else{
		//если задан, то должен быть задан первый мн-лен и модуль
		if ((el1==0)||(ml==0)){
			error.setERRNO(2);
			error.DoModal();
			return;
		}
	}

	int not_errors, err_no;
	char *edit1 = new char[el1+1];
	char *mod = new char[ml+1];
	m_Mod.GetLine(0,mod,ml);
	m_Edit1.GetLine(0,edit1,el1);
	long module = atol(mod);
	Polynomial poly1(edit1,el1,module,m_Endian);
  	delete [] mod;
	delete [] edit1;
	Polynomial *poly_mod, *poly2;
	CString res;//строка результата
	not_errors=1;//были ли ошибки при создании полиномов
	//если есть образующий полином
	if (epml>0){
		char *editPolyMod = new char[epml+1];
		m_EditPolyMod.GetLine(0,editPolyMod,epml);
		poly_mod = new Polynomial(editPolyMod,epml,module,m_Endian);
		delete [] editPolyMod;
		if(poly_mod->Err == 1){
			err_no = 1; not_errors = 0;
		}
		if(poly_mod->Err == 2){
			err_no = 2; not_errors = 0;
		}
	}
	//если есть второй полином
	if (el2>0){
		char *edit2 = new char[el2+1];
		m_Edit2.GetLine(0,edit2,el2);
		poly2 = new Polynomial(edit2,el2,module,m_Endian);
		delete [] edit2;
		if(poly2->Err == 1){
			err_no = 1; not_errors = 0;
		}
		if(poly2->Err == 2){
			err_no = 2; not_errors = 0;
		}
	}
	//проверка первого полинома
	if (poly1.Err == 1){
		err_no = 1; not_errors=0;
	}
	if (poly1.Err == 2){
		err_no = 2; not_errors=0;
	}
	
	if (not_errors){
		if (epml>0){
			/* задан образующий многочлен
			 * поиск обратного
			 */
			//поиск обратного по алгоритму Евклида
			Euclid_return *er = new Euclid_return(poly1,*poly_mod);
			res = er->A->toString(m_Endian);
			delete er;
		}
		else{
			/* образующий многочлен не задан
			 * алгоритм Евклида
			 */
			Euclid_return *er = new Euclid_return(poly1,*poly2);
			res = "A = "+er->A->toString(m_Endian)+ \
				"; B = "+er->B->toString(m_Endian)+ \
				"; NOD = "+er->Nod->toString(m_Endian);
			delete er;
		}
		m_Edit3.SetWindowText(LPCTSTR(res));
		newt = time(NULL);
	}
	else{
		newt = time(NULL);
		error.setERRNO(err_no);
		error.DoModal();
	}
	if (epml>0) delete poly_mod;
	//вывести время, очистить прогресс
	Period pr(oldt, newt);
	CEuclidDlg::m_Progress.SetPos(0);
	CEuclidDlg::m_What.SetWindowText(LPCTSTR(pr.toString()));
}
//////////////////////////////////////////////////////////////
void CEuclidDlg::OnChangeEdit1() 
{
	int el1 = m_Edit1.LineLength();
	if (el1!=0){ 
		ch_edit1=1;
		m_eucl.EnableWindow(TRUE);
	}
	else{ 
		ch_edit1 = 0;
		m_eucl.EnableWindow(FALSE);
	}
	if(ch_edit2 && ch_module)
		EnableButtons(TRUE);
}
//////////////////////////////////////////////////////////////
void CEuclidDlg::OnChangeEdit2() 
{
	int el2 = m_Edit2.LineLength();
	if (el2!=0) ch_edit2=1;
	else ch_edit2 = 0;
	if(ch_edit1 && ch_module)
		EnableButtons(TRUE);
}
//////////////////////////////////////////////////////////////
void CEuclidDlg::OnChangeEditMod() 
{
	int ml = m_Mod.LineLength();
	if (ml!=0) ch_module=1;
	else ch_module=0;
	if(ch_edit2 && ch_edit1)
		EnableButtons(TRUE);
}
//////////////////////////////////////////////////////////////
void CEuclidDlg::EnableButtons(BOOL yn){
	m_div.EnableWindow(yn);
	//m_eucl.EnableWindow(yn);
	//эта кнопка доступна сразу после редактирования Edit1
	m_plus.EnableWindow(yn);
	m_minus.EnableWindow(yn);
	m_mult.EnableWindow(yn);
	m_reset.EnableWindow(yn);
}
//////////////////////////////////////////////////////////////
void CEuclidDlg::OnMINUS() 
{
	CEuclidDlg::m_What.SetWindowText("Calculating subtraction...");
	ErrorDlg error;
	time_t newt, oldt = time(NULL);
	int el1 = m_Edit1.LineLength();
	int el2 = m_Edit2.LineLength();
	int ml = m_Mod.LineLength();
	int epml = m_EditPolyMod.LineLength();
	if ((el1==0)||(el2==0)||(ml==0)){
		error.setERRNO(2);
		error.DoModal();
		return;
	}

	int not_errors, err_no;
	char *edit1 = new char[el1+1];
	char *edit2 = new char[el2+1];
	char *mod = new char[ml+1];

	m_Mod.GetLine(0,mod,ml);
	m_Edit1.GetLine(0,edit1,el1);
	m_Edit2.GetLine(0,edit2,el2);

	long module = atol(mod);
	Polynomial poly1(edit1,el1,module,m_Endian);
  	Polynomial poly2(edit2,el2,module,m_Endian);
	Polynomial *poly_mod, *res;
	not_errors=1;//были ли ошибки при создании полиномов
	if (epml>0){
		char *editPolyMod = new char[epml+1];
		m_EditPolyMod.GetLine(0,editPolyMod,epml);
		poly_mod = new Polynomial(editPolyMod,epml,module,m_Endian);
		delete [] editPolyMod;
		if(poly_mod->Err == 1){
			err_no = 1; not_errors = 0;
		}
		if(poly_mod->Err == 2){
			err_no = 2; not_errors = 0;
		}
	}
	delete [] mod;
	delete [] edit1;
	delete [] edit2;
	if ((poly1.Err == 1)||(poly2.Err == 1)){
		err_no = 1; not_errors=0;
	}
	if ((poly1.Err == 2)||(poly2.Err == 2)){
		err_no = 2; not_errors=0;
	}
	
	if (not_errors){
		if (epml>0){
			Polynomial &pp = poly1-poly2;
			if (pp.Deg>=poly_mod->Deg){
				Div_poly &dp = pp.div(*poly_mod);
				res = new Polynomial(dp.Rem_deg,dp.Rem);
			}
			else res = new Polynomial(pp);
		}
		else{
			res = new Polynomial(poly1 - poly2);
		}
		m_Edit3.SetWindowText(LPCTSTR(res->toString(m_Endian)));
		delete res;
		newt = time(NULL);
	}
	else{
		newt = time(NULL);
		error.setERRNO(err_no);
		error.DoModal();
	}
	if (epml>0) delete poly_mod;
	//вывести время, очистить прогресс
	Period pr(oldt, newt);
	CEuclidDlg::m_Progress.SetPos(0);
	CEuclidDlg::m_What.SetWindowText(LPCTSTR(pr.toString()));
}
//////////////////////////////////////////////////////////////
void CEuclidDlg::OnMULT() 
{
	CEuclidDlg::m_What.SetWindowText("Calculating multiplication...");
	ErrorDlg error;
	time_t newt, oldt = time(NULL);
	int el1 = m_Edit1.LineLength();
	int el2 = m_Edit2.LineLength();
	int ml = m_Mod.LineLength();
	int epml = m_EditPolyMod.LineLength();
	if ((el1==0)||(el2==0)||(ml==0)){
		error.setERRNO(2);
		error.DoModal();
		return;
	}

	int not_errors, err_no;
	char *edit1 = new char[el1+1];
	char *edit2 = new char[el2+1];
	char *mod = new char[ml+1];

	m_Mod.GetLine(0,mod,ml);
	m_Edit1.GetLine(0,edit1,el1);
	m_Edit2.GetLine(0,edit2,el2);

	long module = atol(mod);
	Polynomial poly1(edit1,el1,module,m_Endian);
  	Polynomial poly2(edit2,el2,module,m_Endian);
	Polynomial *poly_mod, *res;
	not_errors=1;//были ли ошибки при создании полиномов
	if (epml>0){
		char *editPolyMod = new char[epml+1];
		m_EditPolyMod.GetLine(0,editPolyMod,epml);
		poly_mod = new Polynomial(editPolyMod,epml,module,m_Endian);
		delete [] editPolyMod;
		if(poly_mod->Err == 1){
			err_no = 1; not_errors = 0;
		}
		if(poly_mod->Err == 2){
			err_no = 2; not_errors = 0;
		}
	}
	delete [] mod;
	delete [] edit1;
	delete [] edit2;
	if ((poly1.Err == 1)||(poly2.Err == 1)){
		err_no = 1; not_errors=0;
	}
	if ((poly1.Err == 2)||(poly2.Err == 2)){
		err_no = 2; not_errors=0;
	}
	
	if (not_errors){
		if (epml>0){
			Polynomial &pp = poly1 * poly2;
			if (pp.Deg>=poly_mod->Deg){
				Div_poly &dp = pp.div(*poly_mod);
				res = new Polynomial(dp.Rem_deg,dp.Rem);
			}
			else res = new Polynomial(pp);
		}
		else{
			res = new Polynomial(poly1 * poly2);
		}
		m_Edit3.SetWindowText(LPCTSTR(res->toString(m_Endian)));
		delete res;
		newt = time(NULL);
	}
	else{
		newt = time(NULL);
		error.setERRNO(err_no);
		error.DoModal();
	}
	if (epml>0) delete poly_mod;
	//вывести время, очистить прогресс
	Period pr(oldt, newt);
	CEuclidDlg::m_Progress.SetPos(0);
	CEuclidDlg::m_What.SetWindowText(LPCTSTR(pr.toString()));		
}
//////////////////////////////////////////////////////////////
void CEuclidDlg::OnPLUS() 
{
	CEuclidDlg::m_What.SetWindowText("Calculating summation...");
	ErrorDlg error;
	time_t newt, oldt = time(NULL);
	int el1 = m_Edit1.LineLength();
	int el2 = m_Edit2.LineLength();
	int ml = m_Mod.LineLength();
	int epml = m_EditPolyMod.LineLength();
	if ((el1==0)||(el2==0)||(ml==0)){
		error.setERRNO(2);
		error.DoModal();
		return;
	}

	int not_errors, err_no;
	char *edit1 = new char[el1+1];
	char *edit2 = new char[el2+1];
	char *mod = new char[ml+1];

	m_Mod.GetLine(0,mod,ml);
	m_Edit1.GetLine(0,edit1,el1);
	m_Edit2.GetLine(0,edit2,el2);

	long module = atol(mod);
	Polynomial poly1(edit1,el1,module,m_Endian);
  	Polynomial poly2(edit2,el2,module,m_Endian);
	Polynomial *poly_mod, *sum;
	not_errors=1;//были ли ошибки при создании полиномов
	if (epml>0){
		char *editPolyMod = new char[epml+1];
		m_EditPolyMod.GetLine(0,editPolyMod,epml);
		poly_mod = new Polynomial(editPolyMod,epml,module,m_Endian);
		delete [] editPolyMod;
		if(poly_mod->Err == 1){
			err_no = 1; not_errors = 0;
		}
		if(poly_mod->Err == 2){
			err_no = 2; not_errors = 0;
		}
	}
	delete [] mod;
	delete [] edit1;
	delete [] edit2;
	if ((poly1.Err == 1)||(poly2.Err == 1)){
		err_no = 1; not_errors=0;
	}
	if ((poly1.Err == 2)||(poly2.Err == 2)){
		err_no = 2; not_errors=0;
	}
	
	if (not_errors){
		if (epml>0){
			Polynomial &pp = poly1+poly2;
			if (pp.Deg>=poly_mod->Deg){
				Div_poly &dp = pp.div(*poly_mod);
				sum = new Polynomial(dp.Rem_deg,dp.Rem);
			}
			else sum = new Polynomial(pp);
		}
		else{
			sum = new Polynomial(poly1 + poly2);
		}
		m_Edit3.SetWindowText(LPCTSTR(sum->toString(m_Endian)));
		delete sum;
		newt = time(NULL);
	}
	else{
		newt = time(NULL);
		error.setERRNO(err_no);
		error.DoModal();
	}
	if (epml>0) delete poly_mod;
	//вывести время, очистить прогресс
	Period pr(oldt, newt);
	CEuclidDlg::m_Progress.SetPos(0);
	CEuclidDlg::m_What.SetWindowText(LPCTSTR(pr.toString()));
}
//////////////////////////////////////////////////////////////
void CEuclidDlg::OnReset() 
{
	m_Edit1.SetWindowText("");
	m_Edit2.SetWindowText("");
	m_Mod.SetWindowText(""); 
	m_Edit3.SetWindowText("");
	m_EditPolyMod.SetWindowText("");
	this->EnableButtons(FALSE);
}
//////////////////////////////////////////////////////////////
//функции доставания исходных многочленов из файлов
//и созранения результатов в файл...
void CEuclidDlg::OnFileE1() 
{
	// открыть файл с полиномом 1
	//здесь будет имя открытого файла с полиномом
	TCHAR szBuffer[MAX_PATH]=_T("");
	OPENFILENAME ofn={0};
	ofn.lStructSize=sizeof(ofn);
	//ofn.hwndOwner=hWnd;
	//ofn.hInstance=hInstance;
	ofn.lpstrFilter=_T("Polynomial files\x0*.poly\x0");
	ofn.lpstrFile=szBuffer;
	ofn.nMaxFile=MAX_PATH;
	ofn.Flags=
		OFN_ENABLESIZING|
		OFN_EXPLORER|
		OFN_FILEMUSTEXIST|
		OFN_HIDEREADONLY|
		OFN_PATHMUSTEXIST;
	if(GetOpenFileName(&ofn)){
		FILE *f;
		f = fopen((char *)szBuffer,"r");
		char next;
		CString str("");
		next = fgetc(f);
		while((next != 0x0A)&&(next != EOF)){
			str += (TCHAR) next;
			next = fgetc(f);
		}
		fclose(f);
		m_Edit1.SetWindowText(LPCTSTR(str));
	}	
}
///////////////////////////////////////////////////////////////
void CEuclidDlg::OnFileE2() 
{
	// открыть файл с полиномом 2
	TCHAR szBuffer[MAX_PATH]=_T("");
	OPENFILENAME ofn={0};
	ofn.lStructSize=sizeof(ofn);
	//ofn.hwndOwner=hWnd;
	//ofn.hInstance=hInstance;
	ofn.lpstrFilter=_T("Polynomial files\x0*.poly\x0");
	ofn.lpstrFile=szBuffer;
	ofn.nMaxFile=MAX_PATH;
	ofn.Flags=
		OFN_ENABLESIZING|
		OFN_EXPLORER|
		OFN_FILEMUSTEXIST|
		OFN_HIDEREADONLY|
		OFN_PATHMUSTEXIST;
	if(GetOpenFileName(&ofn)){
		FILE *f;
		f = fopen((char *)szBuffer,"r");
		char next;
		CString str("");
		next = fgetc(f);
		while((next != 0x0A)&&(next != EOF)){
			str += (TCHAR) next;
			next = fgetc(f);
		}
		fclose(f);
		m_Edit2.SetWindowText(LPCTSTR(str));
	}		
}
////////////////////////////////////////////////////////////
void CEuclidDlg::OnFileE3() 
{
	// сохранить в файл полином 3
	TCHAR szBuffer[MAX_PATH]=_T("");
	OPENFILENAME ofn={0};
	ofn.lStructSize=sizeof(ofn);
	//ofn.hwndOwner=hWnd;
	//ofn.hInstance=hInstance;
	ofn.lpstrFilter=_T("Polynomial files\x0*.poly\x0");
	ofn.lpstrFile=szBuffer;
	ofn.nMaxFile=MAX_PATH;
	ofn.Flags=
		OFN_ENABLESIZING|
		OFN_EXPLORER|
		OFN_FILEMUSTEXIST|
		OFN_HIDEREADONLY|
		OFN_PATHMUSTEXIST;
	if(GetSaveFileName(&ofn)){
		FILE *f;
		int len = m_Edit3.LineLength();
		if (len>0){
			char *buff = new char[len];
			m_Edit3.GetLine(0,buff,len);
		
			f=fopen((char *)szBuffer,"w");
			//отпарсить буффер buff от мусора
			if((buff[0] == 'q') || (buff[0] == 'A')){
				//quot = ...; rem = ...
				//или алг. Евклида
				int k=0;
				for(int i=0;i<len;i++){
					if((isdigit(buff[i]))||(buff[i] == ' ')) fputc(buff[i],f);
					else{
						k++;
						if(k<11) fputc(buff[i],f);
						else break;
					}
				}
			}
			else{
				//просто число
				for(int i=0;i<len-1;i+=2){
					if((isdigit(buff[i]))&&(buff[i+1]==' ')){
						fputc(buff[i],f);
						fputc(buff[i+1],f);
					}
					else break;
				}
			}
			fclose(f);
			delete [] buff;
		}
	}		
}
/////////////////////////////////////////////////////////////
void CEuclidDlg::OnChangeNolog(){
	CEuclidDlg::m_NoLog = !CEuclidDlg::m_NoLog;
}
////////////////////////////////////////////////////////////
//При нажатии на кнопку происходит проверка заданног многочлена
//на наприводимость. Если многочлен не задан, то спрешиватеся его
//степень и предлагается многочлен простой и заданной степени. 
void CEuclidDlg::OnCii() 
{
	ErrorDlg error;
	int el = m_EditPolyMod.LineLength();
	int ml = m_Mod.LineLength();
	long mod;
	if (ml==0){
		error.setERRNO(2);
		error.DoModal();
		return;
	}
	char *module = new char[ml+1];
	m_Mod.GetLine(0,module,ml);
	mod = atol(module);
	delete [] module;
	
	CEuclidDlg::m_StopVal = FALSE;
	pcip.set(el,mod,&this->m_EditPolyMod, this->m_Endian,&this->m_MainProgress);
	pfip.set(mod,&this->m_EditPolyMod, this->m_Endian,&this->m_MainProgress);
	if(el>0){
		//что-то ввели в окно ввода
		this->thread = AfxBeginThread(process_check_irred,&pcip);
	}
	else{
		//ничего не ввели - надо предлагать самому
		this->thread = AfxBeginThread(process_find_irred,&pfip);
	}

}

///////////////////////////////////////////////////////////////
UINT process_find_irred(void *pParam){
	int i, des_deg, isSimple;
	time_t nowt, newt;
	Polynomial *poly;
	char endstr[60];
	PFIParam *param = (PFIParam *)pParam;
	DegSelect ds;
	ds.DoModal();
	des_deg = ds.m_Deg;
	BOOL isAdmissible = Polynomial::isAdmissible(des_deg);
	if (des_deg != 0){
		//создание полинома заданной степени
		Field *coeff = new Field[des_deg+1];
		//установка модуля
		for (i=0;i<=des_deg;i++)
			coeff[i].set(0,param->mod);
		//сконтруировали полином
		poly = new Polynomial(des_deg,coeff);
		delete [] coeff;
		nowt = time(NULL);
		int isExist = 1,
			flag = 1;
		isSimple = 0;
		long total_cnt = long(pow(param->mod,des_deg));
		long max_cnt = long(2*total_cnt);
		//Mod+DIV(pow(mod,Deg),Deg)+Deg-1
		int calcTime = (int)((max_cnt-total_cnt)* \
			(param->mod+des_deg-1+DIV_(pow(param->mod,des_deg),des_deg)));
		param->progress->SetRange32(0,calcTime);
		param->progress->SetPos(0);
		param->progress->SetStep(1);
		while((isSimple == 0) && flag){
			CEuclidDlg::m_What.SetWindowText("Generating irreducible polynomial...");
			param->progress->StepIt();
			for(i=0;i<=des_deg;i++){
				CEuclidDlg::showProgress();
				/* заполнение коэффициентов полинома по порядку
				 * начиная от всех 0 до всех единиц
				 */
				//перевод total_cnt в двоичную СС поразрядно
				poly->Coeff[i].Data = (total_cnt/long(pow(param->mod,i))) % param->mod;
			}
			if(isAdmissible)
				isSimple = poly->isSimple(param->progress);
			else
				isSimple = poly->isSimpleB(param->progress);
			total_cnt++;
			if(total_cnt>max_cnt){
				isExist = 0; 
				flag = 0;
			}
		}
		newt = time(NULL);
		char tmp[30];
		if (isExist) param->m_EditPolyMod->SetWindowText(LPCTSTR(poly->toString(param->m_Endian)));
		else {
			sprintf(tmp,"Not found: deg=%d p=%d",des_deg,param->mod);
		}
		delete poly;
		Period pr(nowt, newt);
		sprintf(endstr,"%s %s",LPCTSTR(pr.toString()),tmp);	
	}
	else sprintf(endstr,"Calculations aborted");
	CEuclidDlg::m_Progress.SetPos(0);
	CEuclidDlg::m_What.SetWindowText(endstr);
	param->progress->SetPos(0);
	return 0;
}
///////////////////////////////////////////////////////////////
UINT process_check_irred(void *pParam){
	int not_errors, err_no, isSimple;
	time_t nowt, newt;
	ErrorDlg error;
	char endstr[60];
	PCIParam *param = (PCIParam *)pParam;
	char *edit = new char[param->el+1];
	param->m_EditPolyMod->GetLine(0,edit,param->el);
	Polynomial *poly = new Polynomial(edit,param->el,param->mod,param->m_Endian);
	delete [] edit;

	BOOL isAdmissible = Polynomial::isAdmissible(poly->Deg);
	
	not_errors=1;
	if (poly->Err == 1){
		err_no = 1;
		not_errors=0;
	}
	if (poly->Err == 2){
		err_no = 2;
		not_errors=0;
	}
	
	if (not_errors){
		//сложность: Mod+DIV(pow(mod,Deg),Deg)+Deg-1
		long calcTime = (int)(param->mod + poly->Deg + \
			DIV_(pow(param->mod,poly->Deg),poly->Deg));
		//calcTime = ((calcTime>65500) ? 65500 : calcTime);
		CProgressCtrl *prg = param->progress;
		prg->SetRange32(0,100);
		prg->SetStep(1);
		prg->SetPos(0);
		nowt = time(NULL);
		if (isAdmissible) isSimple = poly->isSimple(prg);
		else isSimple = poly->isSimpleB(prg);
		newt = time(NULL);
		Period pr(nowt, newt);
		strcpy(endstr,LPCTSTR(pr.toString()));
		if (isSimple == 0){
			//полином не простой
			error.setERRNO(4);
			error.DoModal();
		}
	}
	else{
		error.setERRNO(err_no);
		error.DoModal();
	}
	delete poly;
	CEuclidDlg::m_Progress.SetPos(0);
	CEuclidDlg::m_What.SetWindowText(endstr);
	param->progress->SetPos(0);
	return 0;
}
///////////////////////////////////////////////////////////////
void CEuclidDlg::OnFilePolyMod() 
{
	// открыть файл с полиномом g(x)
	TCHAR szBuffer[MAX_PATH]=_T("");
	OPENFILENAME ofn={0};
	ofn.lStructSize=sizeof(ofn);
	//ofn.hwndOwner=hWnd;
	//ofn.hInstance=hInstance;
	ofn.lpstrFilter=_T("Polynomial files\x0*.poly\x0");
	ofn.lpstrFile=szBuffer;
	ofn.nMaxFile=MAX_PATH;
	ofn.Flags=
		OFN_ENABLESIZING|
		OFN_EXPLORER|
		OFN_FILEMUSTEXIST|
		OFN_HIDEREADONLY|
		OFN_PATHMUSTEXIST;
	if(GetOpenFileName(&ofn)){
		FILE *f;
		f = fopen((char *)szBuffer,"r");
		char next;
		CString str("");
		next = fgetc(f);
		while((next != 0x0A)&&(next != EOF)){
			str += (TCHAR) next;
			next = fgetc(f);
		}
		fclose(f);
		m_EditPolyMod.SetWindowText(LPCTSTR(str));
	}			
}
///////////////////////////////////////////////////////////////
void CEuclidDlg::showProgress(){
	CEuclidDlg::m_Progress.StepIt();
	if (CEuclidDlg::m_Progress.GetPos() == PROGRESS_RANGE) CEuclidDlg::m_Progress.SetPos(0);
}	
///////////////////////////////////////////////////////////////
void CEuclidDlg::OnFpp() 
{
	
	ErrorDlg error;
	//int el = m_EditPolyMod.LineLength();
	int ml = m_Mod.LineLength();
	long mod;
	if (ml==0){
		error.setERRNO(2);
		error.DoModal();
		return;
	}

	char *module = new char[ml+1];
	m_Mod.GetLine(0,module,ml);
	mod = atol(module);
	delete [] module;

	
	//FindPrimitiveDlg fpd;
	if (fpd) delete fpd;
	fpd = new FindPrimitiveDlg();
	fpd->Mod = mod;
	fpd->fpp_progress = &this->m_MainProgress;
	fpd->Endian = m_Endian;
	fpd->Create(IDD_PRIMITIVE_DIALOG);
	fpd->ShowWindow(SW_SHOWNORMAL);
	//fpd.DoModal();
}
/////////////////////////////////////////////////////////////
BOOL CEuclidDlg::PreTranslateMessage(MSG* pMsg) 
{
	m_ToolTipCtrl->RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}
//////////////////////////////////////////////////////////////
void CEuclidDlg::OnEndian() {
	m_Endian = !m_Endian;
	
}

void CEuclidDlg::OnStop() 
{
	CEuclidDlg::m_StopVal = TRUE;
	if (this->thread){
		DWORD tt = this->thread->SuspendThread();
		if (tt != 0xFFFFFFFF){
			CEuclidDlg::m_What.SetWindowText("Calculations aborted");
			CEuclidDlg::m_Progress.SetPos(0);
			this->m_MainProgress.SetPos(0);
		}
	}
}

void CEuclidDlg::WinHelp(DWORD dwData, UINT nCmd) 
{
	ShellExecute(NULL,"open","index.html",NULL,"help",SW_MAXIMIZE);
	CDialog::WinHelp(dwData, nCmd);
}
/////////////////////////////////////////////////////////////
BOOL CEuclidDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	ShellExecute(NULL,"open","help\\index.html",
		NULL,NULL,SW_MAXIMIZE);
	return TRUE;
}
/////////////////////////////////////////////////////////////