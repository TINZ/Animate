// MapEditor.cpp : implementation file
//

#include "stdafx.h"
#include "Animate.h"
#include "MapEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MapEditor dialog


MapEditor::MapEditor(CWnd* pParent /*=NULL*/)
	: CDialog(MapEditor::IDD, pParent)
{
	//{{AFX_DATA_INIT(MapEditor)
	m_edit_quantity = 0;
	m_text_x = _T("");
	m_text_y = _T("");
	m_count_obstacles = _T("");
	m_count_minerals = _T("");
	m_count_homes = _T("");
	m_object_paint = -1;
	m_count_ore = _T("");
	m_mineral_worth = _T("");
	m_ore_worth = _T("");
	m_total_worth = _T("");
	m_rand_min = 0;
	m_rand_max = 0;
	m_show_paths = FALSE;
	m_set_starts = FALSE;
	//}}AFX_DATA_INIT
}


void MapEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MapEditor)
	DDX_Text(pDX, IDC_EDIT_SEE_QUANTITY, m_edit_quantity);
	DDV_MinMaxInt(pDX, m_edit_quantity, 0, 32000);
	DDX_Text(pDX, IDC_TEXT_X, m_text_x);
	DDV_MaxChars(pDX, m_text_x, 4);
	DDX_Text(pDX, IDC_TEXT_Y, m_text_y);
	DDV_MaxChars(pDX, m_text_y, 4);
	DDX_Text(pDX, IDC_TEXT_OBSTACLES, m_count_obstacles);
	DDX_Text(pDX, IDC_TEXT_MINERALS, m_count_minerals);
	DDX_Text(pDX, IDC_TEXT_HOMES, m_count_homes);
	DDX_Radio(pDX, IDC_RADIO_OBSTACLES, m_object_paint);
	DDX_Text(pDX, IDC_TEXT_ORE, m_count_ore);
	DDX_Text(pDX, IDC_TEXT_MIN_WORTH, m_mineral_worth);
	DDX_Text(pDX, IDC_TEXT_ORE_WORTH, m_ore_worth);
	DDX_Text(pDX, IDC_TEXT_TOTAL_WORTH, m_total_worth);
	DDX_Text(pDX, IDC_EDIT_RAND_MIN, m_rand_min);
	DDV_MinMaxInt(pDX, m_rand_min, 1, 32000);
	DDX_Text(pDX, IDC_EDIT_RAND_MAX, m_rand_max);
	DDV_MinMaxInt(pDX, m_rand_max, 1, 32000);
	DDX_Check(pDX, IDC_CHECK_PATHS, m_show_paths);
	DDX_Check(pDX, IDC_CHECK_STARTS, m_set_starts);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MapEditor, CDialog)
	//{{AFX_MSG_MAP(MapEditor)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_RAND_OBSTACLES, OnRandObstacles)
	ON_BN_CLICKED(IDC_RAND_MINERALS, OnRandMinerals)
	ON_BN_CLICKED(IDC_CLEAR_OBSTACLES, OnClearObstacles)
	ON_BN_CLICKED(IDC_CLEAR_MINERALS, OnClearMinerals)
	ON_BN_CLICKED(IDC_RAND_QUANTITY, OnRandQuantity)
	ON_BN_CLICKED(IDC_SAVE_GRID, OnSaveGrid)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_LOAD_GRID, OnLoadGrid)
	ON_BN_CLICKED(IDC_RESET_ALL_MAP, OnResetAllMap)
	ON_BN_CLICKED(IDC_RADIO_OBSTACLES, OnRadioObstacles)
	ON_BN_CLICKED(IDC_RADIO_MINERALS, OnRadioMinerals)
	ON_BN_CLICKED(IDC_RADIO_ORE, OnRadioOre)
	ON_BN_CLICKED(IDC_RADIO_HOMES, OnRadioHomes)
	ON_BN_CLICKED(IDC_RADIO_SET_QUANTITY, OnRadioSetQuantity)
	ON_BN_CLICKED(IDC_RAND_ORE, OnRandOre)
	ON_BN_CLICKED(IDC_CLEAR_ORE, OnClearOre)
	ON_BN_CLICKED(IDC_CLEAR_HOMES, OnClearHomes)
	ON_BN_CLICKED(IDC_BUTTON_VALIDATE, OnButtonValidate)
	ON_BN_CLICKED(IDC_BUTTON_LEVEL_QUAN, OnButtonLevelQuan)
	ON_BN_CLICKED(IDC_CHECK_PATHS, OnCheckPaths)
	ON_BN_CLICKED(ID_BUTTON_OK, OnButtonOk)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_CHECK_STARTS, OnCheckStarts)
	ON_EN_KILLFOCUS(IDC_EDIT_SEE_QUANTITY, OnKillfocusEditSeeQuantity)
	ON_EN_KILLFOCUS(IDC_EDIT_RAND_MIN, OnKillfocusEditRandMin)
	ON_EN_KILLFOCUS(IDC_EDIT_RAND_MAX, OnKillfocusEditRandMax)
	ON_WM_RBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//ON_EN_CHANGE(IDC_EDIT_LOAD_FILENAME, OnChangeEditLoadFilename)
	
