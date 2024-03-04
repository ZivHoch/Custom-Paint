#include "stdafx.h"
#include "EllipseMine.h"


IMPLEMENT_SERIAL(EllipseMine, CObject, 1)

EllipseMine::EllipseMine()
{
}


EllipseMine::EllipseMine(int type,CPoint p1, CPoint p2, COLORREF bg, int Pen_Width):Figure2D(type, p1,  p2,bg,Pen_Width)
{
}

EllipseMine::~EllipseMine()
{

}

void EllipseMine::Draw(CDC *dc, const COLORREF &BG_color, const int &penwidth) 
{
	CPen pen(PS_SOLID, penwidth, fg);
	CBrush brush(BG_color);
	CPen *oldPen = dc->SelectObject(&pen);
	CBrush *oldBrush = dc->SelectObject(&brush);
	dc->Ellipse(this->GetStart().x, this->GetStart().y, this->GetEnd().x, this->GetEnd().y);
}

int EllipseMine::Resize(const CPoint &point)
{
		CPoint left_up(fmin(GetStart().x , GetEnd().x), (GetStart().y + GetEnd().y)/2); //left_up;
		CPoint left_down((GetStart().x + GetEnd().x) / 2, fmax(GetStart().y, GetEnd().y)); //left_down;
		CPoint right_up((GetStart().x + GetEnd().x) / 2, fmin(GetStart().y, GetEnd().y));
		CPoint right_down(fmax(GetStart().x , GetEnd().x), (GetStart().y + GetEnd().y)/2);
		double temp1;
		double temp2;
		if ((left_down.x - 6 <= point.x && left_down.x + 6 >= point.x) && (left_down.y + 6 >= point.y && left_down.y - 6 <= point.y))
		{
			temp1 = fmax(GetStart().x, GetEnd().x);
			SetEnd(fmin(GetStart().x, GetEnd().x), left_down.y);
			SetStart(temp1, right_up.y);
			return 3;
		}
		else if ((left_up.x - 6 <= point.x && left_up.x + 6 >= point.x) && (left_up.y + 6 >= point.y && left_up.y - 6 <= point.y))
		{
			temp1 = fmax(GetStart().y, GetEnd().y);
			temp2 = fmax(GetStart().x, GetEnd().x);
			SetEnd(left_up.x, fmin(GetStart().y,GetEnd().y));
			SetStart(temp2,temp1);
			return 4;
		}
		else if ((right_down.x - 6 <= point.x && right_down.x + 6 >= point.x) && (right_down.y + 6 >= point.y && right_down.y - 6 <= point.y))
		{
			temp1 = fmin(GetStart().y, GetEnd().y);
			SetEnd(right_down.x, fmax(GetStart().y,GetEnd().y));
			SetStart(left_up.x, temp1);
			return 5;
		}
		else if ((right_up.x - 6 <= point.x && right_up.x + 6 >= point.x) && (right_up.y + 6 >= point.y && right_up.y - 6 <= point.y))
		{
			temp1 = fmin(GetStart().x, GetEnd().x);
			SetEnd(fmax(GetStart().x, GetEnd().x), right_up.y);
			SetStart(temp1, left_down.y);
			return 6;
		}
		return 1;
}

