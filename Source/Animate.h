// Animate.h : main header file for the ANIMATE application
//

#if !defined(AFX_ANIMATE_H__55EF9E14_B1F0_11D2_B024_444553540000__INCLUDED_)
#define AFX_ANIMATE_H__55EF9E14_B1F0_11D2_B024_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAnimateApp:
// See Animate.cpp for the implementation of this class
//

class CAnimateApp : public CWinApp
{
public:
	CAnimateApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimateApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAnimateApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATE_H__55EF9E14_B1F0_11D2_B024_444553540000__INCLUDED_)
