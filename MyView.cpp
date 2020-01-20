#include "stdafx.h"
#include "MyView.h"
#include <fstream>
#include <cstdlib>
MyView::MyView(HINSTANCE hInstance):View(hInstance)
{
	can_draw = true;
	
}

MyView::MyView(HWND w):View(w)
{
	can_draw = true;
	
}

MyView::~MyView() 
{
}
#include "FigEllipse.h"
#include "FigLine.h"
#include "FigRect.h"
#include "TButton.h"
#include "ToolBar.h"
#include "MenuBar.h"
#include "Menu.h"
#include "MenuItem.h"
#include "Group.h"

void MyView::OnLButtonDown(Event e)
{
	//현재 위치를 기억시키자
	can_draw = true;
	m_start = e;
	
	//메뉴가 펼쳐진 상황에서는 버튼클릭이아니라 메뉴클릭이 되어야 한다!!!!
	if (menu) {
		if (menu->re_isPressed() == true) {

			//메뉴 열린 상태면 그림을 그리지 않는다.
			can_draw = false;
			//다음 클릭이 메뉴아이템 안에 있는 경우
			item_current = menu->insideItem(e.x, e.y);

			//도형 메뉴 선택
			if (item_current && menu == btnFig) {
				//메뉴항목이 눌렸을 경우 툴바버튼을 모두 끈다.
				
				btnItemEllipse->set_isPressed(false);
				btnItemRect->set_isPressed(false);
				btnItemLine->set_isPressed(false);

				item_current->set_isPressed(true);

				btnEllipse->set_isPressed(false);
				btnLine->set_isPressed(false);
				btnRect->set_isPressed(false);

				item_current->action();
			}
			//파일 메뉴 선택
			if (item_current && menu == btnFile) {
				if (item_current->re_identity() == 0) { //저장 클릭
					
					ofstream a_file("MyFigure.txt");
					a_file << myFigList.size()<<"\n";
					for (auto a : myFigList) {
						//도형 정보
						if (a->re_myFigure() != 3) { //그룹이 아닐 경우
							//저장할것 : 모양, 선색, 채움색, 좌표
							a_file << a->re_myFigure() << " ";
							//선색 정보
							a_file << a->re_lineColor() << " ";
							//채움색 정보
							a_file << a->re_fillColor() << " ";
							//좌표 정보
							a_file << a->re_x1() << " ";
							a_file << a->re_y1() << " ";
							a_file << a->re_x2() << " ";
							a_file << a->re_y2() << "\n";
						}
					}

					a_file.close();
				}
				else if (item_current->re_identity() == 1) { //열기 클릭
					
					//도형리스트를 비운다.
					myFigList.clear();

					int numFig;
					int x1, y1, x2, y2;
					//기본값
					COLORREF m_line = RGB(0, 0, 0);
					COLORREF m_fill = RGB(255, 255, 255);

					int information[7]; //정보는 7개임...
					
					ifstream b_file("MyFigure.txt");
					b_file >> numFig; //도형 개수 저장
					
					for (int i = 0; i < numFig; i++) {
						for (int k = 0; k < 7; k++) {
							b_file >> information[k];
						}

						x1 = information[3];
						y1 = information[4];
						x2 = information[5];
						y2 = information[6];
						//선 색 설정
						switch (information[1])
						{
						case 255: //빨강
							m_line = RGB(255, 0, 0);
							break;
						case 65280: //초록
							m_line = RGB(0, 255, 0);
							break;
						case 16711680: //파랑
							m_line = RGB(0, 0, 255);
							break;
						default:
							break;
						}
						//채움 색 설정
						switch (information[2])
						{
						case 255: //빨강
							m_fill = RGB(255, 0, 0);
							break;
						case 65280: //초록
							m_fill = RGB(0, 255, 0);
							break;
						case 16711680: //파랑
							m_fill = RGB(0, 0, 255);
							break;
						default:
							break;
						}
						//도형설정
						switch (information[0])
						{
						case 0: //사각형
							myFigList.push_back(new FigRect(x1, y1, x2, y2, this, m_line, m_fill));
							break;
						case 1: //타원
							myFigList.push_back(new FigEllipse(x1, y1, x2, y2, this, m_line, m_fill));
							break;
						case 2: //선분
							myFigList.push_back(new FigLine(x1, y1, x2, y2, this, m_line, m_fill));
							break;
						default:
							break;
						}
					}
					
					b_file.close();
					
				}
				item_current->action();
			}

			//선색 메뉴 선택
			if (item_current && menu == btnMenuLineColor) {
				
				btnRedLine->set_isPressed(false);
				btnGreenLine->set_isPressed(false);
				btnBlueLine->set_isPressed(false);

				if (item_current->re_identity() == 0) {
					btnRedLine->set_isPressed(true);
				}
				else if (item_current->re_identity() == 1) {
					btnGreenLine->set_isPressed(true);
				}
				else if(item_current->re_identity() == 2){
					btnBlueLine->set_isPressed(true);
				}

				item_current->action();
			}
			//채움색 메뉴 선택
			if (item_current && menu == btnMenuFillColor) {
				
				btnRedFill->set_isPressed(false);
				btnGreenFill->set_isPressed(false);
				btnBlueFill->set_isPressed(false);

				debugOutput(item_current->re_identity());
				if (item_current->re_identity()==0) {
					btnRedFill->set_isPressed(true);
				}
				else if (item_current->re_identity()==1) {
					btnGreenFill->set_isPressed(true);
				}
				else if (item_current->re_identity()==2) {
					btnBlueFill->set_isPressed(true);
				}

				item_current->action();
			}
			return;
		}
		
	}
	
	//툴바 버튼이 눌렸을 경우에는 메뉴항목을 nullptr로 만든다,
	Component *b = m_toolbar->t_findButton(e.x, e.y);
	if (b) {
		item_current = nullptr;
	}
	//다른 종류(툴바,메뉴)의 버튼이 눌리 경우 상대의 모든 버튼을 false로 바꾸는 이유는
	//도형을 그리는 코드가 메뉴가 라인이 눌려져있으면 툴바로 사각형을 선택해도
	//사각형이 그려지지 않고 라인이 그려지는 순서의 문제 때문..
	t_current = m_toolbar->t_findButton(e.x, e.y);
	if (t_current) {
		if (t_current->re_identity() == 1) {
			//도형..
			btnEllipse->set_isPressed(false);
			btnLine->set_isPressed(false);
			btnRect->set_isPressed(false);
			btnItemEllipse->set_isPressed(false);
			btnItemRect->set_isPressed(false);
			btnItemLine->set_isPressed(false);

			t_current->set_isPressed(true);
		}
		if (t_current->re_identity() == 2) {
			//선색...
			btnRedLine->set_isPressed(false);
			btnGreenLine->set_isPressed(false);
			btnBlueLine->set_isPressed(false);
			t_current->set_isPressed(true);
		}
		if (t_current->re_identity() == 3) {
			//채움색..
			btnRedFill->set_isPressed(false);
			btnGreenFill->set_isPressed(false);
			btnBlueFill->set_isPressed(false);
			t_current->set_isPressed(true);
		}
		if (t_current->re_identity() == 4) {
			//전체삭제...
			myFigList.clear();

		}
	}

	Figure * figure = findSelectFigure();
	
	if (figure) {
		//쉬프트 누른상태로 왼쪽 클릭->이동진행
		if (e.shiftPressed() && !e.ctrlPressed()) {
			m_before = e; //이동 전 위치 기억
		}

		//컨트롤 쉬프트 둘다 누른 상태->그룹화
		if (e.shiftPressed() && e.ctrlPressed()) {
			Group *g = new Group(this);
			for (auto a : mySelectedList) {
				//현재 선택된 도형을 그룹에 넣기
				g->addGroupFigure(a);
				//원래리스트에서 삭제
				eraseFig(a);
			}
			//도형리스트에 그룹을 추가
			g->setFirstPoint();
			addFigure(g);
		}
	}
	
}
void MyView::OnLButtonUp(Event e) {

	
	View::OnLButtonUp(e);
	
	Figure * figure = findSelectFigure();
	
	if (figure) {
		//마우스를 뗏을 때도 shift가 눌려진 상태라면,
		if (e.shiftPressed() && !e.ctrlPressed()) {
			m_after = e; //이동 후 위치 기억
			for (auto a : mySelectedList) {
				a->setPoint(m_after.x - m_before.x, m_after.y - m_before.y);
			}
			//기능을 수행했으니 선택된 리스트를 clear한다
			mySelectedList.clear();

			//도형의 이동시에는 그림을 그리지 않는다.
			return;
		}
		//컨트롤 누른상태로 왼쪽 클릭->복사진행
		if (e.ctrlPressed() && !e.shiftPressed()) {
			for (auto a : mySelectedList) {
				a->addFigure();
			}
			//기능을 수행했으니 선택된 리스트를 clear한다
			mySelectedList.clear();
			//도형의 복사시에는 그림을 그리지 않는다.
			return;
		}
		
	}
	//어떠한 기능을 수행하지 않은 채로 왼쪽 클릭이 되었을 경우에도 선택 리스트를 비운다
	mySelectedList.clear();

	//툴바창에서는 그림을 그릴 수 없다.
	if (m_toolbar->insideTool(m_start.x, m_start.y)) {
		return;
	}
	if (m_toolbar->insideTool(e.x, e.y)) {
		return;
	}
	//메뉴창에서는 그림을 그릴 수 없다.
	if (m_menubar->insideMenu(m_start.x, m_start.y)) {
		return;
	}
	if (m_menubar->insideMenu(e.x, e.y)) {
		return;
	}
	//쉬프트/컨트롤이 눌려진 상태면 그림을 그릴 수 없다.
	if (e.ctrlPressed() || e.shiftPressed()) {
		return;
	}

	if (can_draw == false) return;
	//각 버튼의 isPressed가 참이거나 메뉴아이템이 눌렸을 경우
	if (btnEllipse->re_isPressed()||btnItemEllipse->re_isPressed()) {
		if (btnRedLine->re_isPressed()) {
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(255, 255, 255)));
			}
		}
		else if (btnGreenLine->re_isPressed()) {
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(255, 255, 255)));
			}
		}
		else if(btnBlueLine->re_isPressed()){
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(255, 255, 255)));
			}
		}
		else {
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(255, 255, 255)));
			}
		}
	}
	else if (btnLine->re_isPressed()||btnItemLine->re_isPressed()) {
		if (btnRedLine->re_isPressed()) {
			myFigList.push_back(new FigLine(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(0, 0, 0)));
		}
		else if (btnGreenLine->re_isPressed()) {
				myFigList.push_back(new FigLine(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(0, 0, 0)));
		}
		else if (btnBlueLine->re_isPressed()) {
			myFigList.push_back(new FigLine(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(0, 0, 0)));
		}
		else {
			myFigList.push_back(new FigLine(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(0, 0, 0)));
		}
	}
	else if (btnRect->re_isPressed() ||btnItemRect->re_isPressed()) {
		if (btnRedLine->re_isPressed()) {
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(255, 255, 255)));
			}
		}
		else if (btnGreenLine->re_isPressed()) {
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(255, 255, 255)));
			}
		}
		else if (btnBlueLine->re_isPressed()) {
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(255, 255, 255)));
			}
		}
		else {
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(255, 255, 255)));
			}
		}
	}
	else {
		return;
	}

	View::invalidate(); //움직이지않아도 바로 사각형 그려줌
}

