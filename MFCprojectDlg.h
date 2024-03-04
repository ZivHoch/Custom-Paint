// MFCprojectDlg.h : header file
//

#include<stack>
#include "square.h"
#include "Circle.h"
#include "Figure2D.h"
#include "MFCproject.h"
#include "RectangleM.h"
#include "EllipseMine.h"
#include "Square_like_dimond.h"

using namespace std;

#pragma once

// CMFCprojectDlg dialog
class CMFCprojectDlg : public CDialogEx
{

// Construction
public:
	CMFCprojectDlg(CWnd* pParent = nullptr);	// standard constructor

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPROJECT_DIALOG };
#endif
	
	enum FIGURES {null, DRAGME, DIAMOND, CIRCLE, SQUARE, RECTANGLE, ELLIPSE};
	
	bool isPressed;//flag for if mouse is pressed
	int Resize;
	int pen_width;
	int who_to_move;
	int who_to_resize;
	int with_or_without_borders;
	FIGURES Which_Shape_To_Draw;
	RectangleM Area_To_Draw;
	CBrush mybrush;
	COLORREF fg, bg;
	CPoint startingPoint;//x,y of beginnig 
	CPoint endingPoint;//x,y of end
	CTypedPtrArray< CObArray, Figure2D*>figs;
	stack<Figure2D*>undone;
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	DECLARE_MESSAGE_MAP();

public:
	virtual BOOL OnInitDialog();
	
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void SetPenWidth();
	afx_msg bool isInside_Area_To_Draw(int startX, int startY, int endX, int endY) const;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	BOOL isThin;
	CComboBox m_ComboPenWidth;
	~CMFCprojectDlg();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadioSquare();
	afx_msg void OnBnClickedRadioCircle();
	afx_msg void OnBnClickedRadioDrag();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedRadioRezise();
	afx_msg void OnBnClickedButtonchoosecolor();
	afx_msg void OnCbnSelchangeCombodropdownlist();
	afx_msg void OnCbnSelendokCombodropdownlist();
	afx_msg void OnBnClickedButtonUndo();
	afx_msg void OnBnClickedButtonRedo();
	afx_msg void OnBnClickedCheckWithborder();
	afx_msg void OnBnClickedRadiorectanglelikediamond();
	afx_msg void OnBnClickedButtonFlushAll();
};
