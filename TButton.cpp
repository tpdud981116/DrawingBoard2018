#include "stdafx.h"
#include "TButton.h"
#include "View.h"

TButton::TButton(int i,View* v):MyButton(v) {
	m_identity = i;
}
TButton::TButton(string name,View* view) :MyButton(name,view)
{
	m_icon = 0;
}


TButton::~TButton()
{
}

void TButton::action() {
	isPressed = true;
	draw();
	debugOutput(m_name);
}
void TButton::setPoint(int x1, int y1, int sizeX, int sizeY) {
	m_x = x1;
	m_y = y1;
	m_sizex = sizeX;
	m_sizey = sizeY;
}

/* 컴포넌트로 옮김
void TButton::setIcon(HICON i) {
	m_icon = i;
	debugOutput("아이콘이 그려지긴 햇ㄴㄴ데.......");
	//mainview->drawIcon(m_x,m_y,m_icon);
}

void TButton::drawIcon() {
	if (mainview != 0 && m_icon != 0) {
		mainview->drawIcon(m_x, m_y, m_icon);
	}
}*/

