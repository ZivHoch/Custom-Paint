#pragma once
#include "stdafx.h"
#include "Figure2D.h"


class RectangleM:public Figure2D
{
	DECLARE_SERIAL(RectangleM)

public:

	//CONSTRUCTOR
	RectangleM();
	RectangleM(int type, CPoint p1, CPoint p2, COLORREF bg, int Pen_Width);
	
	//DESTRUCTORS
	~RectangleM();
	
	//FUNCTIONS
	virtual void Draw(CDC *dc, const COLORREF &BG_color, const int &penwidth);
};