void MyView::OnRButtonDown(Event e)
{
	// 프로그램 종료 방법을 데모하기 위해 우측 버튼 클릭시 아래 줄을 호출하게 만들었습니다.
	//eraseRect(e.x, e.y, 100, 100);
	//::PostMessage(m_WindowHandle, WM_CLOSE, NULL, NULL);
	m_start = e;
}

void MyView::OnRButtonUp(Event e)
{
	m_end = e;

	int temp;
	if (m_start.x > m_end.x) {
		temp = m_start.x;
		m_start.x = m_end.x;
		m_end.x = temp;
	}
	if (m_start.y > m_end.y) {
		temp = m_start.y;
		m_start.y = m_end.y;
		m_end.y = temp;
	}
	findAreaFigure(m_start.x, m_start.y, m_end.x, m_end.y);
}

void MyView::OnChar(long ch)
{
	// 키보드 입력이 되면 이 함수가 자동 호출됩니다.  cin이나 getchar, scanf 같은
	// 표준 입력함수는 작동하지 않으니 onchar 를 잘 이용해야 합니다.
	
	if (ch == 8) { //backspace누르면 선택된 도형 삭제
		for (auto a : mySelectedList) {
			eraseFig(a);
		}
	}

	if (ch == 103) {
		for (auto a : myFigList) {
			if (a->re_myFigure() == 3) {
				a->setG(true);
			}
		}
	}
	invalidate();
}

