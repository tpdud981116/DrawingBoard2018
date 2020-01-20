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
이 함수는  상위 클래스인 Component로 이동하였음.
아직 차이점이 없어서 override 하지 않고 있음.

//버튼 그리기 함수
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

//사각형 내부에 있는지 판단해주는 함수
bool MyButton::inside(int x, int y) {
	return (m_x <= x && x <= m_x + m_sizex
		&& m_y <= y && y <= m_y + m_sizey);
}

//버튼을 누르면 어떤 버튼인지 출력
void MyButton::action() {
	debugOutput(m_name);
	isPressed = true;
	draw();
}

//마우스가 버튼 위에 있는 경우 그리는 함수
void MyButton::redraw() {
	//색 정하기
	mainview->setPenColor(RGB(235, 235, 235));
	mainview->setFillColor(RGB(200, 200, 200));
	mainview->setTextBkColor(RGB(200, 200, 200));

	mainview->drawRectangle(m_x, m_y, m_x + m_sizex, m_y + m_sizey);
	SIZE s = mainview->textSize(m_name);
	int xoff = (m_sizex - s.cx) / 2;
	int yoff = (m_sizey - s.cy) / 2;
	mainview->drawText(m_name, m_x + xoff, m_y + yoff);

}

//마우스의 위치가 버튼 위에있는지 아닌지에 따라 상태를 봐서 그려주는 함수
void MyButton::state() {
	if (isON == true) {
		redraw();
	}else {
		draw();
	}
}

//버튼의 상태들을 설정해주고 반환해주는 함수들
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