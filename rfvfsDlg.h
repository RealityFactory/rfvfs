// rfvfsDlg.h : header file
//

#if !defined(AFX_RFVFSDLG_H__C0560EA6_F2FD_11D4_85EA_0060674A702D__INCLUDED_)
#define AFX_RFVFSDLG_H__C0560EA6_F2FD_11D4_85EA_0060674A702D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "FileTreeCtrl.h"
#include "EllepticalButton.h"
#include "basetype.h"
#include "ram.h"
#include "vfile.h"

/////////////////////////////////////////////////////////////////////////////
// CRfvfsDlg dialog

class CRfvfsDlg : public CDialog
{
// Construction
public:
	CRfvfsDlg(CWnd* pParent = NULL);	// standard constructor

	void SetupDirectory();
	BOOL EmptyDirectory(CString &sPath);
	TCHAR m_currentdir[512];

// Dialog Data
	//{{AFX_DATA(CRfvfsDlg)
	enum { IDD = IDD_RFVFS_DIALOG };
	CEllepticalButton	m_buttonsave;
	CEllepticalButton	m_buttonmkdir;
	CEllepticalButton	m_buttonextract;
	CEllepticalButton	m_buttondel;
	CEllepticalButton	m_buttonrename;
	CEllepticalButton	m_buttonopen;
	CEllepticalButton	m_buttonnew;
	CEllepticalButton	m_buttonadd;
	CTreeFileCtrl	m_dirtree;
	BOOL	m_encrypt;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRfvfsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CString vfsFileName;
	CString WinText;
	void ExtractVFS(geVFile *VFS, const char *FileSpec);
	void CopyVFile(geVFile * FmFile,geVFile *ToFile);
	void CopyOneFile(geVFile *FSSrc, geVFile *FSDest, const char *src, const char *dest);
	void GetDir(CString &Path, geVFile *VFS);
	void GetFiles(CString &Path, geVFile *VFS);
	bool MakeDirectory(geVFile *FS, const char *Path);
	void CopyFile(const char *srcPath, const char *destPath);

	// Generated message map functions
	//{{AFX_MSG(CRfvfsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton6();
	afx_msg void OnButton5();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton4();
	afx_msg void OnCheck1();
	afx_msg void OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RFVFSDLG_H__C0560EA6_F2FD_11D4_85EA_0060674A702D__INCLUDED_)
