#pragma once
#include "Container.h"

#include <string>
using namespace std;

class MenuItem;

//�������� �޴��׸��� �����Ѵ�
//�����̳ʿ��� ��ӹ޴´�
class Menu : public Container
{
public:
	Menu(string,View *,int);
	~Menu();

	void addMenuItem(MenuItem *);
	void setPoint(int,int,int,int);
	
	MenuItem* insideItem(int,int);

private:
	//�޴������� ��ġ �������� +32 �� ���ֱ� ���� �ӽ� ����
	//y��ǥ�� �޶���
	int itemY1,itemY2;
};

