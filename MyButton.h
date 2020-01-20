#pragma once

#include "Component.h"
#include "View.h"
#include <string>
using namespace std;

class MyButton:public Component
{
public:
	//생성자
	MyButton();
	MyButton(View *view);
	MyButton(string name,View *view);
	//소멸자
	~MyButton();
	
	/*
	이 함수는  상위 클래스인 Component로 이동하였음.

	//그리기함수
	void draw();

	//사각형 내부에 있는지 판단 함수
	bool inside(int x, int y);

	void action();
	void redraw();
	
	void set_isON(bool result);
	bool re_isON() const;
	void state();

	void set_isPressed(bool result);
	bool re_isPressed() const;
	

protected:
	//텍스트 데이터	
	string m_name;
	View *mainview;

	//사각형 정보
	int m_x, m_y; 
	int m_sizex, m_sizey;
	
	//버튼의 정보
	bool isON; //마우스가 위에 있는지 판단
	bool isPressed; //버튼이 눌렸는지 판단

	*/
};

