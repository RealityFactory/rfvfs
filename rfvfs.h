// rfvfs.h : main header file for the RFVFS application
//

#if !defined(AFX_RFVFS_H__C0560EA4_F2FD_11D4_85EA_0060674A702D__INCLUDED_)
#define AFX_RFVFS_H__C0560EA4_F2FD_11D4_85EA_0060674A702D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <direct.h>

/////////////////////////////////////////////////////////////////////////////
// CRfvfsApp:
// See rfvfs.cpp for the implementation of this class
//

class CRfvfsApp : public CWinApp
{
public:
	CRfvfsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRfvfsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRfvfsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RFVFS_H__C0560EA4_F2FD_11D4_85EA_0060674A702D__INCLUDED_)