/////////////////////////////////////////////////////////////////////////////
// MapEditor message handlers

BOOL MapEditor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	VERIFY(m_button_load.AutoLoad(IDC_LOAD_GRID, this));
	VERIFY(m_button_save.AutoLoad(IDC_SAVE_GRID, this));
	VERIFY(m_button_rand_o.AutoLoad(IDC_RAND_OBSTACLES, this));
	VERIFY(m_button_clear_o.AutoLoad(IDC_CLEAR_OBSTACLES, this));
	VERIFY(m_button_rand_m.AutoLoad(IDC_RAND_MINERALS, this));
	VERIFY(m_button_clear_m.AutoLoad(IDC_CLEAR_MINERALS, this));
	VERIFY(m_button_rand_ore.AutoLoad(IDC_RAND_ORE, this));
	VERIFY(m_button_clear_ore.AutoLoad(IDC_CLEAR_ORE, this));
	VERIFY(m_button_clear_h.AutoLoad(IDC_CLEAR_HOMES, this));
	VERIFY(m_button_rand_q.AutoLoad(IDC_RAND_QUANTITY, this));
	VERIFY(m_button_level.AutoLoad(IDC_BUTTON_LEVEL_QUAN, this));
	VERIFY(m_button_valid.AutoLoad(IDC_BUTTON_VALIDATE, this));
	VERIFY(m_button_reset.AutoLoad(IDC_RESET_ALL_MAP, this));

	// setup search vector
	m_search.clear();

	// allocate and resize search list
	m_search.reserve((40*40)+40);
	m_search.resize((40*40)+40);

	m_show_paths = false;
	m_edit_quantity = 1;
	m_rand_min = 1;
	m_rand_max = 100;
	m_obstacles = 0;				// obstacles in map
	m_minerals = 0;				// minerals in map
	m_ore = 0;					// ore in map
	m_homes = 0;					// home bases in map
	m_mineral_count = 0;			// mineral worth in map
	m_ore_count = 0;				// ore worth in map
	m_total_count = 0;	
	m_grid_x = 0;
	m_grid_y = 0;
	m_object_paint = 0;
	m_file_name = "";
	update_fields();
	m_env.metamorphose(40);
	m_s.metamorphose(40);
	
	make_bitmap();

	update_frame();

	// seed random

	srand( (unsigned)time( NULL ) );

	GetDlgItem(IDC_EDIT_SEE_QUANTITY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LEVEL_QUAN)->EnableWindow(FALSE);
	
	// create a colour table

	triple t;
	short c;
	
	c = 255;

	while(c >= 0)

	{

		t.put(c,255,255);
		m_colour_table.push_back(t);
		c--;
		
	};
	
	c = 254;

	while(c >= 0)

	{

		t.put(0,c,255);
		m_colour_table.push_back(t);
		c--;
		
	};
	
	c = 254;

	while(c >= 0)

	{

		t.put(0,0,c);
		m_colour_table.push_back(t);
		c--;
		
	};

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MapEditor::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	short my_x = (short)point.x;
	short my_y = (short)point.y;
	short object,quantity;

	my_y = (my_y - 10) / 10;
	my_x = (my_x - 10) / 10;

	if(!m_env.check_coord(my_x,my_y))

	{

		return;

	}

	if(m_show_paths)

	{

		update_paths();
		return;
				
	}

	/*if(m_set_starts)

	{

		m_env.put_object_f(my_x,my_y,ASTART,0);
		update_frame();
		return;
	
	}*/

	if(m_object_paint == 4 && !m_set_starts)

	{

		m_env.get_object_f(my_x,my_y,object,quantity);

		switch(object)

		{

		case MINERAL:
		
			UpdateData(TRUE);
			m_mineral_count -= quantity;
			m_total_count -= quantity;
			m_env.put_quantity_f(my_x,my_y,m_edit_quantity);
			m_mineral_count += m_edit_quantity;
			m_total_count += m_edit_quantity;
			update_frame();
			update_fields();
			return;

		case ORE:

			UpdateData(TRUE);
			m_ore_count -= quantity;
			m_total_count -= quantity;
			m_env.put_quantity_f(my_x,my_y,m_edit_quantity);
			m_ore_count += m_edit_quantity;
			m_total_count += m_edit_quantity;
			update_frame();
			update_fields();
			return;

		default:

			return;

		};

	}
		
	m_env.get_object_f(my_x,my_y,object,quantity);
	
	switch(object)
			
	{

		case SPACE:

			break;

		case OBSTACLE:

			m_obstacles--;
			break;

		case MINERAL:

			m_minerals--;
			m_mineral_count -= quantity;
			m_total_count -= quantity;
			break;

		case ORE:

			m_ore--;
			m_ore_count -= quantity;
			m_total_count -= quantity;
			break;

		case HOME:

			m_homes--;
			break;

		default:

			break;

	};

	if(m_set_starts)

	{

		m_env.put_object_f(my_x,my_y,ASTART,0);
		
	}

	else

	{

		switch(m_object_paint)
				
		{
			
		case 0:

			m_obstacles++;
			m_env.put_object_f(my_x,my_y,OBSTACLE,0);
			break;

		case 1:

			m_minerals++;
			m_mineral_count++;
			m_total_count++;
			m_env.put_object_f(my_x,my_y,MINERAL,1);
			break;

		case 2:

			m_ore++;
			m_ore_count++;
			m_total_count++;
			m_env.put_object_f(my_x,my_y,ORE,1);
			break;

		case 3:

			m_homes++;
			m_env.put_object_f(my_x,my_y,HOME,0);
			break;

		default:

			break;

		};

	}
	
	update_frame();
	update_fields();
					
	//CDialog::OnLButtonDown(nFlags, point);
}

