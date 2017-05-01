#if !defined(AFX_RENAME_H__CA7DB840_F507_11D4_85EA_0060674A702D__INCLUDED_)
#define AFX_RENAME_H__CA7DB840_F507_11D4_85EA_0060674A702D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Rename.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRename dialog

class CRename : public CDialog
{
// Construction
public:
	CRename(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRename)
	enum { IDD = IDD_RENAME_DIALOG };
	CString	m_newname;
	CString	m_oldname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRename)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRename)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RENAME_H__CA7DB840_F507_11D4_85EA_0060674A702D__INCLUDED_)
