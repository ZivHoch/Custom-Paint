// MFCprojectDlg.cpp : implementation file
#include "stdafx.h"
#include "afxcolorbutton.h"
#include "afxdialogex.h"
#include "MFCprojectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCprojectDlg dialog

CMFCprojectDlg::CMFCprojectDlg(CWnd* pParent): CDialogEx(IDD_MFCPROJECT_DIALOG, pParent){

	who_to_resize = 0;
	who_to_move =0;
	Resize = 0;
	pen_width = 5;
	isPressed = false;
	with_or_without_borders = 1;
	Which_Shape_To_Draw = RECTANGLE;
	Area_To_Draw.SetStart(10,10);
	Area_To_Draw.SetEnd(900, 900);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//microsoft
}

void CMFCprojectDlg::DoDataExchange(CDataExchange* pDX)//microsoft
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBODROPDOWNLIST, m_ComboPenWidth);
}

BEGIN_MESSAGE_MAP(CMFCprojectDlg, CDialogEx)

	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_RADIO5, &CMFCprojectDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CMFCprojectDlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO_Square, &CMFCprojectDlg::OnBnClickedRadioSquare)
	ON_BN_CLICKED(IDC_RADIO_Circle, &CMFCprojectDlg::OnBnClickedRadioCircle)
	ON_BN_CLICKED(IDC_RADIO_DRAG, &CMFCprojectDlg::OnBnClickedRadioDrag)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMFCprojectDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CMFCprojectDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_RADIO_REZISE, &CMFCprojectDlg::OnBnClickedRadioRezise)
	ON_BN_CLICKED(IDC_BUTTONCHOOSECOLOR, &CMFCprojectDlg::OnBnClickedButtonchoosecolor)
	ON_CBN_SELCHANGE(IDC_COMBODROPDOWNLIST, &CMFCprojectDlg::OnCbnSelchangeCombodropdownlist)
	ON_CBN_SELENDOK(IDC_COMBODROPDOWNLIST, &CMFCprojectDlg::OnCbnSelendokCombodropdownlist)
	ON_BN_CLICKED(IDC_BUTTON_Undo, &CMFCprojectDlg::OnBnClickedButtonUndo)
	ON_BN_CLICKED(IDC_BUTTON_REDO, &CMFCprojectDlg::OnBnClickedButtonRedo)
	ON_BN_CLICKED(IDC_CHECK_With_border, &CMFCprojectDlg::OnBnClickedCheckWithborder)
	ON_BN_CLICKED(IDC_RADIORECTANGLELIKEDIAMOND, &CMFCprojectDlg::OnBnClickedRadiorectanglelikediamond)

	ON_BN_CLICKED(IDC_BUTTON_FLUSH_ALL, &CMFCprojectDlg::OnBnClickedButtonFlushAll)
END_MESSAGE_MAP()

// CMFCprojectDlg message handlers

BOOL CMFCprojectDlg::OnInitDialog() {

	//these commands create the dropdown list for the sizes of the pen
	CDialogEx::OnInitDialog();
	int i = 1;
	pen_width = 5;
	m_ComboPenWidth.AddString(_T("Select Pen Width"));
	char sBuf[10];
	for (; i < 10; i++)
		m_ComboPenWidth.AddString(CString(itoa(i, sBuf, 10)));
	m_ComboPenWidth.SetCurSel(9);
	//end of command lines

	//microsoft
	CheckRadioButton(IDC_RADIO5, IDC_RADIO6, IDC_RADIO5);//sets this button as defaul
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control

}

