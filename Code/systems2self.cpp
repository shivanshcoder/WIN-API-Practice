
#include"selfwindow.h"


void windows::paint(HDC hdc) {
	TCHAR message[] = TEXT("HELLO WOlrd");
	TextOut(hdc, 0, 0, message, lstrlen(message));
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdline, int iCmdShow) {
	return ca(iCmdShow);
}

