#include<Windows.h>



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void start_spiral(HDC, int);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE PrevhInstance,
	PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("LINE");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static int cxClient, cyClient;
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message) {

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);
		start_spiral(hdc, 1920 * 1920);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

bool is_prime(unsigned long long num) {
	if (num < 2 || num % 2 == 0)return false;
	else if (num == 2)return true;
	for (unsigned long long n = 3; n <= num / 2; n += 2) if (!(num%n))return false;
	return true;
}


void start_spiral(HDC hdc, int max_num) {
	POINT p{ 0,0 };
	long number = 1;
	int incre = 1;   //increment or decrement value
	int num_incre = 1;   //number of times values have to be changed
	while (number < max_num) {  //Maximum number based on number of pixels

		for (int i = 0; i < num_incre; ++i, number++) {
			if (is_prime(number)) {  //checks if the current number is prime
				SetPixel(hdc, p.x, p.y, RGB(0, 0, 255));  //sets the pixel color blue
			}
            p.x += incre;  //increments or decrements value of point
		}
		for (int i = 0; i < num_incre; ++i, number++) {
			if (is_prime(number)) {
				SetPixel(hdc, p.x, p.y, RGB(0, 0, 255));
			}
			p.y += incre;
		}

		num_incre++; //number of increments are increased after every turn of spiral
		incre *= (-1);  //number of increments are increased after every 2 turn of spiral
	}
}
