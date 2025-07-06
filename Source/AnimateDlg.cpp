// AnimateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Animate.h"
#include "AnimateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimateDlg dialog

CAnimateDlg::CAnimateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnimateDlg)
	m_current = _T("");
	m_max = _T("");
	m_status = _T("");
	m_turns = 0;
	m_iterations = 0;
	m_scenario_map_filename = _T("");
	m_agent_no = 0;
	m_vis_no = 0;
	m_grab_no = 0;
	m_sack_no = 0;
	m_agent_selected = -1;
	m_text_obj_quantity = _T("");
	m_tagging = FALSE;
	m_text_agent_tagged = _T("");
	m_scenario_type = -1;
	m_agent_action = _T("");
	m_agent_fov = FALSE;
	m_explore_map = FALSE;
	m_frame_jump = 0;
	m_pred_stom_max = 0;
	m_pred_stom_init = 0;
	m_density = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	// my variable etc.
	m_script.clear();
	m_frame_index.clear();
	m_border = 0;				// border for scene area
	m_draw_scene = false;		// whether we want to draw anim auto
	m_run_animate = false;			// whether we are running a scenario and
								// animating at the same time
	m_run_scenario = false;		// is a scenario running
	m_current_iter = 0;		// current experiment iteration
	m_index = 0;				// index over m_script
	m_script_size = 0;			// length of vector m_script
	m_current_frame = 0;		// current frame being viewed
	m_max_frame = 0;			// max frames in m_script
	m_mining_agents = 0;		// number of mining agents
	m_predator_agents = 0;	// number of predator agents
	m_prey_agents = 0;		// number of prey agents
	m_miner_vis = 0;			// mining agents visual range
	m_predator_vis = 0;		// predator agents visual range
	m_prey_vis = 0;			// prey agents visual range
	m_miner_grab = 0;			// mining agents grab capacity
	m_miner_sack = 0;			// mining agents sack capacity
	m_current_turn = 0;		// current turn in scenario
	m_anim_speed = 0;			// animation speed
	m_mouse_x = 0;			// mouse x relative to map
	m_mouse_y = 0;			// mouse y relative to map
	m1 = 0;
	m2 = 0;
	m3 = 0;
	m4 = 0;
	m5 = 0;
	m6 = 0;
	m7 = 0;
	m8 = 0;
	m9 = 0;	// script processing
	m_q.wipe(0);					// object quantities for each frame
	m_tagged = 0;				// id of agent tagged
	m_scenario_data.total_agents = 0;
	m_scenario_data.mining_agents = 0;
	m_scenario_data.predator_agents = 0;
	m_scenario_data.prey_agents = 0;
	m_scenario_data.miner_vis = 0;
	m_scenario_data.predator_vis = 0;
	m_scenario_data.prey_vis = 0;
	m_scenario_data.miner_grab = 0;
	m_scenario_data.miner_sack = 0;
	m_scenario_data.pred_stom_m = 0;
	m_scenario_data.pred_stom_i = 0;
	m_scenario_data.turns = 0;
	m_scenario_data.scenario_type = 0;
	m_scenario_data.exploring = true;
	m_exploration = false;			// whether agents explore map
	m_trail_toggle = false;
	m_count = 0;
	m_count2 = 0;
	
}

void CAnimateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimateDlg)
	DDX_Control(pDX, IDC_SLIDER_TAGGING, m_slider_tagged);
	DDX_Control(pDX, IDC_SLIDER_SPEED, m_slider_speed);
	DDX_Control(pDX, IDC_PROGRESS_SCEN, m_scenario_progress);
	DDX_Text(pDX, IDC_C_FRAME, m_current);
	DDV_MaxChars(pDX, m_current, 10);
	DDX_Text(pDX, IDC_M_FRAME, m_max);
	DDV_MaxChars(pDX, m_max, 10);
	DDX_Text(pDX, IDC_STATUS, m_status);
	DDV_MaxChars(pDX, m_status, 40);
	DDX_Text(pDX, IDC_EDIT_TURNS, m_turns);
	DDV_MinMaxInt(pDX, m_turns, 5, 5000);
	DDX_Text(pDX, IDC_EDIT_ITER, m_iterations);
	DDV_MinMaxInt(pDX, m_iterations, 1, 500);
	DDX_Text(pDX, IDC_EDIT_SCENARIO_MAP, m_scenario_map_filename);
	DDV_MaxChars(pDX, m_scenario_map_filename, 200);
	DDX_Text(pDX, IDC_EDIT_AGENT_NO, m_agent_no);
	DDV_MinMaxInt(pDX, m_agent_no, 1, 200);
	DDX_Text(pDX, IDC_EDIT_VIS_RANGE, m_vis_no);
	DDV_MinMaxInt(pDX, m_vis_no, 2, 20);
	DDX_Text(pDX, IDC_EDIT_GRAB_CAP, m_grab_no);
	DDV_MinMaxInt(pDX, m_grab_no, 1, 1000);
	DDX_Text(pDX, IDC_EDIT_SACK_CAP, m_sack_no);
	DDV_MinMaxInt(pDX, m_sack_no, 1, 30000);
	DDX_Radio(pDX, IDC_RADIO_AGENT_TYPE, m_agent_selected);
	DDX_Text(pDX, IDC_TEXT_OBJ_QUANTITY, m_text_obj_quantity);
	DDV_MaxChars(pDX, m_text_obj_quantity, 10);
	DDX_Check(pDX, IDC_CHECK_TAGGING, m_tagging);
	DDX_Text(pDX, IDC_TEXT_AGENT_TAGGED, m_text_agent_tagged);
	DDV_MaxChars(pDX, m_text_agent_tagged, 5);
	DDX_Radio(pDX, IDC_RADIO_SC1, m_scenario_type);
	DDX_Text(pDX, IDC_TEXT_AGENT_ACTION, m_agent_action);
	DDX_Check(pDX, IDC_CHECK_FOV, m_agent_fov);
	DDX_Check(pDX, IDC_CHECK_EXPLORE, m_explore_map);
	DDX_Text(pDX, IDC_EDIT_FRAME_GET, m_frame_jump);
	DDV_MinMaxInt(pDX, m_frame_jump, 1, 2100000);
	DDX_Text(pDX, IDC_EDIT_MAX_STOM, m_pred_stom_max);
	DDX_Text(pDX, IDC_EDIT_INIT_STOM, m_pred_stom_init);
	DDX_Text(pDX, IDC_EDIT_DENSE, m_density);
	DDV_MinMaxInt(pDX, m_density, 0, 32700);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAnimateDlg, CDialog)
	//{{AFX_MSG_MAP(CAnimateDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_STEP_F, OnStepF)
	ON_BN_CLICKED(IDC_STEP_B, OnStepB)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_BN_CLICKED(IDC_MAP_EDITOR, OnMapEditor)
	ON_BN_CLICKED(IDC_RESET_END, OnResetEnd)
	ON_BN_CLICKED(IDC_RUN_SCENARIO, OnRunScenario)
	ON_BN_CLICKED(IDC_RADIO_AGENT_TYPE, OnRadioAgentType)
	ON_BN_CLICKED(IDC_RADIO_PREDATORS, OnRadioPredators)
	ON_BN_CLICKED(IDC_RADIO_PREY, OnRadioPrey)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_EN_CHANGE(IDC_EDIT_SCENARIO_MAP, OnChangeEditScenarioMap)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_CHECK_TAGGING, OnCheckTagging)
	ON_BN_CLICKED(IDC_RADIO_SC1, OnRadioSc1)
	ON_BN_CLICKED(IDC_RADIO_SC2, OnRadioSc2)
	ON_BN_CLICKED(IDC_RADIO_SC3, OnRadioSc3)
	ON_BN_CLICKED(IDC_RADIO_SC4, OnRadioSc4)
	ON_BN_CLICKED(IDC_CHECK_FOV, OnCheckFov)
	ON_BN_CLICKED(IDC_CHECK_EXPLORE, OnCheckExplore)
	ON_BN_CLICKED(IDC_BUTTON_PATHS, OnButtonPaths)
	ON_BN_CLICKED(IDC_RUN_ANIMATE, OnRunAnimate)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_KILL, OnKill)
	ON_BN_CLICKED(IDC_BUTTON_JUMP, OnButtonJump)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_EXIT_APP, OnButtonExitApp)
	ON_EN_KILLFOCUS(IDC_EDIT_FRAME_GET, OnKillfocusEditFrameGet)
	ON_EN_KILLFOCUS(IDC_EDIT_DENSE, OnKillfocusEditDense)
	ON_EN_KILLFOCUS(IDC_EDIT_TURNS, OnKillfocusEditTurns)
	ON_EN_KILLFOCUS(IDC_EDIT_ITER, OnKillfocusEditIter)
	ON_EN_KILLFOCUS(IDC_EDIT_AGENT_NO, OnKillfocusEditAgentNo)
	ON_EN_KILLFOCUS(IDC_EDIT_VIS_RANGE, OnKillfocusEditVisRange)
	ON_EN_KILLFOCUS(IDC_EDIT_GRAB_CAP, OnKillfocusEditGrabCap)
	ON_EN_KILLFOCUS(IDC_EDIT_SACK_CAP, OnKillfocusEditSackCap)
	ON_EN_KILLFOCUS(IDC_EDIT_MAX_STOM, OnKillfocusEditMaxStom)
	ON_EN_KILLFOCUS(IDC_EDIT_INIT_STOM, OnKillfocusEditInitStom)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimateDlg message handlers

