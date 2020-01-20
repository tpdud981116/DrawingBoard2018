#include "stdafx.h"
#include "MenuBar.h"
#include "View.h"

MenuBar::MenuBar(View * v):Container(v)
{
}


MenuBar::~MenuBar()
{
}

//�޴��� �׸���
void MenuBar::draw() {
	mainview->setFillColor(RGB(235, 235, 235));
	mainview->setPenColor(RGB(235, 235, 235));

	mainview->drawRectangle(0, 0, mainview->getWindowWidth(), 32);

	Container::comDraw();
}

//�޴��� �ȿ����� �׸� �׸��� x
bool MenuBar::insideMenu(int x, int y) {
	return (x >= 0 && x <= mainview->getWindowWidth() && y >= 0 && y <= 32);
}

void MenuBar::addMenu(Menu *b) {
	//���⼭ menu�� ��� �׷����� ��ǥ�� �ش�.
	Container::addMenu(b);
	comList.push_back(b);
}

void MenuBar::mouseMove(Component *m) {
	//m�� �����Ѵٸ�
	if (m) { //b�� ���� �Ѵٸ�
		for (auto a : comList) {
			if (a->re_isON() == true) {
				if (a != m) { //a�� b�� �ٸ��ٸ�..
					a->set_isON(false);
					a->state();
				}
			}
		}
		m->set_isON(true);
		m->state();
	}
	else { //����� ����Ŵ
		   //����� �����ѵ� ���� ��ư�� ����...
		for (auto a : comList) {
			if (a->re_isON() == true) {
				a->set_isON(false);
				a->state();
			}
		}
	}
}