void MapEditor::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	if(m_bitmap.m_hObject == NULL)

	{

		return;
			
	}// no bitmap
		
	// Create Bitmap pointer

	CBitmap* pbmOld = NULL;

	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	pbmOld = dcMem.SelectObject(&m_bitmap);
		
	dc.BitBlt(10,10,400,400, &dcMem, 0, 0, SRCCOPY);

	dcMem.SelectObject(pbmOld);
			
	// Do not call CDialog::OnPaint() for painting messages
}

void MapEditor::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	short my_x = (short)point.x;
	short my_y = (short)point.y;
	short object,quantity;
	
	my_y = (my_y - 10) / 10;
	my_x = (my_x - 10) / 10;
		
	if(m_env.check_coord(my_x,my_y))

	{

		m_env.get_object_f(my_x,my_y,object,quantity);

		switch(object)
			
		{

		case SPACE:

			return;

		case OBSTACLE:

			m_obstacles--;
			m_env.put_object_f(my_x,my_y,SPACE,0);
			break;

		case MINERAL:

			m_minerals--;
			m_mineral_count -= quantity;
			m_total_count -= quantity;
			m_env.put_object_f(my_x,my_y,SPACE,0);
			break;

		case ORE:

			m_ore--;
			m_ore_count -= quantity;
			m_total_count -= quantity;
			m_env.put_object_f(my_x,my_y,SPACE,0);
			break;

		case HOME:

			m_homes--;
			m_env.put_object_f(my_x,my_y,SPACE,0);
			break;

		default:

			m_env.put_object_f(my_x,my_y,SPACE,0);
			break;

		};

		update_frame();
		update_fields();

		
	}
	
	//CDialog::OnRButtonDown(nFlags, point);
}

void MapEditor::OnRandObstacles() 
{
	// TODO: Add your control notification handler code here

	OnResetAllMap(); 
	//m_env.clear_objects(OBSTACLE);
	//m_obstacles = 0;

	const short move[16] = {0,-1,1,-1,1,0,1,1,0,1,-1,1,-1,0,-1,-1};

	short obst = (rand() % m_rand_max) + m_rand_min;

	short x,y,c,c1,c2;

	for(c = 0 ; c < obst ; c++)

	{

		x = rand() % 40;
		y = rand() % 40;

		if(m_env.check_coord(x,y))

		{

			m_env.put_object_f(x, y, OBSTACLE, 0);
			
			for(c1 = 0 ; c1 < 15 ; c1+=2)

			{

				c2 = c1 + 1;

				if(m_env.check_coord(x + move[c1], y + move[c2]))
		
				{

					m_env.put_object_f(x + move[c1],y + move[c2],OBSTACLE, 0);
				
				}

			}

		}

	}

	for(x = 0 ; x < 40 ; x++)

	{

		for(y = 0 ; y < 40 ; y++)

		{

			switch(m_env.get_object_f(x,y))

			{

			case OBSTACLE:

				m_obstacles++;
				break;

			default:

				break;

			};

		}

	}

	m_show_paths = FALSE;
	update_frame();
	update_fields();
				
}

void MapEditor::OnRandMinerals() 
{
	// TODO: Add your control notification handler code here

	m_env.clear_objects(MINERAL);
	m_minerals = 0;
	m_total_count -= m_mineral_count;
	m_mineral_count = 0;
	
	short min = (rand() % m_rand_max) + m_rand_min;
	short quantity;
	short x,y,c;

	for(c = 0 ; c < min ; c++)

	{

		x = rand() % 40;
		y = rand() % 40;
		
		if(m_env.check_coord(x,y))

		{

			if(m_env.get_object_f(x,y) == SPACE)

			{

				quantity = (rand() % m_rand_max) + m_rand_min;
				m_env.put_object_f(x, y, MINERAL, quantity);
				m_minerals++;
				m_mineral_count += quantity;

			}

		}

	}

	m_total_count += m_mineral_count;
	m_show_paths = FALSE;
	update_frame();
	update_fields();
	
}

