#pragma once
#include<Windows.h>

class WINDOW_PROP : private WNDCLASS {
public:
	WINDOW_PROP(UINT, HINSTANCE, LPCWSTR, WNDPROC);


	void hicon(HICON hICON) { hIcon = hICON; }
	void hbrush(HBRUSH hbrBACKGROUND) { hbrBackground = hbrBACKGROUND; }
	void hcursor(HCURSOR hCURSOR) { hCursor = hCURSOR; }
};

WINDOW_PROP::WINDOW_PROP(UINT styles, HINSTANCE hInstances, LPCWSTR lpszClassNames,WNDPROC lpfnWndProcs) {
	style = styles;
	hInstance = hInstances;
	lpszClassName = lpszClassNames;
	hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	hCursor = LoadCursor(hInstance, IDC_ARROW);
	hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	lpszMenuName = nullptr;
	cbClsExtra = 0;
	cbWndExtra = 0;
	lpfnWndProc = lpfnWndProcs;
	RegisterClass(this);
}


