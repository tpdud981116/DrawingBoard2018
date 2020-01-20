#include "stdafx.h"
#include "FigEllipse.h"
#include "View.h"


//타원 생성자
FigEllipse::FigEllipse(int x1, int y1, int x2, int y2, View *view, COLORREF line, COLORREF fill)
	:Figure(x1,y1,x2,y2,view,line,fill)
{
	if (m_x1 > m_x2) {  // 좌-우를 바꾼다.
		int t = m_x1; m_x1 = m_x2; m_x2 = t;
	}
	if (m_y1 > m_y2) {  // 상-하를 바꾼다.
		int t = m_y1; m_y1 = m_y2; m_y2 = t;
	}
	m_fig = 1;
}

//타원을 그린다
void FigEllipse::draw() {
	
	Figure::draw(); //여기서 색지정함
	mainView->drawEllipse(m_x1, m_y1, m_x2, m_y2);
}
void FigEllipse::action() {
	Figure::action();
}
void FigEllipse::addFigure() {
	mainView->addFigure(new FigEllipse(m_x1 + 20, m_y1 + 20, m_x2 + 20, m_y2 + 20, mainView, m_line, m_fill));
}

Figure* FigEllipse::re_copyElement() {
	return (new FigEllipse(m_x1 + 20, m_y1 + 20, m_x2 + 20, m_y2 + 20, mainView, m_line, m_fill));
}