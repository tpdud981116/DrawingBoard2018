#pragma once

#include "Figure.h"

//Ÿ��Ŭ����
class FigEllipse :public Figure {
public:
	//������
	FigEllipse(int x1, int y1, int x2, int y2, View *view, COLORREF line, COLORREF fill);

	//Ÿ���� �׸���
	virtual void draw();
	virtual void action();
	virtual void addFigure();
	virtual Figure* re_copyElement();
};