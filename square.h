#pragma once
#include "stdafx.h"
#include "RectangleM.h"



class Square : public RectangleM
{
	
public:

	//CONSTRUCTORS
	Square();
	Square(int type,CPoint p1, CPoint p2, COLORREF bg, int Pen_Width);
	
	//DESTRUCTORS
	~Square();

	void Redefine(const CPoint &start,const CPoint &end);
 
};

