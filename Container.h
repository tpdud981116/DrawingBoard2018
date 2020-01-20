#pragma once

#include "Component.h"
#include <list>

using namespace std;
class TButton;
class Menu;
class MenuItem;

class Container :public Component{
public:
	Container();
	Container(string, View*,int);
	Container(View*);
	~Container();

	virtual void addComponent(TButton *);
	virtual void addMenu(Menu *);
	
	//���ٹ�ưã��
	Component* t_findButton(int,int);
	Component* t_findPressed();
	
	//�޴�ã��
	Menu* m_findButton(int,int);
	Component* m_findPressed();

	//�ٸ� �޴� �ݱ�
	void closeMenu();

	//����, �޴��׸���
	void comDraw();

	virtual void drawItem();
	
protected:
	
	list <Component *> comList;

	//���� ��ư�� ��ġ(���⼭ ���ؼ� �˷������)
	int m_toolX, m_toolY;
	//�޴� ��ư�� ��ġ
	int m_menuX, m_menuY;

};