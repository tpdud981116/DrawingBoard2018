#pragma once

#include "Figure.h"

//����Ŭ����
class FigLine :public Figure {
public:
	//������
	FigLine(int x1, int y1, int x2, int y2, View *view, COLORREF line, COLORREF fill);

	//������ �׸���
	virtual void draw();
	virtual void action();
	virtual void addFigure();
	virtual Figure* re_copyElement();
};