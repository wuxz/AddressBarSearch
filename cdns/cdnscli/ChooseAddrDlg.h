#if !defined(AFX_CHOOSEADDRDLG_H__F8E1B660_92C9_11D3_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_CHOOSEADDRDLG_H__F8E1B660_92C9_11D3_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseAddrDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseAddrDlg dialog

class CChooseAddrDlg : public CDialog
{
// Construction
public:
	CChooseAddrDlg(CWnd* pParent = NULL);   // standard constructor
	
	// The address array to choose
	CStringArray m_arAddr;

	// The selected item index.
	int m_nSel;

	// The seconds before timeout.
	int m_nTimeout;

// Dialog Data
	//{{AFX_DATA(CChooseAddrDlg)
	enum { IDD = IDD_DIALOG_CHOOSEADDRESS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

protected:
	// The Timer ID for detecting timeout.
	UINT m_nTimer;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseAddrDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseAddrDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDblclkListAddress();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEADDRDLG_H__F8E1B660_92C9_11D3_A7FE_0080C8763FA4__INCLUDED_)
