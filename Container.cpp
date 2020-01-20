#include "stdafx.h"
#include "Container.h"
#include "View.h"
#include "TButton.h"
#include "Menu.h"
#include "MenuItem.h"
#include "Component.h"

Container::Container() {
	
}

Container::Container(string name, View* v, int i):Component(name,v) {

}

Container::Container(View *v):Component(v)
{
	m_toolX = 0; m_toolY = 32;
	m_menuX = 0; m_menuY = 0;
	//m_sizeX = mainview->getWindowWidth();
	//m_sizeY = 32;
}

Container::~Container() {

}

void Container::addComponent(TButton * b) {
	b->setPoint(m_toolX, m_toolY, 32, 32);
	m_toolX += 32;
}

void Container::addMenu(Menu * b) {
	b->setPoint(m_menuX,m_menuY,64,32);
	m_menuX += 64;
}


void Container::comDraw(){
	for (list<Component *>::iterator i = comList.begin(); i != comList.end(); i++) {
		(*i)->draw();
	}
}

Component* Container::t_findButton(int x, int y) {
	// TODO: 여기에 구현 코드 추가.
	for (auto b : comList) {
		//존재한다면 그 버튼을 돌려준다.
		if (b->inside(x, y)) return (TButton *)b;
	}
	return nullptr;
}

Menu* Container::m_findButton(int x, int y) {
	// TODO: 여기에 구현 코드 추가.
	for (auto b : comList) {

		//존재한다면 그 버튼을 돌려준다.
		if (b->inside(x, y)) return (Menu *)b;

	}
	return nullptr;
}

Component* Container::t_findPressed() {
	for (auto a : comList) {
		if (a->re_isPressed() == true) {
			return (TButton *)a;
		}
	}
	return nullptr;
}

Component* Container::m_findPressed() {
	for (auto a : comList) {
		if (a->re_isPressed() == true) {
			return (Menu *)a;
		}
	}
	return nullptr;
}

void Container::closeMenu() {
	for (auto a : comList) {
		if (a->re_isPressed() == true) {
			a->set_isPressed(false);
		}
	}
}

void Container::drawItem() {
	/*for (auto a : comList) {
		if (a->re_isPressed() == true) {
			
		}
	}*/
}
