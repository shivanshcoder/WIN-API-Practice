#include "C++_WINAPI_headers.h"


WINDOW_PROP::WINDOW_PROP(UINT styles, HINSTANCE hInstances, LPCWSTR lpszClassNames, WNDPROC lpfnWndProcs) {
	style = styles;
	hInstance = hInstances;
	lpszClassName = lpszClassNames;
	hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	hCursor = LoadCursor(hInstance, IDC_ARROW);
	hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	lpszMenuName = nullptr;
	cbClsExtra = 0;
	cbWndExtra = 0;
	lpfnWndProc = lpfnWndProcs;
	RegisterClass(this);
}


void Scroll::initialize(UINT _fMask, int _nMin, int _nMax, UINT _nPage){
	si.cbSize = sizeof(&si);
	si.fMask = _fMask;
	si.nMin = _nMin;
	si.nMax = _nMax;
	si.nPage = _nPage;
}

void Scroll::initialize_V(UINT _fMask, int _nMin, int _nMax, UINT _nPage){
	initialize(_fMask, _nMin, _nMax, _nPage);
	SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
}
void Scroll::initialize_H(UINT _fMask, int _nMin, int _nMax, UINT _nPage){
	initialize(_fMask, _nMin, _nMax, _nPage);
	SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

}

int Scroll::V_scroll(WPARAM wParam,int cyChar) {
	
	si.cbSize = sizeof(si);
	si.fMask = SIF_ALL;

	::GetScrollInfo(hwnd, SB_VERT, &si);
	iVertPos = si.nPos;

	switch (LOWORD(wParam)) {
	case SB_TOP:
		si.nPos = si.nMin;
		break;

	case SB_BOTTOM:
		si.nPos = si.nMax;
		break;

	case SB_LINEUP:
		si.nPos -= 1;
		break;

	case SB_LINEDOWN:
		si.nPos += 1;
		break;

	case SB_PAGEUP:
		si.nPos -= si.nPage;
		break;

	case SB_PAGEDOWN:
		si.nPos += si.nPage;
		break;

	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break;

	default:
		break;
	}

	si.fMask = SIF_POS;
	SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
	::GetScrollInfo(hwnd, SB_VERT, &si);


	if (si.nPos != iVertPos)
	{
		ScrollWindow(hwnd, 0, cyChar * (iVertPos - si.nPos),NULL, NULL);
		UpdateWindow(hwnd);
	}
	return 0;

}

int Scroll::H_scroll(WPARAM wParam, int cxChar) {
	

	si.cbSize = sizeof(si);
	si.fMask = SIF_ALL;

	// Save the position for comparison later on

	::GetScrollInfo(hwnd, SB_HORZ, &si);
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
	::GetScrollInfo(hwnd, SB_HORZ, &si);

	// If the position has changed, scroll the window 

	if (si.nPos != iHorzPos)
	{
		ScrollWindow(hwnd, cxChar * (iHorzPos - si.nPos), 0,
			NULL, NULL);
	}
	return 0;

}

void Scroll::GetScrollInfo(int type){
	::GetScrollInfo(hwnd, type, &si);
}
