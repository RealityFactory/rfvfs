// Rename.cpp : implementation file
//

#include "stdafx.h"
#include "rfvfs.h"
#include "Rename.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRename dialog


CRename::CRename(CWnd* pParent /*=NULL*/)
	: CDialog(CRename::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRename)
	m_newname = _T("");
	m_oldname = _T("");
	//}}AFX_DATA_INIT
}


void CRename::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRename)
	DDX_Text(pDX, IDC_EDIT1, m_newname);
	DDX_Text(pDX, IDC_EDIT2, m_oldname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRename, CDialog)
	//{{AFX_MSG_MAP(CRename)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRename message handlers

int CRename::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DoModal();
}
