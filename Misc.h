#pragma once
#include "stdafx.h"
#include <string>
//#include "Proj2018.h"
// 잡다한 것들을 넣기 위한 헤더 파일
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