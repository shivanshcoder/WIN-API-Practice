#include<Windows.h>



LRESULT CALLBACK WndProcs(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMains(HINSTANCE hInstance, HINSTANCE PrevhInstance,
	PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("LINE");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.style = 0;
	wndclass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProcs;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;


	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("PIXELS"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProcs(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static int cxClient, cyClient;
	HDC hdc;
	PAINTSTRUCT ps;
	static int x = 0;
	static int y = 0;
	TCHAR szsBuffer[50];

	switch (message) {

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		return 0;
	case WM_PAINT:
		InvalidateRect(hwnd, NULL, TRUE);
		
		//x += 20;
		//y += 20;
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, x, y, szsBuffer, wsprintf(szsBuffer, TEXT("%d"), GetKeyState(VK_ADD)));
		EndPaint(hwnd, &ps);
		return 0;
	case WM_SYSKEYDOWN:
		x += 5;
		y += 15;
		hdc = GetDC(hwnd);
		TextOut(hdc, x, y, szsBuffer, wsprintf(szsBuffer, TEXT("%d"), GetKeyState(VK_ADD)));
		
//	TextOut(hdc, x, y, szsBuffer, wsprintf(szsBuffer, TEXT("%d"), lParam & 0x1<<30));
		ReleaseDC(hwnd, hdc);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

