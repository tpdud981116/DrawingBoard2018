#pragma once
#include "MyButton.h"

class View;
//�޴��׸��� ���� �׼��� �Ͼ�� �ϴ� �κ��̴�.
//��ư���� ��� �޴´�.
class MenuItem : public MyButton
{
public:
	MenuItem(string, View*,int);
	~MenuItem();

	//�ش��ϴ� ��ư�� ������ ���
	void action();
	//���콺 Ŭ���� �ش��ϴ� ��ư �ȿ� �ִ� ���
	//�׳� inside��� ����
	//bool is_inside();

	void setPoint(int,int,int,int);
};

