// EncryptKey.cpp : implementation file
//

#include "stdafx.h"
#include "rfvfs.h"
#include "EncryptKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEncryptKey dialog


CEncryptKey::CEncryptKey(CWnd* pParent /*=NULL*/)
	: CDialog(CEncryptKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEncryptKey)
	m_encryptkey = _T("");
	//}}AFX_DATA_INIT
}


void CEncryptKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEncryptKey)
	DDX_Text(pDX, IDC_EDIT1, m_encryptkey);
	DDV_MaxChars(pDX, m_encryptkey, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEncryptKey, CDialog)
	//{{AFX_MSG_MAP(CEncryptKey)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEncryptKey message handlers
