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
	
	/* ������Ʈ�� �ű�.
	//������ �����Լ�
	void setIcon(HICON i);
	//������ �׸��� �Լ�
	void drawIcon();
	*/
};

