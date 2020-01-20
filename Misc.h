#pragma once
#include "stdafx.h"
#include <string>
//#include "Proj2018.h"
// ����� �͵��� �ֱ� ���� ��� ����
void debugOutput(int n);
void debugOutput(const char *s);
void debugOutput(const std::string &s);

class Event {
public:
	Event();
	Event(WPARAM wParam, LPARAM lParam);
	bool ctrlPressed();
	bool shiftPressed();

	int x, y;
	WPARAM m_wParam;
};