void MapEditor::OnClearObstacles() 
{
	// TODO: Add your control notification handler code here
	m_env.clear_objects(OBSTACLE);
	m_show_paths = FALSE;
	m_obstacles = 0;
	update_frame();
	update_fields();

}

void MapEditor::OnClearMinerals() 
{
	// TODO: Add your control notification handler code here
	m_env.clear_objects(MINERAL);
	m_show_paths = FALSE;
	m_minerals = 0;
	m_total_count -= m_mineral_count;
	m_mineral_count = 0;
	update_frame();
	update_fields();

}

void MapEditor::OnRandQuantity() 
{
	// TODO: Add your control notification handler code here
	m_mineral_count = 0;
	m_ore_count = 0;

	m_env.rand_all_quantities(MINERAL, m_rand_min, m_rand_max);
	m_env.rand_all_quantities(ORE, m_rand_min, m_rand_max);

	short x,y,object,quantity;

	for(x = 0 ; x < 40 ; x++)

	{

		for(y = 0 ; y < 40 ; y++)

		{

			m_env.get_object_f(x,y,object,quantity);

			switch(object)

			{

			case MINERAL:

				m_mineral_count += quantity;
				break;

			case ORE:

				m_ore_count += quantity;
				break;

			default:

				break;

			};

		}

	}

	m_total_count = m_ore_count + m_mineral_count;
	m_show_paths = FALSE;
	update_frame();
	update_fields();
		
}

void MapEditor::OnSaveGrid() 
{
	// TODO: Add your control notification handler code here
	
	// validate this map
	
	if(!validate_map())

	{

		MessageBox("This map has invalid region(s) or no space.\nThe possible invalid region(s) have been indicated in white.\nPlease make the region(s) accessible");
		return;

	}

	// open save dialog
	CString filter = "Animate Map Files (*.map)|*.map|All Files (*.*)|*.*||";
	CFileDialog dlg(FALSE,"map","untitled.map",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);
	
	//CFileDialog dlg(false, "map", "*.map");
	CString file;

	if(dlg.DoModal() != IDOK)
		
	{
		
		return;
		
	}
	
	file = dlg.GetPathName();
	
	ofstream out(file, ios::out);

	if(!out)

	{

		MessageBox("Unable to save the file " + file);
		out.close();
		return;

	}

	m_file_name = file;

	m_env.output_objects(out);
	out.flush();
	out.close();

	MessageBox("Map file " + file + " saved");
	
}

void MapEditor::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	short my_x = (short)point.x;
	short my_y = (short)point.y;
	short quantity;

	my_y = (my_y - 10) / 10;
	my_x = (my_x - 10) / 10;

	if(!m_env.check_coord(my_x,my_y))

	{

		return;

	}

	if((nFlags & MK_LBUTTON) == MK_LBUTTON)

	{

		MapEditor::OnLButtonDown(nFlags, point);
			
	}

	else if((nFlags & MK_RBUTTON) == MK_RBUTTON)

	{

		MapEditor::OnRButtonDown(nFlags, point);
		
	}
	
	if(m_show_paths)

	{

		quantity = m_s.get_f(my_x,my_y);

	}

	else

	{

		quantity = m_env.get_quantity_f(my_x,my_y);

	}

	if(quantity < 0)

	{

		quantity = 0;

	}

	m_edit_quantity = quantity;
	_itoa(my_x, m_temp, 10);
	m_text_x = m_temp;
	_itoa(my_y, m_temp, 10);
	m_text_y = m_temp;
	m_grid_x = my_x;
	m_grid_y = my_y;
	
	UpdateData(FALSE);
		
	//CDialog::OnMouseMove(nFlags, point);
}

