#include "stdafx.h"
#include "MyView.h"
#include <fstream>
#include <cstdlib>
MyView::MyView(HINSTANCE hInstance):View(hInstance)
{
	can_draw = true;
	
}

MyView::MyView(HWND w):View(w)
{
	can_draw = true;
	
}

MyView::~MyView() 
{
}
#include "FigEllipse.h"
#include "FigLine.h"
#include "FigRect.h"
#include "TButton.h"
#include "ToolBar.h"
#include "MenuBar.h"
#include "Menu.h"
#include "MenuItem.h"
#include "Group.h"

void MyView::OnLButtonDown(Event e)
{
	//���� ��ġ�� ����Ű��
	can_draw = true;
	m_start = e;
	
	//�޴��� ������ ��Ȳ������ ��ưŬ���̾ƴ϶� �޴�Ŭ���� �Ǿ�� �Ѵ�!!!!
	if (menu) {
		if (menu->re_isPressed() == true) {

			//�޴� ���� ���¸� �׸��� �׸��� �ʴ´�.
			can_draw = false;
			//���� Ŭ���� �޴������� �ȿ� �ִ� ���
			item_current = menu->insideItem(e.x, e.y);

			//���� �޴� ����
			if (item_current && menu == btnFig) {
				//�޴��׸��� ������ ��� ���ٹ�ư�� ��� ����.
				
				btnItemEllipse->set_isPressed(false);
				btnItemRect->set_isPressed(false);
				btnItemLine->set_isPressed(false);

				item_current->set_isPressed(true);

				btnEllipse->set_isPressed(false);
				btnLine->set_isPressed(false);
				btnRect->set_isPressed(false);

				item_current->action();
			}
			//���� �޴� ����
			if (item_current && menu == btnFile) {
				if (item_current->re_identity() == 0) { //���� Ŭ��
					
					ofstream a_file("MyFigure.txt");
					a_file << myFigList.size()<<"\n";
					for (auto a : myFigList) {
						//���� ����
						if (a->re_myFigure() != 3) { //�׷��� �ƴ� ���
							//�����Ұ� : ���, ����, ä���, ��ǥ
							a_file << a->re_myFigure() << " ";
							//���� ����
							a_file << a->re_lineColor() << " ";
							//ä��� ����
							a_file << a->re_fillColor() << " ";
							//��ǥ ����
							a_file << a->re_x1() << " ";
							a_file << a->re_y1() << " ";
							a_file << a->re_x2() << " ";
							a_file << a->re_y2() << "\n";
						}
					}

					a_file.close();
				}
				else if (item_current->re_identity() == 1) { //���� Ŭ��
					
					//��������Ʈ�� ����.
					myFigList.clear();

					int numFig;
					int x1, y1, x2, y2;
					//�⺻��
					COLORREF m_line = RGB(0, 0, 0);
					COLORREF m_fill = RGB(255, 255, 255);

					int information[7]; //������ 7����...
					
					ifstream b_file("MyFigure.txt");
					b_file >> numFig; //���� ���� ����
					
					for (int i = 0; i < numFig; i++) {
						for (int k = 0; k < 7; k++) {
							b_file >> information[k];
						}

						x1 = information[3];
						y1 = information[4];
						x2 = information[5];
						y2 = information[6];
						//�� �� ����
						switch (information[1])
						{
						case 255: //����
							m_line = RGB(255, 0, 0);
							break;
						case 65280: //�ʷ�
							m_line = RGB(0, 255, 0);
							break;
						case 16711680: //�Ķ�
							m_line = RGB(0, 0, 255);
							break;
						default:
							break;
						}
						//ä�� �� ����
						switch (information[2])
						{
						case 255: //����
							m_fill = RGB(255, 0, 0);
							break;
						case 65280: //�ʷ�
							m_fill = RGB(0, 255, 0);
							break;
						case 16711680: //�Ķ�
							m_fill = RGB(0, 0, 255);
							break;
						default:
							break;
						}
						//��������
						switch (information[0])
						{
						case 0: //�簢��
							myFigList.push_back(new FigRect(x1, y1, x2, y2, this, m_line, m_fill));
							break;
						case 1: //Ÿ��
							myFigList.push_back(new FigEllipse(x1, y1, x2, y2, this, m_line, m_fill));
							break;
						case 2: //����
							myFigList.push_back(new FigLine(x1, y1, x2, y2, this, m_line, m_fill));
							break;
						default:
							break;
						}
					}
					
					b_file.close();
					
				}
				item_current->action();
			}

			//���� �޴� ����
			if (item_current && menu == btnMenuLineColor) {
				
				btnRedLine->set_isPressed(false);
				btnGreenLine->set_isPressed(false);
				btnBlueLine->set_isPressed(false);

				if (item_current->re_identity() == 0) {
					btnRedLine->set_isPressed(true);
				}
				else if (item_current->re_identity() == 1) {
					btnGreenLine->set_isPressed(true);
				}
				else if(item_current->re_identity() == 2){
					btnBlueLine->set_isPressed(true);
				}

				item_current->action();
			}
			//ä��� �޴� ����
			if (item_current && menu == btnMenuFillColor) {
				
				btnRedFill->set_isPressed(false);
				btnGreenFill->set_isPressed(false);
				btnBlueFill->set_isPressed(false);

				debugOutput(item_current->re_identity());
				if (item_current->re_identity()==0) {
					btnRedFill->set_isPressed(true);
				}
				else if (item_current->re_identity()==1) {
					btnGreenFill->set_isPressed(true);
				}
				else if (item_current->re_identity()==2) {
					btnBlueFill->set_isPressed(true);
				}

				item_current->action();
			}
			return;
		}
		
	}
	
	//���� ��ư�� ������ ��쿡�� �޴��׸��� nullptr�� �����,
	Component *b = m_toolbar->t_findButton(e.x, e.y);
	if (b) {
		item_current = nullptr;
	}
	//�ٸ� ����(����,�޴�)�� ��ư�� ���� ��� ����� ��� ��ư�� false�� �ٲٴ� ������
	//������ �׸��� �ڵ尡 �޴��� ������ ������������ ���ٷ� �簢���� �����ص�
	//�簢���� �׷����� �ʰ� ������ �׷����� ������ ���� ����..
	t_current = m_toolbar->t_findButton(e.x, e.y);
	if (t_current) {
		if (t_current->re_identity() == 1) {
			//����..
			btnEllipse->set_isPressed(false);
			btnLine->set_isPressed(false);
			btnRect->set_isPressed(false);
			btnItemEllipse->set_isPressed(false);
			btnItemRect->set_isPressed(false);
			btnItemLine->set_isPressed(false);

			t_current->set_isPressed(true);
		}
		if (t_current->re_identity() == 2) {
			//����...
			btnRedLine->set_isPressed(false);
			btnGreenLine->set_isPressed(false);
			btnBlueLine->set_isPressed(false);
			t_current->set_isPressed(true);
		}
		if (t_current->re_identity() == 3) {
			//ä���..
			btnRedFill->set_isPressed(false);
			btnGreenFill->set_isPressed(false);
			btnBlueFill->set_isPressed(false);
			t_current->set_isPressed(true);
		}
		if (t_current->re_identity() == 4) {
			//��ü����...
			myFigList.clear();

		}
	}

	Figure * figure = findSelectFigure();
	
	if (figure) {
		//����Ʈ �������·� ���� Ŭ��->�̵�����
		if (e.shiftPressed() && !e.ctrlPressed()) {
			m_before = e; //�̵� �� ��ġ ���
		}

		//��Ʈ�� ����Ʈ �Ѵ� ���� ����->�׷�ȭ
		if (e.shiftPressed() && e.ctrlPressed()) {
			Group *g = new Group(this);
			for (auto a : mySelectedList) {
				//���� ���õ� ������ �׷쿡 �ֱ�
				g->addGroupFigure(a);
				//��������Ʈ���� ����
				eraseFig(a);
			}
			//��������Ʈ�� �׷��� �߰�
			g->setFirstPoint();
			addFigure(g);
		}
	}
	
}
void MyView::OnLButtonUp(Event e) {

	
	View::OnLButtonUp(e);
	
	Figure * figure = findSelectFigure();
	
	if (figure) {
		//���콺�� ���� ���� shift�� ������ ���¶��,
		if (e.shiftPressed() && !e.ctrlPressed()) {
			m_after = e; //�̵� �� ��ġ ���
			for (auto a : mySelectedList) {
				a->setPoint(m_after.x - m_before.x, m_after.y - m_before.y);
			}
			//����� ���������� ���õ� ����Ʈ�� clear�Ѵ�
			mySelectedList.clear();

			//������ �̵��ÿ��� �׸��� �׸��� �ʴ´�.
			return;
		}
		//��Ʈ�� �������·� ���� Ŭ��->��������
		if (e.ctrlPressed() && !e.shiftPressed()) {
			for (auto a : mySelectedList) {
				a->addFigure();
			}
			//����� ���������� ���õ� ����Ʈ�� clear�Ѵ�
			mySelectedList.clear();
			//������ ����ÿ��� �׸��� �׸��� �ʴ´�.
			return;
		}
		
	}
	//��� ����� �������� ���� ä�� ���� Ŭ���� �Ǿ��� ��쿡�� ���� ����Ʈ�� ����
	mySelectedList.clear();

	//����â������ �׸��� �׸� �� ����.
	if (m_toolbar->insideTool(m_start.x, m_start.y)) {
		return;
	}
	if (m_toolbar->insideTool(e.x, e.y)) {
		return;
	}
	//�޴�â������ �׸��� �׸� �� ����.
	if (m_menubar->insideMenu(m_start.x, m_start.y)) {
		return;
	}
	if (m_menubar->insideMenu(e.x, e.y)) {
		return;
	}
	//����Ʈ/��Ʈ���� ������ ���¸� �׸��� �׸� �� ����.
	if (e.ctrlPressed() || e.shiftPressed()) {
		return;
	}

	if (can_draw == false) return;
	//�� ��ư�� isPressed�� ���̰ų� �޴��������� ������ ���
	if (btnEllipse->re_isPressed()||btnItemEllipse->re_isPressed()) {
		if (btnRedLine->re_isPressed()) {
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(255, 255, 255)));
			}
		}
		else if (btnGreenLine->re_isPressed()) {
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(255, 255, 255)));
			}
		}
		else if(btnBlueLine->re_isPressed()){
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(255, 255, 255)));
			}
		}
		else {
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigEllipse(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(255, 255, 255)));
			}
		}
	}
	else if (btnLine->re_isPressed()||btnItemLine->re_isPressed()) {
		if (btnRedLine->re_isPressed()) {
			myFigList.push_back(new FigLine(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(0, 0, 0)));
		}
		else if (btnGreenLine->re_isPressed()) {
				myFigList.push_back(new FigLine(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(0, 0, 0)));
		}
		else if (btnBlueLine->re_isPressed()) {
			myFigList.push_back(new FigLine(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(0, 0, 0)));
		}
		else {
			myFigList.push_back(new FigLine(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(0, 0, 0)));
		}
	}
	else if (btnRect->re_isPressed() ||btnItemRect->re_isPressed()) {
		if (btnRedLine->re_isPressed()) {
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(255, 0, 0), RGB(255, 255, 255)));
			}
		}
		else if (btnGreenLine->re_isPressed()) {
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 255, 0), RGB(255, 255, 255)));
			}
		}
		else if (btnBlueLine->re_isPressed()) {
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 255), RGB(255, 255, 255)));
			}
		}
		else {
			if (btnRedFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(255, 0, 0)));
			}
			else if (btnGreenFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(0, 255, 0)));
			}
			else if (btnBlueFill->re_isPressed()) {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(0, 0, 255)));
			}
			else {
				myFigList.push_back(new FigRect(m_start.x, m_start.y, e.x, e.y, this, RGB(0, 0, 0), RGB(255, 255, 255)));
			}
		}
	}
	else {
		return;
	}

	View::invalidate(); //���������ʾƵ� �ٷ� �簢�� �׷���
}

