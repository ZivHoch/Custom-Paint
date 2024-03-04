#include "stdafx.h"
#include "Square_like_dimond.h"


Square_like_dimond::Square_like_dimond()
{

}

Square_like_dimond::Square_like_dimond(int type,CPoint p1, CPoint p2, COLORREF bg, int Pen_Width): RectangleM(type,p1,p2,bg,Pen_Width)
{
	dots[0] = CPoint(p1.x, p1.y);
	if (p1.x == p2.x && p1.y != p2.y)
	{
		dots[1].SetPoint(p1.x - (p2.y - p1.y) / 2, (p2.y + p1.y) / 2);
		dots[2].SetPoint(p1.x, p2.y);
		dots[3].SetPoint(p1.x + (p2.y - p1.y) / 2, (p2.y + p1.y) / 2);
	}
	else
	{
		dots[1].SetPoint((p1.x + p2.x) / 2, p1.y - (p1.x - p2.x) / 2);
		dots[2].SetPoint(p2.x, p1.y);
		dots[3].SetPoint((p1.x + p2.x) / 2, p1.y + (p1.x - p2.x) / 2);
	}
	SetType(5);
}

Square_like_dimond::~Square_like_dimond()
{

}

void Square_like_dimond::Draw(CDC *dc, const COLORREF &BG_color, const int &penwidth) 
{
	CPen pen(PS_SOLID, penwidth, fg);
	CBrush brush(BG_color);
	CPen *oldPen = dc->SelectObject(&pen);
	CBrush *oldBrush = dc->SelectObject(&brush);
	dc->Polygon(dots, 4);
}

void Square_like_dimond::Redefine(const CPoint &p1, const CPoint &p2)
{
	CPoint temp;
	if (p1.x -3 > p2.x) 
	{
		dots[0].SetPoint(p1.x, p1.y);
		SetStart(p1.x, p1.y);
		dots[1].SetPoint((p1.x + p2.x) / 2, p1.y - (p1.x - p2.x) / 2);
		dots[2].SetPoint(p2.x, p1.y);
		dots[3].SetPoint((p1.x + p2.x) / 2, p1.y + (p1.x - p2.x) / 2);
		SetEnd(p2.x, p1.y);
	}
	else if(p1.x < p2.x -3)
	{
		SetStart(p2.x, p1.y);
		dots[0] = GetStart();
		dots[1].SetPoint((p1.x + p2.x) / 2, p1.y - (p1.x - p2.x) / 2);
		dots[2] = p1;
		dots[3].SetPoint((p1.x + p2.x) / 2, p1.y + (p1.x - p2.x) / 2);
		SetEnd(p2.x, p1.y);
	}
	else if (p1.y-3> p2.y)
	{
		SetStart(p1.x + (p1.y - p2.y) / 2, (p1.y + p2.y) / 2);
		dots[0] = GetStart();
		dots[1].x = p1.x;
		dots[1].y = p2.y;
		dots[2].SetPoint(p1.x - (p1.y - p2.y) / 2,(p1.y + p2.y) / 2);
		dots[3].x = p1.x;
		dots[3].y = p1.y;
		SetEnd(dots[2].x, dots[2].y);
	}
	else if (p1.y < p2.y)
	{
		SetStart(p1.x + (p1.y - p2.y) / 2, (p1.y + p2.y) / 2);
		dots[0] = GetStart();
		dots[1].x = p1.x;
		dots[1].y = p2.y;
		dots[2].SetPoint(p1.x - (p1.y - p2.y) / 2, (p1.y + p2.y) / 2);
		dots[3].x = p1.x;
		dots[3].y = p1.y;
		SetEnd(dots[2].x, dots[2].y);
	}
}

bool Square_like_dimond::isInside(const CPoint & P) const
{
	if (dots[0].x > dots[2].x || dots[0].y > dots[2].y)
	{
		CPoint left_buttom_mid((dots[2].x + dots[3].x) / 2, (dots[2].y + dots[3].y) / 2);
		CPoint left_up_mid((dots[2].x + dots[1].x) / 2, (dots[2].y + dots[1].y) / 2);
		CPoint right_buttom_mid((dots[0].x + dots[3].x) / 2, (dots[0].y + dots[3].y) / 2);
		CPoint right_up_mid((dots[0].x + dots[1].x) / 2, (dots[0].y + dots[1].y) / 2);
		if ((P.x >= left_buttom_mid.x && P.x <= right_buttom_mid.x) && (P.y <= left_buttom_mid.y && P.y >= right_up_mid.y))
		{
			return true;
		}
	}
	else
	{
		CPoint left_buttom_mid((dots[2].x + dots[3].x) / 2, (dots[2].y + dots[3].y) / 2);
		CPoint left_up_mid((dots[2].x + dots[1].x) / 2, (dots[2].y + dots[1].y) / 2);
		CPoint right_buttom_mid((dots[0].x + dots[3].x) / 2, (dots[0].y + dots[3].y) / 2);
		CPoint right_up_mid((dots[0].x + dots[1].x) / 2, (dots[0].y + dots[1].y) / 2);
		if ((P.x >= left_buttom_mid.x && P.x <= right_buttom_mid.x) && (P.y >= left_buttom_mid.y && P.y >= right_up_mid.y))
		{
			return true;
		}
	}
	return false;
}





