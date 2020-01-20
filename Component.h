#pragma once

#include <string>
using namespace std;

class View;

class Component
{
public:
	//������
	Component();
	Component(View*);
	Component(string,View*);
	Component(string name, View *view,int i);
	//�Ҹ���
	~Component();

	//�׸����Լ�
	void draw();

	//�簢�� ���ο� �ִ��� �Ǵ� �Լ�
	bool inside(int x, int y);

	virtual void action();
	void redraw();

	void set_isON(bool result);
	bool re_isON() const;
	void state();

	void set_isPressed(bool result);
	bool re_isPressed() const;

	//������ �����Լ�
	void setIcon(HICON i);
	//������ �׸��� �Լ�
	void drawIcon();

	//�� ���� �����ֱ�
	int re_identity() const;
protected:
	//�ؽ�Ʈ ������	
	string m_name;
	View *mainview;

	//���� ����
	int m_x, m_y; //������
	int m_sizex, m_sizey; //������

	//��ư�� ����
	bool isON; //���콺�� ���� �ִ��� �Ǵ�
	bool isPressed; //��ư�� ���ȴ��� �Ǵ�

	//�� ������
	HICON m_icon;

	//��ư�� ����
	int m_identity;

};