BOOL CAnimateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	// autoload custom button bitmaps
	VERIFY(m_button_play.AutoLoad(IDC_PLAY, this));
	VERIFY(m_button_stop.AutoLoad(IDC_STOP, this));
	VERIFY(m_button_step_f.AutoLoad(IDC_STEP_F, this));
	VERIFY(m_button_step_b.AutoLoad(IDC_STEP_B, this));
	VERIFY(m_button_reset_b.AutoLoad(IDC_RESET, this));
	VERIFY(m_button_reset_f.AutoLoad(IDC_RESET_END, this));
	VERIFY(m_button_path.AutoLoad(IDC_BUTTON_PATHS, this));
	VERIFY(m_button_jump.AutoLoad(IDC_BUTTON_JUMP, this));
	VERIFY(m_button_load.AutoLoad(IDC_LOAD, this));
	VERIFY(m_button_save.AutoLoad(IDC_SAVE, this));
	VERIFY(m_button_map.AutoLoad(IDC_MAP_EDITOR, this));
	VERIFY(m_button_run.AutoLoad(IDC_RUN_SCENARIO, this));
	VERIFY(m_button_runa.AutoLoad(IDC_RUN_ANIMATE, this));
	VERIFY(m_button_pause.AutoLoad(IDC_PAUSE, this));
	VERIFY(m_button_kill.AutoLoad(IDC_KILL, this));

	// initialise scenario data structure
	m_scenario_data.total_agents = 0;
	m_scenario_data.mining_agents = 0;
	m_scenario_data.predator_agents = 0;
	m_scenario_data.prey_agents = 0;
	m_scenario_data.miner_vis = 0;
	m_scenario_data.predator_vis = 0;
	m_scenario_data.prey_vis = 0;
	m_scenario_data.miner_grab = 0;
	m_scenario_data.miner_sack = 0;
	m_scenario_data.pred_stom_m = 0;
	m_scenario_data.pred_stom_i = 0;
	m_scenario_data.turns = 0;
	m_scenario_data.scenario_type = 0;
	m_scenario_data.exploring = true;
	
	// set path/trail toggle
	m_trail_toggle = false;

	// set exploration off
	m_exploration = false;
	m_explore_map = FALSE;	// can't cast between bool/BOOL so we use 2

	// set animations and scenario running to off
	m_run_animate = false;
	m_run_scenario = false;
	m_draw_scene = false;

	// set agent field of view(FOV) to off
	m_agent_fov = FALSE;

	// set density
	m_density = 0;

	// initialise current turn
	m_current_turn = 0;

	// setup progress bar
	m_scenario_progress.SetStep(1);
	m_scenario_progress.SetPos(0);
	m_slider_speed.SetRange(1,2000,true);
	m_slider_speed.SetTicFreq(250);
	m_slider_speed.SetPos(300);

	// set tagged slider bar
	m_slider_tagged.SetRange(0,1,true);
	m_slider_tagged.SetPos(0);
	m_text_agent_tagged = "0";

	// set default anim speed
	m_anim_speed = 300;

	// reset quantity grid
	m_q.metamorphose(40);

	// set tagging to off
	m_tagging = FALSE;
	m_tagged = 0;

	// Install a timer
	if(SetTimer(1,m_anim_speed,NULL) == 0)

	{

		MessageBox("Unable to install a system timer.\nThe system is too busy.\nAnimate will terminate.");
		cleanup();
		CDialog::OnOK();

	}

	m_index = 0;				// current position in m_script
	m_script_size = 0;			// size of m_script
	m_current_frame = 0;		// current anim frame
	m_max_frame = 0;			// max anim frames
	m_border = 10;				// border from top-left of window
	m_turns = 100;				// set default scenario turns
	m_iterations = 1;			// set default iterations
	m_scenario_type = 0;		// type of scenario - default is basic mining
	m_mining_agents = 1;		// number of default mining agents
	m_predator_agents = 1;		// number of default predator agents
	m_prey_agents = 1;			// number of default prey agents
	m_miner_vis = 4;			// default mining agents visual range
	m_predator_vis = 8;			// default predator agents visual range
	m_prey_vis = 4;				// default prey agents visual range
	m_miner_grab = 10;			// default mining agents grab capacity
	m_miner_sack = 50;			// default mining agents sack capacity
	m_pred_stom_max = 10;		// default predator max stomach
	m_pred_stom_init = 0;		// default predator initial stomach

	m_agent_no = 1;				// default number of agents
	m_vis_no = 4;				// default miner vision
	m_grab_no = 10;				// default miner grab capacity
	m_sack_no = 50;				// default miner sack capacity
	m_agent_selected = 0;		// default type of agent selected - miners
	m_mouse_x = 0;				// mouse coordinates
	m_mouse_y = 0;				// mouse coordinates

	// set frame jump location
	m_frame_jump = 1;
		
	// make pause scenario button inactive
	GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
	
	// make halt scenario button inactive
	GetDlgItem(IDC_KILL)->EnableWindow(FALSE);
	
	// update frame data
	_itoa(m_max_frame,m_temp,10);
	m_max = m_temp;
	_itoa(m_current_frame,m_temp,10);
	m_current = m_temp;
	m_status = SM_WAIT;
	
	UpdateData(FALSE);

	// set radio button visual context
	OnRadioSc1();

	// setup the bitmap buffers
	make_bitmap();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAnimateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAnimateDlg::OnPaint() 
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
		
		// WE ONLY NEED TO DRAW THE BITMAP BUFFER

		if(m_bitmap.m_hObject == NULL)

		{

			CDialog::OnPaint();	
			return;// bitmap not made yet
				
		}
		
		CClientDC dc(this);

		// not using private member dc's
		CDC dcScreen;

		CBitmap *pOldScreen = NULL;
		
		dcScreen.CreateCompatibleDC(&dc);	// make compatible
			
		pOldScreen = dcScreen.SelectObject(&m_bitmap);
				
		// blit current screen bitmap to screen
		dc.BitBlt(10,10,400,400,&dcScreen,0,0,SRCCOPY);

		// reselect stuff and kill memory dc
		dcScreen.SelectObject(pOldScreen);
		dcScreen.DeleteDC();
						
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAnimateDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAnimateDlg::OnLoad() 
{
	// TODO: Add your control notification handler code here

	// cancel animation
	m_draw_scene = false;

	// do dialog
	CString filter = "Animate Data Files (*.data)|*.data|All Files (*.*)|*.*||";
	CFileDialog dlg(TRUE,"data","*.data",OFN_HIDEREADONLY,filter);
	
	CString scriptfile;
	CString datafile;
	CString mapfile;
	CString autofile;
	int pos = -1;
	
	if(dlg.DoModal() != IDOK)
		
	{
		
		return;
		
	}

	// get file path and name
	scriptfile = dlg.GetPathName();
	pos = scriptfile.Find("_SC");
	
	// check if file was auto-generated by this app
	if(pos != -1)

	{	// create correct ".data" filename

		autofile = scriptfile.Left(pos);
		datafile = autofile;
		datafile += ".datad";
		mapfile = autofile;
		mapfile += ".map";

	}

	else

	{
	
		// work out file names
		pos = scriptfile.Find(".");
		mapfile = scriptfile.Left(pos);
		datafile = mapfile;
		mapfile += ".map";
		datafile += ".datad";
		
	}
	
	// one file for script, other for script data, other for map
	ifstream in1(scriptfile, ios::binary);
	ifstream in2(datafile, ios::in);
	ifstream in3(mapfile, ios::in);
	
	if(!in1)

	{

		MessageBox("Unable to open the script file " + scriptfile);
		in1.close();
		return;

	}

	if(!in2)

	{

		MessageBox("Unable to open the data file " + datafile);
		in2.close();
		return;

	}
	
	if(!in3)

	{

		MessageBox("Unable to open the map file " + mapfile);
		in3.close();
		return;

	}
	
	// tell user were loading
	m_status = SM_LOAD;
	UpdateData(FALSE);

	BeginWaitCursor();
	// setup bitmap buffers
	// get data and draw static objects
	
	Environment e(40);
	e.input_objects(in3);

	if(!e.get_state())

	{

		EndWaitCursor();
		MessageBox("The map file associated with this script could not be loaded correctly");
		in3.close();
		m_status = SM_WAIT;
		UpdateData(FALSE);
		return;

	}

	in3.close();

	// do back buffer
	make_bitmap_background(e);
		
	// now get the scenario data
		
	in2.read(reinterpret_cast<char *>(&m_scenario_data),sizeof(SCENARIO_DATA));

	if(!in2)

	{

		EndWaitCursor();
		MessageBox("The scenario data could not be read correctly");
		in2.close();
		m_status = SM_WAIT;
		UpdateData(FALSE);
		return;

	}

	in2.close();

	// now get script

	chunk p;
	
	// erase old script
	m_script.erase(m_script.begin(), m_script.end());

	// get scenario data

	in1.read(reinterpret_cast<char *>(&p),sizeof(chunk));
		
	while(!in1.eof())

	{

		if(!in1)

		{

			EndWaitCursor();
			MessageBox("The script data could not be read correctly");
			in1.close();
			m_script.erase(m_script.begin(), m_script.end());
			m_status = SM_WAIT;
			UpdateData(FALSE);
			return;

		}

		m_script.push_back(p);
		in1.read(reinterpret_cast<char *>(&p),sizeof(chunk));
	
	};

	in1.close();

	// we have successfully loaded, so setup
	
	// get size of vector and setup animation parameters
	m_script_size = (long)m_script.size();
	build_frame_index();
	m_frame_jump = 1;
	// update windows with animation data
				
	m_scenario_type = m_scenario_data.scenario_type;

	switch(m_scenario_type)

	{

	case 0:	// MINERS

		m_agent_no = m_scenario_data.mining_agents; 
		m_vis_no = m_scenario_data.miner_vis;
		m_grab_no = m_scenario_data.miner_grab;
		m_sack_no = m_scenario_data.miner_sack;
		m_mining_agents = m_agent_no;
		m_miner_vis = m_vis_no;
		m_miner_grab = m_grab_no;
		m_miner_sack = m_sack_no;
		m_agent_selected = 0;
		break;

	case 1:	//CHAIN MINERS

		m_agent_no = m_scenario_data.mining_agents; 
		m_vis_no = m_scenario_data.miner_vis;
		m_grab_no = m_scenario_data.miner_grab;
		m_sack_no = m_scenario_data.miner_sack;
		m_mining_agents = m_agent_no;
		m_miner_vis = m_vis_no;
		m_miner_grab = m_grab_no;
		m_miner_sack = m_sack_no;
		m_agent_selected = 0;
		break;

	case 2:	// pred & prey

		m_agent_no = m_scenario_data.predator_agents; 
		m_vis_no = m_predator_vis;
		m_grab_no = 10;
		m_sack_no = 50;
		m_prey_agents = m_scenario_data.prey_agents;
		m_predator_agents = m_scenario_data.predator_agents;
		m_prey_vis = m_scenario_data.prey_vis;
		m_predator_vis = m_scenario_data.predator_vis;
		m_pred_stom_max = m_scenario_data.pred_stom_m;
		m_pred_stom_init = m_scenario_data.pred_stom_i;
		m_agent_selected = 1;
		break;

	case 3://crowds

		m_agent_no = m_scenario_data.mining_agents; 
		m_vis_no = m_scenario_data.miner_vis;
		m_grab_no = 1;
		m_sack_no = 1;
		m_mining_agents = m_agent_no;
		m_miner_vis = m_vis_no;
		m_miner_grab = m_grab_no;
		m_miner_sack = m_sack_no;
		m_agent_selected = 0;
		break;
	
	default:

		break;

	};

	m_turns = m_scenario_data.turns;
	m_slider_tagged.SetRange(0,(m_scenario_data.total_agents)-1,true);
	m_slider_tagged.SetPos(0);
	m_text_agent_tagged = "0";
		
	m_max_frame = m_turns;
	_itoa(m_max_frame,m_temp,10);
	m_max = m_temp;
	m_exploration = m_scenario_data.exploring;
	m_scenario_map_filename = mapfile;
	m_status = SM_WAIT;
	
	UpdateData(FALSE);

	// set radio button visual context
	OnRadioSc1();
		
	CAnimateDlg::OnReset();	// update frame counts and display first frame
	
	SetWindowText("Animate: " + scriptfile + ", " + mapfile);

	EndWaitCursor();

	MessageBox("Script file " + scriptfile + " loaded successfully");
	
}

void CAnimateDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	// if we are animating then draw next frame
	if(m_draw_scene)

	{
		
		update_frame();
	
	}

	// if running a scenario, do next turn
	if(m_run_scenario)

	{

		execute_scenario_turn();

	}
	
	//CDialog::OnTimer(nIDEvent);
}


void CAnimateDlg::OnPlay() 
{
	// TODO: Add your control notification handler code here

	if(m_script_size == 0)

	{

		MessageBox("Please load or create a script from a scenario");
		m_status = SM_PLS_LOAD;

	}

	else

	{

		m_draw_scene = true;
		m_status = SM_PLAY;

	}

	UpdateData(FALSE);
	
}

void CAnimateDlg::OnStop() 
{
	// TODO: Add your control notification handler code here

	if(m_script_size == 0)

	{

		MessageBox("Please load or create a script from a scenario");
		m_status = SM_PLS_LOAD;

	}

	else

	{

		m_draw_scene = false;
		m_status = SM_WAIT;

	}

	UpdateData(FALSE);
	
}

void CAnimateDlg::OnStepF() 
{
	// TODO: Add your control notification handler code here

	if(m_script_size == 0)

	{

		MessageBox("Please load or create a script from a scenario");
		m_status = SM_PLS_LOAD;

	}

	else

	{

		m_draw_scene = false;
		m_status = SM_STEP;
		update_frame();
		
	}

	UpdateData(FALSE);
		
}

void CAnimateDlg::OnStepB() 
{
	// TODO: Add your control notification handler code here
	if(m_script_size == 0)

	{

		MessageBox("Please load or create a script from a scenario");
		m_status = SM_PLS_LOAD;

	}
	
	else

	{

		
		m_draw_scene = false;
		go_back_one_frame();
		m_status = SM_STEP;
	
	}
	
	UpdateData(FALSE);
	
}

void CAnimateDlg::OnReset() 
{
	// TODO: Add your control notification handler code here
	if(m_script_size == 0)

	{

		MessageBox("Please load or create a script from a scenario");
		m_status = SM_PLS_LOAD;
		UpdateData(FALSE);
		return;

	}

	else

	{

		m_draw_scene = false;
		m_current_frame = 0;
		m_index = 0;
		m_status = SM_RESET;
		update_frame();

	}
		
}

void CAnimateDlg::OnOK() 
{
	// TODO: Add extra validation here

	NextDlgCtrl();
	
	//CDialog::OnOK();
}

void CAnimateDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	cleanup();
	CDialog::OnCancel();
}

void CAnimateDlg::OnMapEditor() 
{
	// TODO: Add your control notification handler code here

	// stop animating
	m_draw_scene = false;

	MapEditor map;

	if(map.DoModal() == IDOK)

	{
	
		m_scenario_map_filename = map.get_file_name();
		UpdateData(FALSE);
	
	}
	
}

void CAnimateDlg::OnResetEnd() 
{
	// TODO: Add your control notification handler code here
	if(m_script_size == 0)

	{

		MessageBox("Please load or create a script from a scenario");
		m_status = SM_PLS_LOAD;
		UpdateData(FALSE);
		return;

	}

	else

	{
	
		m_draw_scene = false;
		seek_frame(m_max_frame);
		m_status = SM_RESET;
		
	}
				
}

void CAnimateDlg::OnRunScenario() 
{
	// TODO: Add your control notification handler code here

	setup_scenario();
					
}

void CAnimateDlg::OnRadioAgentType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	switch(m_agent_selected)

	{

	case 0:	// mining agents

		m_agent_no = m_mining_agents;
		m_vis_no = m_miner_vis;
		m_grab_no = m_miner_grab;
		m_sack_no = m_miner_sack;
		GetDlgItem(IDC_EDIT_MAX_STOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_INIT_STOM)->EnableWindow(FALSE);
				
		if(m_scenario_type <= 1)

		{
		
			GetDlgItem(IDC_EDIT_GRAB_CAP)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_SACK_CAP)->EnableWindow(TRUE);

		}

		else

		{

			GetDlgItem(IDC_EDIT_GRAB_CAP)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SACK_CAP)->EnableWindow(FALSE);

		}
		
		break;

	case 1: // predators

		m_agent_no = m_predator_agents;
		m_vis_no = m_predator_vis;
		GetDlgItem(IDC_EDIT_GRAB_CAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SACK_CAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MAX_STOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_INIT_STOM)->EnableWindow(TRUE);
		break;

	case 2:	// prey

		m_agent_no = m_prey_agents;
		m_vis_no = m_prey_vis;
		GetDlgItem(IDC_EDIT_GRAB_CAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SACK_CAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MAX_STOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_INIT_STOM)->EnableWindow(FALSE);
		break;

	};

	UpdateData(FALSE);
	
}

void CAnimateDlg::OnRadioPredators() 
{
	// TODO: Add your control notification handler code here
	CAnimateDlg::OnRadioAgentType();
	
}

void CAnimateDlg::OnRadioPrey() 
{
	// TODO: Add your control notification handler code here
	CAnimateDlg::OnRadioAgentType();
}

void CAnimateDlg::OnSave() 
{
	// TODO: Add your control notification handler code here

	// cancel any animation
	m_draw_scene = false;

	if(m_script_size == 0)

	{

		MessageBox("No script to be saved");
		return;

	}
	
	CString filter = "Animate Data Files (*.data)|*.data|All Files (*.*)|*.*||";
	CFileDialog dlg(FALSE,"data","untitled.data",OFN_HIDEREADONLY,filter);
	
	if(dlg.DoModal() != IDOK)
		
	{
		
		return;
		
	}
	
	CString file = dlg.GetPathName();

	// check that correct extension
	CString ext = file.Right(4);

	if(ext != "data")

	{

		MessageBox("Incorrect file extension (" + ext + "), please use (data)");
		return;

	}

	// check that a map file exists
	CString mapdest = file.Left(file.Find('.'));
	mapdest += ".map";

	ifstream check(mapdest, ios::in);
	
	if(!check)

	{

		MessageBox("The data file name and map file name must\nbe of the same destination and name. The\nsave operation has failed.");
		check.close();
		return;

	}

	check.close();

	BeginWaitCursor();
	m_status = SM_SAVE;
	UpdateData(FALSE);

	ofstream out1(file, ios::binary);
	ofstream out2(file + "d", ios::out);
	
	if(!out1 || !out2)

	{

		MessageBox("Unable to write the file " + file);
		out1.close();
		out2.close();
		EndWaitCursor();
		m_status = SM_WAIT;
		UpdateData(FALSE);
		return;

	}
		
	// output data struct
	out2.write(reinterpret_cast<const char *>(&m_scenario_data),sizeof(SCENARIO_DATA));
	out2.flush();
	out2.close();

	// tidy the script
	m_script.resize(m_script.size());

	chunk p;
	SCRIPT_IT it;
	
	// output script
	
	for(it = m_script.begin() ; it != m_script.end() ; ++it)

	{
	
		p = *it;
		out1.write(reinterpret_cast<const char *>(&p),sizeof(chunk));
	
	};

	out1.flush();
	out1.close();
	
	EndWaitCursor();
	m_status = SM_WAIT;
	UpdateData(FALSE);
	SetWindowText("Animate: " + file + ", " + mapdest);
			
	MessageBox("Script file " + file + " saved correctly");
	
}

void CAnimateDlg::OnChangeEditScenarioMap() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	
}

void CAnimateDlg::make_bitmap()

