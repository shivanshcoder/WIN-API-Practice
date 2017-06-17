#include<Windows.h>

LRESULT CALLBACK WndProcs(HWND, UINT, WPARAM, LPARAM);

int WINAPI sWinMain(HINSTANCE hInstance, HINSTANCE PrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("PENS AND BRUSHES");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	HBRUSH hbrush = CreateHatchBrush(HS_CROSS,RGB(255,0,255));

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProcs;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_HAND);
	wndclass.hbrBackground = (HBRUSH)(hbrush);
	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("Practice"), WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&msg, NULL, 0, 0));{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
//
//LRESULT CALLBACK WndProcs(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
//
//}