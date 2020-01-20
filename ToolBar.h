#pragma once

#include <list>
#include "Container.h"

using namespace std;

class TButton;
class View;

class ToolBar : public Container
{
public:
	ToolBar(View *);
	~ToolBar();

	//버튼 추가
	void addComponent(TButton *);
	
	//툴바가 표시될 줄 그리기
	void draw();

	//툴바 사이즈 설정
	//void setSize();

	void mouseMove(Component *b);
	
	//툴바창에서는 그림을 그릴 수 없음
	//그것을 판단해주는 함수
	bool insideTool(int x, int y);

private:
	/*
	//각 버튼의 크기 및 위치
	int m_btnX, m_btnY;
	int m_btnSizeX, m_btnSizeY;
	*/
	//툴바 창의 사이즈
	//int m_sizeX; int m_sizeY;

};

