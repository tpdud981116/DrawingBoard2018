#include "stdafx.h"
#include "Component.h"
#include "View.h"

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

Component::Component() {
}
Component::Component(View *v): mainview(v) {
	isON = false;
	isPressed = false;
}
Component::Component(string name, View* v):m_name(name),mainview(v) {

}
Component::Component(string name, View *view,int i)
	:m_name(name), mainview(view),m_identity(i)
{
	isON = false;
	isPressed = false;
}

Component::~Component()
{
}

//버튼 그리기 함수
void Component::draw() {
	mainview->setPenColor(RGB(235, 235, 235));
	mainview->setFillColor(RGB(235, 235, 235));
	mainview->setTextBkColor(RGB(235, 235, 235));
	mainview->drawRectangle(m_x, m_y, m_x + m_sizex, m_y + m_sizey);
	
	if (m_name.c_str() != nullptr) {
		SIZE s = mainview->textSize(m_name);
		int xoff = (m_sizex - s.cx) / 2;
		int yoff = (m_sizey - s.cy) / 2;
		mainview->drawText(m_name, m_x + xoff, m_y + yoff);
	}
	if (m_icon) {
		drawIcon();
	}
}

//사각형 내부에 있는지 판단해주는 함수
bool Component::inside(int x, int y) {
	return (m_x <= x && x <= m_x + m_sizex
		&& m_y <= y && y <= m_y + m_sizey);
}

//버튼을 누르면 어떤 버튼인지 출력
void Component::action() {
	//다형성으로 만듬
	debugOutput(m_name);
	/*isPressed = true;
	draw();*/
}

//마우스가 버튼 위에 있는 경우 그리는 함수
void Component::redraw() {
	//색 정하기
	mainview->setPenColor(RGB(235, 235, 235));
	mainview->setFillColor(RGB(200, 200, 200));
	mainview->setTextBkColor(RGB(200, 200, 200));

	mainview->drawRectangle(m_x, m_y, m_x + m_sizex, m_y + m_sizey);

	//내 이름이 있을 경우
	if (m_name.c_str() != nullptr) {
		SIZE s = mainview->textSize(m_name);
		int xoff = (m_sizex - s.cx) / 2;
		int yoff = (m_sizey - s.cy) / 2;
		mainview->drawText(m_name, m_x + xoff, m_y + yoff);
	}
	if (m_icon) {
		drawIcon();
	}
}

//마우스의 위치가 버튼 위에있는지 아닌지에 따라 상태를 봐서 그려주는 함수
void Component::state() {
	if (isON == true) {
		redraw();
	}
	else {
		draw();
	}
}

//버튼의 상태들을 설정해주고 반환해주는 함수들
void Component::set_isON(bool result) {
	isON = result;
}
bool Component::re_isON() const {
	return isON;
}
void Component::set_isPressed(bool result) {
	isPressed = result;
}
bool Component::re_isPressed() const {
	return isPressed;
}


void Component::setIcon(HICON i) {
	m_icon = i;
}

void Component::drawIcon() {
	if (mainview != 0 && m_icon != 0) {
		mainview->drawIcon(m_x, m_y, m_icon);
	}
}

int Component::re_identity() const{
	return m_identity;
}