{

	if(m_bitmap.m_hObject != NULL)

	{

		m_bitmap.DeleteObject();   // get rid of old bitmap

	}

	if(m_static_bitmap.m_hObject != NULL)

	{

		m_static_bitmap.DeleteObject();   // get rid of old bitmap

	}

	if(m_objects.m_hObject != NULL)

	{

		m_objects.DeleteObject();   // get rid of old bitmap

	}

	// order is important
	CClientDC dc(this);

	m_dcObject.DeleteDC();
	m_dcBack.DeleteDC();
	m_dcScreen.DeleteDC();

	CBitmap *pOldObject = NULL;
	CBitmap *pOldBack = NULL;
	CBitmap *pOldScreen = NULL;
			
	// load object resource - 24bit
	m_objects.LoadBitmap(IDB_OBJECTS);

	// make compatible
	m_dcObject.CreateCompatibleDC(&dc);
	
	// select in
	pOldObject = m_dcObject.SelectObject(&m_objects);

	// make other dc's compatible
	m_dcBack.CreateCompatibleDC(&dc);
	m_dcScreen.CreateCompatibleDC(&dc);
	
	// make other bitmaps
	m_static_bitmap.CreateCompatibleBitmap(&dc,400,400);
	ASSERT(m_static_bitmap.m_hObject != NULL);
	m_bitmap.CreateCompatibleBitmap(&dc,400,400);
	ASSERT(m_bitmap.m_hObject != NULL);
		
	// select in
	pOldBack = m_dcBack.SelectObject(&m_static_bitmap);
	pOldScreen = m_dcScreen.SelectObject(&m_bitmap);

	// make back brush from background of object
	CBrush back_brush(m_dcObject.GetPixel(60,90));	// background
										
	// brush pointer to original
	CBrush* pOriginalBrush = m_dcBack.SelectObject(&back_brush);
	
	// wipe static bitmap background
	CRect rect(0,0,400,400);
	m_dcBack.FillRect(rect,&back_brush);
	m_dcBack.SelectObject(pOriginalBrush);

	// copy back to screen
	m_dcScreen.BitBlt(0,0,400,400,&m_dcBack,0,0,SRCCOPY);

	// select old
	m_dcBack.SelectObject(pOldBack);
	m_dcScreen.SelectObject(pOldScreen);
	m_dcObject.SelectObject(pOldObject);
	
}

void CAnimateDlg::make_bitmap_background(Environment &e)

{

	if(m_objects.m_hObject == NULL || m_static_bitmap.m_hObject == NULL ||
		m_bitmap.m_hObject == NULL)

	{

		return;// bitmap(s) gone!
			
	}
	
	CClientDC dc(this);
	
	m_dcObject.DeleteDC();
	m_dcBack.DeleteDC();
	m_dcScreen.DeleteDC();

	CBitmap *pOldObject = NULL;
	CBitmap *pOldBack = NULL;
	CBitmap *pOldScreen = NULL;
	
	m_dcObject.CreateCompatibleDC(&dc);	// make compatible
	m_dcBack.CreateCompatibleDC(&dc);	// make compatible
	m_dcScreen.CreateCompatibleDC(&dc);	// make compatible
		
	pOldObject = m_dcObject.SelectObject(&m_objects);
	pOldBack = m_dcBack.SelectObject(&m_static_bitmap);
	pOldScreen = m_dcScreen.SelectObject(&m_bitmap);

	// make back brush from background of object
	CBrush back_brush(m_dcObject.GetPixel(60,90));	// background
										
	// brush pointer to original
	CBrush* pOriginalBrush = m_dcBack.SelectObject(&back_brush);
	
	// wipe static bitmap background
	CRect rect(0,0,400,400);
	m_dcBack.FillRect(rect,&back_brush);
	m_dcBack.SelectObject(pOriginalBrush);
	
	// get all OBSTACLES into back buffer
	// quantities in [m_q]

	short x,y,object,quantity;

	for(x = 0 ; x < 40 ; x++)

	{

		for(y = 0 ; y < 40 ; y++)

		{

			// get data
			e.get_object(x,y,object,quantity);
			// record quantity
			m_q.put_f(x,y,quantity);

			// record static objects in back-buffer
			if(object == OBSTACLE)

			{

				m_dcBack.BitBlt(x*10,y*10,10,10,&m_dcObject,10,0,SRCCOPY);
			
			}

		}

	}

	// copy back to screen
	m_dcScreen.BitBlt(0,0,400,400,&m_dcBack,0,0,SRCCOPY);

	// update other dynamic objects remaining in [e]
	// this is so user can see the map to be used
	
	for(x = 0 ; x < 40 ; x++)

	{

		for(y = 0 ; y < 40 ; y++)

		{

			// get data
			if((object = e.get_object_f(x,y)) > OBSTACLE)

			{

				m_dcScreen.BitBlt(x*10,y*10,10,10,&m_dcObject,object*10,0,SRCCOPY);

			}
				
		}

	}

	// update the screen
	dc.BitBlt(10,10,400,400,&m_dcScreen,0,0,SRCCOPY);
	
	// select old
	m_dcObject.SelectObject(pOldObject);
	m_dcBack.SelectObject(pOldBack);
	m_dcScreen.SelectObject(pOldScreen);
		
}

void CAnimateDlg::update_frame()

{

	if(m_objects.m_hObject == NULL || m_static_bitmap.m_hObject == NULL ||
		m_bitmap.m_hObject == NULL || m_script_size == 0)

	{

		return;// bitmap(s) gone!
			
	}
	
	CClientDC dc(this);
	
	CBitmap *pOldObject = NULL;
	CBitmap *pOldBack = NULL;
	CBitmap *pOldScreen = NULL;
	
	pOldObject = m_dcObject.SelectObject(&m_objects);
	pOldBack = m_dcBack.SelectObject(&m_static_bitmap);
	pOldScreen = m_dcScreen.SelectObject(&m_bitmap);
	
	// create a black brush for tagging
	CBrush black_brush(RGB(0,0,0));

	// create pointer
	CBrush *pOriginalBrush;

	// erase quantities
	m_q.wipe(0);	//note we lose values for obstacles
	
	// copy background to screen bitmap
	m_dcScreen.BitBlt(0,0,400,400,&m_dcBack,0,0,SRCCOPY);
	
	if(m_index >= m_script_size)

	{

		m_index = 0;
		m_current_frame = 0;
	
	}

	m_script[m_index].get_frames(m2);
	m_count = m_index + (long)m2;
	m_current_frame++;
	m_index++;	// go past info field
	m_count2 = m_index;
		
	_itoa(m_current_frame,m_temp,10);
	m_current = m_temp;
	
	UpdateData(FALSE);
		
	while(m_index <= m_count)

	{// alive,type,name,xcoord,ycoord,action,quantity,spare,spare

		m_script[m_index].get_anim(m2,m4,m5,m7);
		
		// update quantities
		m_q.put_f(m4/10,m5/10,m7);
		
		if(m2 > OBSTACLE)

		{
			
			m_dcScreen.BitBlt(m4,m5,10,10,&m_dcObject,m2*10,0,SRCCOPY);

		}

		m_index++;
				
	};
	
	if(m_tagging)

	{

		while(m_count2 < m_index)

		{// spare,type,name,xcoord,ycoord,action,quantity,targetx,targety

			m_script[m_count2].get_tagging(m2,m3,m4,m5,m6,m8,m9);

			if(m3 == m_tagged && m2 > OBSTACLE && m2 < MINERAL)
				
			{
			
				pOriginalBrush = m_dcScreen.SelectObject(&black_brush);
				
				if(m2 != CARCASS)

				{
					
					m_dcScreen.Draw3dRect(m8,m9,OBJECT_SIZE,OBJECT_SIZE,RGB(255,255,255),RGB(0,0,0));
				
				}
				
				m_dcScreen.Rectangle(m4+3,m5+3,m4+7,m5+7);
				
				if(m_agent_fov)

				{

					switch(m2)

					{

					case MINER:

						m_dcScreen.Draw3dRect(m4-(m_scenario_data.miner_vis*OBJECT_SIZE),
										m5-(m_scenario_data.miner_vis*OBJECT_SIZE),
										OBJECT_SIZE*(m_scenario_data.miner_vis*2)+OBJECT_SIZE,
										OBJECT_SIZE*(m_scenario_data.miner_vis*2)+OBJECT_SIZE,
										RGB(255,255,255),RGB(0,0,0));
						break;

					case PREDATOR:

						m_dcScreen.Draw3dRect(m4-(m_scenario_data.predator_vis*OBJECT_SIZE),
										m5-(m_scenario_data.predator_vis*OBJECT_SIZE),
										OBJECT_SIZE*(m_scenario_data.predator_vis*2)+OBJECT_SIZE,
										OBJECT_SIZE*(m_scenario_data.predator_vis*2)+OBJECT_SIZE,
										RGB(255,255,255),RGB(0,0,0));
						break;

					case PREY:

						m_dcScreen.Draw3dRect(m4-(m_scenario_data.prey_vis*OBJECT_SIZE),
										m5-(m_scenario_data.prey_vis*OBJECT_SIZE),
										OBJECT_SIZE*(m_scenario_data.prey_vis*2)+OBJECT_SIZE,
										OBJECT_SIZE*(m_scenario_data.prey_vis*2)+OBJECT_SIZE,
										RGB(255,255,255),RGB(0,0,0));
						break;

					default:

						break;

					};


				}

				m_dcScreen.SelectObject(pOriginalBrush);
				
				switch(m6)

				{

				case MOVE:

					m_agent_action = "Moving to a target";
					break;

				case GRAB:

					m_agent_action = "Collecting a Resource";
					break;

				case DROP:

					m_agent_action = "Dropping a Resource";
					break;

				case POUNCE:

					m_agent_action = "Pouncing on Prey";
					break;

				case JUMP:

					m_agent_action = "Leaping to Safety";
					break;

				case NOTHING:

					m_agent_action = "Idle";
					break;

				default:

					m_agent_action = "** Undefined **";
					break;

				};

				UpdateData(FALSE);
				break;

			}

			m_count2++;
					
		};

	}

	else

	{

		m_agent_action = "Tagging inactive";
		UpdateData(FALSE);

	}

	// blit to screen
	dc.BitBlt(10,10,400,400,&m_dcScreen,0,0,SRCCOPY);
	
	// clean up
	m_dcObject.SelectObject(pOldObject);
	m_dcBack.SelectObject(pOldBack);
	m_dcScreen.SelectObject(pOldScreen);

	// set quantities pointed to by mouse
	if(m_q.check(m_mouse_x,m_mouse_y))

	{
		
		_itoa(m_q.get_f(m_mouse_x,m_mouse_y), m_temp, 10);
		m_text_obj_quantity = m_temp;
		UpdateData(FALSE);
		
	}
	
}

void CAnimateDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	m_mouse_x = (short)point.x;
	m_mouse_y = (short)point.y;
	m_mouse_x = (m_mouse_x - 10) / 10;
	m_mouse_y = (m_mouse_y - 10) / 10;
	short quantity;
		
	if(m_q.check(m_mouse_x,m_mouse_y))

	{

		quantity = m_q.get_f(m_mouse_x,m_mouse_y);
	
		_itoa(quantity, m_temp, 10);
		m_text_obj_quantity = m_temp;
		UpdateData(FALSE);
			
	}
					
	CDialog::OnMouseMove(nFlags, point);
}

void CAnimateDlg::OnCheckTagging() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(!m_draw_scene && !m_run_scenario)

	{
		
		redraw_frame();
		
	}
	
}

void CAnimateDlg::OnRadioSc1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	switch(m_scenario_type)

	{

	case 0:	// basic mining

		GetDlgItem(IDC_RADIO_AGENT_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_GRAB_CAP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SACK_CAP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MAX_STOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_INIT_STOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_PREDATORS)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_PREY)->EnableWindow(FALSE);
		m_agent_selected = 0;	// mining agents selected
		break;

	case 1: // chain mining

		GetDlgItem(IDC_RADIO_AGENT_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_GRAB_CAP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SACK_CAP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MAX_STOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_INIT_STOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_PREDATORS)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_PREY)->EnableWindow(FALSE);
		m_agent_selected = 0;	// mining agents selected
		break;

	case 2:	// predators prey

		GetDlgItem(IDC_EDIT_GRAB_CAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SACK_CAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MAX_STOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_INIT_STOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_PREDATORS)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_PREY)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_AGENT_TYPE)->EnableWindow(FALSE);
		m_agent_selected = 1;	// predator agents selected
		break;

	case 3:	// crowd

		GetDlgItem(IDC_RADIO_AGENT_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_GRAB_CAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SACK_CAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MAX_STOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_INIT_STOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_PREDATORS)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_PREY)->EnableWindow(FALSE);
		m_agent_selected = 0;	// mining agents selected
		break;

	default:

		GetDlgItem(IDC_EDIT_GRAB_CAP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SACK_CAP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MAX_STOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_INIT_STOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_PREDATORS)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_PREY)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_AGENT_TYPE)->EnableWindow(TRUE);
		m_agent_selected = 0;	// mining agents selected
		break;
		
	};

	UpdateData(FALSE);

	CAnimateDlg::OnRadioAgentType();
	
}

void CAnimateDlg::OnRadioSc2() 
{
	// TODO: Add your control notification handler code here
	CAnimateDlg::OnRadioSc1();
	
}

void CAnimateDlg::OnRadioSc3() 
{
	// TODO: Add your control notification handler code here
	CAnimateDlg::OnRadioSc1();
	
}

void CAnimateDlg::OnRadioSc4() 
{
	// TODO: Add your control notification handler code here
	CAnimateDlg::OnRadioSc1();
	
}

void CAnimateDlg::OnCheckFov() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(!m_draw_scene && !m_run_scenario)

	{
			
		redraw_frame();
		
	}
	
}

void CAnimateDlg::OnCheckExplore() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	// can't cast from bool to BOOL so have to do this...
	if(m_explore_map)

	{

		m_exploration = true;

	}

	else

	{

		m_exploration = false;

	}	
	
}

void CAnimateDlg::compute_paths()

{
	
	if(m_bitmap.m_hObject == NULL)

	{

		return;
			
	}// no bitmap
		
	// create a colour table

	PATH p;
	triple t;
	short c;
	
	for(c = 255 ; c >= 0 ; c--)

	{

		t.put(c,c,c);
		p.push_back(t);

	}

	// reuse m_q for data gathering

	// run through script

	long index = 0;
	m_q.wipe(0);
	short colour_factor = m_frame_jump/255;
	short value;

	if(colour_factor < 10)

	{

		colour_factor = 10;

	}
	
	SCRIPT_IT it;

	for(it = m_script.begin() ; it != m_script.end() ; ++it)
		
	{

		it -> get_paths(m1,m2,m4,m5);

		if(m1 == 1)

		{

			index++;
			
			if(index == (m_frame_jump+1))

			{

				break;

			}

		}

		else if(m2 > OBSTACLE && m2 < MINERAL) //	is an agent

		{

			// increment
			if((value = m_q.get_f(m4/10,m5/10)) < MAX_VALUE)

			{
				
				m_q.put_f(m4/10,m5/10,value + colour_factor);

			}

		}

	}
	
	// update bitmap
	
	short colour;

	// Create DC

	CClientDC dc(this);

	// Create Bitmap pointer

	CBitmap* pbmOld = NULL;
	
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	pbmOld = dcMem.SelectObject(&m_bitmap);
		
	// Create a pen
				
	CPen black_pen(PS_SOLID,1,RGB(0,0,0));
	CPen* pOriginalPen = dcMem.SelectObject(&black_pen);

	// copy path values over

	for(m1 = 0 ; m1 < 40 ; m1++)

	{

		for(m2 = 0 ; m2 < 40 ; m2++)

		{

			colour = m_q.get_f(m1,m2);

			if(m_density != 0 && colour >= m_density)

			{

				dcMem.FillSolidRect(m1*10,m2*10,OBJECT_SIZE,OBJECT_SIZE,RGB(255,0,0));

			}
			
			else if(colour > 255)

			{


				dcMem.FillSolidRect(m1*10,m2*10,OBJECT_SIZE,OBJECT_SIZE,RGB(0,0,0));

			}

			else

			{

				p[colour].get(m3,m4,m5);
				dcMem.FillSolidRect(m1*10,m2*10,OBJECT_SIZE,OBJECT_SIZE,RGB(m3,m4,m5));

			}

		}

	}

	// do screen

	dc.BitBlt(10,10,400,400, &dcMem, 0, 0, SRCCOPY);

	// clean up
	dcMem.SelectObject(pbmOld);
	dcMem.SelectObject(pOriginalPen);
	dcMem.DeleteDC();
	
}

void CAnimateDlg::compute_trails()

{
	
	if(m_bitmap.m_hObject == NULL)

	{

		return;
			
	}// no bitmap

	if(m_objects.m_hObject == NULL)

	{

		return;
			
	}// no bitmap
		
	// create a vector of agents, indexed by name

	PATH agents;
	triple t;
	m_q.wipe(0);

	for(short x = 0 ; x < m_scenario_data.total_agents ; x++)

	{

		t.put(0,0,0);
		agents.push_back(t);

	}
	
	// Create DC
	CClientDC dc(this);

	// Create Bitmap pointers
	CBitmap* pbmOld1 = NULL;
	CBitmap* pbmOld2 = NULL;
	
	CDC dcMem;
	CDC dcObj;
	dcMem.CreateCompatibleDC(&dc);
	dcObj.CreateCompatibleDC(&dc);
	pbmOld1 = dcMem.SelectObject(&m_bitmap);
	pbmOld2 = dcObj.SelectObject(&m_objects);
		
	// make back brush
	CBrush back_brush(dcObj.GetPixel(60,90));
	
	// brush pointer to original
	CBrush* pOriginalBrush = dcMem.SelectObject(&back_brush);
	
	// wipe bitmap
	CRect rect(0,0,400,400);
	dcMem.FillRect(rect,&back_brush);
	dcMem.SelectObject(pOriginalBrush);
	
	// create a thick black pen

	CPen prey_pen(PS_SOLID,3,(RGB(0,0,0)));
	CPen *pOriginalPen;

	SCRIPT_IT it;
	PATH_IT i;

	// first get starting coordinates

	for(it = (m_script.begin()+1) ; it != m_script.end() ; ++it)
		
	{

		it -> get_loc(m1,m2,m3,m4,m5);

		if(m1 == 1)

		{

			break;
			
		}

		else if(m2 >= MINER && m2 < MINERAL) //	is an agent

		{

			agents[m3].put(m2,m4,m5);
			
		}

	}

	// run through script, setting trails

	long index = 0;

	for(it = m_script.begin() ; it != m_script.end() ; ++it)
		
	{

		it -> get_trails(m1,m2,m3,m4,m5,m8,m9);

		if(m1 != 1 && m2 >= MINER && m2 < MINERAL)

		{

			agents[m3].get(m7,m8,m9);

			if(m2 == PREY)

			{

				pOriginalPen = dcMem.SelectObject(&prey_pen);
				dcMem.MoveTo(m8+5,m9+5);
				dcMem.LineTo(m4+5,m5+5);
				dcMem.SelectObject(pOriginalPen);

			}

			else

			{

				dcMem.MoveTo(m8+5,m9+5);
				dcMem.LineTo(m4+5,m5+5);
				
			}

			agents[m3].put(m2,m4,m5);

		}

		else if(m1 == 1)

		{

			index++;
			
			if(index == (m_frame_jump+1))

			{

				break;

			}

		}

	}

	// place agents over bitmap

	for(i = agents.begin() ; i != agents.end() ; ++i)
		
	{

		i -> get(m2,m4,m5);

		dcMem.BitBlt(m4,m5,10,10,&dcObj,10*m2,0,SRCCOPY);
		dcMem.Draw3dRect(m4,m5,10,10,RGB(255,255,255),RGB(0,0,0));

	};
		
	// do screen

	dc.BitBlt(10,10,400,400,&dcMem,0,0,SRCCOPY);

	// clean up
	dcMem.SelectObject(pbmOld1);
	dcObj.SelectObject(pbmOld2);
	dcMem.DeleteDC();
	dcObj.DeleteDC();
	
}

