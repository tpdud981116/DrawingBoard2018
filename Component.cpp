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

//��ư �׸��� �Լ�
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

//�簢�� ���ο� �ִ��� �Ǵ����ִ� �Լ�
bool Component::inside(int x, int y) {
	return (m_x <= x && x <= m_x + m_sizex
		&& m_y <= y && y <= m_y + m_sizey);
}

//��ư�� ������ � ��ư���� ���
void Component::action() {
	//���������� ����
	debugOutput(m_name);
	/*isPressed = true;
	draw();*/
}

//���콺�� ��ư ���� �ִ� ��� �׸��� �Լ�
void Component::redraw() {
	//�� ���ϱ�
	mainview->setPenColor(RGB(235, 235, 235));
	mainview->setFillColor(RGB(200, 200, 200));
	mainview->setTextBkColor(RGB(200, 200, 200));

	mainview->drawRectangle(m_x, m_y, m_x + m_sizex, m_y + m_sizey);

	//�� �̸��� ���� ���
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

//���콺�� ��ġ�� ��ư �����ִ��� �ƴ����� ���� ���¸� ���� �׷��ִ� �Լ�
void Component::state() {
	if (isON == true) {
		redraw();
	}
	else {
		draw();
	}
}

//��ư�� ���µ��� �������ְ� ��ȯ���ִ� �Լ���
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
