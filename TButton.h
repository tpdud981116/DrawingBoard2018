#pragma once

#include "MyButton.h"
#include <string>
using namespace std;

class View;
class TButton:public MyButton
{
public:
	TButton(int,View *);
	TButton(string,View*);
	~TButton();
	void action();
	void setPoint(int x1,int y1, int sizeX, int sizeY);
	
	/* 컴포넌트로 옮김.
	//아이콘 설정함수
	void setIcon(HICON i);
	//아이콘 그리는 함수
	void drawIcon();
	*/
};

