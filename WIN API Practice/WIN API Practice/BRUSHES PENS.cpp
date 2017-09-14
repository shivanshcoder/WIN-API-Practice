#include<Windows.h>
#include<vector>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
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
		WS_OVERLAPPEDWINDOW|WS_VSCROLL,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
/*for updating POINT VALS together */
void upc(POINT& val, int x, int y) {
	val.x = x;
	val.y = y;
}
void maze(HDC &hdc, int def,int cxcli) {
	def = 35*def  ;
	int size = (def - 2) / 2 * 4 + 1;
	POINT *apt = new POINT[size];
	int x = 10;
	int y = 10;
	int z=0;
	for (int i = size / 4; def>2; i--,def-=20,x+=10,y+=10) {
		upc(apt[z++], x, y); 
		x += def;
		upc(apt[z++], x, y);
		y += def;
		upc(apt[z++], x, y);
		x -= def;
		upc(apt[z++], x, y);
		y -= def;
		upc(apt[z++], x, y);
	}

	Polygon(hdc, apt, size);
	delete apt;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static POINT aptf[] = { 10,10 ,20,10 ,20,40 ,10,40 ,5,40 ,5,80 ,20,80, 20,40 ,50,50};
	int psize = sizeof(aptf) / sizeof(aptf[0]);
	static int cxClient, cyClient;
	HDC hdc;
	int i;
	PAINTSTRUCT ps;
	POINT apt[9];
	HBRUSH hbrush = CreateHatchBrush(HS_FDIAGONAL, RGB(255, 0,255));
	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_VSCROLL:

		hdc = GetDC(hwnd);
		SetWindowOrgEx(hdc, 10, 10, NULL);
		ReleaseDC(hwnd, hdc);
		UpdateWindow(hwnd);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, hbrush);
		 // SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		//for (i = 0; i < psize; i++)
		//{
		//	  apt[i].x = cxClient * aptf[i].x / 200 ;
		//	 apt[i].y = cyClient * aptf[i].y / 100 ;
		//	/*apt[i].x = aptf[i].x;
		//	apt[i].y = aptf[i].y;*/
		//}
	//	SetWindowOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);
		SetPolyFillMode(hdc, ALTERNATE);
		//Polygon(hdc, apt, psize);
		/*
		for (i = 0; i < 4; i++)
		{
			apt[i].x += cxClient / 2;
		}

		SetPolyFillMode(hdc, WINDING);
		Polygon(hdc, apt, 4);
*/

		maze(hdc, 20,cxClient);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}