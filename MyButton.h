#pragma once

#include "Component.h"
#include "View.h"
#include <string>
using namespace std;

class MyButton:public Component
{
public:
	//������
	MyButton();
	MyButton(View *view);
	MyButton(string name,View *view);
	//�Ҹ���
	~MyButton();
	
	/*
	�� �Լ���  ���� Ŭ������ Component�� �̵��Ͽ���.

	//�׸����Լ�
	void draw();

	//�簢�� ���ο� �ִ��� �Ǵ� �Լ�
	bool inside(int x, int y);

	void action();
	void redraw();
	
	void set_isON(bool result);
	bool re_isON() const;
	void state();

	void set_isPressed(bool result);
	bool re_isPressed() const;
	

protected:
	//�ؽ�Ʈ ������	
	string m_name;
	View *mainview;

	//�簢�� ����
	int m_x, m_y; 
	int m_sizex, m_sizey;
	
	//��ư�� ����
	bool isON; //���콺�� ���� �ִ��� �Ǵ�
	bool isPressed; //��ư�� ���ȴ��� �Ǵ�

	*/
};

