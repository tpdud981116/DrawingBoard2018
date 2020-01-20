#include "stdafx.h"
#include "View.h"
#include "stdio.h"
#include "iostream"
#include "string"
#include "Misc.h"
#include <list>
#include "Figure.h"
#include "FigEllipse.h"
#include "FigLine.h"
#include "FigRect.h"
#include "Component.h"
#include "TButton.h"
#include "ToolBar.h"
#include "MenuBar.h"
#include "MenuItem.h"
#include "Group.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);  // Prototype to external fun

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM View::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJ2018));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL; //  MAKEINTRESOURCEW(IDC_PROJ2018);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

View::View(HINSTANCE hInstance):m_InstanceHandle(hInstance) {
	m_InstanceHandle = hInstance;
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PROJ2018, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
}
View::View(HWND w):m_WindowHandle(w)
{
	m_DCHandle = ::GetDC(w);
	onInitialize();
}

View::View() {

}

View::~View()
{

}

BOOL View::initInstance( int nCmdShow)
{
	//m_InstanceHandle = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	m_WindowHandle = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_InstanceHandle, nullptr);

	if (!m_WindowHandle)
	{
		return FALSE;
	}

	ShowWindow(m_WindowHandle, nCmdShow);
	UpdateWindow(m_WindowHandle);
	m_DCHandle = ::GetDC(m_WindowHandle);
	onInitialize();
	//mainView = new View(hWnd);

	return TRUE;
}

void View::OnLButtonDown(Event e)
{
	
}

void View::OnLButtonUp(Event e){

	//툴바의 버튼을 눌렀을 때 해당 버튼의 액션이 실행되는것은 라이브러리의
	//공통적인 부분
	Component *a = m_toolbar->t_findPressed();
	Component *b = m_toolbar->t_findButton(e.x, e.y);
	//메뉴바가 선택된 메뉴에게 선택됬다고 알려준다.
	menu = m_menubar->m_findButton(e.x, e.y);
	if (menu) {
		//파일메뉴가 닫혀있다면, 메뉴바에게 다른 메뉴를 닫아달라고한다
		//파일메뉴를 펼친다.
		if (menu->re_isPressed() == false) {
			m_menubar->closeMenu();
			menu->set_isPressed(true); //선택된 메뉴만 펼친상태로.
		}
		else {	//열려있다면 다시 닫는 상태로 돌린다.
			menu->set_isPressed(false);
		}
		invalidate();
	}
	else {
		//메뉴가 아닌 곳을 누른 경우 모두 닫는다.
		m_menubar->closeMenu();
		invalidate();
	}

	//같은 버튼을 눌렀다 뗐는지 판단
	if (t_current != b) {
		return;
	}
	if (b) { //b가 nullptr 가 아닐 경우
			 //버튼 이름 출력
		
		if (a) { //전에 눌렀던 버튼이 존재한다면
			//역할이 같으며 (예->도형관련) 다른 버튼일경우(예->사각형 vs타원)
			if (a->re_identity() == b->re_identity() && a!=b) { //전에 눌렀던 버튼과 현재 누른 버튼이 다른 경우
				a->set_isPressed(false); //전의 버튼을 거짓으로 바꾼다.
			}
		}
		b->action(); //action에서 현재 눌린 버튼을 참으로 바꾼다.
		is_drawing = false;
	}
	else {
		is_drawing = true;
	}

	if (!is_drawing) return;

}

void View::OnRButtonDown(Event e)
{
	//
}

void View::OnRButtonUp(Event e)
{
	// 
}

void View::OnChar(long ch)
{
	//
}

void View::OnKeyDown(long ch) {

}
void View::OnKeyUp(long ch) {

}

// 라인의 색을 지정하기
void View::setPenColor(COLORREF color)
{
	thePen = CreatePen(PS_SOLID, 1, color);
	SelectObject(m_DCHandle, thePen);
}

// 선의 색과 두께를 동시에 지정하기
void View::setPen(COLORREF color, int width)
{
	thePen = CreatePen(PS_SOLID, width, color);
	SelectObject(m_DCHandle, thePen);
}

// 채움 색을 결정하는 함수.
void View::setFillColor(COLORREF color)
{
	theBrush = CreateSolidBrush(color);
	SelectObject(m_DCHandle, theBrush);
}

// 글자 색을 지정하는 함수.
void View::setTextColor(COLORREF color)
{
	SetTextColor(m_DCHandle, color);
}

// 글자 배경색을 지정하는 함수를 만든다.
void View::setTextBkColor(COLORREF color)
{
	SetBkColor(m_DCHandle, color);
}

