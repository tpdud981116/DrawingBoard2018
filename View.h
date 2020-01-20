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
	HWND m_WindowHandle;    //  ���� ���� handle
	HDC m_DCHandle;	// DC handle
	HBRUSH brushWhite, brushBlack;
	HPEN penWhite, penBlack;
	// �ӽ� ����
	int count = 0;
	HPEN thePen;
	HBRUSH theBrush;
	HINSTANCE m_InstanceHandle;
	WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

public:
	// �ʱ�ȭ �Լ���
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL initInstance(/*HINSTANCE hInstance, */int nCmdShow);

	// �̺�Ʈ ó�� �Լ���
	virtual void OnLButtonDown(Event e);
	virtual void OnLButtonUp(Event e);
	virtual void OnRButtonDown(Event e);
	virtual void OnRButtonUp(Event e);
	virtual void OnChar(long ch);
	virtual void OnKeyDown(long ch);
	virtual void OnKeyUp(long ch);

	void setPenColor(COLORREF color);         // �� ���� ����. �β��� 1�� �ڵ�.
	void setPen(COLORREF color, int width);   // �� ����� �β����� ����.
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
	//���� ����Ʈ
	list <Figure *> myFigList;
	//���õ� ���� ����Ʈ
	list <Figure *> mySelectedList;


	//���� �ȿ� ������ �ִ��� ã�� �Լ���
	void findAreaFigure(int,int,int,int);
	Figure *findSelectFigure();
	
	bool is_drawing;
	
	//�ֱ����ٹ�ư
	Component * t_current;

	ToolBar * m_toolbar;
	MenuBar * m_menubar;

	Menu *menu;

	//�ֱ� �޴������� ��ư
	MenuItem*item_current;
	
	//�̵���ġ
	Event m_before; //�̵� �� ��ġ
	Event m_after; //�̵� �� ��ġ

public:
	
	virtual void addButton(TButton *b);
	void OnMouseMove(Event e);

	//�����߰��Լ�
	void addFigure(Figure *);
	void addSelectFigure(Figure *);

	
	//�׷����� ���� �߰��Ǿ� ���� ����Ʈ���� ���Ϸδ� ������.
	void eraseFig(Figure *);
};

