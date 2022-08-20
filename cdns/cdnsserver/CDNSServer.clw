; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCDNSServerView
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CDNSServer.h"
LastPage=0

ClassCount=7
Class1=CCDNSServerApp
Class2=CCDNSServerDoc
Class3=CCDNSServerView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CListenSocket
Class7=CRequestSocket
Resource3=IDD_CDNSSERVER_FORM

[CLS:CCDNSServerApp]
Type=0
HeaderFile=CDNSServer.h
ImplementationFile=CDNSServer.cpp
Filter=N

[CLS:CCDNSServerDoc]
Type=0
HeaderFile=CDNSServerDoc.h
ImplementationFile=CDNSServerDoc.cpp
Filter=N

[CLS:CCDNSServerView]
Type=0
HeaderFile=CDNSServerView.h
ImplementationFile=CDNSServerView.cpp
Filter=D
BaseClass=COleDBRecordView
VirtualFilter=RVWC
LastObject=IDC_EDIT1


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=CDNSServer.cpp
ImplementationFile=CDNSServer.cpp
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
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
CommandCount=10

[DLG:IDD_CDNSSERVER_FORM]
Type=1
Class=CCDNSServerView
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CListenSocket]
Type=0
HeaderFile=ListenSocket.h
ImplementationFile=ListenSocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q

[CLS:CRequestSocket]
Type=0
HeaderFile=RequestSocket.h
ImplementationFile=RequestSocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q