void MapEditor::OnLoadGrid() 
{
	// TODO: Add your control notification handler code here

	CString filter = "Animate Map Files (*.map)|*.map|All Files (*.*)|*.*||";
	CFileDialog dlg(TRUE,"map","*.map",OFN_HIDEREADONLY,filter);
	
	//CFileDialog dlg(true, "map", "*.map");
	CString file;

	if(dlg.DoModal() != IDOK)
		
	{
		
		return;
		
	}
	
	file = dlg.GetPathName();
	
	ifstream in(file, ios::in);

	if(!in)

	{

		MessageBox("Unable to load file " + file);
		in.close();
		return;

	}
	
	m_env.input_objects(in);

	if(!m_env.get_state())

	{

		MessageBox("Unable to correctly read the file " + file);
		m_env.metamorphose(40);
		in.close();
		return;

	}

	m_file_name = file;
	in.close();

	m_obstacles = 0;
	m_minerals = 0;
	m_mineral_count = 0;
	m_ore = 0;
	m_ore_count = 0;
	m_homes = 0;

	short x,y,object,quantity;

	for(x = 0 ; x < 40 ; x++)

	{

		for(y = 0 ; y < 40 ; y++)

		{

			m_env.get_object_f(x,y,object,quantity);

			switch(object)

			{

			case OBSTACLE:

				m_obstacles++;
				break;

			case MINERAL:

				m_minerals++;
				m_mineral_count += quantity;
				break;

			case ORE:

				m_ore++;
				m_ore_count += quantity;
				break;

			case HOME:

				m_homes++;
				break;

			default:

				break;

			};

		}

	}

	m_total_count = m_mineral_count + m_ore_count;
	update_fields();
	update_frame();
	MessageBox("Map file " + file + " loaded");
		
}

void MapEditor::OnResetAllMap() 
{
	// TODO: Add your control notification handler code here
	m_env.clear_all();
	m_show_paths = FALSE;
	m_obstacles = 0;
	m_minerals = 0;
	m_ore = 0;
	m_homes = 0;
	m_mineral_count = 0;
	m_ore_count = 0;
	m_total_count = 0;
	update_frame();
	update_fields();

}

void MapEditor::update_frame()

{

	if(m_bitmap.m_hObject == NULL)

	{

		return;
			
	}// no bitmap

	if(m_objects.m_hObject == NULL)

	{

		return;
			
	}// no bitmap
	
	CClientDC dc(this);

	CDC dcObject;
	CDC dcScreen;

	CBitmap* pOldObject = NULL;
	CBitmap* pOldScreen = NULL;
	
	dcObject.CreateCompatibleDC(&dc);	// make compatible
	dcScreen.CreateCompatibleDC(&dc);	// make compatible
		
	pOldObject = dcObject.SelectObject(&m_objects);
	pOldScreen = dcScreen.SelectObject(&m_bitmap);
	
	// make back brush from background of object
	CBrush back_brush(dcObject.GetPixel(60,90));	// background
										
	// brush pointer to original
	CBrush* pOriginalBrush = dcScreen.SelectObject(&back_brush);
	
	// wipe bitmap
	CRect rect(0,0,400,400);
	dcScreen.FillRect(rect,&back_brush);
	dcScreen.SelectObject(pOriginalBrush);
				
	// Create unknown Brush
	CBrush white_brush(RGB(255,255,255));	// unknown - invalid area
			
	short x,y,object;

	for(x = 0 ; x < 40 ; x++)

	{

		for(y = 0 ; y < 40 ; y++)

		{

			object = m_env.get_object_f(x,y);

			switch(object)

			{

			case OBSTACLE:

				dcScreen.BitBlt(x*10,y*10,10,10,&dcObject,object*10,0,SRCCOPY);
				break;
			
			case MINERAL:

				dcScreen.BitBlt(x*10,y*10,10,10,&dcObject,object*10,0,SRCCOPY);
				break;

			case ORE:

				dcScreen.BitBlt(x*10,y*10,10,10,&dcObject,object*10,0,SRCCOPY);
				break;

			case HOME:

				dcScreen.BitBlt(x*10,y*10,10,10,&dcObject,object*10,0,SRCCOPY);
				break;

			case UNKNOWN:

				pOriginalBrush = dcScreen.SelectObject(&white_brush);
				dcScreen.Ellipse(x*10,y*10,(x*10)+10,(y*10)+10);
				dcScreen.SelectObject(pOriginalBrush);
				break;

			case ASTART:

				dcScreen.BitBlt(x*10,y*10,10,10,&dcObject,0,0,SRCCOPY);
				break;

			default:

				break;
					
			};

		}

	}

	// copy to screen
	dc.BitBlt(10,10,400,400,&dcScreen,0,0,SRCCOPY);

	// clean up
	dcObject.SelectObject(pOldObject);
	dcScreen.SelectObject(pOldScreen);

}

void MapEditor::make_bitmap()

