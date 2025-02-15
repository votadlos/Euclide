// FindPrimitiveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Euclid.h"
#include "FindPrimitiveDlg.h"
#include <time.h>
#include <math.h>
#include "EuclidDlg.h"
#include "Period.h"
#include "ErrorDlg.h"
#include "PCPParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

PCPParam pcpp;

/////////////////////////////////////////////////////////////////////////////
// FindPrimitiveDlg dialog


FindPrimitiveDlg::FindPrimitiveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FindPrimitiveDlg::IDD, pParent)
{
	this->thread = NULL;
	//{{AFX_DATA_INIT(FindPrimitiveDlg)
	m_Irred = FALSE;
	//}}AFX_DATA_INIT
}


void FindPrimitiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FindPrimitiveDlg)
	DDX_Control(pDX, IDC_DEGREE, m_Deg);
	DDX_Control(pDX, IDC_OUTPUT, m_Output);
	DDX_Check(pDX, IDC_CHECK_IRRED, m_Irred);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FindPrimitiveDlg, CDialog)
	//{{AFX_MSG_MAP(FindPrimitiveDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FindPrimitiveDlg message handlers

void FindPrimitiveDlg::OnCancel() 
{
	if (this->thread){
		DWORD tt = this->thread->SuspendThread();
		if (tt != 0xFFFFFFFF){
			CEuclidDlg::m_What.SetWindowText("Calculations aborted");
			CEuclidDlg::m_Progress.SetPos(0);
			this->fpp_progress->SetPos(0);
		}
	}
	CDialog::OnCancel();
}

void FindPrimitiveDlg::OnOK() 
{
	//CDialog::OnOK();
	
	ErrorDlg error;
	int dl = m_Deg.LineLength();
	if (dl==0){
		error.setERRNO(6);
		error.DoModal();
		return;
	}

	char *degree = new char[dl+1];
	m_Deg.GetLine(0,degree,dl);
	int des_deg = atoi(degree);
	if ((des_deg <= 0)||(des_deg > 65000)){
		error.setERRNO(7);
		error.DoModal();
		return;
	}
	delete [] degree;
	UpdateData();
	pcpp.set(this->Mod, des_deg, this->Endian, &this->m_Output,this->fpp_progress,this->m_Irred);
	this->thread = AfxBeginThread(process_calc_prime,&pcpp);
}
////////////////////////////////////////////////////////////
UINT process_calc_prime(void * pParam){
	PCPParam *param = (PCPParam *) pParam;
	int des_deg = param->des_deg;
	BOOL admissible = Polynomial::isAdmissible(des_deg);
	long Mod = param->mod;
	BOOL Endian = param->endian;
	BOOL m_Irred = param->irred;
	int i, pr_counter = 0;
	CString text("");
	time_t nowt = time(NULL), newt;
	//создание коэффициентов полинома заданной степени
	Field *coeff = new Field[des_deg+1];
	//установка модуля
	for (i=0;i<=des_deg;i++)
		coeff[i].setModule(Mod);
	//сконтруировали полином желаемой степени
	Polynomial *poly = new Polynomial(des_deg,coeff);
	delete [] coeff;
	CEuclidDlg::m_What.SetWindowText("Finding all prime polynomials...");
	long total_cnt, max_cnt;
	total_cnt = long(pow(Mod,des_deg));//начать с того, что в старшем разряде 1
	max_cnt=total_cnt*2;//только нормированные
	param->progress->SetRange32(0,int(total_cnt)+1);
	param->progress->SetStep(1);
	param->progress->SetPos(0);
	while(total_cnt <= max_cnt){
		param->progress->StepIt();
		for(i=0;i<=des_deg;i++){
			CEuclidDlg::showProgress();
			poly->Coeff[i].Data = (total_cnt/long(pow(Mod,i))) % Mod;
		}
		int result;
		if(m_Irred){
			result = ((admissible)?poly->isSimple():poly->isSimpleB());
		}else{
			result = poly->isPrime();
		}
		if(result) {
			pr_counter++;
			text = text + poly->toString(Endian) + "\r\n";
		}
		total_cnt++;
	}
	newt = time(NULL);
	delete poly;
	char pr_counter_txt[100];
	sprintf(pr_counter_txt,"-------\r\n%d items",pr_counter);
	text = text + pr_counter_txt;
	param->output->SetWindowText(LPCTSTR(text));
	Period pr(nowt, newt);
	CEuclidDlg::m_What.SetWindowText(LPCTSTR(pr.toString()));
	CEuclidDlg::m_Progress.SetPos(0);
	param->progress->SetPos(0);
	return 0;
}
