#pragma once

class View;

class Figure
{
public:
	//������ �׸���
	Figure(int x1, int y1, int x2, int y2, View *view,COLORREF line, COLORREF fill);
	Figure(View*);
	~Figure();

	//���� �׸��� �Լ�
	virtual void draw();

	virtual void drawArea();
	
	COLORREF re_lineColor() const;
	COLORREF re_fillColor() const;

	//���� �ȿ� ������ �ִ��� �˷��ִ� �Լ�
	bool is_inside_area(int,int,int,int);

	//�������ô��ߴ�!!�����ֱ�
	virtual void action();
	bool re_selected() const;

	//�����߰��Լ�
	virtual void addFigure();
	virtual Figure * re_copyElement();

	//�� ��ǥ�� �ٲٴ� �Լ�
	virtual void setPoint(int,int);

	virtual void setG(bool);
	virtual bool re_G();
	//���� ���� �������� �˷��ִ� �Լ�
	int re_myFigure();

	//�� ��ǥ�� �����ݴϴ�.
	int re_x1() const;
	int re_y1() const;
	int re_x2() const;
	int re_y2() const;

	//�μ� ���� ���� �����ֱ�
	virtual int re_numElements() const;

	
protected:
	//���� ����
	int m_x1, m_x2, m_y1, m_y2;
	View *mainView;
	
	COLORREF m_line;
	COLORREF m_fill;
	//���� �����������
	int m_fig;

	//���� ���� �Ǿ���?
	bool is_selected;
	bool g_pressed;
};