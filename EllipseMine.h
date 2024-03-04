#pragma once
#include "stdafx.h"
#include "Figure2D.h"



class EllipseMine :public Figure2D
{

	DECLARE_SERIAL(EllipseMine)

public:
	EllipseMine();
	EllipseMine(int type,CPoint p1, CPoint p2, COLORREF bg, int Pen_Width);
	~EllipseMine();

	void Draw(CDC *dc, const COLORREF &BG_color, const int &penwidth) ;
	int Resize(const CPoint &point);
	
};

