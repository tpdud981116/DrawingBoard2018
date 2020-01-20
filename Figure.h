#pragma once

class View;

class Figure
{
public:
	//도형을 그린다
	Figure(int x1, int y1, int x2, int y2, View *view,COLORREF line, COLORREF fill);
	Figure(View*);
	~Figure();

	//도형 그리는 함수
	virtual void draw();

	virtual void drawArea();
	
	COLORREF re_lineColor() const;
	COLORREF re_fillColor() const;

	//영역 안에 도형이 있는지 알려주는 함수
	bool is_inside_area(int,int,int,int);

	//내가선택당했다!!말해주기
	virtual void action();
	bool re_selected() const;

	//도형추가함수
	virtual void addFigure();
	virtual Figure * re_copyElement();

	//내 좌표를 바꾸는 함수
	virtual void setPoint(int,int);

	virtual void setG(bool);
	virtual bool re_G();
	//내가 무슨 도형인지 알려주는 함수
	int re_myFigure();

	//내 좌표를 돌려줍니다.
	int re_x1() const;
	int re_y1() const;
	int re_x2() const;
	int re_y2() const;

	//부속 도형 개수 돌려주기
	virtual int re_numElements() const;

	
protected:
	//도형 정보
	int m_x1, m_x2, m_y1, m_y2;
	View *mainView;
	
	COLORREF m_line;
	COLORREF m_fill;
	//내가 무슨모양인지
	int m_fig;

	//내가 선택 되엇나?
	bool is_selected;
	bool g_pressed;
};