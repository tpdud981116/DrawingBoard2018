#pragma once

#include "Figure.h"

//�簢��Ŭ����
class FigRect :public Figure {
public:
	//������
	FigRect(int x1, int y1, int x2, int y2, View *view, COLORREF line, COLORREF fill);

	//�簢���� �׸���
	virtual void draw();
	virtual void action();
	virtual void addFigure();
	virtual Figure* re_copyElement();
};