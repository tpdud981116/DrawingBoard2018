#pragma once

#include "Figure.h"

//사각형클래스
class FigRect :public Figure {
public:
	//생성자
	FigRect(int x1, int y1, int x2, int y2, View *view, COLORREF line, COLORREF fill);

	//사각형을 그린다
	virtual void draw();
	virtual void action();
	virtual void addFigure();
	virtual Figure* re_copyElement();
};