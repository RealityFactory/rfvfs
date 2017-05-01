// rfvfsDlg.cpp : implementation file
//

#include "stdafx.h"
#include <afxtempl.h>
#include "FileTreeCtrl.h"
#include "rfvfs.h"
#include "rfvfsDlg.h"
#include "MFileDlg.h"
#include "basetype.h"
#include "vfile.h"
#include "Rename.h"
#include "Delete.h"
#include "MakeDir.h"
#include "EncryptKey.h"
#include <direct.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CRfvfsDlg dialog

CRfvfsDlg::CRfvfsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRfvfsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRfvfsDlg)
	m_encrypt = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRfvfsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRfvfsDlg)
	DDX_Control(pDX, IDC_BUTTON4, m_buttonsave);
	DDX_Control(pDX, IDC_BUTTON8, m_buttonmkdir);
	DDX_Control(pDX, IDC_BUTTON7, m_buttonextract);
	DDX_Control(pDX, IDC_BUTTON5, m_buttondel);
	DDX_Control(pDX, IDC_BUTTON6, m_buttonrename);
	DDX_Control(pDX, IDC_BUTTON3, m_buttonopen);
	DDX_Control(pDX, IDC_BUTTON2, m_buttonnew);
	DDX_Control(pDX, IDC_BUTTON1, m_buttonadd);
	DDX_Control(pDX, IDC_TREE1, m_dirtree);
	DDX_Check(pDX, IDC_CHECK1, m_encrypt);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRfvfsDlg, CDialog)
	//{{AFX_MSG_MAP(CRfvfsDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE1, OnItemexpandingTree1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRfvfsDlg message handlers

BOOL CRfvfsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	vfsFileName = "";
	GetWindowText(WinText);
	WinText += "  ";
	_chdir("..");
	_getcwd(m_currentdir, 512);
	SetupDirectory();
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRfvfsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRfvfsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//
// Add
//

void CRfvfsDlg::OnButton1() 
{
	CString SelPath = m_dirtree.GetSelectedPath();
	int nLength = SelPath.GetLength();
	if (SelPath.GetAt(nLength-1) != _T('\\'))
      SelPath += "\\";

	MFileDlg dlgFile(TRUE);
	TCHAR m_dir[512];
	strcpy(m_dir, m_currentdir);
	strcat(m_dir, "\\media");
	dlgFile.SetInitalDir(m_dir);
	
	CString title, strFilter, strDefault;
	VERIFY(title.LoadString(AFX_IDS_OPENFILE));
	
	// append the "*.*"  files filter
	strFilter = _T("All Files (*.*)");
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += _T("*.*");
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.nMaxCustFilter++;
	
	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;
	dlgFile.m_ofn.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
	chdir(m_currentdir);

	if (dlgFile.DoModal() == IDOK)
	{
		POSITION pos = dlgFile.GetStartPosition();
		while (pos != NULL)
		{
			CString strPath = dlgFile.GetNextPathName(pos);
			CString FileName = strPath.Mid(strPath.ReverseFind('\\')+1);
			CString destPath = SelPath + FileName;
			CopyFile(strPath, destPath);
			chdir(m_currentdir);
		}
		m_dirtree.OnViewRefresh();
		m_dirtree.ExpandFill();
	}
}

BOOL CRfvfsDlg::EmptyDirectory(CString &sPath)
{
	CFileFind finder;
	
	CString  sWildCard = sPath + "\\*.*";
	
	BOOL bFound;
	BOOL bWorking = finder.FindFile(sWildCard);
	
	bFound = bWorking;
	
	while (bWorking) 
	{
		bWorking = finder.FindNextFile();
		
		if (finder.IsDots()) continue;
		
		if (finder.IsDirectory()) 
		{
			CString s = finder.GetFilePath();
			EmptyDirectory(s);
			RemoveDirectory(finder.GetFilePath());
			continue; 
		}
		_unlink( finder.GetFilePath() );
		
	}
	
	return bFound;
	
}


void CRfvfsDlg::OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_dirtree.OnItemexpanding(pNMHDR,pResult);
}

