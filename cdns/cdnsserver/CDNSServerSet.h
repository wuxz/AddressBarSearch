// CDNSServerSet.h : interface of the CCDNSServerSet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDNSSERVERSET_H__9299B2EE_9823_11D3_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_CDNSSERVERSET_H__9299B2EE_9823_11D3_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCnaddr
{
public:
	CCnaddr()
	{
		memset( (void*)this, 0, sizeof(*this) );
	};

	char m_Address[26];
	int m_ID;
	char m_Text[26];


BEGIN_COLUMN_MAP(CCnaddr)
		COLUMN_ENTRY_TYPE(3, DBTYPE_STR, m_Address)
		COLUMN_ENTRY_TYPE(1, DBTYPE_I4, m_ID)
		COLUMN_ENTRY_TYPE(2, DBTYPE_STR, m_Text)
END_COLUMN_MAP()

};

class CCDNSServerSet : public CCommand<CAccessor<CCnaddr> >
{
protected:
		CDataSource db;
		CSession session;
		CDBPropSet dbinit;
		CDBPropSet propset;

public:

	CCDNSServerSet() : dbinit(DBPROPSET_DBINIT), propset(DBPROPSET_ROWSET)
	{
		dbinit.AddProperty(DBPROP_AUTH_CACHE_AUTHINFO, true);
		dbinit.AddProperty(DBPROP_AUTH_ENCRYPT_PASSWORD, false);
		dbinit.AddProperty(DBPROP_AUTH_MASK_PASSWORD, false);
		dbinit.AddProperty(DBPROP_AUTH_PASSWORD, "");
		dbinit.AddProperty(DBPROP_AUTH_USERID, "Admin");

		// Get the current path.
		TCHAR pszPath[1024];
		TCHAR * pszDB = _T("cnaddr.mdb");

		GetModuleFileName(AfxGetInstanceHandle(), pszPath, 1024);

		for (int i = lstrlen(pszPath) - 1; i >= 0; i --)
		{
			if (pszPath[i] == '\\')
				break;
		}

		// If can not find the '\'(it is impossible:), use file name
		// directly; Otherwise, replace the module file name with the 
		// database file name.
		if (i < 0)
			lstrcpy(pszPath, pszDB);
		else
		{
			for (int j = 0; j < lstrlen(pszDB); j ++)
				pszPath[++ i] = pszDB[j];

			pszPath[++i] = '\0';
		}

		dbinit.AddProperty(DBPROP_INIT_DATASOURCE, pszPath);
		dbinit.AddProperty(DBPROP_INIT_MODE, (long)16);
		dbinit.AddProperty(DBPROP_INIT_PROMPT, (short)4);
		dbinit.AddProperty(DBPROP_INIT_PROVIDERSTRING, "");
		dbinit.AddProperty(DBPROP_INIT_LCID, (long)1033);
		dbinit.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);

//		propset.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
//		propset.AddProperty(DBPROP_IRowsetScroll, true);
//		propset.AddProperty(DBPROP_IRowsetChange, true);
//		propset.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE );
	}

	HRESULT Open(LPCTSTR pszText = NULL)
	{
		HRESULT hr;

		if (m_spRowset)
			Close();

		if (!db.m_spInit)
		{
			hr = db.OpenWithServiceComponents(_T("Microsoft.Jet.OLEDB.3.51"), &dbinit);
			if (FAILED(hr))
				return hr;
		}

		if (!session.m_spOpenRowset)
		{
			hr = session.Open(db);
			if (FAILED(hr))
				return hr;
		}

		CString strSQL = _T("SELECT * FROM cnaddr");
		if (pszText)
		{
//			strSQL += " WHERE Text LIKE '";
//			strSQL += pszText;
//			strSQL += "%'";
			strSQL += _T(" WHERE Text = '");
			strSQL += pszText;
			strSQL += _T("'");
		}

		hr = CCommand<CAccessor<CCnaddr> >::Open(session, strSQL, &propset);
		if (FAILED(hr))
			return hr;

		return MoveFirst();
	}

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDNSSERVERSET_H__9299B2EE_9823_11D3_A7FE_0080C8763FA4__INCLUDED_)

