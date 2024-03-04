#pragma once
#include "RectangleM.h"





class Square_like_dimond : public RectangleM
{


private:
	CPoint dots[4];
public:
	Square_like_dimond();
	Square_like_dimond(int type,CPoint p1, CPoint p2, COLORREF bg, int Pen_Width);

	~Square_like_dimond();
	void Draw(CDC *dc, const COLORREF &BG_color, const int &penwidth);
	void Redefine(const CPoint &p1, const CPoint &p2);
	bool isInside(const CPoint &P) const ;
};