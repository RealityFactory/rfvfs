// MakeDir.cpp : implementation file
//

#include "stdafx.h"
#include "rfvfs.h"
#include "MakeDir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMakeDir dialog


CMakeDir::CMakeDir(CWnd* pParent /*=NULL*/)
	: CDialog(CMakeDir::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMakeDir)
	m_subdirectory = _T("");
	m_directory = _T("");
	//}}AFX_DATA_INIT
}


void CMakeDir::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMakeDir)
	DDX_Text(pDX, IDC_EDIT1, m_subdirectory);
	DDX_Text(pDX, IDC_EDIT2, m_directory);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMakeDir, CDialog)
	//{{AFX_MSG_MAP(CMakeDir)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakeDir message handlers
