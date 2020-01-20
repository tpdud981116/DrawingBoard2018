#pragma once

#include "Figure.h"

//타원클래스
class FigEllipse :public Figure {
public:
	//생성자
	FigEllipse(int x1, int y1, int x2, int y2, View *view, COLORREF line, COLORREF fill);

	//타원을 그린다
	virtual void draw();
	virtual void action();
	virtual void addFigure();
	virtual Figure* re_copyElement();
};