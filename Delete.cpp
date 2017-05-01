// Delete.cpp : implementation file
//

#include "stdafx.h"
#include "rfvfs.h"
#include "Delete.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelete dialog


CDelete::CDelete(CWnd* pParent /*=NULL*/)
	: CDialog(CDelete::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDelete)
	m_filename = _T("");
	//}}AFX_DATA_INIT
}


void CDelete::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDelete)
	DDX_Text(pDX, IDC_EDIT1, m_filename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDelete, CDialog)
	//{{AFX_MSG_MAP(CDelete)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelete message handlers
