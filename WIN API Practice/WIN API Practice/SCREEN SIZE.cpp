#include<Windows.h>
#include<tchar.h>
#include<stdio.h>

int CDECL MessageBoxPrintf(TCHAR* szCaption, TCHAR* szFormat, int x, int y) {
	TCHAR szBuffer[1024];
	va_list pArglist;

	//	va_start(pArglist, szFormat);

	_vsntprintf(szBuffer, sizeof(szBuffer) / sizeof(TCHAR), szFormat, pArglist);

	//va_end(pArglist);

	return MessageBox(NULL, szBuffer, szCaption, 0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, PSTR szCmdline, int iCmdshow) {
	int cxScreen, cyScreen;

	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	cyScreen = GetSystemMetrics(SM_CYSCREEN);
	MessageBoxPrintf(TEXT("ScreenSize"), TEXT("The Screen is %i pixels wide and %i pixels high"), cxScreen, cyScreen);
	return 0;
}