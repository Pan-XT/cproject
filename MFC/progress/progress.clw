; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProgressDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "progress.h"

ClassCount=3
Class1=CProgressApp
Class2=CProgressDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PROGRESS_DIALOG

[CLS:CProgressApp]
Type=0
HeaderFile=progress.h
ImplementationFile=progress.cpp
Filter=N

[CLS:CProgressDlg]
Type=0
HeaderFile=progressDlg.h
ImplementationFile=progressDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CProgressDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=progressDlg.h
ImplementationFile=progressDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROGRESS_DIALOG]
Type=1
Class=CProgressDlg
ControlCount=1
Control1=IDC_PROGRESS1,msctls_progress32,1350565889

