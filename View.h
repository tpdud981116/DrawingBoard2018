#pragma once
#include "iostream"
#include "string"
#include "Proj2018.h"
#include <list>
#include "Misc.h"
#include "Container.h"

#define MAX_LOADSTRING 100
using namespace std;

class MenuBar;
class Menu;
class Figure;
class ToolBar;
class TButton;
class Group;
class View:public Container
{
public:
	View();
	View(HINSTANCE);
	View(HWND);
	~View();
protected:
	HWND m_WindowHandle;    //  바탕 윈도 handle
	HDC m_DCHandle;	// DC handle
	HBRUSH brushWhite, brushBlack;
	HPEN penWhite, penBlack;
	// 임시 변수
	int count = 0;
	HPEN thePen;
	HBRUSH theBrush;
	HINSTANCE m_InstanceHandle;
	WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
	WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

public:
	// 초기화 함수들
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL initInstance(/*HINSTANCE hInstance, */int nCmdShow);

	// 이벤트 처리 함수들
	virtual void OnLButtonDown(Event e);
	virtual void OnLButtonUp(Event e);
	virtual void OnRButtonDown(Event e);
	virtual void OnRButtonUp(Event e);
	virtual void OnChar(long ch);
	virtual void OnKeyDown(long ch);
	virtual void OnKeyUp(long ch);

	void setPenColor(COLORREF color);         // 펜 색깔 설정. 두께는 1로 자동.
	void setPen(COLORREF color, int width);   // 펜 색깔과 두께까지 설정.
	void setFillColor(COLORREF color);
	void setTextColor(COLORREF color);
	void setTextBkColor(COLORREF color);
 
	void drawRectangle(int x, int y, int sizeX, int sizeY);
	void drawEllipse(int x, int y, int sizeX, int sizeY);
	void drawLine(int x, int y, int sizeX, int sizeY);
	void drawText(std::string str, int x, int y);
	virtual void redrawAll();
	//void eraseAll();
	void invalidate();
	virtual void onInitialize();

	int getWindowWidth();
	int getWindowHeight();
	void eraseRect(int x, int y, int sizeX, int sizeY);
	RECT getClientRect();
	SIZE textSize(std::string text);

	void drawIcon(int,int,HICON);
protected:
	Event m_start;
	Event m_end;
	//도형 리스트
	list <Figure *> myFigList;
	//선택된 도형 리스트
	list <Figure *> mySelectedList;


	//영역 안에 도형이 있는지 찾는 함수용
	void findAreaFigure(int,int,int,int);
	Figure *findSelectFigure();
	
	bool is_drawing;
	
	//최근툴바버튼
	Component * t_current;

	ToolBar * m_toolbar;
	MenuBar * m_menubar;

	Menu *menu;

	//최근 메뉴아이템 버튼
	MenuItem*item_current;
	
	//이동위치
	Event m_before; //이동 전 위치
	Event m_after; //이동 후 위치

public:
	
	virtual void addButton(TButton *b);
	void OnMouseMove(Event e);

	//도형추가함수
	void addFigure(Figure *);
	void addSelectFigure(Figure *);

	
	//그룹으로 새로 추가되어 원래 리스트에서 단일로는 삭제됨.
	void eraseFig(Figure *);
};

