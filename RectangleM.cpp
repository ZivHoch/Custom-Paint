#include "stdafx.h"
#include "RectangleM.h"


IMPLEMENT_SERIAL(RectangleM, CObject, 1)

RectangleM::RectangleM()
{
}

//CONSTRUCTOR

RectangleM::RectangleM(int type,CPoint p1, CPoint p2, COLORREF bg, int Pen_Width) :Figure2D(type ,p1, p2, bg, Pen_Width)
{
}

//DESTRUCTOR
RectangleM::~RectangleM() {
}

void RectangleM::Draw(CDC *dc, const COLORREF &BG_color, const int &penwidth) 
{
	CPen pen(PS_SOLID, penwidth,fg);//PS_DASHDOT for kavim mekuvkavim
	CBrush brush(BG_color);
	CPen *oldPen = dc->SelectObject(&pen);
	CBrush *oldBrush = dc->SelectObject(&brush);
	dc->Rectangle(this->GetStart().x, this->GetStart().y, this->GetEnd().x, this->GetEnd().y);
}