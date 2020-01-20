#include "stdafx.h"
#include "MenuItem.h"

#include <string>
using namespace std;

MenuItem::MenuItem(string name, View *v,int i) :MyButton(name,v)
{
	m_identity = i;
}


MenuItem::~MenuItem()
{
}

//메뉴에게서 자신이 그려질 좌표를 받는다.
void MenuItem::setPoint(int x1, int y1, int x2, int y2) {
	m_x = x1;
	m_y = y1;
	m_sizex = x2;
	m_sizey = y2;
}

void MenuItem::action() {

}