void CAnimateDlg::OnButtonPaths() 
{
	// TODO: Add your control notification handler code here

	if(m_script_size == 0)

	{

		MessageBox("Please load or create a script from a scenario");
		m_status = SM_PLS_LOAD;

	}

	else

	{

		m_trail_toggle = !m_trail_toggle;

		if(m_trail_toggle)

		{

			compute_trails();

		}

		else

		{
			
			compute_paths();

		}

		m_status = SM_PATHS;
	
	}

	UpdateData(FALSE);
	
}

void CAnimateDlg::OnRunAnimate() 
{
	// TODO: Add your control notification handler code here
	
	// assertion

	if(m_run_animate == true)

	{

		return;

	}

	m_run_animate = true;
	CAnimateDlg::OnRunScenario();
	
}

void CAnimateDlg::setup_scenario()

{

	// cancel any animation

	m_draw_scene = false;

	// get data from controls

	UpdateData(TRUE);
	
	// check that map file exists, initialise static bitmap back-buffer
	// and update animation windows

	// first check we have a valid map filename
	
	ifstream map(m_scenario_map_filename, ios::in);
	
	Environment e(40);
	
	if(!map)

	{

		MessageBox("Unable to open map file " + m_scenario_map_filename);
		map.close();
		m_run_animate = false;
		return;

	}

	else

	{

		e.input_objects(map);
		
		if(!e.get_state())

		{

			MessageBox("Unable to correctly read the file " + m_scenario_map_filename);
			map.close();
			m_run_animate = false;
			return;

		}

		// update static back-buffer and update screen

		make_bitmap_background(e);

	}

	// reset map file pointer
	
	map.seekg(0);
		
	// don't close map yet - needed for switch

	bool setup;

	switch(m_scenario_type)

	{	// these also act as resets

	case 0:	// basic mining

		setup = m_admin.setup_miner1(m_exploration, m_mining_agents, m_miner_vis,
										m_miner_grab, m_miner_sack, 40, map);
		break;

	case 1:

		setup = m_admin.setup_miner2(m_exploration, m_mining_agents, m_miner_vis,
										m_miner_grab, m_miner_sack, 40, map);
		break;

	case 2:

		setup = m_admin.setup_hunting(m_exploration, m_predator_agents, m_prey_agents,
				m_predator_vis,m_prey_vis,m_pred_stom_init,m_pred_stom_max,40,map);

		break;

	case 3:

		setup = m_admin.setup_crowd1(m_exploration,m_mining_agents,m_miner_vis,40,map);
		break;

	default:

		m_run_animate = false;
		return;

	};

	map.close();

	if(!setup)

	{

		//HERE
		MessageBox("The scenario setup failed. Either the map file is invalid\nor there is not enough space in the environment to\n	accomodate the agents");
		m_run_animate = false;
		//make_bitmap();
		m_script.clear();
		m_script_size = 0;
		m_index = 0;
		m_frame_index.clear();
		m_current_frame = 0;
		m_max_frame = 0;
		_itoa(m_current_frame,m_temp,10);
		m_current = m_temp;
		_itoa(m_max_frame,m_temp,10);
		m_max = m_temp;
		UpdateData(FALSE);
		return;

	}
	
	int result = MessageBox("Click OK to proceed","Confirm Scenario Execution?",
								MB_OKCANCEL + MB_ICONQUESTION);

	if(result == IDCANCEL)

	{
		
		m_run_animate = false;
		return;

	}
	
	// stop user fiddling and messing it all up
	
	GetDlgItem(IDC_LOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_PLAY)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_STEP_F)->EnableWindow(FALSE);
	GetDlgItem(IDC_STEP_B)->EnableWindow(FALSE);
	GetDlgItem(IDC_RESET)->EnableWindow(FALSE);
	GetDlgItem(IDC_MAP_EDITOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_RESET_END)->EnableWindow(FALSE);
	GetDlgItem(IDC_RUN_SCENARIO)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_AGENT_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_PREDATORS)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_PREY)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_AGENT_NO)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_VIS_RANGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_GRAB_CAP)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SACK_CAP)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SCENARIO_MAP)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_TURNS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_ITER)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_SC1)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_SC2)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_SC3)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_SC4)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_EXPLORE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PATHS)->EnableWindow(FALSE);
	GetDlgItem(IDC_RUN_ANIMATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FRAME_GET)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DENSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_JUMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_EXIT_APP)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MAX_STOM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_INIT_STOM)->EnableWindow(FALSE);
	
	if(!m_run_animate)

	{

		GetDlgItem(IDC_CHECK_TAGGING)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_TAGGING)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_FOV)->EnableWindow(FALSE);
	
	}
	
	// set scenario data
	//SETUP
	switch(m_scenario_type)

	{

	case 0:		// basic mining

		m_scenario_data.total_agents = (int)m_mining_agents;
		m_scenario_data.mining_agents = m_mining_agents;
		m_scenario_data.predator_agents = 0;
		m_scenario_data.prey_agents = 0;
		m_scenario_data.miner_vis = m_miner_vis;
		m_scenario_data.predator_vis = 0;
		m_scenario_data.prey_vis = 0;
		m_scenario_data.miner_grab = m_miner_grab;
		m_scenario_data.miner_sack = m_miner_sack;
		m_scenario_data.pred_stom_m = 10;
		m_scenario_data.pred_stom_i = 0;
		m_scenario_data.turns = m_turns;
		m_scenario_data.scenario_type = m_scenario_type;
		m_scenario_data.exploring = m_exploration;
		break;

	case 1:	// chain mining

		m_scenario_data.total_agents = (int)m_mining_agents;
		m_scenario_data.mining_agents = m_mining_agents;
		m_scenario_data.predator_agents = 0;
		m_scenario_data.prey_agents = 0;
		m_scenario_data.miner_vis = m_miner_vis;
		m_scenario_data.predator_vis = 0;
		m_scenario_data.prey_vis = 0;
		m_scenario_data.miner_grab = m_miner_grab;
		m_scenario_data.miner_sack = m_miner_sack;
		m_scenario_data.pred_stom_m = 10;
		m_scenario_data.pred_stom_i = 0;
		m_scenario_data.turns = m_turns;
		m_scenario_data.scenario_type = m_scenario_type;
		m_scenario_data.exploring = m_exploration;
		break;

	case 2:	// predators & prey

		m_scenario_data.total_agents = ((int)(m_predator_agents + m_prey_agents));
		m_scenario_data.mining_agents = 0;
		m_scenario_data.predator_agents = m_predator_agents;
		m_scenario_data.prey_agents = m_prey_agents;
		m_scenario_data.miner_vis = 0;
		m_scenario_data.predator_vis = m_predator_vis;
		m_scenario_data.prey_vis = m_prey_vis;
		m_scenario_data.miner_grab = 1;
		m_scenario_data.miner_sack = 1;
		m_scenario_data.pred_stom_m = m_pred_stom_max;
		m_scenario_data.pred_stom_i = m_pred_stom_init;
		m_scenario_data.turns = m_turns;
		m_scenario_data.scenario_type = m_scenario_type;
		m_scenario_data.exploring = m_exploration;
		break;

	case 3:

		m_scenario_data.total_agents = (int)m_mining_agents;
		m_scenario_data.mining_agents = m_mining_agents;
		m_scenario_data.predator_agents = 0;
		m_scenario_data.prey_agents = 0;
		m_scenario_data.miner_vis = m_miner_vis;
		m_scenario_data.predator_vis = 0;
		m_scenario_data.prey_vis = 0;
		m_scenario_data.miner_grab = 1;
		m_scenario_data.miner_sack = 1;
		m_scenario_data.pred_stom_m = 10;
		m_scenario_data.pred_stom_i = 0;
		m_scenario_data.turns = m_turns;
		m_scenario_data.scenario_type = m_scenario_type;
		m_scenario_data.exploring = m_exploration;
		break;

	default:

		m_run_animate = false;
		return;

	};
		
	// set progress bar
	m_scenario_progress.SetRange(0,(int)m_scenario_data.turns);

	// update progress bar to reflect position - first frame done
	m_scenario_progress.StepIt();
			
	// set starting turn
	m_current_turn = 2;

	// this has to be two because the first turn is the initial state

	// record iterations
	m_current_iter = 1;

	// update system status
	m_status = SM_SCEN;
		
	// update slider for tagging
	m_slider_tagged.SetRange(0,(m_scenario_data.total_agents)-1,true);
	m_slider_tagged.SetPos(0);

	// update tagged slider output
	m_text_agent_tagged = "0";

	// reset frames info
	_itoa(m_scenario_data.turns,m_temp,10);
	m_max = m_temp;
	m_current = "0";
	
	UpdateData(FALSE);

	// indicate that scenario is active
	// WM_TIMER will capture this and activate turns

	m_run_scenario = true;

	if(m_iterations > 1 && m_current_iter <= m_iterations)

	{

		CString info = "Animate: Iteration ";
		_itoa(m_current_iter,m_temp,10);
		info += m_temp;
		info += " of ";
		_itoa(m_iterations,m_temp,10);
		info += m_temp;
		SetWindowText(info);

	}
		
	// make pause scenario button active
	GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
	
	// make halt scenario button active
	GetDlgItem(IDC_KILL)->EnableWindow(TRUE);
	
}


