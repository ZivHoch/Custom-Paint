#pragma once
#include "stdafx.h"
#include "EllipseMine.h"

class Circle: public EllipseMine {

public:

	//constructors

	Circle(int type, CPoint p1, CPoint p2, COLORREF bg, int Pen_Width);
	
	//destructor
	~Circle();

	//functions
	void Redefine(const CPoint &p1, const CPoint &p2);
};

