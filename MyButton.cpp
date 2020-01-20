#include "stdafx.h"
#include "MyButton.h"
#include "View.h"

#include <string>
using namespace std;

MyButton::MyButton() {

}

MyButton::MyButton(View *view) :Component(view) 
{
}

MyButton::MyButton(string name, View *view)
	:Component(name,view)
{
}

MyButton::~MyButton()
{
}



/*
�� �Լ���  ���� Ŭ������ Component�� �̵��Ͽ���.
���� �������� ��� override ���� �ʰ� ����.

//��ư �׸��� �Լ�
void MyButton::draw() {
	mainview->setPenColor(RGB(235, 235, 235));
	mainview->setFillColor(RGB(235, 235, 235));
	mainview->setTextBkColor(RGB(235, 235, 235));
	mainview->drawRectangle(m_x, m_y, m_x + m_sizex, m_y + m_sizey);
	SIZE s = mainview->textSize(m_name);
	int xoff = (m_sizex - s.cx) / 2;
	int yoff = (m_sizey - s.cy) / 2;
	mainview->drawText(m_name, m_x + xoff, m_y + yoff);
}

//�簢�� ���ο� �ִ��� �Ǵ����ִ� �Լ�
bool MyButton::inside(int x, int y) {
	return (m_x <= x && x <= m_x + m_sizex
		&& m_y <= y && y <= m_y + m_sizey);
}

//��ư�� ������ � ��ư���� ���
void MyButton::action() {
	debugOutput(m_name);
	isPressed = true;
	draw();
}

//���콺�� ��ư ���� �ִ� ��� �׸��� �Լ�
void MyButton::redraw() {
	//�� ���ϱ�
	mainview->setPenColor(RGB(235, 235, 235));
	mainview->setFillColor(RGB(200, 200, 200));
	mainview->setTextBkColor(RGB(200, 200, 200));

	mainview->drawRectangle(m_x, m_y, m_x + m_sizex, m_y + m_sizey);
	SIZE s = mainview->textSize(m_name);
	int xoff = (m_sizex - s.cx) / 2;
	int yoff = (m_sizey - s.cy) / 2;
	mainview->drawText(m_name, m_x + xoff, m_y + yoff);

}

//���콺�� ��ġ�� ��ư �����ִ��� �ƴ����� ���� ���¸� ���� �׷��ִ� �Լ�
void MyButton::state() {
	if (isON == true) {
		redraw();
	}else {
		draw();
	}
}

//��ư�� ���µ��� �������ְ� ��ȯ���ִ� �Լ���
void MyButton::set_isON(bool result) {
	isON = result;
}
bool MyButton::re_isON() const{
	return isON;
}
void MyButton::set_isPressed(bool result) {
	isPressed = result;
}
bool MyButton::re_isPressed() const{
	return isPressed;
}
*/