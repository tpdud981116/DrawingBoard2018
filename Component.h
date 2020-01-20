#pragma once

#include <string>
using namespace std;

class View;

class Component
{
public:
	//생성자
	Component();
	Component(View*);
	Component(string,View*);
	Component(string name, View *view,int i);
	//소멸자
	~Component();

	//그리기함수
	void draw();

	//사각형 내부에 있는지 판단 함수
	bool inside(int x, int y);

	virtual void action();
	void redraw();

	void set_isON(bool result);
	bool re_isON() const;
	void state();

	void set_isPressed(bool result);
	bool re_isPressed() const;

	//아이콘 설정함수
	void setIcon(HICON i);
	//아이콘 그리는 함수
	void drawIcon();

	//내 역할 돌려주기
	int re_identity() const;
protected:
	//텍스트 데이터	
	string m_name;
	View *mainview;

	//도형 정보
	int m_x, m_y; //시작점
	int m_sizex, m_sizey; //사이즈

	//버튼의 정보
	bool isON; //마우스가 위에 있는지 판단
	bool isPressed; //버튼이 눌렸는지 판단

	//내 아이콘
	HICON m_icon;

	//버튼의 역할
	int m_identity;

};