void View::drawRectangle(int x1, int y1, int x2, int y2)
{
	Rectangle(m_DCHandle, x1, y1, x2, y2);
}

void View::drawEllipse(int x1, int y1, int x2, int y2)
{
	Ellipse(m_DCHandle, x1, y1, x2, y2);
}

void View::drawLine(int x1, int y1, int x2, int y2)
{
	MoveToEx(m_DCHandle, x1, y1, NULL);
	LineTo(m_DCHandle, x2,y2);
}


void View::drawText(std::string str, int x, int y)
{
	TextOutA(m_DCHandle, x, y, str.c_str(), strlen(str.c_str()));
}

// 모든  내용물들을 다시 그려주는 함수.  수정이 필요할 것이다.
void View::redrawAll()
{
	if (m_toolbar) {
		//m_toolbar->setSize();
		m_toolbar->draw();
	}
	if (m_menubar) {
		m_menubar->draw();
	}
	//열린상태이면 메뉴항목그리고
	//닫힌상태이면 그리지않는다.
	if (menu) {
		if (menu->re_isPressed() == true) {
			menu->comDraw();
		}
	}

	
}

// 화면이 현재 제대로 안되어 있다고 알리는 함수입니다.
// 이 함수를 호출하면 화면이 지워지고 
// Main.cpp 쪽에 case WM_PAINT: 부분이 실행됩니다.
// 결국은 View 객체의 display가 실행되겠죠.
void View::invalidate()
{
	InvalidateRect(m_WindowHandle, NULL, true);
}

// 모든 윈도들을 onInitialize 함수에서 초기화하자.
void View::onInitialize()
{
	//툴바를 만들어주는것은 라이브러리의 공통적인 부분.
	m_toolbar = new ToolBar(this);
	//메뉴를 만들어주는것은 라이브러리의 공통적인 부분.
	m_menubar = new MenuBar(this);
}

// 사각형 위치를 지운다.
void View::eraseRect(int x, int y, int   sizeX, int  sizeY) // 좌상귀 x y 그리고 x축 y축 크기
{
	// TODO: 여기에 구현 코드 추가.
	setPenColor(RGB(255, 255, 255));
	setFillColor(RGB(255, 255, 255));
	drawRectangle(x, y, sizeX, sizeY);
}

// 윈도의 위치를 돌려준다.
RECT View::getClientRect()   // RECT에는 left, right, top, bottom 멤버 변수가 있다.
{
	// TODO: 여기에 구현 코드 추가.
	RECT r;
	GetClientRect(m_WindowHandle, &r);
	return r;
}


// 현재 폰트에서 text를 출력했을 때, 화면상에 차지하는 크기를 돌려주는 함수
SIZE View::textSize(const std::string text)
{
	// TODO: 여기에 구현 코드 추가.
	SIZE size;
	const char *s = text.c_str();
	GetTextExtentPoint32A(m_DCHandle, s, strlen(s), &size);
	return size;
}

int View::getWindowWidth() {
	RECT r;
	GetWindowRect(m_WindowHandle, &r);
	return r.right - r.left;
}
int View::getWindowHeight() {
	RECT r;
	GetWindowRect(m_WindowHandle, &r);
	
	return r.bottom - r.top;
}
void View::addButton(TButton *b) {
	//
}

void View::OnMouseMove(Event e) {
	//메뉴가 펼쳐진 상황에서는 버튼 위에 있어도 다시 그리지 않게한다.
	if (menu) {
		if (menu->re_isPressed() == true) {
			return;
		}
	}
	Component *b = m_toolbar->t_findButton(e.x, e.y);
	m_toolbar->mouseMove(b);

	Component *m = m_menubar->m_findButton(e.x,e.y);
	m_menubar->mouseMove(m);

}

void View::drawIcon(int x, int y, HICON i) {
	DrawIcon(m_DCHandle,x,y,i);
}

void View::findAreaFigure(int x1,int y1, int x2, int y2) {
	for (auto a : myFigList) {
		
		if (a->is_inside_area(x1,y1,x2,y2)) {
			addSelectFigure(a);
			a->action();
		}
	}
}

Figure* View::findSelectFigure() {
	for (auto a : myFigList) {
		if (a->re_selected()) {
			return a;
		}
	}
	return nullptr;
}

void View::addFigure(Figure * f) {
	myFigList.push_back(f);
}

void View::addSelectFigure(Figure * f) {
	mySelectedList.push_back(f);
}

void View::eraseFig(Figure *f) {
	myFigList.remove(f);
}