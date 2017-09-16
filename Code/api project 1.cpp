#include<Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("First Project");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("Project"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	PAINTSTRUCT ps;
	SCROLLINFO  si;


	switch (message) {
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		// Set vertical scroll bar range and page size

		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = NUMLINES - 1;
		si.nPage = cyClient / cyChar;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

		// Set horizontal scroll bar range and page size

		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = 2 + iMaxWidth / cxChar;
		si.nPage = cxClient / cxChar;
		SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
		return 0;
	case WM_VSCROLL:
		
	//	// Get all the vertial scroll bar information

	//	si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;
	//	GetScrollInfo(hwnd, SB_VERT, &si);

	//	// Save the position for comparison later on

	//	iVertPos = si.nPos;

	//	switch (LOWORD(wParam))
	//	{
	//	case SB_TOP:
	//		si.nPos = si.nMin;
	//		break;

	//	case SB_BOTTOM:
	//		si.nPos = si.nMax;
	//		break;

	//	case SB_LINEUP:
	//		si.nPos -= 1;
	//		break;

	//	case SB_LINEDOWN:
	//		si.nPos += 1;
	//		break;

	//	case SB_PAGEUP:
	//		si.nPos -= si.nPage;
	//		break;

	//	case SB_PAGEDOWN:
	//		si.nPos += si.nPage;
	//		break;

	//	case SB_THUMBTRACK:
	//		si.nPos = si.nTrackPos;
	//		break;

	//	default:
	//		break;
	//	}
	//	// Set the position and then retrieve it.  Due to adjustments
	//	//   by Windows it may not be the same as the value set.

	//	si.fMask = SIF_POS;
	//	SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
	//	GetScrollInfo(hwnd, SB_VERT, &si);

	//	// If the position has changed, scroll the window and update it

	//	if (si.nPos != iVertPos)
	//	{
	//		ScrollWindow(hwnd, 0, cyChar * (iVertPos - si.nPos),
	//			NULL, NULL);
	//		UpdateWindow(hwnd);
	//	}
		return 0;

	case WM_HSCROLL:
		// Get all the vertial scroll bar information

		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;

		// Save the position for comparison later on

		GetScrollInfo(hwnd, SB_HORZ, &si);
		iHorzPos = si.nPos;

		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
			si.nPos -= 1;
			break;

		case SB_LINERIGHT:
			si.nPos += 1;
			break;

		case SB_PAGELEFT:
			si.nPos -= si.nPage;
			break;

		case SB_PAGERIGHT:
			si.nPos += si.nPage;
			break;

		case SB_THUMBPOSITION:
			si.nPos = si.nTrackPos;
			break;

		default:
			break;
		}
		// Set the position and then retrieve it.  Due to adjustments
		//   by Windows it may not be the same as the value set.

		si.fMask = SIF_POS;
		SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
		GetScrollInfo(hwnd, SB_HORZ, &si);

		// If the position has changed, scroll the window 

		if (si.nPos != iHorzPos)
		{
			ScrollWindow(hwnd, cxChar * (iHorzPos - si.nPos), 0,
				NULL, NULL);
		}
		return 0;


	}
}