{

	if(m_bitmap.m_hObject != NULL)

	{

		m_bitmap.DeleteObject();   // get rid of old bitmap

	}

	if(m_objects.m_hObject != NULL)

	{

		m_objects.DeleteObject();   // get rid of old bitmap

	}

	// order is important
	CClientDC dc(this);

	CDC dcObject;
	CDC dcScreen;

	// make pointers
	CBitmap* pOldScreen = NULL;
	CBitmap* pOldObject = NULL;
	
	// load object resource - 24bit
	m_objects.LoadBitmap(IDB_OBJECTS);

	// make compatible
	dcObject.CreateCompatibleDC(&dc);
	
	// select in
	pOldObject = dcObject.SelectObject(&m_objects);

	// make other dc's compatible
	dcScreen.CreateCompatibleDC(&dc);
	
	// make other bitmaps
	m_bitmap.CreateCompatibleBitmap(&dc,400,400);
	ASSERT(m_bitmap.m_hObject != NULL);
		
	// select in
	pOldScreen = dcScreen.SelectObject(&m_bitmap);

	// make back brush from background of object
	CBrush back_brush(dcObject.GetPixel(60,90));	// background
										
	// brush pointer to original
	CBrush* pOriginalBrush = dcScreen.SelectObject(&back_brush);
	
	// wipe static bitmap background
	CRect rect(0,0,400,400);
	dcScreen.FillRect(rect,&back_brush);
	dcScreen.SelectObject(pOriginalBrush);
	
	// copy to screen
	dc.BitBlt(0,0,400,400,&dcScreen,0,0,SRCCOPY);

	// select old
	dcScreen.SelectObject(pOldScreen);
	dcObject.SelectObject(pOldObject);
	dcObject.DeleteDC();
	dcScreen.DeleteDC();
		
}

void MapEditor::update_search_memory()

{

	// erase any unknowns in m_env
	m_env.clear_objects(UNKNOWN);

	// get object map into m_s
	m_env.get_all_objects(m_s);

	// clear starts
	m_s.replace_all_instances(ASTART,-2);
	
	// set all obstacles
	m_s.replace_all_non_zero_instances(-1);

}

void MapEditor::execute_search_flood(short x, short y)

{

	short value = 10;		// the path cost
	short c1,c2,cx,cy,put_value,temp;
	triple t(x,y,value);	// for recording algorithm progress
	m_search.clear();
	m_search.push_back(t);			// set first value
	m_s.put_f(x,y,value);	// record in search grid
	short count = 0;		// loop counter
	bool hypotenuse = true;		// a toggle that represents a diagonal move
	
	while(count < m_search.size())

	{

		m_search[count].get(x,y,value);
		
		for(c1 = 0 ; c1 < (MOVE_DIM - 1) ; c1+=2)

		{

			c2 = c1 + 1;
			cx = x + moves[c1];
			cy = y + moves[c2];
			hypotenuse = !hypotenuse;
			put_value = value;

			if(m_s.check(cx,cy))
				
			{	

				if((temp = m_s.get_f(cx,cy)) != -1)

				{
					
					if(hypotenuse)

					{
						
						if(((put_value += 14) < temp) || temp == SPACE)

						{
						
							m_s.put_f(cx,cy,put_value);
							t.put(cx,cy,put_value);
							m_search.push_back(t);

						}
						
					}

					else

					{

						if(((put_value += 10) < temp) || temp == SPACE)

						{

							m_s.put_f(cx,cy,put_value);
							t.put(cx,cy,put_value);
							m_search.push_back(t);

						}
						
					}

				}

			}

		}

		count++;
		
	};
	
}

bool MapEditor::validate_map()

{

	short x,y;
	bool hit = false;

	// update search memory

	update_search_memory();
	
	// find a space

	for(x = 0 ; x < 40 ; x++)

	{

		for(y = 0 ; y < 40 ; y++)

		{
			
			if(m_s.get_f(x,y) == SPACE)

			{

				hit = true;
				break;

			}

		}

		if(hit)

		{

			break;

		}

	}

	if(!hit)

	{

		return(false);
		// no space at all

	}

	// flood grid

	execute_search_flood(x,y);

	// look for unobtainable regions

	hit = true;

	for(x = 0 ; x < 40 ; x++)

	{

		for(y = 0 ; y < 40 ; y++)

		{
			
			if(m_s.get_f(x,y) == SPACE)

			{

				m_env.put_object_f(x,y,UNKNOWN,0);
				hit = false;
				
			}

		}
		
	}

	update_frame();
	return(hit);

}

const CString MapEditor::get_file_name()

{

	return(m_file_name);

}

void MapEditor::OnRadioObstacles() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_EDIT_SEE_QUANTITY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LEVEL_QUAN)->EnableWindow(FALSE);
	m_set_starts = FALSE;
	m_show_paths = FALSE;
	UpdateData(FALSE);
	
}

void MapEditor::OnRadioMinerals() 
{
	// TODO: Add your control notification handler code here
	MapEditor::OnRadioObstacles();
	
}

void MapEditor::OnRadioOre() 
{
	// TODO: Add your control notification handler code here
	MapEditor::OnRadioObstacles();
	
}

void MapEditor::OnRadioHomes() 
{
	// TODO: Add your control notification handler code here
	MapEditor::OnRadioObstacles();
}

void MapEditor::OnRadioSetQuantity() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_EDIT_SEE_QUANTITY)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LEVEL_QUAN)->EnableWindow(TRUE);
			
}