void MyView::OnKeyDown(long ch) {
	
}
void MyView::OnKeyUp(long ch) {
	//g==71
	//m==77
	if (ch == 71) {
		for (auto a : myFigList) {
			if (a->re_myFigure() == 3) {
				a->setG(false);
			}
		}
	}
	invalidate();
}


// 모든 윈도들을 onInitialize 함수에서 초기화하자.
void MyView::onInitialize()
{
	// *** 모든 컴포넌트들을 여기에서 초기화하자.
	View::onInitialize();
	//어떤 버튼을 만들건지는 응용

	//툴바 도형 선택 버튼
	btnRect = new TButton(1,this);
	rectIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,32,32,LR_DEFAULTCOLOR);
	btnRect->setIcon(rectIcon);

	btnEllipse = new TButton(1,this);
	ellipseIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnEllipse->setIcon(ellipseIcon);

	btnLine = new TButton(1,this);
	lineIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnLine->setIcon(lineIcon);
	
	addButton(btnRect);
	addButton(btnEllipse);
	addButton(btnLine);

	//선 색 선택 버튼
	//파라메터로 RGB색 보낸다.
	btnRedLine = new TButton(2,this);
	LredIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON4), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnRedLine->setIcon(LredIcon);
	
	btnGreenLine = new TButton(2,this);
	LgreenIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON6), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnGreenLine->setIcon(LgreenIcon);

	btnBlueLine = new TButton(2,this);
	LblueIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON5), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBlueLine->setIcon(LblueIcon);

	addButton(btnRedLine);
	addButton(btnGreenLine);
	addButton(btnBlueLine);

	//툴바 채움색 버튼
	btnRedFill = new TButton(3,this);
	FredIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON7), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnRedFill->setIcon(FredIcon);

	btnGreenFill = new TButton(3,this);
	FgreenIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON8), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnGreenFill->setIcon(FgreenIcon);

	btnBlueFill = new TButton(3,this);
	FblueIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON9), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBlueFill->setIcon(FblueIcon);

	//툴바 다지우기 버튼
	btnEraseAll = new TButton(4, this);
	eraseAll = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON10), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnEraseAll->setIcon(eraseAll);

	addButton(btnRedFill);
	addButton(btnGreenFill);
	addButton(btnBlueFill);
	addButton(btnEraseAll);

	//파일, 도형메뉴 만들고 메뉴리스트에 추가
	btnFile = new Menu("파일",this,1);
	btnFig = new Menu("도형", this,2);
	btnMenuLineColor = new Menu("선 색",this,3);
	btnMenuFillColor = new Menu("채움 색", this,4);
	addButton(btnFile);
	addButton(btnFig);
	addButton(btnMenuLineColor);
	addButton(btnMenuFillColor);

	//메뉴 선색 버튼에 빨강, 초록, 파랑 넣기
	btnMenuLineRed = new MenuItem("빨강", this,0);
	btnMenuLineGreen = new MenuItem("초록", this,1);
	btnMenuLineBlue = new MenuItem("파랑",this,2);
	addMenuItem(btnMenuLineColor,btnMenuLineRed);
	addMenuItem(btnMenuLineColor, btnMenuLineGreen);
	addMenuItem(btnMenuLineColor, btnMenuLineBlue);

	//메뉴 채움색 버튼에 빨강, 초록, 파랑 넣기
	btnMenuFillRed = new MenuItem("빨강", this,0);
	btnMenuFillGreen = new MenuItem("초록", this,1);
	btnMenuFillBlue = new MenuItem("파랑", this,2);
	addMenuItem(btnMenuFillColor, btnMenuFillRed);
	addMenuItem(btnMenuFillColor, btnMenuFillGreen);
	addMenuItem(btnMenuFillColor, btnMenuFillBlue);

	//파일버튼에 저장, 열기 넣기
	btnSave = new MenuItem("저장",this,0);
	btnOpen = new MenuItem("열기", this,1);
	addMenuItem(btnFile,btnSave);
	addMenuItem(btnFile,btnOpen);
	
	//도형버튼에 사각형, 타원, 선분 넣기
	btnItemRect = new MenuItem("사각형",this,0);
	btnItemEllipse = new MenuItem("타원", this,1);
	btnItemLine = new MenuItem("선분", this,2);
	addMenuItem(btnFig, btnItemRect);
	addMenuItem(btnFig, btnItemEllipse);
	addMenuItem(btnFig, btnItemLine);

	View::invalidate();

}
void MyView::addMenuItem(Menu *mymenu,MenuItem *b) {
	mymenu->addMenuItem(b);
}
void MyView::addButton(TButton *b) {
	m_toolbar->addComponent(b); //TButton이 들어가야된다.
}

void MyView::addButton(Menu *b) {
	m_menubar->addMenu(b); //Menu 들어가야된다.
}

// 모든  내용물들을 다시 그려주는 함수.  수정이 필요할 것이다.
void MyView::redrawAll()
{
	
	//모든 사각형을 그려준다.
	for (list <Figure *>::iterator i = myFigList.begin(); i != myFigList.end(); i++) {
		//모든 figure에서 draw해준다.
		(*i)->draw();
	}
	for (auto a : myFigList) {
		if (a->re_myFigure() == 3) {
			if (a->re_G() == true) {
				a->drawArea();
			}
		}
	}

	View::redrawAll();

}