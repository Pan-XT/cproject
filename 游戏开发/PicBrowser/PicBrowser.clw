; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPicBrowserView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PicBrowser.h"
LastPage=0

ClassCount=5
Class1=CPicBrowserApp
Class2=CPicBrowserDoc
Class3=CPicBrowserView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CPicBrowserApp]
Type=0
HeaderFile=PicBrowser.h
ImplementationFile=PicBrowser.cpp
Filter=N

[CLS:CPicBrowserDoc]
Type=0
HeaderFile=PicBrowserDoc.h
ImplementationFile=PicBrowserDoc.cpp
Filter=N

[CLS:CPicBrowserView]
Type=0
HeaderFile=PicBrowserView.h
ImplementationFile=PicBrowserView.cpp
Filter=C
BaseClass=CHtmlView
VirtualFilter=7VWC
LastObject=ID_BROWER_BTN


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_BROWER_BTN




[CLS:CAboutDlg]
Type=0
HeaderFile=PicBrowser.cpp
ImplementationFile=PicBrowser.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_SETUP
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_APP_ABOUT
CommandCount=15

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_BROWER_BTN
CommandCount=9

