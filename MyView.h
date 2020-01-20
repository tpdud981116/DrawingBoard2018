#pragma once

#include "View.h"

class MyView :public View
{
public:
	MyView(HINSTANCE);
	MyView(HWND);
	~MyView();

	void OnLButtonDown(Event e);
	void OnLButtonUp(Event e);
	void OnRButtonDown(Event e);
	void OnRButtonUp(Event e);
	void OnChar(long ch);
	void OnKeyDown(long ch);
	void OnKeyUp(long ch);

	void addButton(TButton *b);
	void addButton(Menu *b);
	void addMenuItem(Menu *mymenu,MenuItem *b);

	void redrawAll();
	void onInitialize();
private:
	TButton * btnRect, *btnEllipse, *btnLine;
	TButton * btnRedLine, *btnGreenLine, *btnBlueLine;
	TButton * btnRedFill, *btnGreenFill, *btnBlueFill;
	TButton * btnEraseAll;

	Menu * btnFile, *btnFig, *btnMenuLineColor, *btnMenuFillColor;
	MenuItem *btnSave, *btnOpen;
	MenuItem *btnItemRect, *btnItemEllipse, *btnItemLine;
	MenuItem *btnMenuLineRed, *btnMenuLineGreen, *btnMenuLineBlue;
	MenuItem *btnMenuFillRed, *btnMenuFillGreen, *btnMenuFillBlue;
	
	//도형 아이콘
	HICON rectIcon, ellipseIcon, lineIcon;
	//선 색 아이콘
	HICON LredIcon, LgreenIcon, LblueIcon;
	//채움 색 아이콘
	HICON FredIcon, FgreenIcon, FblueIcon;
	//모두지우기 아이콘
	HICON eraseAll;

	bool can_draw;

};
