#pragma once
#include<Windows.h>

class WINDOW_PROP : private WNDCLASS {
public:
	WINDOW_PROP(UINT, HINSTANCE, LPCWSTR, WNDPROC);


	void hicon(HICON hICON) { hIcon = hICON; }
	void hbrush(HBRUSH hbrBACKGROUND) { hbrBackground = hbrBACKGROUND; }
	void hcursor(HCURSOR hCURSOR) { hCursor = hCURSOR; }
};

class Scroll {
public:
	Scroll(HWND _hwnd)
		:iVertPos(0), iHorzPos(0) {
		hwnd = _hwnd;
	}

	void initialize_V(UINT _fMask, int _nMin, int _nMax, UINT _nPage);
	void initialize_H(UINT _fMask, int _nMin, int _nMax, UINT _nPage);

	int V_scroll(WPARAM wParam,int cyChar); //skipped to add fmask as parameter if necessary only than add
	int H_scroll(WPARAM wParam, int cxChar); //skipped to add fmask as parameter if necessary only than add

	int nPos_at() { return si.nPos; }
	void set_mask(UINT _fMask) { si.fMask = _fMask; }

	void GetScrollInfo(int type);
	int iVertPos;
	int iHorzPos;
private:
	HWND hwnd;
	SCROLLINFO si;
	void initialize(UINT _fMask, int _nMin, int _nMax, UINT _nPage);
};



