#if !defined(AFX_MAKEDIR_H__D4075140_F55D_11D4_85EA_0060674A702D__INCLUDED_)
#define AFX_MAKEDIR_H__D4075140_F55D_11D4_85EA_0060674A702D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MakeDir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMakeDir dialog

class CMakeDir : public CDialog
{
// Construction
public:
	CMakeDir(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMakeDir)
	enum { IDD = IDD_MAKEDIR_DIALOG };
	CString	m_subdirectory;
	CString	m_directory;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMakeDir)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMakeDir)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAKEDIR_H__D4075140_F55D_11D4_85EA_0060674A702D__INCLUDED_)
