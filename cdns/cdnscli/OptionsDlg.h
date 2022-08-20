#if !defined(AFX_OPTIONSDLG_H__F8E1B661_92C9_11D3_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_OPTIONSDLG_H__F8E1B661_92C9_11D3_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog
class CMainFrame;

class COptionsDlg : public CDialog
{
// Construction
public:
	CMainFrame * m_pMainFrame;
	COptionsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsDlg)
	enum { IDD = IDD_DIALOG_OPTIONS };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDlg)
	afx_msg void OnRadioLetmechoose();
	afx_msg void OnRadioUsefirst();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDLG_H__F8E1B661_92C9_11D3_A7FE_0080C8763FA4__INCLUDED_)
