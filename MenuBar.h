#pragma once
#include "Container.h"
#include <list>
#include "Menu.h"

class View;

//�������� �޴��� �����Ѵ�
//�����̳ʿ��� ��ӹ޴´�
class MenuBar : public Container
{
public:
	MenuBar(View *);
	~MenuBar();
	
	//�޴��ٱ׸���(���⼭ �޴���ư�� �� �׸��� �ȴ�)
	void draw();

	//�޴���ư�߰�
	void addMenu(Menu *);
	bool insideMenu(int x, int y);

	void mouseMove(Component *);
};

