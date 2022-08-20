// CDNSServerDoc.cpp : implementation of the CCDNSServerDoc class
//

#include "stdafx.h"
#include "CDNSServer.h"

#include "CDNSServerSet.h"
#include "CDNSServerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCDNSServerDoc

IMPLEMENT_DYNCREATE(CCDNSServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CCDNSServerDoc, CDocument)
	//{{AFX_MSG_MAP(CCDNSServerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDNSServerDoc construction/destruction

CCDNSServerDoc::CCDNSServerDoc()
{
	// TODO: add one-time construction code here

}

CCDNSServerDoc::~CCDNSServerDoc()
{
}

BOOL CCDNSServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCDNSServerDoc diagnostics

#ifdef _DEBUG
void CCDNSServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCDNSServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCDNSServerDoc commands
