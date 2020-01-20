#pragma once
#include "Container.h"
#include <list>
#include "Menu.h"

class View;

//여러개의 메뉴를 포함한다
//컨테이너에서 상속받는다
class MenuBar : public Container
{
public:
	MenuBar(View *);
	~MenuBar();
	
	//메뉴바그리기(여기서 메뉴버튼도 다 그리면 된다)
	void draw();

	//메뉴버튼추가
	void addMenu(Menu *);
	bool insideMenu(int x, int y);

	void mouseMove(Component *);
};