void CRfvfsDlg::SetupDirectory()
{
	CString sPath = m_currentdir;
	CString sMain, sFolder;
	sPath += "\\$$temp";
	EmptyDirectory(sPath);
	_rmdir(sPath);
	CreateDirectory(sPath,NULL);
	sMain = sPath+"\\install";
	CreateDirectory(sMain,NULL);
	sMain = sPath+"\\media";
	CreateDirectory(sMain,NULL);
	sFolder = sMain+"\\actors";
	CreateDirectory(sFolder,NULL);
	sFolder = sMain+"\\levels";
	CreateDirectory(sFolder,NULL);
	sFolder = sMain+"\\bitmaps";
	CreateDirectory(sFolder,NULL);
	sFolder = sMain+"\\bitmaps\\menu";
	CreateDirectory(sFolder,NULL);
	sFolder = sMain+"\\bitmaps\\fonts";
	CreateDirectory(sFolder,NULL);
	sFolder = sMain+"\\bitmaps\\fx";
	CreateDirectory(sFolder,NULL);
	sFolder = sMain+"\\bitmaps\\explode";
	CreateDirectory(sFolder,NULL);
	sFolder = sMain+"\\bitmaps\\crosshairs";
	CreateDirectory(sFolder,NULL);
	sFolder = sMain+"\\audio";
	CreateDirectory(sFolder,NULL);
	sFolder = sMain+"\\audio\\menu";
	CreateDirectory(sFolder,NULL);

	m_dirtree.SetRootFolder(sPath); 
}

//
// New
//
void CRfvfsDlg::OnButton2() 
{
	SetupDirectory();
	m_dirtree.ExpandFill();
	vfsFileName = "";
	SetWindowText(WinText);
}

//
// Open
//

void CRfvfsDlg::OnButton3() 
{
	CFileDialog dlgFile(TRUE);
	dlgFile.m_ofn.lpstrInitialDir = m_currentdir;
	
	CString title, strFilter, strDefault;
	VERIFY(title.LoadString(AFX_IDS_OPENFILE));
	
	// append the "*.vfs"  files filter
	strFilter = _T("VFS Files (*.vfs)");
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += _T("*.vfs");
	strFilter += (TCHAR)'\0';
	dlgFile.m_ofn.nMaxCustFilter++;
	strFilter += _T("All Files (*.*)");
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += _T("*.*");
	dlgFile.m_ofn.nMaxCustFilter++;
	strFilter += (TCHAR)'\0';   // last string
	strFilter += (TCHAR)'\0'; 
	
	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;
	dlgFile.m_ofn.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
	
	if (dlgFile.DoModal() == IDOK)
	{
		POSITION pos = dlgFile.GetStartPosition();
		while (pos != NULL)
		{
			CString strPath = dlgFile.GetNextPathName(pos);
			vfsFileName = strPath.Mid(strPath.ReverseFind('\\')+1);
			CString destPath = m_currentdir;
			destPath += "\\$$tmp$$.vfs";

			CopyFile(strPath, destPath);
			chdir(m_currentdir);

			geVFile *VFS;
			CFile sourceFile;
			BYTE buffer[256];
			DWORD dwRead;
			CFileException ex;
			sourceFile.Open(destPath, CFile::modeRead | CFile::shareDenyWrite, &ex);
			dwRead = sourceFile.Read(buffer, 4);
			sourceFile.Close();
			CString Encrpt = "";
			if(strnicmp((char *)buffer, "CF00", 4)==0)
			{
				CEncryptKey EKey;
				if(EKey.DoModal())
				{
					TCHAR encrypt[512];
					CString EnKey = EKey.m_encryptkey+"        ";
					EnKey = EnKey.Left(8);
					strcpy(encrypt, EnKey);
					VFS = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_VIRTUAL, "$$tmp$$.vfs", encrypt, GE_VFILE_OPEN_READONLY | GE_VFILE_OPEN_DIRECTORY);
					Encrpt = " (Encrypted)";
				}
				else
				{
					remove(destPath);
					break;
				}
			}
			else
				VFS = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_VIRTUAL, "$$tmp$$.vfs", NULL, GE_VFILE_OPEN_READONLY | GE_VFILE_OPEN_DIRECTORY);
			if(!VFS)
			{
				MessageBox("Unable to Get VFS for "+vfsFileName, "RealityFactory VFS", MB_ICONSTOP | MB_OK);
				remove(destPath);
				break;
			}

			CString sPath = m_currentdir;
			sPath += "\\$$temp";
			EmptyDirectory(sPath);

			CWaitCursor c;
			ExtractVFS(VFS, "*.*");

			geVFile_Close(VFS);
			remove(destPath);
			CString WText;
			WText = WinText + vfsFileName;
			WText += Encrpt;
			SetWindowText(WText);

			m_dirtree.SetRootFolder(sPath);
			m_dirtree.ExpandFill();
		}
	}
}

