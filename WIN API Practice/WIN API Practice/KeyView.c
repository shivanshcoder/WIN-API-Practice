#include<Windows.h>
#include"Header.h"

LRESULT CALLBACK WndProc(WHND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("KeyView1");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.hInstance = hInstance;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("KeyBoard Message Viewer"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWIndow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static int cxClientMax, cyClientMax, cxClient, cyClient, cxChar, cyChar;
	static int cLines, cLinesMax;
	static PMSG pmsg;
	static RECT rectScroll;
	static TCHAR szTop[] = TEXT("Message      Key      Char")
		TEXT("Repeat  Scan Ext Alt Prev Tran");
	static TCHAR szUnd[] = TEXT("_______      ___      ____")
		TEXT("______  ____ ___ ___ ____ ____");
	static TCHAR * szFormat[2] = {
		TEXT("%-13s %3d %-15s%c%6u %4u")
	}

}