void MapEditor::OnRandOre() 
{
	// TODO: Add your control notification handler code here
	m_env.clear_objects(ORE);
	m_ore = 0;
	m_total_count -= m_ore_count;
	m_ore_count = 0;
	
	short min = (rand() % m_rand_max) + m_rand_min;
	short quantity;
	short x,y,c;

	for(c = 0 ; c < min ; c++)

	{

		x = rand() % 40;
		y = rand() % 40;
		
		if(m_env.check_coord(x,y))

		{

			if(m_env.get_object_f(x,y) == SPACE)

			{

				quantity = (rand() % m_rand_max) + m_rand_min;
				m_env.put_object_f(x, y, ORE, quantity);
				m_ore++;
				m_ore_count += quantity;

			}

		}

	}

	m_total_count += m_ore_count;
	m_show_paths = FALSE;
	update_frame();
	update_fields();
	
}

void MapEditor::OnClearOre() 
{
	// TODO: Add your control notification handler code here
	m_env.clear_objects(ORE);
	m_show_paths = FALSE;
	m_ore = 0;
	m_total_count -= m_ore_count;
	m_ore_count = 0;
	update_frame();
	update_fields();
	
}

void MapEditor::OnClearHomes() 
{
	// TODO: Add your control notification handler code here
	m_env.clear_objects(HOME);
	m_show_paths = FALSE;
	m_homes = 0;
	update_frame();
	update_fields();

}

void MapEditor::OnButtonValidate() 
{
	// TODO: Add your control notification handler code here

	if(!validate_map())

	{

		MessageBox("This map has invalid region(s) or no space.\nThe possible invalid region(s) have been indicated in white.\nPlease make the region(s) accessible");
		
	}

	else

	{
		MessageBox("Map OK");

	}

}

void MapEditor::OnButtonLevelQuan() 
{
	// TODO: Add your control notification handler code here

	MapEditor::OnKillfocusEditSeeQuantity();

	if(m_edit_quantity == 0)

	{

		MessageBox("When setting a Mineral or Ore quantity, it must be greater than zero");
		m_edit_quantity = 1;
		return;

	}

	m_env.set_all_quantities(MINERAL, m_edit_quantity);
	m_env.set_all_quantities(ORE, m_edit_quantity);

	m_mineral_count = m_edit_quantity * m_minerals;
	m_ore_count = m_edit_quantity * m_ore;
	m_total_count = m_mineral_count + m_ore_count;
	update_frame();
	update_fields();
	
}

void MapEditor::update_paths() 
{
	// TODO: Add your control notification handler code here
	if(m_bitmap.m_hObject == NULL)

	{

		return;
			
	}// no bitmap
		
	// Create DC

	CClientDC dc(this);
		
	// Create Bitmap pointer

	CBitmap* pbmOld = NULL;

	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	pbmOld = dcMem.SelectObject(&m_bitmap);
		
	update_search_memory();
	execute_search_flood(m_grid_x,m_grid_y);

	illustrate_path();

	short size = m_colour_table.size();
	short x,y;
			
	// run through search grid

	short c1,c2,co1,co2,co3,colour;

	for(c1 = 0 ; c1 < 40 ; c1++)
	
	{

		for(c2 = 0 ; c2 < 40 ; c2++)

		{

			colour = m_s.get_f(c1,c2);
			x = c1 * 10;
			y = c2 * 10;

			if(colour > size)
				
			{
				
				dcMem.FillSolidRect(x,y,10,10,RGB(0,0,0));
				dcMem.Draw3dRect(x,y,10,10,RGB(255,255,255),RGB(0,0,0));
			
			}

			else

			{

				switch(colour)

				{

				case 0:	//unobtainable

					dcMem.FillSolidRect(x,y,10,10,RGB(255,0,0));
					break;

				case -1:	// obstacles

					dcMem.FillSolidRect(x,y,10,10,RGB(0,0,0));
					break;

				case -2:

					dcMem.FillSolidRect(x,y,10,10,RGB(0,255,0));
					break;

				default:	// path

					m_colour_table[colour].get(co1,co2,co3);
					dcMem.FillSolidRect(x,y,10,10,RGB(co1,co2,co3));
					dcMem.Draw3dRect(x,y,10,10,RGB(255,255,255),RGB(0,0,0));
					break;

				};

			}
											
		}

	}

	dc.BitBlt(10,10,400,400, &dcMem, 0, 0, SRCCOPY);
	
	dcMem.SelectObject(pbmOld);
	dcMem.DeleteDC();

}

void MapEditor::OnCheckPaths() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(!m_show_paths)

	{

		update_frame();

	}

	else

	{
		
		m_set_starts = FALSE;
		m_object_paint = 4;
		UpdateData(FALSE);

	}
	
}

void MapEditor::OnOK() 
{
	// TODO: Add extra validation here
	
	NextDlgCtrl();
	//CDialog::OnOK();
}

void MapEditor::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	
	cleanup();
	CDialog::OnOK();
}

void MapEditor::fill(const short x, const short y)

