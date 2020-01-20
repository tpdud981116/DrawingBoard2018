#pragma once

#include "Component.h"
#include <list>

using namespace std;
class TButton;
class Menu;
class MenuItem;

class Container :public Component{
public:
	Container();
	Container(string, View*,int);
	Container(View*);
	~Container();

	virtual void addComponent(TButton *);
	virtual void addMenu(Menu *);
	
	//툴바버튼찾기
	Component* t_findButton(int,int);
	Component* t_findPressed();
	
	//메뉴찾기
	Menu* m_findButton(int,int);
	Component* m_findPressed();

	//다른 메뉴 닫기
	void closeMenu();

	//툴바, 메뉴그리기
	void comDraw();

	virtual void drawItem();
	
protected:
	
	list <Component *> comList;

	//툴바 버튼의 위치(여기서 정해서 알려줘야함)
	int m_toolX, m_toolY;
	//메뉴 버튼의 위치
	int m_menuX, m_menuY;

};