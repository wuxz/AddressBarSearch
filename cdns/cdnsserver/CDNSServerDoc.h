// CDNSServerDoc.h : interface of the CCDNSServerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDNSSERVERDOC_H__9299B2EA_9823_11D3_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_CDNSSERVERDOC_H__9299B2EA_9823_11D3_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CDNSServerSet.h"


class CCDNSServerDoc : public CDocument
{
protected: // create from serialization only
	CCDNSServerDoc();
	DECLARE_DYNCREATE(CCDNSServerDoc)

// Attributes
public:
	CCDNSServerSet m_cDNSServerSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDNSServerDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCDNSServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCDNSServerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDNSSERVERDOC_H__9299B2EA_9823_11D3_A7FE_0080C8763FA4__INCLUDED_)
