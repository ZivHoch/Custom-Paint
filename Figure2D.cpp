
#include "stdafx.h"
#include "Figure2D.h"

IMPLEMENT_SERIAL(Figure2D, CObject, 1)

//CONSTRUCTORS
Figure2D::Figure2D() { 
	
	fg = RGB(0, 0, 0); 
}

Figure2D::Figure2D(int type,CPoint p1, CPoint p2, COLORREF bg, int Pen_Width) {

	this->Start = p1;
	this->End = p2;
	this->bg = bg;
	this->Pen_Width = Pen_Width;
}

//DESTRUCTOR
Figure2D::~Figure2D() {

}

//GET FUNCTIONS
CPoint Figure2D::GetStart()const
{
	return this->Start;
}

CPoint Figure2D::GetEnd()const
{
	return this->End;
}

int Figure2D::GetType()
{
	return Type;
}

COLORREF Figure2D::Get_bg_color()
{
	return bg;
}

COLORREF Figure2D::Get_fg_color()
{
	return fg;
}

int Figure2D::GetPenWidth()
{
	return Pen_Width;
}

//SET FUNCTIONS
void Figure2D::SetStart(int x , int y)
{
	this->Start.x = x;
	this->Start.y = y;
}

void Figure2D::SetEnd(int x , int y)
{
	this->End.x = x;
	this->End.y = y;
}

void Figure2D::SetType(int type)
{
	this->Type = type;
}

void Figure2D::SetPenWidth(int number)
{
	Pen_Width = number;
}

void Figure2D::SetShape_Color(COLORREF color)
{
	bg = color;
}

void Figure2D::Set_bg_color(COLORREF BG)
{
	bg = BG;
}



//CLASS FUNCTIONS

void Figure2D::Serialize(CArchive& ar) {

	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << Start;
		ar << End;
		ar << bg;
		ar << fg;
		ar << Type;
		ar << Pen_Width;
	}
	else // Loading, not storing
	{
		ar >> Start;
		ar >> End;
		ar >> bg;
		ar >> fg;
		ar >> Type;
		ar >> Pen_Width;
	}
}

void Figure2D::Draw(CDC *dc, const COLORREF &BG_color, const int &penwidth)  
{
	Draw(dc,BG_color,penwidth);
}

bool Figure2D::isInside(const CPoint &P) const
{

	return (Start.x <= P.x && P.x <= End.x || Start.x >= P.x && P.x >= End.x) &&
		(Start.y <= P.y && P.y <= End.y || Start.y >= P.y && P.y >= End.y);
}

int Figure2D::Resize(const CPoint &point)
{
	CPoint left_up(fmin(Start.x, End.x), fmin(Start.y, End.y)); //left_up
	CPoint left_down(fmin(Start.x, End.x), fmax(Start.y, End.y)); //left_down
	CPoint right_up(fmax(Start.x, End.x), fmin(Start.y, End.y)); //right_up
	CPoint right_down(fmax(Start.x, End.x), fmax(Start.y, End.y)); //right_down

	if ((left_down.x-6  <= point.x && left_down.x +6 >= point.x) && (left_down.y + 6 >= point.y && left_down.y- 6 <= point.y))
	{
		Start.x = right_up.x;
		Start.y = right_up.y;
		End.x = left_down.x;
		End.y = left_down.y;
		return 2;
	}
	else if ((left_up.x - 6 <= point.x && left_up.x + 6 >= point.x) && (left_up.y + 6 >= point.y && left_up.y - 6 <= point.y))
	{
		Start.x = right_down.x;
		Start.y = right_down.y;
		End.x = left_up.x;
		End.y = left_up.y;
		return 2;
	}
	else if ((right_down.x - 6 <= point.x && right_down.x + 6 >= point.x) && (right_down.y + 6 >= point.y && right_down.y - 6 <= point.y))
	{
		Start.x = left_up.x;
		Start.y = left_up.y;
		End.x = right_down.x;
		End.y = right_down.y;
		return 2;
	}
	else if ((right_up.x - 6 <= point.x && right_up.x + 6 >= point.x) && (right_up.y + 6 >= point.y && right_up.y - 6 <= point.y))
	{
		Start.x = left_down.x;
		Start.y = left_down.y;
		End.x = right_up.x;
		End.y = right_up.y;
		return 2;
	}
	return 1;

}

void Figure2D::Redefine(const CPoint &p1, const CPoint &p2)
{ 
	 Start = p1; 
	 End = p2; 
}


