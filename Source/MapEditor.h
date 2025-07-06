#if !defined(AFX_MAPEDITOR_H__7C7EAD6F_B491_11D2_B024_444553540000__INCLUDED_)
#define AFX_MAPEDITOR_H__7C7EAD6F_B491_11D2_B024_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MapEditor.h : header file
//

#include "Environment.h"
#include "Agent.h"			// map validation
#include "CDib.h"

/////////////////////////////////////////////////////////////////////////////
// MapEditor dialog

class MapEditor : public CDialog
{
// Construction
public:
	MapEditor(CWnd* pParent = NULL);   // standard constructor

	Environment m_env;				// data gathering
	Grid m_s;						// map validation (search)
	const CString get_file_name();	// returns last filename saved/loaded
	char m_temp[10];				// used for conversions
	short m_obstacles;				// obstacles in map
	short m_minerals;				// minerals in map
	short m_ore;					// ore in map
	short m_homes;					// home bases in map
	short m_mineral_count;			// mineral worth in map
	short m_ore_count;				// ore worth in map
	short m_total_count;			// mineral worth + ore worth
	short m_grid_x;					// mouse position relative to grid
	short m_grid_y;					// mouse position relative to grid
	CString m_file_name;			// last file opened or saved
	CBitmap m_bitmap;				// bitmap buffer
	CBitmap m_objects;				// object buffer
	PATH m_colour_table;			// vector of colours
	PATH m_search;					// search vector

	void update_frame();								// paint scene
	void make_bitmap();									// create bitmap buffer
	void update_search_memory();						// map validation using search
	void execute_search_flood(short x, short y);		// map validation using search
	
	void illustrate_path();

	bool validate_map();								// validate map
	void update_paths();								// illustrate paths in map
	void fill(const short x, const short y);			// fill with OBSTACLE
	void cleanup();

	void update_fields();								// update data

	CBitmapButton m_button_load;
	CBitmapButton m_button_save;
	CBitmapButton m_button_rand_o;
	CBitmapButton m_button_clear_o;
	CBitmapButton m_button_rand_m;
	CBitmapButton m_button_clear_m;
	CBitmapButton m_button_rand_ore;
	CBitmapButton m_button_clear_ore;
	CBitmapButton m_button_clear_h;
	CBitmapButton m_button_rand_q;
	CBitmapButton m_button_level;
	CBitmapButton m_button_valid;
	CBitmapButton m_button_reset;
		
// Dialog Data
	//{{AFX_DATA(MapEditor)
	enum { IDD = IDD_MAP_EDITING };
	short	m_edit_quantity;
	CString	m_text_x;
	CString	m_text_y;
	CString	m_count_obstacles;
	CString	m_count_minerals;
	CString	m_count_homes;
	int		m_object_paint;
	CString	m_count_ore;
	CString	m_mineral_worth;
	CString	m_ore_worth;
	CString	m_total_worth;
	short	m_rand_min;
	short	m_rand_max;
	BOOL	m_show_paths;
	BOOL	m_set_starts;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MapEditor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(MapEditor)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRandObstacles();
	afx_msg void OnRandMinerals();
	afx_msg void OnClearObstacles();
	afx_msg void OnClearMinerals();
	afx_msg void OnRandQuantity();
	afx_msg void OnSaveGrid();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLoadGrid();
	afx_msg void OnResetAllMap();
	afx_msg void OnRadioObstacles();
	afx_msg void OnRadioMinerals();
	afx_msg void OnRadioOre();
	afx_msg void OnRadioHomes();
	afx_msg void OnRadioSetQuantity();
	afx_msg void OnRandOre();
	afx_msg void OnClearOre();
	afx_msg void OnClearHomes();
	afx_msg void OnButtonValidate();
	afx_msg void OnButtonLevelQuan();
	afx_msg void OnCheckPaths();
	virtual void OnOK();
	afx_msg void OnButtonOk();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void OnCancel();
	afx_msg void OnCheckStarts();
	afx_msg void OnKillfocusEditSeeQuantity();
	afx_msg void OnKillfocusEditRandMin();
	afx_msg void OnKillfocusEditRandMax();
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPEDITOR_H__7C7EAD6F_B491_11D2_B024_444553540000__INCLUDED_)
