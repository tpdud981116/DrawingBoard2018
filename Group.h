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

	//�׷� ���(����) �߰� �Լ�
	void addGroupFigure(Figure *);

	//setPoint�Լ� �������̵�
	void setPoint(int, int);

	//���� ����
	void addFigure();
	
	//���� �׸����Լ�
	void draw();

	//ó�� ��ǥ �����̿�
	void setFirstPoint();
	
	//�׷�ȭ ���� �׸���
	void drawArea();

	//�μ� ���� ���� �����ֱ�
	virtual int re_numElements() const;
private:
	list <Figure *> myGroupElements; //�� �׷쿡 ���ԵǴ� ��ҵ�
	
};

