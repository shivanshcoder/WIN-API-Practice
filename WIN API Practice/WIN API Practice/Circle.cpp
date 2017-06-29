#include<Windows.h>
#include<algorithm>
#define PI 3.14/180 
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void circle(HDC& hdc, POINT centre, int radius);
inline void quarterinc(int &angle) { if (angle == 90)angle = 0; else angle++; }

void upc(POINT& val, int x, int y) {
	val.x = x;
	val.y = y;
}

void quarter(HDC& hdc, POINT CENTRE, int radius, static int z = 0);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE PrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("PENSBRUSHES");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	//HBRUSH hbrush = CreateHatchBrush(HS,RGB(255,0,255));

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpszMenuName = NULL;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_HAND);
	//wndclass.hbrBackground = (HBRUSH)(hbrush);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName, TEXT("Practice"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static POINT aptf[] = { 10,10 ,20,10 ,20,40 ,10,40 ,5,40 ,5,80 ,20,80, 20,40 ,50,50 };
	int psize = sizeof(aptf) / sizeof(aptf[0]);
	static int cxClient, cyClient;
	HDC hdc;
	HPEN hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	POINT p{ 700,700 };

	POINT temp1{ 100,100 };
	POINT temp2{ 200,300 };

	int i;
	PAINTSTRUCT ps;
	POINT apt[9];
	HBRUSH hbrush = CreateHatchBrush(HS_FDIAGONAL, RGB(255, 0, 255));
	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_MOUSEMOVE:
	//case WM_MOUSEFIRST:
		if (MK_LBUTTON ||MK_RBUTTON)
		{
					hdc = GetDC(hwnd);
			//	//	HPEN hpen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			//	//	HPEN hpen2 = CreatePen(PS_DASHDOT, 3, RGB(255, 255, 255));
			//		//SelectObject(hdc, GetStockObject(WHITE_PEN));
			//		//DrawBezier(hdc, apt);

			//		//MoveToEx(hdc, temp1.x, temp1.y, NULL);
			//		//LineTo(hdc, temp2.x, temp2.y);

			if (MK_LBUTTON)
			{
				//	SelectObject(hdc, hpen1);
				SetWindowOrgEx(hdc, -cxClient / 4, -cyClient / 4, NULL);

			}

			if (MK_RBUTTON)
			{
				//	SelectObject(hdc, hpen1);
				SetViewportOrgEx(hdc, cxClient / 4, cyClient / 4, NULL);
			}

			InvalidateRect(hwnd, NULL, FALSE);
			ReleaseDC(hwnd, hdc);
		}
	//		////DrawBezier(hdc, apt);
	//		//MoveToEx(hdc, temp1.x, temp1.y, NULL);
	//		//LineTo(hdc, temp2.x, temp2.y);
	//		//ReleaseDC(hwnd, hdc);
	//	}
	//	return 0;
	//case WM_MOUSELEAVE:
	//	temp2.x = LOWORD(lParam);
	//	temp2.y = HIWORD(lParam);
	//	hdc = GetDC(hwnd);
	//	SelectObject(hdc, hpen);
	//	MoveToEx(hdc, temp1.x, temp1.y,NULL);
	//	LineTo(hdc,temp2.x, temp2.y);
	//	ReleaseDC(hwnd, hdc);
	case WM_PAINT:
		POINT p1, p2;
		hdc = BeginPaint(hwnd, &ps);/*
		SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);
		SetWindowOrgEx(hdc, -cxClient / 4, -cyClient / 4, NULL);
*/
		GetViewportOrgEx(hdc, &p1);
		GetWindowOrgEx(hdc, &p2);
		TextOut(hdc, cxClient / 4, cyClient / 4, TEXT("HOLA"),5);
		SelectObject(hdc, hpen);
		MoveToEx(hdc, p1.x, p1.y, NULL);
		LineTo(hdc, p2.x,p2.y);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
/*no need to fil value of z*/
void quarter(HDC & hdc, POINT centre, int radius, static int z)
{
	POINT *apt = new POINT[radius];
	int x = 0;
	int y = radius;
	for (int i = 0; i < radius;i++, x++) {
		upc(apt[i], x+centre.x, centre.y-y);
		y = sqrt(radius*radius-x*x);
	}
	Polyline(hdc, apt, radius);
}

void anglequarter(POINT* apt,int radius, int anglecos) {
	int size = sizeof(apt) / sizeof(apt[0]);
	int z;
	for (int i = anglecos; i<90; i+=1) {
		apt[i].x = radius* cos(i*PI) +700;
		apt[i].y = radius* sin((0.5 - i)*PI) +700;
	}
}
 void circle(HDC& hdc, POINT centre, int radius) {
	int angles =  90;
	POINT *apt = new POINT[angles];
	anglequarter(apt, radius, 0);
	Polyline(hdc, apt, angles);
}
