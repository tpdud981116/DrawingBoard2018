#include "stdafx.h"
#include "ToolBar.h"
#include "View.h"
#include "TButton.h"

ToolBar::ToolBar(View *v):Container(v)
{
	/*m_btnX = 0; m_btnY = 0;
	m_btnSizeX = 32; m_btnSizeY = 32;*/
	//m_sizeX = mainview->getWindowWidth();
	//m_sizeY = 64;
}

ToolBar::~ToolBar()
{
}

/*void ToolBar::setSize() {
	m_sizeX = mainview->getWindowWidth();
}*/

void ToolBar::addComponent(TButton *b) {
	//���⼭ TButton�� ��� �׷����� ��ǥ�� �ش�.
	Container::addComponent(b);
	comList.push_back(b);
	
}

//���ٰ� ǥ�õ� �� �׸���
void ToolBar::draw() {
	
	//���߿��� ���⼭ ��ư�� �� �׸��� �ȴٿ�
	mainview->setFillColor(RGB(235,235,235));
	mainview->setPenColor(RGB(235,235,235));
	mainview->drawRectangle(0, 32, mainview->getWindowWidth(), 64);

	Container::comDraw();
}

void ToolBar::mouseMove(Component *b) {
	

	if (b) { //b�� ���� �Ѵٸ�
		for (auto a : comList) {
			if (a->re_isON() == true) {
				if (a != b) { //a�� b�� �ٸ��ٸ�..
					a->set_isON(false);
					a->state();
				}
			}
		}
		b->set_isON(true);
		b->state();
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

bool ToolBar::insideTool(int x, int y) {
	return (x >= 0 && x <= mainview->getWindowWidth() && y >= 32 && y <= 64);
}
