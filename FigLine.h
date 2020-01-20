#pragma once

#include "Figure.h"

//선분클래스
class FigLine :public Figure {
public:
	//생성자
	FigLine(int x1, int y1, int x2, int y2, View *view, COLORREF line, COLORREF fill);

	//선분을 그린다
	virtual void draw();
	virtual void action();
	virtual void addFigure();
	virtual Figure* re_copyElement();
};