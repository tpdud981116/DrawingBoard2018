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

	//��ư �߰�
	void addComponent(TButton *);
	
	//���ٰ� ǥ�õ� �� �׸���
	void draw();

	//���� ������ ����
	//void setSize();

	void mouseMove(Component *b);
	
	//����â������ �׸��� �׸� �� ����
	//�װ��� �Ǵ����ִ� �Լ�
	bool insideTool(int x, int y);

private:
	/*
	//�� ��ư�� ũ�� �� ��ġ
	int m_btnX, m_btnY;
	int m_btnSizeX, m_btnSizeY;
	*/
	//���� â�� ������
	//int m_sizeX; int m_sizeY;

};

