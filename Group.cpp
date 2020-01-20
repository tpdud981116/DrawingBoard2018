#include "stdafx.h"
#include "Group.h"

#include "View.h"

Group::Group(View *v) : Figure(v)
{
	m_fig = 3;
}


Group::~Group()
{
}


void Group::addGroupFigure(Figure *g) {
	myGroupElements.push_back(g);
}

void Group::draw() {
	//drawArea();
	for (auto a : myGroupElements) {
		a->draw();
	}
}

void Group::drawArea() {
	//내 선분 4개
	mainView->setPenColor(RGB(156, 139, 180));
	mainView->drawLine(m_x1, m_y1, m_x2, m_y1);
	mainView->drawLine(m_x1, m_y1, m_x1, m_y2);
	mainView->drawLine(m_x2, m_y1, m_x2, m_y2);
	mainView->drawLine(m_x1, m_y2, m_x2, m_y2);
	
}

void Group::setFirstPoint() {
	int x1 = mainView->getWindowWidth();
	int y1 = mainView->getWindowHeight();
	int x2 = 0;
	int y2 = 0;
	for (auto a : myGroupElements) {
		if (a->re_x1() < x1) {
			x1 = a->re_x1();
		}
	}
	for (auto a : myGroupElements) {
		if (a->re_y1() < y1) {
			y1 = a->re_y1();
		}
	}
	for (auto a : myGroupElements) {
		if (a->re_x2() > x2) {
			x2 = a->re_x2();
		}
	}
	for (auto a : myGroupElements) {
		if (a->re_y2() > y2) {
			y2 = a->re_y2();
		}
	}
	m_x1 = x1 - 20;
	m_x2 = x2 + 20;
	m_y1 = y1 - 20;
	m_y2 = y2 + 20;
}

void Group::setPoint(int x, int y) {
	Figure::setPoint(x,y);
	for (auto a : myGroupElements) {
		a->setPoint(x,y);
	}
}

void Group::addFigure() {
	//새로 new해서
	Group *g = new Group(mainView);
	
	//이 사이에서 그룹 안에 도형또한 추가한다.
	for (auto a : myGroupElements) {
	
		Figure *f = a->re_copyElement(); //여기서 좌표추가한걸주는거임
		g->addGroupFigure(f);
		
	}
	//넣어준다.
	g->setFirstPoint();

	//main의 figList에 붙여주는거임 얘는.
	mainView->addFigure(g);
}

int Group::re_numElements() const{
	return myGroupElements.size();
}
