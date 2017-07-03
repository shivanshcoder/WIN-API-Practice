#include<Windows.h>
#include"mYcONSTRUCTS.H"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static int cxClient, cyClient;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE PrevhInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("ViewPorts and Windows");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndclass);

	hwnd = CreateWindowDEF(szAppName, TEXT("Practice"), hInstance);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}
void Paint(HDC hdc) {
	POINT p = { 700,800 };
	SetMapMode(hdc, MM_ISOTROPIC);
	SetWindowExtEx(hdc, 2, 2, NULL);
	SetViewportExtEx(hdc, 1, 1, NULL);
	TextOut(hdc, POINTtoXY(p) , TEXT("VOILA"), 6);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message) {
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		Paint(hdc);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}