void CRfvfsDlg::ExtractVFS(geVFile *VFS, const char *FileSpec)
{
	geVFile_Finder *	Finder;

	Finder = geVFile_CreateFinder(VFS, FileSpec);
	if	(!Finder)
		return;

	while	(geVFile_FinderGetNextFile(Finder))
	{
		geVFile_Properties	Properties;
		geVFile_FinderGetProperties(Finder, &Properties);
		CString srcDir, srcFile, destDir, destFile;
		srcDir = FileSpec;
		int length = srcDir.ReverseFind('\\');
		if(length>0)
			srcDir = srcDir.Left(length)+"\\";
		else
			srcDir = "";
		srcFile = Properties.Name;
		destDir = m_currentdir;
		destDir += "\\$$temp\\";
		destFile = Properties.Name;
		if	(Properties.AttributeFlags & GE_VFILE_ATTRIB_DIRECTORY)
		{
			srcDir += srcFile;
			destDir = destDir+srcDir;
			CreateDirectory(destDir,NULL);
			srcDir += "\\*.*";
			ExtractVFS(VFS, srcDir);
		}
		else
		{
			destDir = destDir+srcDir;
			if (destDir.GetAt(destDir.GetLength()-1) == _T('\\'))
				destDir = destDir.Left(destDir.GetLength()-1);
			geVFile *FSDest = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS, destDir, NULL, GE_VFILE_OPEN_UPDATE | GE_VFILE_OPEN_DIRECTORY);
			CopyOneFile(VFS, FSDest, srcDir+srcFile, destFile);
			geVFile_Close(FSDest);
		} 
	}
	geVFile_DestroyFinder(Finder);
	return;
}

void CRfvfsDlg::CopyVFile(geVFile * FmFile,geVFile *ToFile)
{
	char CopyBuf[16384];
	int CopyBufLen = 16384;
	long Size;
	geVFile_Properties Props;
	
	if ( ! geVFile_GetProperties(FmFile,&Props) )
		return;
	
	if ( ! geVFile_Size(FmFile,&Size) )
		return;
	
	while( Size )
	{
		int CurLen = min(Size,CopyBufLen);
		
		if ( ! geVFile_Read(FmFile,CopyBuf,CurLen) )
			return;
		
		if ( ! geVFile_Write(ToFile,CopyBuf,CurLen) )
			return;
		
		Size -= CurLen;
	}
	return;
}

void CRfvfsDlg::CopyOneFile(geVFile *FSSrc, geVFile *FSDest, const char *src, const char *dest)
{
	geVFile *		SrcFile;
	geVFile *     DestFile;

	SrcFile = geVFile_Open(FSSrc, src, GE_VFILE_OPEN_READONLY);
	if	(!SrcFile)
		return;
	DestFile = geVFile_Open(FSDest, dest, GE_VFILE_OPEN_CREATE);
	if	(!DestFile)
		return;

	CopyVFile(SrcFile, DestFile);

	geVFile_Close(DestFile);
	geVFile_Close(SrcFile);

	return;
}

//
// Rename
//

void CRfvfsDlg::OnButton6() 
{
	HTREEITEM hItem = m_dirtree.GetSelectedItem();
	if (hItem)
	{
		CString oldname = m_dirtree.ItemToPath(hItem);
		CString FileName = oldname.Mid(oldname.ReverseFind('\\')+1);
		oldname = oldname.Left(oldname.ReverseFind('\\')+1);

		CRename dlg(NULL);
		dlg.m_oldname = FileName;
		dlg.m_newname = FileName;
		if(dlg.DoModal())
		{
			CString Old = oldname + FileName;
			CString New = dlg.m_newname;
			if(!New.IsEmpty())
			{
				New.TrimLeft();
				if(!New.IsEmpty())
				{
					New = oldname + New;
					rename(Old, New);
					m_dirtree.OnViewRefresh();
				}
			}
		}
	}
}