void CAnimateDlg::execute_scenario_turn()

{

	// assertion, also in case paused or killed

	if(!m_run_scenario)

	{

		return;

	}
	
	// update system message
	m_status = SM_SCEN;
	UpdateData(FALSE);	
	
	if(m_current_iter <= m_iterations)

	{
		
		if(m_current_turn <= (m_scenario_data.turns))

		{

			
			// update frame info
			_itoa(m_current_turn,m_temp,10);
			m_current = m_temp;
			
			// update progress bar
			m_scenario_progress.StepIt();
			
			// allow agents to deliberate
			m_admin.deliberate();
			
			// get agents intended actions
			m_admin.get_intentions();
			
			// arbitrate the actions
			m_admin.arbitrate();
		
			// handle special events
			switch(m_scenario_type)

			{

			//place special options here
			
			case 2:	// predators & prey

				m_admin.check_hunting_POUNCE();
				break;

			default:

				break;

			};

			// set agents actions after arbitration
			m_admin.set_intentions();
			
			// allow agents to execute their actions
			m_admin.execute_actions();
			
			// update script
			m_admin.update_script();

			// if run and animate - update screen
			if(m_run_animate)

			{
			
				// get script for turn just run
				m_admin.get_last_turn(m_script);
							
				// set anim parameters
				m_script_size = (long)m_script.size();
				build_frame_index();
				m_current_frame = (m_current_turn-1);
				m_index = 0;

				// do screen
				update_frame();

			}

			m_current_turn++;

		}

		else

		{

			// save this script if asked to save script
			// function that auto creates a script
			if(m_iterations > 1)

			{

				auto_save_script();
				m_current_turn = 2;
				m_scenario_progress.SetPos(1);

			}

			m_current_iter++;

			if(m_iterations > 1 && m_current_iter <= m_iterations)

			{

				CString info = "Animate: Iteration ";
				_itoa(m_current_iter,m_temp,10);
				info += m_temp;
				info += " of ";
				_itoa(m_iterations,m_temp,10);
				info += m_temp;
				
				SetWindowText(info);

			}
			
		}
		
	}

	else
		
	{

		// make timer ignore scenario calls
		m_run_scenario = false;

		// reflect no longer animating and running a scenario
		m_run_animate = false;
		
		// get controls back
		finish_scenario_execution();

		
	}
		
}

void CAnimateDlg::finish_scenario_execution()

{

	// scenario has now finished

	// make pause scenario button inactive
	GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
	
	// make halt scenario button inactive
	GetDlgItem(IDC_KILL)->EnableWindow(FALSE);
	
	if(m_iterations == 1)

	{
		
		// copy script over from administrator
		m_admin.get_script(m_script);
				
		// tidy up the script
		m_script.resize(m_script.size());
		
		// set anim parameters
		m_script_size = (long)m_script.size();
		build_frame_index();
		m_frame_jump = 1;
		m_current_frame = 0;
		m_index = 0;

		// set scenario turns in case this script was stopped before complete
		m_scenario_data.turns = (short)m_max_frame;

		// update frame information
		_itoa(m_max_frame,m_temp,10);
		m_max = m_temp;
		_itoa(m_current_frame,m_temp,10);
		m_current = m_temp;
			
	}

	else

	{

		// make sure no silly data
		// erase old script
		m_script.erase(m_script.begin(),m_script.end());
		m_script_size = 0;
		m_max_frame = 0;
		m_current_frame = 0;
		m_index = 0;

		_itoa(m_max_frame,m_temp,10);
		m_max = m_temp;
		_itoa(m_current_frame,m_temp,10);
		m_current = m_temp;

	}

	// update first frame
	update_frame();
		
	MessageBox("Scenario finished");
	m_scenario_progress.SetPos(0);

	// allow clicking!!

	GetDlgItem(IDC_LOAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_PLAY)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_STEP_F)->EnableWindow(TRUE);
	GetDlgItem(IDC_STEP_B)->EnableWindow(TRUE);
	GetDlgItem(IDC_RESET)->EnableWindow(TRUE);
	GetDlgItem(IDC_MAP_EDITOR)->EnableWindow(TRUE);
	GetDlgItem(IDC_RESET_END)->EnableWindow(TRUE);
	GetDlgItem(IDC_RUN_SCENARIO)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_AGENT_TYPE)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_PREDATORS)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_PREY)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_AGENT_NO)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_VIS_RANGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_GRAB_CAP)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SACK_CAP)->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SCENARIO_MAP)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_TURNS)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_ITER)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_SC1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_SC2)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_SC3)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_SC4)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_EXPLORE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_PATHS)->EnableWindow(TRUE);
	GetDlgItem(IDC_RUN_ANIMATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_TAGGING)->EnableWindow(TRUE);
	GetDlgItem(IDC_SLIDER_TAGGING)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_FOV)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_FRAME_GET)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DENSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_JUMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_EXIT_APP)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_MAX_STOM)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_INIT_STOM)->EnableWindow(TRUE);

	m_status = SM_WAIT;
	UpdateData(FALSE);

	// set scenario selection controls
	CAnimateDlg::OnRadioSc1();

	// set agents selected
	CAnimateDlg::OnRadioAgentType();

	if(m_iterations > 1)

	{

		SetWindowText("Animate: scripts auto-saved, " + m_scenario_map_filename);

	}

	else

	{

		SetWindowText("Animate: script not saved, " + m_scenario_map_filename);

	}
		
}

void CAnimateDlg::OnPause() 
{
	// TODO: Add your control notification handler code here
	m_run_scenario = !m_run_scenario;

	if(!m_run_scenario)

	{

		m_status = SM_PAUSE;
		UpdateData(FALSE);
	
	}
		
}

void CAnimateDlg::OnKill() 
{
	// TODO: Add your control notification handler code here
	m_run_scenario = false;
	m_status = SM_PAUSE;
	UpdateData(FALSE);
	
	int result = MessageBox("Click OK to finish, CANCEL to resume","Stop this Scenario?",
								MB_OKCANCEL);

	if(result == IDCANCEL)

	{
		
		m_run_scenario = true;
		return;

	}
	
	if(result == IDOK)

	{
		
		// reflect no longer animating and running a scenario
		m_run_animate = false;
		
		// autosave will detect that we are not finished
		if(m_iterations > 1)

		{

			auto_save_script();

		}

		finish_scenario_execution();

	}

}

void CAnimateDlg::auto_save_script()

{

	m_status = SM_AUTO;
	UpdateData(FALSE);
	// was this cancelled?
	if(m_current_turn == ((m_scenario_data.turns)+1))

	{

		// erase old script
		m_script.erase(m_script.begin(),m_script.end());
		
		// copy script over from administrator
		m_admin.get_script(m_script);
					
		// tidy up the script
		m_script.resize(m_script.size());
			
		// auto create a filename

		// get map filename
		CString autofile = m_scenario_map_filename.Left(m_scenario_map_filename.Find("."));
		// add context identifier
		autofile += "_SC";
		// make unique experiment identifier
		_itoa(m_current_iter,m_temp,10);
		autofile += m_temp;
		autofile += ".data";

		// save script
			
		ofstream out(autofile, ios::binary);
		
		if(!out)

		{

			MessageBox("Unable to auto-write the file " + autofile);
			out.close();
			return;

		}
		
		// tidy the script
		m_script.resize(m_script.size());

		chunk p;
		
		// output script
		SCRIPT_IT it;

		for(it = m_script.begin() ; it != m_script.end() ; ++it)

		{
		
			p = *it;
			out.write(reinterpret_cast<const char *>(&p),sizeof(chunk));
		
		};

		out.flush();

		if(!out)

		{

			MessageBox("An I/O error occured whilst auto-saving the script data.\nScript data may be corrupt");

		}

		out.close();

		//if a pred&prey, get data

		if(m_scenario_type == 2)

		{

			extract_data_from_script();

		}

		// if this is the last in an experiment, we must save datad
		// collecting data

		if(!(m_current_iter == m_iterations))

		{

			// first get map background
			
			ifstream map(m_scenario_map_filename, ios::in);
			//short agents = 0;
			Environment e(40);
			
			if(!map)

			{

				MessageBox("Unable to open map file " + m_scenario_map_filename);
				map.close();
				return;

			}

			else

			{

				e.input_objects(map);

				if(!e.get_state())

				{

					MessageBox("Unable to correctly read the file " + m_scenario_map_filename);
					map.close();
					return;

				}

				// update static back-buffer and update screen

				make_bitmap_background(e);

			}

			// reset map file pointer
			
			map.seekg(0);
				
			// don't close map yet - needed for switch

			bool setup;

			switch(m_scenario_type)

			{	// these also act as resets

			case 0:	// basic mining

				setup = m_admin.setup_miner1(m_exploration, m_mining_agents, m_miner_vis,
												m_miner_grab, m_miner_sack, 40, map);
				break;

			case 1:

				setup = m_admin.setup_miner2(m_exploration, m_mining_agents, m_miner_vis,
												m_miner_grab, m_miner_sack, 40, map);
				break;

			case 2:

				setup = m_admin.setup_hunting(m_exploration, m_predator_agents, m_prey_agents,
							m_predator_vis,m_prey_vis,m_pred_stom_init,m_pred_stom_max,40,map);

				break;

			case 3:

				setup = m_admin.setup_crowd1(m_exploration,m_mining_agents,m_miner_vis,40,map);
				break;

			default:

				map.close();
				cleanup();
				CDialog::OnOK();//something bad has happened
				return;

			};

			map.close();

			if(!setup)

			{

				MessageBox("The scenario setup failed. Either the map file is invalid\nor there is not enough space in the environment to\n	accomodate the agents");
				
			}//***needs better handler
		
		}

		else

		{

			//last turn so save datad
			autofile = m_scenario_map_filename.Left(m_scenario_map_filename.Find("."));
			autofile += ".datad";

			ofstream out(autofile, ios::out);

			out.write(reinterpret_cast<const char *>(&m_scenario_data),sizeof(SCENARIO_DATA));
			out.flush();

			if(!out)

			{

				MessageBox("An I/O error occured whilst auto-saving the scenario data.\nFile data may be corrupt");

			}

			out.close();

		}

	}

	else

	{

		//run was cancelled - ensure we save datad dile
		CString file = m_scenario_map_filename.Left(m_scenario_map_filename.Find("."));
		file += ".datad";

		ofstream out2(file, ios::out);

		out2.write(reinterpret_cast<const char *>(&m_scenario_data),sizeof(SCENARIO_DATA));
		out2.flush();

		if(!out2)

		{

			MessageBox("An I/O error occured whilst auto-saving the scenario data.\nFile data may be corrupt");

		}

		out2.close();

	}

}

