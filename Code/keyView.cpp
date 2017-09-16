#include<Windows.h>
#include<math.h>
#include"C++_WINAPI_headers.h"

#define NUM    1000
#define TWOPI  (2 * 3.14159)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//class WINDOW_PROP: private WNDCLASS {
//public:
//	WINDOW_PROP(UINT, HINSTANCE, LPCWSTR);
//	void hicon(HICON hICON) { hIcon = hICON; }
//	void hbrush(HBRUSH hbrBACKGROUND) { hbrBackground = hbrBACKGROUND; }
//	void hcursor(HCURSOR hCURSOR) { hCursor = hCURSOR; }
//};
//
//WINDOW_PROP::WINDOW_PROP(UINT styles,HINSTANCE hInstances, LPCWSTR lpszClassNames) {
//	style = styles;
//	hInstance = hInstances;
//	lpszClassName = lpszClassNames;
//	hIcon = LoadIcon(hInstance, IDI_APPLICATION);
//	hCursor = LoadCursor(hInstance, IDC_ARROW);
//	hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	lpszMenuName = nullptr;
//	cbClsExtra = 0;
//	cbWndExtra = 0;
//	lpfnWndProc = WndProc;
//	RegisterClass(this);
//}
//

struct Client_Area {
	int cxClient;
	int cyClient;
};
struct Characters_size {
	int cxChar;
	int cyChar;
};

//class WINDOW  {
//public:
//	LRESULT CALLBACK _WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
//	LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
//	void GetSystemMetrics();
//protected:
//	Client_Area cArea;
//	Characters_size Charac_size;
//	HWND _hwnd;
//	UINT _message;
//	WPARAM _wParam;
//	LPARAM _lParam;
//	HDC _hdc;
//};
//
//void WINDOW::GetSystemMetrics() {
//	cArea.cxClient = ::GetSystemMetrics(SM_CXSCREEN);
//	cArea.cyClient = ::GetSystemMetrics(SM_CYSCREEN);
//}
//
//
//
//LRESULT WINDOW::_WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
//	_hwnd = hwnd;
//	_message = message;
//	_wParam = wParam;
//	_lParam = lParam;
//	return WndProc(hwnd, message, wParam, lParam);
//}
//
//class temp : public WINDOW {
//	int a;
//	LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
//};
//
//void main() {
//	temp a;
//	a.
//}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	HWND hwnd;
	MSG msg;
	WINDOW_PROP W(CS_VREDRAW | CS_HREDRAW, hInstance, TEXT("TEST"),WndProc);
	hwnd = CreateWindow(TEXT("TEST"), TEXT("PIXELS"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static int  cxClient, cyClient;
	HDC         hdc;
	int         i;
	PAINTSTRUCT ps;
	POINT       apt[NUM];

	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		MoveToEx(hdc, 0, cyClient / 2, NULL);
		LineTo(hdc, cxClient, cyClient / 2);

		for (i = 0; i < NUM; i++)
		{
			apt[i].x = i * cxClient / NUM;
			apt[i].y = (int)(cyClient / 2 * (1 - log(sin(i / NUM))));
		}

		Polyline(hdc, apt, NUM);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

