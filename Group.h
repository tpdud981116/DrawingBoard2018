#pragma once

#include <list>
#include "Figure.h"
#include "Misc.h"

using namespace std;

class View;

class Group : public Figure
{
public:
	Group(View *);
	~Group();

	//그룹 요소(도형) 추가 함수
	void addGroupFigure(Figure *);

	//setPoint함수 오버라이드
	void setPoint(int, int);

	//도형 복사
	void addFigure();
	
	//도형 그리기함수
	void draw();

	//처음 좌표 설정이요
	void setFirstPoint();
	
	//그룹화 범위 그리기
	void drawArea();

	//부속 도형 개수 돌려주기
	virtual int re_numElements() const;
private:
	list <Figure *> myGroupElements; //내 그룹에 포함되는 요소들
	
};