void CAnimateDlg::go_back_one_frame()

{

	seek_frame(m_current_frame-1);
	
}

void CAnimateDlg::OnButtonJump() 
{
	// TODO: Add your control notification handler code here
	
	m_draw_scene = false;
	seek_frame(m_frame_jump);
	
}

void CAnimateDlg::seek_frame(const int pos)

{

	if(m_script_size == 0)

	{

		return;

	}

	if(pos <= 0)

	{	// catch any peculiarities

		m_index = 0;
		m_current_frame = 0;
		update_frame();

	}

	else

	{

		m_index = m_frame_index[(pos-1)];
		m_current_frame = (pos - 1);
		update_frame();

	}
	
}

void CAnimateDlg::build_frame_index()

{

	if(m_script_size == 0)

	{	// don't bother - no script

		return;

	}

	// erase old index
	m_frame_index.clear();

	SCRIPT_IT it;
	long i = 0;
	
	for(it = m_script.begin() ; it != m_script.end() ; ++it)

	{	// for every info frame, mark its index

		it -> get_info(m1);
		
		if(m1 == 1)

		{

			m_frame_index.push_back(i);
		
		}

		i++;
		
	}

	i = m_frame_index.size();
	m_frame_index.resize(i);	// save memory
	m_max_frame = i;	// set max frames too

}

void CAnimateDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	int speed;

	if((speed = m_slider_speed.GetPos()) != m_anim_speed)

	{

		m_anim_speed = speed;

		KillTimer(1);
		
		if(SetTimer(1,m_anim_speed,NULL) == 0)

		{

			MessageBox("Unable to create a system timer.\nThe system is too busy.\nPlease save your work and release system resources");
	
		}

	}
	
	CSliderCtrl *p = (CSliderCtrl*) pScrollBar;

	if(p == &m_slider_tagged)

	{

		m_tagged = (short)m_slider_tagged.GetPos();

		_itoa(m_tagged,m_temp,10);
		m_text_agent_tagged = m_temp;
		UpdateData(FALSE);

		if(!m_draw_scene && !m_run_scenario)

		{
			
			redraw_frame();
			
		}

	}

	//CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CAnimateDlg::redraw_frame()

{

	seek_frame(m_current_frame);
	
}

void CAnimateDlg::OnButtonExitApp() 
{
	// TODO: Add your control notification handler code here

	int result = MessageBox("Please confirm exit from this program","Quit the Animate Program",
							MB_OKCANCEL + MB_ICONQUESTION);

	if(result == IDCANCEL)

	{

		return;

	}

	cleanup();
	CDialog::OnOK();
	
}

void CAnimateDlg::cleanup()

{

	m_draw_scene = false;
	m_run_animate = false;
	m_run_scenario = false;
	
	if(m_bitmap.m_hObject != NULL)
		
	{

		m_bitmap.DeleteObject();

	}
	
	if(m_static_bitmap.m_hObject != NULL)
		
	{

		m_static_bitmap.DeleteObject();

	}
	
	if(m_objects.m_hObject != NULL)
		
	{

		m_objects.DeleteObject();

	}

	m_dcObject.DeleteDC();
	m_dcBack.DeleteDC();
	m_dcScreen.DeleteDC();

	m_script.clear();
	m_frame_index.clear();

	KillTimer(1);

}

void CAnimateDlg::extract_data_from_script()

{
	
	// this only handles cases of 1 prey agent
	if(m_scenario_data.prey_agents > 1 || m_script.size() == 0)

	{

		return;

	}

	// only used in pred & prey

	short turn = 0;
	short stomach = 0;
	long pos;
	bool hit = false;

	SCRIPT_IT i;
	
	ofstream out("data.txt", ios::app);

	if(!out)

	{

		MessageBox("Unable to generate data file!");
		out.close();
		return;

	}

	// look for a dead prey
	for(i = m_script.begin() ; i != m_script.end() ; ++i)

	{

		i -> get_agent(m1,m2,m3);

		if(m1 == 1)

		{

			turn++;

		}

		// has a prey been killed? - do not handle multiple prey

		else if(m2 == CARCASS)

		{

			out << "Scenario," << m_current_iter << ",Prey," << m3 << ",Killed at turn,";
			out << turn-1;
			hit = true;
			break;

		}

	}

	if(!hit)

	{

		out << "Scenario," << m_current_iter << ",prey not killed";
		
	}

	// now add on total predator stomach contents
	// start at back of script and stop when info flag reached
	
	pos = m_script.size();
	m_script[pos].get_quantity(m1,m2,m7);

	while(m1 != 1)

	{
		
		if(m2 == PREDATOR)

		{

			stomach += m7;

		}

		pos--;
		m_script[pos].get_quantity(m1,m2,m7);

	};

	// now output

	out << ",Total Predator Stomach contents," << stomach << endl;

	out.close();

}

void CAnimateDlg::OnKillfocusEditFrameGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_script_size == 0)

	{

		m_frame_jump = 1;
		UpdateData(FALSE);
		return;

	}

	if(m_frame_jump < 1 || m_frame_jump > m_max_frame)

	{

		MessageBox("Please enter a valid frame number");
		m_frame_jump = 1;
		UpdateData(FALSE);

	}
	
}

void CAnimateDlg::OnKillfocusEditDense() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CAnimateDlg::OnKillfocusEditTurns() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
}

void CAnimateDlg::OnKillfocusEditIter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
}

void CAnimateDlg::OnKillfocusEditAgentNo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	switch(m_agent_selected)

	{

	case 0:	// mining agents

		m_mining_agents = m_agent_no;
		break;

	case 1: // predators

		m_predator_agents = m_agent_no;
		break;

	case 2:	// prey

		m_prey_agents = m_agent_no;
		break;

	};
	
}

void CAnimateDlg::OnKillfocusEditVisRange() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	switch(m_agent_selected)

	{

	case 0:	// mining agents

		m_miner_vis = m_vis_no;
		break;

	case 1: // predators

		m_predator_vis = m_vis_no;
		break;

	case 2:	// prey

		m_prey_vis = m_vis_no;
		break;

	};
	
}

void CAnimateDlg::OnKillfocusEditGrabCap() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_miner_grab = m_grab_no;
	
}

void CAnimateDlg::OnKillfocusEditSackCap() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_miner_sack = m_sack_no;
	
}

void CAnimateDlg::OnKillfocusEditMaxStom() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_pred_stom_max < 10  || m_pred_stom_max > 500)

	{

		MessageBox("Stomach Capacity must be >= 10 and <= 500");
		m_pred_stom_max = 10;
		UpdateData(FALSE);

	}

	if(m_pred_stom_max < m_pred_stom_init)

	{

		MessageBox("Stomach Capacity must be greater than Initial Capacity");
		m_pred_stom_max = 10;
		UpdateData(FALSE);

	}
	
}

void CAnimateDlg::OnKillfocusEditInitStom() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_pred_stom_init < 0  || m_pred_stom_init > m_pred_stom_max)

	{

		MessageBox("Initial Stomach Capacity must be >= 0 and <= Maximum Stomach Capacity");
		m_pred_stom_init = 0;
		UpdateData(FALSE);

	}

}

void CAnimateDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if(m_draw_scene || m_run_scenario)

	{
		
		return;

	}

	CRect rect(10,10,410,410);
	
	if(rect.PtInRect(point))

	{

		if(m_bitmap.m_hObject == NULL)

		{

			return;// bitmap not made yet
				
		}
		
		// create saving dialog with bitmap file filter
		CString filter = "Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||";
		CFileDialog dlg(FALSE,"bmp","*.bmp",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);
	
		CString path;
		
		if(dlg.DoModal() == IDOK)

		{

			path = dlg.GetPathName();
			
			CClientDC dc(this);
			CSize size(400,400);
			CDib dib(size,24);
			dib.CreateSection(&dc);
			CDC pic;
			CDC file;
			pic.CreateCompatibleDC(&dc);
			file.CreateCompatibleDC(&dc);
			CBitmap* pBITMAP1 = pic.SelectObject(&m_bitmap);
			CBitmap* pBITMAP2 = file.SelectObject(CBitmap::FromHandle(dib.m_hBitmap));
			file.BitBlt(0,0,400,400,&pic,0,0,SRCCOPY);
			pic.SelectObject(pBITMAP1);
			file.SelectObject(pBITMAP2);

			// write bmp
			const char* pFileName = (LPCTSTR) path;
	
			TRY
	
			{
		
				CFile f(pFileName,CFile::modeCreate | CFile::modeWrite | CFile::shareDenyRead);
				dib.Write(&f);
				f.Close();
		
			}

			CATCH(CFileException,e)
		
			{

				MessageBox("Unable to save the file " + path);
				return;
			}
		
			END_CATCH

			MessageBox("Animation frame buffer saved to " + path);  

		}

	}

}
