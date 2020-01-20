#include "stdafx.h"
#include "FigLine.h"
#include "View.h"

//���� ������
FigLine::FigLine(int x1, int y1, int x2, int y2, View *view, COLORREF line, COLORREF fill)
	:Figure(x1,y1,x2,y2,view,line,fill)
{
	m_fig = 2;
}

//������ �׸���
void FigLine::draw() {
	
	Figure::draw(); //���⼭ ��������
	mainView->drawLine(m_x1, m_y1, m_x2, m_y2);
}

void FigLine::action() {
	Figure::action();
}

void FigLine::addFigure() {
	mainView->addFigure(new FigLine(m_x1 + 20, m_y1 + 20, m_x2 + 20, m_y2 + 20, mainView, m_line, m_fill));
}

Figure* FigLine::re_copyElement() {
	return (new FigLine(m_x1 + 20, m_y1 + 20, m_x2 + 20, m_y2 + 20, mainView, m_line, m_fill));
}
