// Euclid.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "Euclid.h"
#include "EuclidDlg.h"
#include "Polynomial.h"
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//инициализация счетчика полиномов
int Polynomial::counter = 0;
//лог куда все пишется
FILE *Polynomial::log;

BEGIN_MESSAGE_MAP(CEuclidApp, CWinApp)
	//{{AFX_MSG_MAP(CEuclidApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEuclidApp construction

CEuclidApp::CEuclidApp()
{

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEuclidApp object

CEuclidApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEuclidApp initialization

BOOL CEuclidApp::InitInstance()
{

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	//открытие лога для многочленов
	char log_name[30];//имя лога

	time_t now = time(NULL);
	sprintf(log_name, "%s\\poly_%d.log" ,LOG_DIR, now);
	Polynomial::log = fopen(log_name,"a");
	fprintf(Polynomial::log,"Program started at %s-----\n\n", \
		ctime(&now));

	CEuclidDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	
	fclose(Polynomial::log);//закрыть лог

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
