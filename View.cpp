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
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
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
	//m_InstanceHandle = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

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

	//������ ��ư�� ������ �� �ش� ��ư�� �׼��� ����Ǵ°��� ���̺귯����
	//�������� �κ�
	Component *a = m_toolbar->t_findPressed();
	Component *b = m_toolbar->t_findButton(e.x, e.y);
	//�޴��ٰ� ���õ� �޴����� ���É�ٰ� �˷��ش�.
	menu = m_menubar->m_findButton(e.x, e.y);
	if (menu) {
		//���ϸ޴��� �����ִٸ�, �޴��ٿ��� �ٸ� �޴��� �ݾƴ޶���Ѵ�
		//���ϸ޴��� ��ģ��.
		if (menu->re_isPressed() == false) {
			m_menubar->closeMenu();
			menu->set_isPressed(true); //���õ� �޴��� ��ģ���·�.
		}
		else {	//�����ִٸ� �ٽ� �ݴ� ���·� ������.
			menu->set_isPressed(false);
		}
		invalidate();
	}
	else {
		//�޴��� �ƴ� ���� ���� ��� ��� �ݴ´�.
		m_menubar->closeMenu();
		invalidate();
	}

	//���� ��ư�� ������ �ô��� �Ǵ�
	if (t_current != b) {
		return;
	}
	if (b) { //b�� nullptr �� �ƴ� ���
			 //��ư �̸� ���
		
		if (a) { //���� ������ ��ư�� �����Ѵٸ�
			//������ ������ (��->��������) �ٸ� ��ư�ϰ��(��->�簢�� vsŸ��)
			if (a->re_identity() == b->re_identity() && a!=b) { //���� ������ ��ư�� ���� ���� ��ư�� �ٸ� ���
				a->set_isPressed(false); //���� ��ư�� �������� �ٲ۴�.
			}
		}
		b->action(); //action���� ���� ���� ��ư�� ������ �ٲ۴�.
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

// ������ ���� �����ϱ�
void View::setPenColor(COLORREF color)
{
	thePen = CreatePen(PS_SOLID, 1, color);
	SelectObject(m_DCHandle, thePen);
}

// ���� ���� �β��� ���ÿ� �����ϱ�
void View::setPen(COLORREF color, int width)
{
	thePen = CreatePen(PS_SOLID, width, color);
	SelectObject(m_DCHandle, thePen);
}

// ä�� ���� �����ϴ� �Լ�.
void View::setFillColor(COLORREF color)
{
	theBrush = CreateSolidBrush(color);
	SelectObject(m_DCHandle, theBrush);
}

// ���� ���� �����ϴ� �Լ�.
void View::setTextColor(COLORREF color)
{
	SetTextColor(m_DCHandle, color);
}

// ���� ������ �����ϴ� �Լ��� �����.
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

// ���  ���빰���� �ٽ� �׷��ִ� �Լ�.  ������ �ʿ��� ���̴�.
void View::redrawAll()
{
	if (m_toolbar) {
		//m_toolbar->setSize();
		m_toolbar->draw();
	}
	if (m_menubar) {
		m_menubar->draw();
	}
	//���������̸� �޴��׸�׸���
	//���������̸� �׸����ʴ´�.
	if (menu) {
		if (menu->re_isPressed() == true) {
			menu->comDraw();
		}
	}

	
}

// ȭ���� ���� ����� �ȵǾ� �ִٰ� �˸��� �Լ��Դϴ�.
// �� �Լ��� ȣ���ϸ� ȭ���� �������� 
// Main.cpp �ʿ� case WM_PAINT: �κ��� ����˴ϴ�.
// �ᱹ�� View ��ü�� display�� ����ǰ���.
void View::invalidate()
{
	InvalidateRect(m_WindowHandle, NULL, true);
}

// ��� �������� onInitialize �Լ����� �ʱ�ȭ����.
void View::onInitialize()
{
	//���ٸ� ������ִ°��� ���̺귯���� �������� �κ�.
	m_toolbar = new ToolBar(this);
	//�޴��� ������ִ°��� ���̺귯���� �������� �κ�.
	m_menubar = new MenuBar(this);
}

// �簢�� ��ġ�� �����.
void View::eraseRect(int x, int y, int   sizeX, int  sizeY) // �»�� x y �׸��� x�� y�� ũ��
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	setPenColor(RGB(255, 255, 255));
	setFillColor(RGB(255, 255, 255));
	drawRectangle(x, y, sizeX, sizeY);
}

// ������ ��ġ�� �����ش�.
RECT View::getClientRect()   // RECT���� left, right, top, bottom ��� ������ �ִ�.
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	RECT r;
	GetClientRect(m_WindowHandle, &r);
	return r;
}


// ���� ��Ʈ���� text�� ������� ��, ȭ��� �����ϴ� ũ�⸦ �����ִ� �Լ�
SIZE View::textSize(const std::string text)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
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
	//�޴��� ������ ��Ȳ������ ��ư ���� �־ �ٽ� �׸��� �ʰ��Ѵ�.
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