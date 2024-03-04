#include "stdafx.h"
#include "square.h"

//CONSTRUCTORS
Square::Square()
{

}



Square::Square(int type,CPoint p1, CPoint p2, COLORREF bg, int Pen_Width):RectangleM(type, p1, p2, bg, Pen_Width)
{

}

//DESTRUCTORS
Square::~Square()
{
}

void Square::Redefine(const CPoint &start, const CPoint &end) {

	int min = fmin(abs(start.x - end.x), abs(start.y - end.y));

	if (start.x < end.x && start.y < end.y)
	{
		SetEnd(start.x + min, start.y + min);
	}
	else if(start.x > end.x && start.y > end.y)
	{
		SetEnd(start.x - min, start.y - min);
	}
	else if (start.x < end.x && start.y > end.y)
	{
		SetEnd(start.x + min, start.y - min);
	}
	else if (start.x > end.x && start.y < end.y)
	{
		SetEnd(start.x - min, start.y + min);
	}
}
