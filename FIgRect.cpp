#include "stdafx.h"
#include "FigRect.h"
#include "View.h"

//사각형 생성자
FigRect::FigRect(int x1, int y1, int x2, int y2, View *view, COLORREF line, COLORREF fill)
	:Figure(x1,y1,x2,y2,view,line,fill)
{
	if (m_x1 > m_x2) {  // 좌-우를 바꾼다.
		int t = m_x1; m_x1 = m_x2; m_x2 = t;
	}
	if (m_y1 > m_y2) {  // 상-하를 바꾼다.
		int t = m_y1; m_y1 = m_y2; m_y2 = t;
	}

	m_fig = 0;
}

//사각형을 그린다
void FigRect::draw() {
	
	Figure::draw();//여기서 색지정함
	mainView->drawRectangle(m_x1, m_y1, m_x2, m_y2);
}

void FigRect::action() {
	Figure::action();
}

void FigRect::addFigure() {
	mainView->addFigure(new FigRect(m_x1 + 20, m_y1 + 20, m_x2 + 20, m_y2 + 20,mainView,m_line,m_fill));
}

Figure* FigRect::re_copyElement() {
	return (new FigRect(m_x1 + 20, m_y1 + 20, m_x2 + 20, m_y2 + 20, mainView, m_line, m_fill));
}