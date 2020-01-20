#pragma once
#include "Container.h"

#include <string>
using namespace std;

class MenuItem;

//여러개의 메뉴항목을 포함한다
//컨테이너에서 상속받는다
class Menu : public Container
{
public:
	Menu(string,View *,int);
	~Menu();

	void addMenuItem(MenuItem *);
	void setPoint(int,int,int,int);
	
	MenuItem* insideItem(int,int);

private:
	//메뉴아이템 위치 설정에서 +32 씩 해주기 위한 임시 변수
	//y좌표만 달라짐
	int itemY1,itemY2;
};

