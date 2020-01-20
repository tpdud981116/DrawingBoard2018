#include "stdafx.h"
#include "Menu.h"
#include "MenuItem.h"

Menu::Menu(string name, View * v,int i):Container(name,v,i)
{
	itemY1 = 32; itemY2 = 32;
	isPressed = false;
}


Menu::~Menu()
{
}

void Menu::addMenuItem(MenuItem *b) {
	//메뉴아이템에게 자기 버튼의 x좌표를 줘야함
	b->setPoint(m_x, itemY1, 64, itemY2);
	itemY1 += 32;
	
	comList.push_back(b);
}


void Menu::setPoint(int x1, int y1, int x2, int y2) {
	m_x = x1;
	m_y = y1;
	m_sizex = x2;
	m_sizey = y2;
}

MenuItem* Menu::insideItem(int x, int y) {
	for (auto a:comList) {
		//현재 클릭한 좌표가 아이템 안에 있다면
		if (a->inside(x,y)) return (MenuItem*)a;
	}
	return nullptr;
}