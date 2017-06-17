#pragma once
#include<Windows.h>

WPARAM ca(int iCmdShow);

extern LRESULT CALLBACK WndProcs(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
/*CALLBACK Function to be defined*/
class windows :public WNDCLASS {
public:
	/*FOR DEFINING ALL PROPERIES INDIVIDUALLY*/
	windows();
	/*FOR USING SOME PREDEFINED PROPERTIES*/
	windows(TCHAR szAppName[],int iCmdShow);

	void registerwnd() { RegisterClass(this); }

	WPARAM showwnd(int CmdShow) { ShowWindow(hwnd, CmdShow); upwin(); return messages(); }

	void upwin() { UpdateWindow(hwnd); }

static void paint(HDC hdc);
static void WM_size();

	WPARAM messages();
	HWND hwnd;
	MSG msg;
private:
};

class call {
	LRESULT a;
};