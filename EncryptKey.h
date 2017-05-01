#if !defined(AFX_ENCRYPTKEY_H__F2B491E0_F871_11D4_85EA_0060674A702D__INCLUDED_)
#define AFX_ENCRYPTKEY_H__F2B491E0_F871_11D4_85EA_0060674A702D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EncryptKey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEncryptKey dialog

class CEncryptKey : public CDialog
{
// Construction
public:
	CEncryptKey(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEncryptKey)
	enum { IDD = IDD_ENCRYPTKEY_DIALOG };
	CString	m_encryptkey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEncryptKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEncryptKey)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENCRYPTKEY_H__F2B491E0_F871_11D4_85EA_0060674A702D__INCLUDED_)