void MyView::OnRButtonDown(Event e)
{
	// ���α׷� ���� ����� �����ϱ� ���� ���� ��ư Ŭ���� �Ʒ� ���� ȣ���ϰ� ��������ϴ�.
	//eraseRect(e.x, e.y, 100, 100);
	//::PostMessage(m_WindowHandle, WM_CLOSE, NULL, NULL);
	m_start = e;
}

void MyView::OnRButtonUp(Event e)
{
	m_end = e;

	int temp;
	if (m_start.x > m_end.x) {
		temp = m_start.x;
		m_start.x = m_end.x;
		m_end.x = temp;
	}
	if (m_start.y > m_end.y) {
		temp = m_start.y;
		m_start.y = m_end.y;
		m_end.y = temp;
	}
	findAreaFigure(m_start.x, m_start.y, m_end.x, m_end.y);
}

void MyView::OnChar(long ch)
{
	// Ű���� �Է��� �Ǹ� �� �Լ��� �ڵ� ȣ��˴ϴ�.  cin�̳� getchar, scanf ����
	// ǥ�� �Է��Լ��� �۵����� ������ onchar �� �� �̿��ؾ� �մϴ�.
	
	if (ch == 8) { //backspace������ ���õ� ���� ����
		for (auto a : mySelectedList) {
			eraseFig(a);
		}
	}

	if (ch == 103) {
		for (auto a : myFigList) {
			if (a->re_myFigure() == 3) {
				a->setG(true);
			}
		}
	}
	invalidate();
}

