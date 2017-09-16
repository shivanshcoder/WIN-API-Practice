#include"selfwindow.h"


windows::windows(TCHAR szAppName[],int iCmdShow) {
	this->style = CS_HREDRAW | CS_VREDRAW;
	this->lpfnWndProc = WndProcs;
	this->cbClsExtra = 0;
	this->cbWndExtra = 0;
	this->hInstance = hInstance;
	this->hIcon = LoadIcon(NULL, IDI_APPLICATION);
	this->hCursor = LoadCursor(NULL, IDC_ARROW);
	this->hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	this->lpszMenuName = NULL;
	this->lpszClassName = szAppName;
	this->registerwnd();
	hwnd = CreateWindow(szAppName, TEXT("Get System Metrics No. 2"),
		WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL | WS_MAXIMIZE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
	this->showwnd(iCmdShow);
	//this->upwin();
}

WPARAM windows::messages() {
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


LRESULT CALLBACK WndProcs(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int  cxChar, cxCaps, cyChar, cyClient, iVscrollPos;
	HDC         hdc;
	int         i, y;
	PAINTSTRUCT ps;
	TCHAR       szBuffer[10];
	TEXTMETRIC  tm;

	switch (message)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);

		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_SIZE:
		cyClient = HIWORD(lParam);
		return 0;

	
	case WM_PAINT:
		
		hdc = BeginPaint(hwnd, &ps);
		windows::paint(hdc);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