//
// Delete
//

void CRfvfsDlg::OnButton5() 
{
	HTREEITEM hItem = m_dirtree.GetSelectedItem();
	if (hItem)
	{
		CString oldname = m_dirtree.ItemToPath(hItem);
		CString FileName = oldname.Mid(oldname.ReverseFind('\\')+1);
		oldname = oldname.Left(oldname.ReverseFind('\\')+1);

		CDelete dlg(NULL);
		dlg.m_filename = "File : ";
		if(m_dirtree.IsFolder(m_dirtree.ItemToPath(hItem)))
			dlg.m_filename = "Folder : ";
		dlg.m_filename += FileName;
		if(dlg.DoModal())
		{
			if(m_dirtree.IsFolder(m_dirtree.ItemToPath(hItem)))
			{
				EmptyDirectory(m_dirtree.ItemToPath(hItem));
				_rmdir(m_dirtree.ItemToPath(hItem));
			}
			else
			{
				remove(oldname + FileName);
			}
			m_dirtree.OnViewRefresh();
		}
	}
}

//
// Extract
//

void CRfvfsDlg::OnButton7() 
{
	HTREEITEM hItem = m_dirtree.GetSelectedItem();
	if (hItem)
	{
		char drive[_MAX_DRIVE],dir[_MAX_DIR],filename[_MAX_FNAME+_MAX_EXT],ext[_MAX_EXT];
		_splitpath(m_dirtree.ItemToPath(hItem),drive,dir,filename,ext);
		strcat(filename,ext);
		CString srcPath = m_dirtree.ItemToPath(hItem);
		chdir(m_currentdir);
		
		if(m_dirtree.IsFile(m_dirtree.ItemToPath(hItem)))
		{
			CFileDialog dlgFile(FALSE);
			dlgFile.m_ofn.lpstrInitialDir = m_currentdir;
			dlgFile.m_ofn.lpstrFile = filename;
			
			CString title, strFilter, strDefault;
			VERIFY(title.LoadString(AFX_IDS_SAVEFILE));
			
			// append the files filter
			strFilter = _T("All Files (*");
			strFilter += _T(ext);
			strFilter += _T(")");
			strFilter += (TCHAR)'\0';   // next string please
			strFilter += _T("*");
			strFilter += _T(ext);
			strFilter += (TCHAR)'\0';   // last string
			dlgFile.m_ofn.nMaxCustFilter++;
			
			dlgFile.m_ofn.lpstrFilter = strFilter;
			dlgFile.m_ofn.lpstrTitle = title;
			dlgFile.m_ofn.Flags |= OFN_OVERWRITEPROMPT;
			dlgFile.m_ofn.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
			
			if (dlgFile.DoModal() == IDOK)
			{
				POSITION pos = dlgFile.GetStartPosition();
				if(pos != NULL)
				{
					CString destPath = dlgFile.GetNextPathName(pos);
					CopyFile(srcPath, destPath);
					chdir(m_currentdir);
				}
			}
		}
	}
}

//
// MkDir
//

void CRfvfsDlg::OnButton8() 
{
	HTREEITEM hItem = m_dirtree.GetSelectedItem();
	if (hItem)
	{
		CString dirPath = m_dirtree.ItemToPath(hItem);
		if(m_dirtree.IsFile(dirPath))
			dirPath = dirPath.Left(dirPath.ReverseFind('\\'));
		CString dirName = dirPath.Mid(dirPath.ReverseFind('\\')+1);
		dirPath += "\\";

		CMakeDir dlg(NULL);
		dlg.m_directory = dirName;
		dlg.m_subdirectory = "";
		if(dlg.DoModal())
		{
			CString New = dlg.m_subdirectory;
			if(!New.IsEmpty())
			{
				New.TrimLeft();
				if(!New.IsEmpty())
				{
					New = dirPath + New;
					_mkdir(New);
					m_dirtree.OnViewRefresh();
					m_dirtree.ExpandFill(); 
				}
			}
		}
	}
}

