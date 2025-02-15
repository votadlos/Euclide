; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=FindPrimitiveDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Euclid.h"

ClassCount=6
Class1=CEuclidApp
Class2=CEuclidDlg
Class3=CAboutDlg

ResourceCount=8
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_EUCLID_DIALOG
Resource4=IDD_DEG_ENT
Resource5=IDD_ABOUTBOX (English (U.S.))
Class4=ErrorDlg
Resource6=IDD_ERROR
Class5=DegSelect
Resource7=IDD_EUCLID_DIALOG (English (U.S.))
Class6=FindPrimitiveDlg
Resource8=IDD_PRIMITIVE_DIALOG

[CLS:CEuclidApp]
Type=0
HeaderFile=Euclid.h
ImplementationFile=Euclid.cpp
Filter=N
LastObject=CEuclidApp

[CLS:CEuclidDlg]
Type=0
HeaderFile=EuclidDlg.h
ImplementationFile=EuclidDlg.cpp
Filter=D
LastObject=CEuclidDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=EuclidDlg.h
ImplementationFile=EuclidDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_EUCLID_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CEuclidDlg

[DLG:IDD_EUCLID_DIALOG (English (U.S.))]
Type=1
Class=CEuclidDlg
ControlCount=28
Control1=DIV,button,1476460545
Control2=EUCL,button,1476460544
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_EDIT3,edit,1350631552
Control6=IDC_EDIT_MOD,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=PLUS,button,1476460545
Control9=MINUS,button,1476460545
Control10=MULT,button,1476460545
Control11=IDC_RESET,button,1476460544
Control12=IDC_FILE_E1,button,1342242816
Control13=IDC_FILE_E2,button,1342242816
Control14=IDC_FILE_E3,button,1342242816
Control15=IDC_POLY_MOD,edit,1350631552
Control16=IDC_FILE_POLY_MOD,button,1342242816
Control17=IDC_CII,button,1342242816
Control18=IDC_PROGRESS1,msctls_progress32,1350565888
Control19=IDC_STATIC_WHAT,static,1342308352
Control20=IDC_NOLOG,button,1342242819
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_FPP,button,1342242816
Control26=IDC_ENDIAN,button,1342242819
Control27=IDC_MAIN_PROGRESS,msctls_progress32,1350565888
Control28=IDC_STOP,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ERROR]
Type=1
Class=ErrorDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_ERR_TEXT,static,1342308352

[CLS:ErrorDlg]
Type=0
HeaderFile=ErrorDlg.h
ImplementationFile=ErrorDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ErrorDlg
VirtualFilter=dWC

[DLG:IDD_DEG_ENT]
Type=1
Class=DegSelect
ControlCount=3
Control1=IDOK,button,1476460545
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT,edit,1350631552

[CLS:DegSelect]
Type=0
HeaderFile=DegSelect.h
ImplementationFile=DegSelect.cpp
BaseClass=CDialog
Filter=D
LastObject=DegSelect
VirtualFilter=dWC

[DLG:IDD_PRIMITIVE_DIALOG]
Type=1
Class=FindPrimitiveDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_OUTPUT,edit,1353781444
Control4=IDC_DEGREE,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_CHECK_IRRED,button,1342242819

[CLS:FindPrimitiveDlg]
Type=0
HeaderFile=FindPrimitiveDlg.h
ImplementationFile=FindPrimitiveDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECK_IRRED
VirtualFilter=dWC

