#if !defined(AFX_DELETE_H__CA7DB841_F507_11D4_85EA_0060674A702D__INCLUDED_)
#define AFX_DELETE_H__CA7DB841_F507_11D4_85EA_0060674A702D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Delete.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDelete dialog

class CDelete : public CDialog
{
// Construction
public:
	CDelete(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDelete)
	enum { IDD = IDD_DELETE_DIALOG };
	CString	m_filename;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelete)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDelete)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELETE_H__CA7DB841_F507_11D4_85EA_0060674A702D__INCLUDED_)
