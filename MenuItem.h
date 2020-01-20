#pragma once
#include "MyButton.h"

class View;
//메뉴항목은 실제 액션이 일어나야 하는 부분이다.
//버튼에서 상속 받는다.
class MenuItem : public MyButton
{
public:
	MenuItem(string, View*,int);
	~MenuItem();

	//해당하는 버튼이 눌렸을 경우
	void action();
	//마우스 클릭이 해당하는 버튼 안에 있는 경우
	//그냥 inside사용 가능
	//bool is_inside();

	void setPoint(int,int,int,int);
};

