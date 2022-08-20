; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "cdnscli.h"
LastPage=0

ClassCount=6
Class1=CCDNSCliApp
Class2=CAboutDlg
Class3=CChooseAddrDlg
Class4=CMainFrame
Class5=COptionsDlg
Class6=CSystemTray

ResourceCount=5
Resource1=IDD_DIALOG_CHOOSEADDRESS
Resource2=IDD_ABOUTBOX
Resource3=IDR_MENU_TRAY
Resource4=IDR_MAINFRAME
Resource5=IDD_DIALOG_OPTIONS

[CLS:CCDNSCliApp]
Type=0
BaseClass=CWinApp
HeaderFile=CDNSCli.h
ImplementationFile=CDNSCli.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=CDNSCli.cpp
ImplementationFile=CDNSCli.cpp
LastObject=CAboutDlg

[CLS:CChooseAddrDlg]
Type=0
BaseClass=CDialog
HeaderFile=ChooseAddrDlg.h
ImplementationFile=ChooseAddrDlg.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=ID_TRAY_TEST
Filter=T
VirtualFilter=fWC

[CLS:COptionsDlg]
Type=0
BaseClass=CDialog
HeaderFile=OptionsDlg.h
ImplementationFile=OptionsDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_RADIO_LETMECHOOSE

[CLS:CSystemTray]
Type=0
BaseClass=CWnd
HeaderFile=SystemTray.h
ImplementationFile=SystemTray.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG_CHOOSEADDRESS]
Type=1
Class=CChooseAddrDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_ADDRESS,listbox,1353777281
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_OPTIONS]
Type=1
Class=COptionsDlg
ControlCount=20
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_RADIO_USEFIRST,button,1342373897
Control4=IDC_RADIO_LETMECHOOSE,button,1342242825
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_TIMEOUT,edit,1350631552
Control7=IDC_SPIN_TIMEOUT,msctls_updown32,1342177718
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,button,1342177287
Control10=IDC_CHECK_USEPROXY,button,1342242819
Control11=IDC_STATIC,static,1342308352
Control12=IDC_COMBO_PROXY,combobox,1344340290
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_CONNECT_PORT,edit,1350639744
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_CONNECT_TIMEOUT,edit,1350631552
Control17=IDC_SPIN_CONNECT_TIMEOUT,msctls_updown32,1342177718
Control18=IDC_STATIC,static,1342308352
Control19=IDOK,button,1342242817
Control20=IDCANCEL,button,1342242816

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_APP_ABOUT
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[MNU:IDR_MENU_TRAY]
Type=1
Class=CMainFrame
Command1=ID_APP_ABOUT
Command2=ID_TRAY_START
Command3=ID_TRAY_OPTIONS
Command4=ID_APP_EXIT
CommandCount=4

