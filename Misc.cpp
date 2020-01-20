#include "stdafx.h"
#include "Misc.h"
#include <cstdio>
#include <string>

void debugOutput(int n) {
	char buf[100];
	sprintf_s(buf, " %d ", n);
	OutputDebugStringA(buf);
}

void debugOutput(const char *s) {
	OutputDebugStringA(s);
}

void debugOutput(const std::string &s) {
	OutputDebugStringA(s.c_str());
}

Event::Event()
	:m_wParam(0), x(0), y(0) {
	//
}
Event::Event(WPARAM wp, LPARAM lp)
	: m_wParam(wp), x(LOWORD(lp)), y(HIWORD(lp)) {
	//
}

bool Event::ctrlPressed() {
	if (m_wParam & MK_CONTROL) {
		return true;
	}
	else {
		return false;
	}
}

bool Event::shiftPressed() {
	if (m_wParam & MK_SHIFT) {
		return true;
	}
	else {
		return false;
	}
}