{

	update_search_memory();
	execute_search_flood(x,y);

	short a,b;

	for(a = 0 ; a < 40 ; a++)

	{

		for(b = 0 ; b < 40 ; b++)

		{

			if(m_s.get_f(a,b) > 0)

			{

				m_env.put_object_f(a,b,OBSTACLE,0);
				m_obstacles++;

			}

		}

	}
	
}

void MapEditor::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if(m_object_paint != 0 || m_set_starts)

	{

		return;

	}

	short my_x = (short)point.x;
	short my_y = (short)point.y;
	
	my_y = (my_y - 10) / 10;
	my_x = (my_x - 10) / 10;

	if(!m_env.check_coord(my_x,my_y))

	{

		return;

	}
	
	fill(my_x,my_y);

	update_frame();
			
	//CDialog::OnLButtonDblClk(nFlags, point);

}

void MapEditor::cleanup()

{

	if(m_bitmap.m_hObject != NULL)

	{

		m_bitmap.DeleteObject();
			
	}

	if(m_objects.m_hObject != NULL)

	{

		m_objects.DeleteObject();
			
	}

	m_colour_table.clear();			// vector of colours
	m_search.clear();					// search vector

}

void MapEditor::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	cleanup();
	CDialog::OnCancel();

}

void MapEditor::OnCheckStarts() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_set_starts)

	{

		m_object_paint = 4;
		m_show_paths = FALSE;
		UpdateData(FALSE);

	}
	
}

void MapEditor::illustrate_path()

{

	// first find a start
	short x,y;
	bool hit = false;

	for(x = 0 ; x < 40 ; x++)

	{

		for(y = 0 ; y < 40 ; y++)

		{

			if(m_s.get_f(x,y) == -2)

			{

				hit = true;
				break;

			}

		}

		if(hit)

		{

			break;

		}

	}

	if(!hit)

	{

		return;

	}

	short score = MAX_VALUE;
	short c1,c2,cx,cy,temp,gox,goy;
	
	// walk through setting a path

	while(!(x == m_grid_x && y == m_grid_y))

	{

		hit = false;

		for(c1 = 0 ; c1 < (MOVE_DIM - 1) ; c1+=2)

		{

			c2 = c1 + 1;

			cx = x + moves[c1];
			cy = y + moves[c2];
			
			if(m_s.check(cx,cy))
			
			{
								
				temp = m_s.get_f(cx,cy);
					//temp < score && temp != -1 && temp != 0)
				if(temp < score && temp > 0)

				{
						
					// record this move
					score = temp;
					gox = cx;
					goy = cy;
					hit = true;
				
				}
						
			}

		}

		if(hit)

		{

			m_s.put_f(gox,goy,-2);
			x = gox;
			y = goy;
			score = MAX_VALUE;

		}

		else

		{

			return;

		}

	};

}

void MapEditor::OnKillfocusEditSeeQuantity() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
}

void MapEditor::OnKillfocusEditRandMin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(((long)(m_rand_max + m_rand_min)) > 32000 ||
		m_rand_min < 1 || m_rand_max < 1)
		
	{
		
		MessageBox("Random range invalid. Maximum + coefficient must be less than 32000");
		m_rand_min = 1;
		m_rand_max = 100;
		UpdateData(FALSE);
		return;

	}

	if(m_rand_max <= m_rand_min)

	{

		MessageBox("The random coefficient must be less than the random maximum");
		m_rand_min = 1;
		m_rand_max = 100;
		UpdateData(FALSE);

	}
	
}

void MapEditor::OnKillfocusEditRandMax() 
{
	// TODO: Add your control notification handler code here
	MapEditor::OnKillfocusEditRandMin();
	
}

void MapEditor::update_fields()

{

	_itoa(m_obstacles,m_temp,10);
	m_count_obstacles = m_temp;

	_itoa(m_minerals,m_temp,10);
	m_count_minerals = m_temp;

	_itoa(m_ore,m_temp,10);
	m_count_ore = m_temp;

	_itoa(m_homes,m_temp,10);
	m_count_homes = m_temp;

	_itoa(m_mineral_count,m_temp,10);
	m_mineral_worth = m_temp;

	_itoa(m_ore_count,m_temp,10);
	m_ore_worth = m_temp;

	_itoa(m_total_count,m_temp,10);
	m_total_worth = m_temp;

	if(m_total_count < 0)

	{

		MessageBox("One or some Mineral/Ore values are too high. Please fix");

	}

	UpdateData(FALSE);

}

void MapEditor::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

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

			if(dlg.GetFileExt() != "bmp")
			
			{
			
				MessageBox("Only bitmap files (.bmp) may be saved");
				return;

			}

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

			MessageBox("Map captured and saved to " + path);  

		}


	}

	else

	{
	
		CDialog::OnRButtonDblClk(nFlags, point);

	}

}