//
// Save
//

void CRfvfsDlg::OnButton4() 
{
	CFileDialog dlgFile(FALSE);
	dlgFile.m_ofn.lpstrInitialDir = m_currentdir;
	TCHAR m_dir[512];
	if(vfsFileName=="")
		m_dir[0] = (TCHAR)'\0';
	else
		strcpy(m_dir, vfsFileName);
	dlgFile.m_ofn.lpstrFile = m_dir;
	
	CString title, strFilter, strDefault;
	VERIFY(title.LoadString(AFX_IDS_SAVEFILE));
	
	// append the files filter
	strFilter = _T("VFS Files (*.vfs");
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += _T("*.vfs");
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.nMaxCustFilter++;
	strFilter += _T("All Files (*.*)");
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += _T("*.*");
	dlgFile.m_ofn.nMaxCustFilter++;
	strFilter += (TCHAR)'\0';   // last string
	strFilter += (TCHAR)'\0'; 
	
	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;
	dlgFile.m_ofn.lpstrDefExt = _T("vfs");
	dlgFile.m_ofn.Flags |= OFN_OVERWRITEPROMPT;
	dlgFile.m_ofn.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
	
	if (dlgFile.DoModal() == IDOK)
	{
		POSITION pos = dlgFile.GetStartPosition();
		if(pos != NULL)
		{
			CString destPath = dlgFile.GetNextPathName(pos);
			vfsFileName = destPath.Mid(destPath.ReverseFind('\\')+1);
			CString sPath = "";
			CString srcPath = m_currentdir;
			srcPath += "\\$$tmp$$.vfs";
			chdir(m_currentdir);
			
			geVFile *VFS;
			CString Encrpt = "";
			
			if(m_encrypt)
			{
				CEncryptKey EKey;
				if(EKey.DoModal())
				{
					TCHAR encrypt[512];
					CString EnKey = EKey.m_encryptkey+"        ";
					EnKey = EnKey.Left(8);
					strcpy(encrypt, EnKey);
					VFS = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_VIRTUAL, "$$tmp$$.vfs", encrypt, GE_VFILE_OPEN_CREATE | GE_VFILE_OPEN_DIRECTORY);
					Encrpt = " (Encrypted)";
				}
				else
				{
					remove(srcPath);
					return;
				}
			}
			else
				VFS = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_VIRTUAL, "$$tmp$$.vfs", NULL, GE_VFILE_OPEN_CREATE | GE_VFILE_OPEN_DIRECTORY);
			if(!VFS)
			{
				MessageBox("Unable to Get VFS for "+vfsFileName, "RealityFactory VFS", MB_ICONSTOP | MB_OK);
				remove(srcPath);
			}
			else
			{
				CWaitCursor c;
				GetFiles(sPath, VFS);
				GetDir(sPath, VFS);
				geVFile_Close(VFS);
				chdir(m_currentdir);
				CopyFile(srcPath, destPath);
				chdir(m_currentdir);
				remove(srcPath);
				CString WText;
				WText = WinText + vfsFileName;
				WText += Encrpt;
				SetWindowText(WText);
			}
		}
	}
}


void CRfvfsDlg::GetDir(CString &Path, geVFile *VFS)
{
	struct _finddata_t  c_file;
	long fhandle;
	CString newPath;
	CString searchString = m_currentdir;
	searchString += "\\$$temp\\";
	searchString += Path;
	searchString+= "\\*.*";

	if ((fhandle=_findfirst( searchString, &c_file ))!=-1) 
	{	
		if ((c_file.attrib & _A_SUBDIR)==_A_SUBDIR) 
		{
			if ((strcmp(c_file.name, ".")!=0) && (strcmp(c_file.name, "..")!=0)) 
			{
				newPath = Path;
				newPath+= "\\";
				newPath+= c_file.name;
				MakeDirectory(VFS, newPath);
				GetFiles(newPath, VFS);
				GetDir(newPath, VFS);
			}
		}
		while(_findnext( fhandle, &c_file ) == 0 ) 
		{		
			if ((c_file.attrib & _A_SUBDIR)==_A_SUBDIR) 
			{
				if ((strcmp(c_file.name, ".")!=0) && (strcmp(c_file.name, "..")!=0)) 
				{
					newPath = Path;
					newPath+= "\\";
					newPath+= c_file.name;
					MakeDirectory(VFS, newPath);
					GetFiles(newPath, VFS);
					GetDir(newPath, VFS);
				}
			}
		}
	}
	_findclose(fhandle);
}

