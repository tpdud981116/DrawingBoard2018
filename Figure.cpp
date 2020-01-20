#include "stdafx.h"
#include "Figure.h"

#include "View.h"

Figure::Figure(int x1, int y1, int x2, int y2, View *view, COLORREF line, COLORREF fill)
	:m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2),mainView(view),m_line(line),m_fill(fill)
{
	//
	is_selected = false;
	g_pressed = false;
	
}

Figure::Figure(View *v) {
	mainView = v;
	g_pressed = false;
}

Figure::~Figure()
{
}


COLORREF Figure::re_lineColor() const{
	return m_line;
}
COLORREF Figure::re_fillColor()const {
	return m_fill;
}


//도형을 그린다
void Figure::draw() {
	mainView->setPenColor(m_line);
	mainView->setFillColor(m_fill);
}

//영역안에 도형이 있는지 알려주는 함수
bool Figure::is_inside_area(int x1,int y1, int x2, int y2) {
	
	int temp;

	if (x1 > x2) {
		temp = x1;
		x1 = x2;
		x2 = x1;
	}
	if (y1 > y2) {
		temp = y1;
		y1 = y2;
		y2 = temp;
	}
	if (m_x1 > m_x2) {
		temp = m_x1;
		m_x1 = m_x2;
		m_x2 = m_x1;
	}
	if (m_y1 > m_y2) {
		temp = m_y1;
		m_y1 = m_y2;
		m_y2 = temp;
	}

	if(x1 <= m_x1 && x2 >= m_x2 && y1 <= m_y1 && y2 >= m_y2) {
		is_selected = true;
		return true;
	}
	else {
		is_selected = false;
		return false;
	}
}

void Figure::action() {
	//is_selected = true; inside 함수에서 해결
	if (is_selected) {
		mainView->setPenColor(RGB(0, 0, 0));
		mainView->setFillColor(RGB(0, 0, 0));
		mainView->drawRectangle(m_x1 - 10, m_y1 - 10, m_x1, m_y1);
		mainView->drawRectangle(m_x2, m_y1 - 10, m_x2+10, m_y1);
		mainView->drawRectangle(m_x1 - 10, m_y2, m_x1, m_y2+10);
		mainView->drawRectangle(m_x2, m_y2, m_x2+10, m_y2+10);
	}
}

bool Figure::re_selected() const{
	return is_selected;
}

void Figure::addFigure() {
	//
}

void Figure::setPoint(int x, int y) {
	m_x1 += x; m_y1 += y;
	m_x2 += x; m_y2 += y;
}

int Figure::re_myFigure() {
	return m_fig;
}

int Figure::re_x1() const {
	return m_x1;
}
int Figure::re_y1() const {
	return m_y1;
}
int Figure::re_x2() const {
	return m_x2;
}
int Figure::re_y2() const {
	return m_y2;
}

Figure* Figure::re_copyElement() {
	return nullptr;
}

void Figure::drawArea() {
	//
}

//부속 도형 개수 돌려주기
int Figure::re_numElements() const {
	return 0;
}

void Figure::setG(bool b) {
	g_pressed = b;
}

bool Figure::re_G() {
	return g_pressed;
}