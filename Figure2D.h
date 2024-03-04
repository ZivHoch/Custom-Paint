#pragma once

#include "stdafx.h"
#include <math.h>
class Figure2D : public CObject {

	DECLARE_SERIAL(Figure2D)

private:
	int Pen_Width;
	int Type = 0;//figure - 0 , rectangle - 1 , ellipse -2 , circle -3 , square - 4 , diamond - 5
	COLORREF bg;
	CPoint Start;
	CPoint End;
	

public:
	//PUBLIC VARIABLE
	COLORREF fg;

	//constructors
	Figure2D();
	Figure2D(int type,CPoint p1, CPoint p2,COLORREF bg,int Pen_Width);
	
	//destructor
	~Figure2D();

	//virtual functions
	virtual void Draw(CDC *dc,const COLORREF &BG_color,const int &penwidth);
	virtual void Redefine(const CPoint &p1,const CPoint &p2);
	virtual bool isInside(const CPoint &P) const;
	virtual int Resize(const CPoint &point);
	
	//functions
	virtual void Serialize(CArchive& ar);
	void SetStart(int x, int y);
	void Figure2D::SetEnd(int x, int y);
	CPoint GetStart()const;
	CPoint Figure2D::GetEnd()const;

	//GET FUNCTIONS
	int GetType();
	int GetPenWidth();
	COLORREF Get_bg_color();
	COLORREF Get_fg_color();
	
	//SET FUNCTIONS
	void SetType(int type);
	void SetPenWidth(int number);
	void SetShape_Color(COLORREF color);
	void Set_bg_color(COLORREF BG);
	
	
};