void MyView::OnKeyDown(long ch) {
	
}
void MyView::OnKeyUp(long ch) {
	//g==71
	//m==77
	if (ch == 71) {
		for (auto a : myFigList) {
			if (a->re_myFigure() == 3) {
				a->setG(false);
			}
		}
	}
	invalidate();
}


// ��� �������� onInitialize �Լ����� �ʱ�ȭ����.
void MyView::onInitialize()
{
	// *** ��� ������Ʈ���� ���⿡�� �ʱ�ȭ����.
	View::onInitialize();
	//� ��ư�� ��������� ����

	//���� ���� ���� ��ư
	btnRect = new TButton(1,this);
	rectIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,32,32,LR_DEFAULTCOLOR);
	btnRect->setIcon(rectIcon);

	btnEllipse = new TButton(1,this);
	ellipseIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnEllipse->setIcon(ellipseIcon);

	btnLine = new TButton(1,this);
	lineIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnLine->setIcon(lineIcon);
	
	addButton(btnRect);
	addButton(btnEllipse);
	addButton(btnLine);

	//�� �� ���� ��ư
	//�Ķ���ͷ� RGB�� ������.
	btnRedLine = new TButton(2,this);
	LredIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON4), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnRedLine->setIcon(LredIcon);
	
	btnGreenLine = new TButton(2,this);
	LgreenIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON6), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnGreenLine->setIcon(LgreenIcon);

	btnBlueLine = new TButton(2,this);
	LblueIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON5), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBlueLine->setIcon(LblueIcon);

	addButton(btnRedLine);
	addButton(btnGreenLine);
	addButton(btnBlueLine);

	//���� ä��� ��ư
	btnRedFill = new TButton(3,this);
	FredIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON7), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnRedFill->setIcon(FredIcon);

	btnGreenFill = new TButton(3,this);
	FgreenIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON8), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnGreenFill->setIcon(FgreenIcon);

	btnBlueFill = new TButton(3,this);
	FblueIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON9), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBlueFill->setIcon(FblueIcon);

	//���� ������� ��ư
	btnEraseAll = new TButton(4, this);
	eraseAll = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON10), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnEraseAll->setIcon(eraseAll);

	addButton(btnRedFill);
	addButton(btnGreenFill);
	addButton(btnBlueFill);
	addButton(btnEraseAll);

	//����, �����޴� ����� �޴�����Ʈ�� �߰�
	btnFile = new Menu("����",this,1);
	btnFig = new Menu("����", this,2);
	btnMenuLineColor = new Menu("�� ��",this,3);
	btnMenuFillColor = new Menu("ä�� ��", this,4);
	addButton(btnFile);
	addButton(btnFig);
	addButton(btnMenuLineColor);
	addButton(btnMenuFillColor);

	//�޴� ���� ��ư�� ����, �ʷ�, �Ķ� �ֱ�
	btnMenuLineRed = new MenuItem("����", this,0);
	btnMenuLineGreen = new MenuItem("�ʷ�", this,1);
	btnMenuLineBlue = new MenuItem("�Ķ�",this,2);
	addMenuItem(btnMenuLineColor,btnMenuLineRed);
	addMenuItem(btnMenuLineColor, btnMenuLineGreen);
	addMenuItem(btnMenuLineColor, btnMenuLineBlue);

	//�޴� ä��� ��ư�� ����, �ʷ�, �Ķ� �ֱ�
	btnMenuFillRed = new MenuItem("����", this,0);
	btnMenuFillGreen = new MenuItem("�ʷ�", this,1);
	btnMenuFillBlue = new MenuItem("�Ķ�", this,2);
	addMenuItem(btnMenuFillColor, btnMenuFillRed);
	addMenuItem(btnMenuFillColor, btnMenuFillGreen);
	addMenuItem(btnMenuFillColor, btnMenuFillBlue);

	//���Ϲ�ư�� ����, ���� �ֱ�
	btnSave = new MenuItem("����",this,0);
	btnOpen = new MenuItem("����", this,1);
	addMenuItem(btnFile,btnSave);
	addMenuItem(btnFile,btnOpen);
	
	//������ư�� �簢��, Ÿ��, ���� �ֱ�
	btnItemRect = new MenuItem("�簢��",this,0);
	btnItemEllipse = new MenuItem("Ÿ��", this,1);
	btnItemLine = new MenuItem("����", this,2);
	addMenuItem(btnFig, btnItemRect);
	addMenuItem(btnFig, btnItemEllipse);
	addMenuItem(btnFig, btnItemLine);

	View::invalidate();

}
void MyView::addMenuItem(Menu *mymenu,MenuItem *b) {
	mymenu->addMenuItem(b);
}
void MyView::addButton(TButton *b) {
	m_toolbar->addComponent(b); //TButton�� ���ߵȴ�.
}

void MyView::addButton(Menu *b) {
	m_menubar->addMenu(b); //Menu ���ߵȴ�.
}

// ���  ���빰���� �ٽ� �׷��ִ� �Լ�.  ������ �ʿ��� ���̴�.
void MyView::redrawAll()
{
	
	//��� �簢���� �׷��ش�.
	for (list <Figure *>::iterator i = myFigList.begin(); i != myFigList.end(); i++) {
		//��� figure���� draw���ش�.
		(*i)->draw();
	}
	for (auto a : myFigList) {
		if (a->re_myFigure() == 3) {
			if (a->re_G() == true) {
				a->drawArea();
			}
		}
	}

	View::redrawAll();

}