void CRfvfsDlg::GetFiles(CString &Path, geVFile *VFS)
{
	struct _finddata_t  c_file;
	long fhandle;
	CString newPath;
	geVFile *FSSrc;
	CString searchString = m_currentdir;
	searchString += "\\$$temp\\";
	searchString += Path;
	searchString+= "\\*.*";

	if ((fhandle=_findfirst( searchString, &c_file ))!=-1) 
	{	
		if ((c_file.attrib & _A_SUBDIR)==0) 
		{
			if ((strcmp(c_file.name, ".")!=0) && (strcmp(c_file.name, "..")!=0)) 
			{
				newPath = Path;
				newPath+= "\\";
				newPath+= c_file.name;
				newPath =newPath.Mid(1);
				CString srcPath = m_currentdir;
				srcPath += "\\$$temp\\";
				srcPath += Path;
				if (srcPath.GetAt(srcPath.GetLength()-1) == _T('\\'))
					srcPath = srcPath.Left(srcPath.GetLength()-1);
				FSSrc = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS, srcPath, NULL, GE_VFILE_OPEN_READONLY | GE_VFILE_OPEN_DIRECTORY);
				CopyOneFile(FSSrc, VFS, c_file.name, newPath);
			}
		}
		while(_findnext( fhandle, &c_file ) == 0 ) 
		{		
			if ((c_file.attrib & _A_SUBDIR)==0) 
			{
				if ((strcmp(c_file.name, ".")!=0) && (strcmp(c_file.name, "..")!=0)) 
				{
					newPath = Path;
					newPath+= "\\";
					newPath+= c_file.name;
					newPath =newPath.Mid(1);
					CString srcPath = m_currentdir;
					srcPath += "\\$$temp\\";
					srcPath += Path;
					if (srcPath.GetAt(srcPath.GetLength()-1) == _T('\\'))
						srcPath = srcPath.Left(srcPath.GetLength()-1);
					FSSrc = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS, srcPath, NULL, GE_VFILE_OPEN_READONLY | GE_VFILE_OPEN_DIRECTORY);
					CopyOneFile(FSSrc, VFS, c_file.name, newPath);
				}
			}
		}
	}
	_findclose(fhandle);
}

bool CRfvfsDlg::MakeDirectory(geVFile *FS, const char *Path)
{
	char		Buff[_MAX_PATH];
	char *		p;
	geVFile *		NewDirectory;
	bool	Res;

	if	(*Path == '\0')
		return false;

	p = Buff;
	while	(*Path && *Path != '\\')
		*p++ = *Path++;

	*p = '\0';

	NewDirectory = geVFile_Open(FS, Buff, GE_VFILE_OPEN_DIRECTORY);
	if	(!NewDirectory)
	{
		NewDirectory = geVFile_Open(FS, Buff, GE_VFILE_OPEN_CREATE | GE_VFILE_OPEN_DIRECTORY);
		if	(!NewDirectory)
			return false;
	}

	if	(*Path == '\\')
		Path++;

	Res = MakeDirectory(NewDirectory, Path);
	geVFile_Close(NewDirectory);
	return Res;
}

void CRfvfsDlg::CopyFile(const char *srcPath, const char *destPath)
{
	CFile sourceFile;
	CFile destFile;
	BYTE buffer[16384];
	DWORD dwRead;
	
	CWaitCursor c;
	CFileException ex;
	sourceFile.Open(srcPath, CFile::modeRead | CFile::shareDenyWrite, &ex);
	destFile.Open(destPath, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate, &ex);
	do
	{
		dwRead = sourceFile.Read(buffer, 16384);
		destFile.Write(buffer, dwRead);
	}
	while (dwRead > 0);
	
	destFile.Close();
	sourceFile.Close();
}

void CRfvfsDlg::OnCheck1() 
{
	UpdateData();
}

void CRfvfsDlg::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_dirtree.OnDblclk(pNMHDR, pResult);
}
