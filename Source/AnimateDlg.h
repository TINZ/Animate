// AnimateDlg.h : header file
//

#if !defined(AFX_ANIMATEDLG_H__55EF9E16_B1F0_11D2_B024_444553540000__INCLUDED_)
#define AFX_ANIMATEDLG_H__55EF9E16_B1F0_11D2_B024_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

// ** Vectors and file input

#include "Environment.h"	// for enumerations
#include "DataStructures.h"
#include "Administrator.h"
#include "MapEditor.h"
#include "CDib.h"
#include <vector>
//#include <algorithm>
#include <fstream>
using namespace std;

// ** Constants

const short OBJECT_SIZE = 10;
const CString SM_WAIT = "Waiting";
const CString SM_LOAD = "Loading a Script";
const CString SM_SAVE = "Saving a Script";
const CString SM_PLAY = "Running Animation";
const CString SM_SCEN = "Running Scenario";
const CString SM_STEP = "Stepping Frames";
const CString SM_RESET = "Reset Frames";
const CString SM_PLS_LOAD = "!No Scenario Data";
const CString SM_PAUSE = "Scenario Paused";
const CString SM_PATHS = "Agents' Paths Revealed";
const CString SM_JUMP = "Jump to a Frame";
const CString SM_AUTO = "Auto-Saving Script";

/////////////////////////////////////////////////////////////////////////////
// CAnimateDlg dialog

class CAnimateDlg : public CDialog
{
// Construction
public:
	CAnimateDlg(CWnd* pParent = NULL);	// standard constructor

	// ** my bits
	
	SCRIPT m_script;			// list of objects for animation script
	short m_border;				// border for scene area
	bool m_draw_scene;			// whether we want to draw anim auto
	bool m_run_animate;			// whether we are running a scenario and
								// animating at the same time
	bool m_run_scenario;		// is a scenario running
	short m_current_iter;		// current experiment iteration
	long m_index;				// index over m_script
	long m_script_size;			// length of vector m_script
	long m_current_frame;		// current frame being viewed
	long m_max_frame;			// max frames in m_script
	short m_mining_agents;		// number of mining agents
	short m_predator_agents;	// number of predator agents
	short m_prey_agents;		// number of prey agents
	short m_miner_vis;			// mining agents visual range
	short m_predator_vis;		// predator agents visual range
	short m_prey_vis;			// prey agents visual range
	short m_miner_grab;			// mining agents grab capacity
	short m_miner_sack;			// mining agents sack capacity
	short m_current_turn;		// current turn in scenario
	int m_anim_speed;			// animation speed
	short m_mouse_x;			// mouse x relative to map
	short m_mouse_y;			// mouse y relative to map
	short m1,m2,m3,m4,m5,m6,m7,m8,m9;	// script processing
	Administrator m_admin;		// the scenario administrator
	Grid m_q;					// object quantities for each frame
	short m_tagged;				// id of agent tagged
	SCENARIO_DATA m_scenario_data;	// scenario data structure
	bool m_exploration;			// whether agents explore map
	FRAMES m_frame_index;		// index of frame start positions
	bool m_trail_toggle;
	long m_count;
	long m_count2;
	CDC m_dcObject;
	CDC m_dcBack;
	CDC m_dcScreen;

	// button bitmaps

	CBitmapButton m_button_play;
	CBitmapButton m_button_stop;
	CBitmapButton m_button_step_f;
	CBitmapButton m_button_step_b;
	CBitmapButton m_button_reset_b;
	CBitmapButton m_button_reset_f;
	CBitmapButton m_button_path;
	CBitmapButton m_button_jump;
	CBitmapButton m_button_load;
	CBitmapButton m_button_save;
	CBitmapButton m_button_map;
	CBitmapButton m_button_run;
	CBitmapButton m_button_runa;
	CBitmapButton m_button_pause;
	CBitmapButton m_button_kill;

	CBitmap m_bitmap;			// for animation - a bitmap buffer
	CBitmap m_static_bitmap;	// buffer for obstacles that don't move
	CBitmap m_objects;			// buffer for objects

	char m_temp[10];				// used extensively for conversions
	void make_bitmap();								// setup the screen bitmap
	void make_bitmap_background(Environment &e);	// setup the static bitmap
	void update_frame();							// draw next frame
	void compute_paths();							// show agents paths
	void compute_trails();
	void setup_scenario();							// start a scenario
	void execute_scenario_turn();					// do a turn - see WM_TIMER
	void finish_scenario_execution();				// tidy up after scenario completion
	void auto_save_script();						// saves script when iterations > 1
	void go_back_one_frame();
	void redraw_frame();
	void seek_frame(const int pos);
	void build_frame_index();
	void extract_data_from_script();
	void cleanup(); // delete objects before exit
	
// Dialog Data
	//{{AFX_DATA(CAnimateDlg)
	enum { IDD = IDD_ANIMATE_DIALOG };
	CSliderCtrl	m_slider_tagged;
	CSliderCtrl	m_slider_speed;
	CProgressCtrl	m_scenario_progress;// progress control instance
	CString	m_current;					// text output of current frame
	CString	m_max;						// text output of max frames
	CString	m_status;					// text output of system status
	short	m_turns;					// scenario turns
	short	m_iterations;				// scenario iterations
	CString	m_scenario_map_filename;	// filename for scenario map
	short	m_agent_no;					// number of agents
	short	m_vis_no;					// agent visual range
	short	m_grab_no;					// amount agent can grab
	short	m_sack_no;					// agent sack capacity
	int		m_agent_selected;			// type of agent selected
	CString	m_text_obj_quantity;
	BOOL	m_tagging;
	CString	m_text_agent_tagged;
	int		m_scenario_type;
	CString	m_agent_action;
	BOOL	m_agent_fov;
	BOOL	m_explore_map;
	int		m_frame_jump;
	short	m_pred_stom_max;
	short	m_pred_stom_init;
	short	m_density;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	
	// Generated message map functions
	//{{AFX_MSG(CAnimateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLoad();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnStepF();
	afx_msg void OnStepB();
	afx_msg void OnReset();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMapEditor();
	afx_msg void OnResetEnd();
	afx_msg void OnRunScenario();
	afx_msg void OnRadioAgentType();
	afx_msg void OnRadioPredators();
	afx_msg void OnRadioPrey();
	afx_msg void OnSave();
	afx_msg void OnChangeEditScenarioMap();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCheckTagging();
	afx_msg void OnRadioSc1();
	afx_msg void OnRadioSc2();
	afx_msg void OnRadioSc3();
	afx_msg void OnRadioSc4();
	afx_msg void OnCheckFov();
	afx_msg void OnCheckExplore();
	afx_msg void OnButtonPaths();
	afx_msg void OnRunAnimate();
	afx_msg void OnPause();
	afx_msg void OnKill();
	afx_msg void OnButtonJump();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnButtonExitApp();
	afx_msg void OnKillfocusEditFrameGet();
	afx_msg void OnKillfocusEditDense();
	afx_msg void OnKillfocusEditTurns();
	afx_msg void OnKillfocusEditIter();
	afx_msg void OnKillfocusEditAgentNo();
	afx_msg void OnKillfocusEditVisRange();
	afx_msg void OnKillfocusEditGrabCap();
	afx_msg void OnKillfocusEditSackCap();
	afx_msg void OnKillfocusEditMaxStom();
	afx_msg void OnKillfocusEditInitStom();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATEDLG_H__55EF9E16_B1F0_11D2_B024_444553540000__INCLUDED_)
