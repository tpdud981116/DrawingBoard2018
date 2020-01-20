#include "stdafx.h"
#include "MenuBar.h"
#include "View.h"

MenuBar::MenuBar(View * v):Container(v)
{
}


MenuBar::~MenuBar()
{
}

//메뉴바 그리기
void MenuBar::draw() {
	mainview->setFillColor(RGB(235, 235, 235));
	mainview->setPenColor(RGB(235, 235, 235));

	mainview->drawRectangle(0, 0, mainview->getWindowWidth(), 32);

	Container::comDraw();
}

//메뉴바 안에서는 그림 그릴수 x
bool MenuBar::insideMenu(int x, int y) {
	return (x >= 0 && x <= mainview->getWindowWidth() && y >= 0 && y <= 32);
}

void MenuBar::addMenu(Menu *b) {
	//여기서 menu가 어디에 그려질지 좌표를 준다.
	Container::addMenu(b);
	comList.push_back(b);
}

void MenuBar::mouseMove(Component *m) {
	//m이 존재한다면
	if (m) { //b가 존재 한다면
		for (auto a : comList) {
			if (a->re_isON() == true) {
				if (a != m) { //a와 b가 다르다면..
					a->set_isON(false);
					a->state();
				}
			}
		}
		m->set_isON(true);
		m->state();
	}
	else { //허공을 가리킴
		   //허공을 가리켜도 켜진 버튼을 끈다...
		for (auto a : comList) {
			if (a->re_isON() == true) {
				a->set_isON(false);
				a->state();
			}
		}
	}
}