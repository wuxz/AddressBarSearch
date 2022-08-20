// CDNSServerView.h : interface of the CCDNSServerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDNSSERVERVIEW_H__9299B2EC_9823_11D3_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_CDNSSERVERVIEW_H__9299B2EC_9823_11D3_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCDNSServerSet;
class CListenSocket;

class CCDNSServerView : public COleDBRecordView
{
protected: // create from serialization only
	CCDNSServerView();
	DECLARE_DYNCREATE(CCDNSServerView)

public:
	//{{AFX_DATA(CCDNSServerView)
	enum { IDD = IDD_CDNSSERVER_FORM };
	CCDNSServerSet* m_pSet;
	//}}AFX_DATA

// Attributes
public:
	CCDNSServerDoc* GetDocument();

protected:
	// The listening socket.
	CListenSocket* m_pListen;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDNSServerView)
	public:
	virtual CRowset* OnGetRowset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCDNSServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL StartListening();
	void StopListening();
	//{{AFX_MSG(CCDNSServerView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CDNSServerView.cpp
inline CCDNSServerDoc* CCDNSServerView::GetDocument()
   { return (CCDNSServerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDNSSERVERVIEW_H__9299B2EC_9823_11D3_A7FE_0080C8763FA4__INCLUDED_)