void CMFCprojectDlg::OnPaint() {

	CFont font, *oldFont;
	CBrush myBrush, *oldBrush;
	CPaintDC dc(this);
	CDC pDC();
	CRect rect;
	CString string;
	if (with_or_without_borders == 0)
	{
		
		myBrush.CreateSolidBrush(RGB(0, 100, 100));
		oldBrush = dc.SelectObject(&myBrush);//start drawing
		dc.Rectangle(Area_To_Draw.GetStart().x, Area_To_Draw.GetStart().y, Area_To_Draw.GetEnd().x, Area_To_Draw.GetEnd().y);
		dc.SelectObject(oldBrush);//stop drawing
	}
	GetClientRect(&rect);//this is for the cordinations
	font.CreatePointFont(500, _T("Showcard Gothic"));
	oldFont = dc.SelectObject(&font);//end
	dc.SetBkMode(TRANSPARENT); //this is for the background color ,brushes and pen style.
	string = _T("Welcome");//what text
	rect.OffsetRect(400, 400);//size of the text
	dc.SetTextColor(RGB(0, 0, 0));//whcih color
	dc.DrawText(string, &rect, DT_SINGLELINE |DT_CENTER | DT_VCENTER);

	//drawing the shapes
	for (int i = 0; i < figs.GetSize(); i++)
	{
		figs[i]->Draw(&dc,figs[i]->Get_bg_color(), figs[i]->GetPenWidth());		
	}
	CDialogEx::OnPaint();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
//microsoft
HCURSOR CMFCprojectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCprojectDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (with_or_without_borders || isInside_Area_To_Draw(point.x,point.y,point.x,point.y))
	{
		startingPoint = endingPoint = point;
		isPressed = true;
		switch (Which_Shape_To_Draw)
		{
			case DIAMOND:
			{
				figs.Add(new Square_like_dimond(5, startingPoint, endingPoint,bg,pen_width));
				figs[figs.GetSize() - 1]->Figure2D::SetPenWidth(pen_width);
				figs[figs.GetSize() - 1]->SetShape_Color(bg);
				break;
			}
			case RECTANGLE:
			{
				figs.Add(new RectangleM(1, startingPoint, endingPoint,bg,pen_width));
				break;
			}
			case ELLIPSE:
			{
				figs.Add(new EllipseMine(2, startingPoint, endingPoint, bg, pen_width));
				break;
			}

			case SQUARE:
			{
				figs.Add(new Square(4, startingPoint, endingPoint, bg, pen_width));
				break;
			}
			case CIRCLE:
			{
				figs.Add(new Circle(3, startingPoint, endingPoint, bg, pen_width));
				break;
			}
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMFCprojectDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (isPressed)
	{
		if (Resize > 1)
		{
			Resize = 1;
		}
		who_to_move = 0;
		endingPoint = point;
		isPressed = false;
		Invalidate();
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CMFCprojectDlg::OnMouseMove(UINT nFlags, CPoint point) {
	
	int i;
	CString str;
	CClientDC dc(this);
	str.Format(_T("X:%d , y:%d"), point.x , point.y);
	dc.TextOutW(0, 920, str);

	if (isPressed)
	{
		if (!Resize)
		{
			if (Which_Shape_To_Draw == DRAGME)
			{
				
				for (i = ((who_to_move !=0)? who_to_move -1:(figs.GetSize()-1)); i >= 0; i--)
				{
					if (figs[i]->GetType() == 5)
					{
						int ab = abs(figs[i]->GetStart().x - startingPoint.x);
						if (with_or_without_borders || isInside_Area_To_Draw(point.x - ab -5, point.y - ab - 5, point.x + ab +5, point.y + ab +5))
						{
							if (figs[i]->isInside(point))
							{
								if (who_to_move == 0)
									who_to_move = i + 1;
								CPoint temp(point.x - (startingPoint.x - figs[i]->GetStart().x), point.y - abs(figs[i]->GetStart().y - startingPoint.y));
								figs[i]->SetEnd(point.x - abs(startingPoint.x - (figs[i]->GetEnd().x)), point.y - abs(figs[i]->GetEnd().y - startingPoint.y));
								figs[i]->Redefine(temp, figs[i]->GetEnd());
								startingPoint = point;
								i = -1;
							}
						}
					}
					else
					{
						if (figs[i]->isInside(point))
						{
							if (with_or_without_borders || isInside_Area_To_Draw(point.x - abs(figs[i]->GetStart().x - startingPoint.x), point.x + abs(figs[i]->GetEnd().x - startingPoint.x), point.y - abs(figs[i]->GetStart().y - startingPoint.y), point.y + abs(figs[i]->GetEnd().y - startingPoint.y)))
							{
								if (who_to_move == 0)
								{
									who_to_move = i + 1;
								}
								figs[i]->SetStart(point.x - abs(figs[i]->GetStart().x - startingPoint.x), point.y - abs(figs[i]->GetStart().y - startingPoint.y));
								figs[i]->SetEnd(point.x + abs(figs[i]->GetEnd().x - startingPoint.x), point.y + abs(figs[i]->GetEnd().y - startingPoint.y));
								startingPoint.x = point.x;
								startingPoint.y = point.y;
								i = -1;
							}
						}
					}	
				}
			}
			else
			{
				endingPoint = point;
				if (with_or_without_borders || isInside_Area_To_Draw(point.x, point.y, startingPoint.x, startingPoint.y))
				{
					figs[figs.GetSize() - 1]->Redefine(startingPoint, endingPoint);
				}
			}
			Invalidate();
		}
		else
		{
			for (int i = 0; i < figs.GetSize(); i++)
			{
				if (with_or_without_borders ||  isInside_Area_To_Draw(startingPoint.x, startingPoint.y, point.x, point.y))
				{
					if (Resize == 2)
					{
						figs[who_to_resize]->Redefine(figs[who_to_resize]->GetStart(), point);
						break;
					}
					else if (Resize == 3 || Resize == 6)
					{
						if (figs[who_to_move]->GetType() == 3)
						{
							if (figs[who_to_resize]->GetEnd().x > point.x)
							{
								figs[who_to_resize]->SetEnd(abs(figs[who_to_resize]->GetEnd().x - abs(figs[who_to_resize]->GetEnd().x - point.x)), point.y);
							}
							else
							{
								figs[who_to_resize]->SetEnd(figs[who_to_resize]->GetEnd().x + abs(figs[who_to_resize]->GetEnd().x - point.x), point.y);
							}
						}
						else
							figs[who_to_resize]->SetEnd(figs[who_to_resize]->GetEnd().x, point.y);

						figs[who_to_resize]->Redefine(figs[who_to_resize]->GetStart(), figs[who_to_resize]->GetEnd());
						break;
					}
					else if (Resize == 4 || Resize == 5)
					{
						if (figs[who_to_move]->GetType() == 3)
						{
							if (figs[who_to_resize]->GetEnd().y > point.y)
							{
								figs[who_to_resize]->SetEnd(point.x, abs(figs[who_to_resize]->GetEnd().y - abs(figs[who_to_resize]->GetEnd().y - point.y)));
							}
							else
								figs[who_to_resize]->SetEnd(point.x, figs[who_to_resize]->GetEnd().y + abs(figs[who_to_resize]->GetEnd().y - point.y));

						}
						else
							figs[who_to_resize]->SetEnd(point.x, figs[who_to_resize]->GetEnd().y);

						figs[who_to_resize]->Redefine(figs[who_to_resize]->GetStart(), figs[who_to_resize]->GetEnd());
						break;
					}
					else
					{
						if (figs[i]->isInside(point))
						{
							Resize = figs[i]->Resize(point);
							who_to_resize = i;
							break;
						}
					}
				}
			}
			Invalidate();
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}

CMFCprojectDlg::~CMFCprojectDlg()
{
	for (int i = 0; i < figs.GetSize(); i++)
		delete figs[i];
}

void CMFCprojectDlg::OnBnClickedRadio5()
{
	Which_Shape_To_Draw = RECTANGLE;
	Resize = 0;
}

void CMFCprojectDlg::OnBnClickedRadio6()
{
	Which_Shape_To_Draw = ELLIPSE;
	Resize = 0;
}

void CMFCprojectDlg::OnBnClickedRadioSquare()
{
	Which_Shape_To_Draw = SQUARE;
	Resize = 0;
}

void CMFCprojectDlg::OnBnClickedRadioCircle()
{
	Which_Shape_To_Draw = CIRCLE;
	Resize = 0;
}

void CMFCprojectDlg::OnBnClickedRadioDrag()
{
	Which_Shape_To_Draw = DRAGME;
	Resize = 0;
}

bool CMFCprojectDlg::isInside_Area_To_Draw(int startX, int startY, int endX, int endY) const
{
	return ((Area_To_Draw.GetStart().x < startX && Area_To_Draw.GetStart().y < startY) &&
		(Area_To_Draw.GetStart().x < endX && Area_To_Draw.GetStart().y < endY) &&
		(Area_To_Draw.GetEnd().x > startX && Area_To_Draw.GetEnd().y > startY) &&
		(Area_To_Draw.GetEnd().x > endX && Area_To_Draw.GetEnd().y > endY));
}

void CMFCprojectDlg::OnBnClickedButtonSave()
{
	CFileDialog dlg(FALSE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;	
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		figs.Serialize(ar);
		ar.Close();
		file.Close();
	}
}

void CMFCprojectDlg::OnBnClickedButtonLoad()
{
	CFileDialog dlg(TRUE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		figs.Serialize(ar);
		ar.Close();
		file.Close();
		Invalidate();
	}
}

void CMFCprojectDlg::OnBnClickedRadioRezise()
{
	Resize = 1;
	Which_Shape_To_Draw = null;
}

void CMFCprojectDlg::OnBnClickedButtonchoosecolor()
{
	CColorDialog dcolor;
	if (dcolor.DoModal() == IDOK)
	{
		bg = dcolor.GetColor();
	}
}

void CMFCprojectDlg::OnCbnSelchangeCombodropdownlist()
{
	SetPenWidth();
}

void CMFCprojectDlg::SetPenWidth()
{
	int nIndex = m_ComboPenWidth.GetCurSel();
	CString strCBText;
	m_ComboPenWidth.GetLBText(nIndex, strCBText);
	CT2A ascii(strCBText);
	pen_width = atoi(ascii.m_psz);
	if (pen_width == 0)
		pen_width = 1;
}

void CMFCprojectDlg::OnCbnSelendokCombodropdownlist()
{
	SetPenWidth();
}

void CMFCprojectDlg::OnBnClickedButtonUndo()
{
	if (figs.GetSize() >= 1)
	{
		Figure2D *figure = figs[figs.GetSize() - 1];
		figs.RemoveAt(figs.GetSize() - 1, 1);
		undone.push(figure);
		Invalidate();
	}
}

void CMFCprojectDlg::OnBnClickedButtonRedo()
{
	if (!undone.empty())
	{
		Figure2D *figure = undone.top();
		figs.Add(figure);
		undone.pop();
		Invalidate();
	}
}

void CMFCprojectDlg::OnBnClickedCheckWithborder()
{
	if (with_or_without_borders == 1)
		with_or_without_borders = 0;
	else
		with_or_without_borders = 1;
	figs.RemoveAll();
	while(!undone.empty())
	{
		undone.pop();
	}
	Invalidate();
}

void CMFCprojectDlg::OnBnClickedRadiorectanglelikediamond()
{
	Which_Shape_To_Draw = DIAMOND;
	Resize = 0;
}


void CMFCprojectDlg::OnBnClickedButtonFlushAll()
{
	figs.RemoveAll();
	while (!undone.empty())
	{
		undone.pop();
	}
	Invalidate();
}
