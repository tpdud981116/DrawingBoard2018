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
	//여기서 TButton이 어디에 그려질지 좌표를 준다.
	Container::addComponent(b);
	comList.push_back(b);
	
}

//툴바가 표시될 줄 그리기
void ToolBar::draw() {
	
	//나중에는 여기서 버튼도 다 그리면 된다용
	mainview->setFillColor(RGB(235,235,235));
	mainview->setPenColor(RGB(235,235,235));
	mainview->drawRectangle(0, 32, mainview->getWindowWidth(), 64);

	Container::comDraw();
}

void ToolBar::mouseMove(Component *b) {
	

	if (b) { //b가 존재 한다면
		for (auto a : comList) {
			if (a->re_isON() == true) {
				if (a != b) { //a와 b가 다르다면..
					a->set_isON(false);
					a->state();
				}
			}
		}
		b->set_isON(true);
		b->state();
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

bool ToolBar::insideTool(int x, int y) {
	return (x >= 0 && x <= mainview->getWindowWidth() && y >= 32 && y <= 64);
}
