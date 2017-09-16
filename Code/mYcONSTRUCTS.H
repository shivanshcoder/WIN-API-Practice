#pragma once

#include<Windows.h>
/*for default values of CreateWindow*/
#define CreateWindowDEF(szAppName,window_name,hInstance) CreateWindow(szAppName, window_name, WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT,NULL, NULL, hInstance, NULL);

/*x and y coordinate to */
#define XYtoPOINT(x,y) POINT{x,y}
#define POINTtoXY(point) point.x,point.y
/*For combining two values int a Point type*//*
POINT point_combine(long x, long y) {
	POINT p;
	p.x = x;
	p.y = y;
	return p;
}*/

/*Directly returns the Converted POINT*/
POINT DPtoLP(HDC hdc, long cxClient, long  cyClient) {

	POINT p = POINT{ cxClient,cyClient };
	DPtoLP(hdc, &p, 1);
	return p;
}

void SetWindowOrgEx(HDC hdc, POINT P, LPPOINT PrevP) {
	SetWindowOrgEx(hdc, P.x, P.y, PrevP);
}
void SetViewportOrgEx(HDC hdc, POINT P, LPPOINT PrevP) {
	SetWindowOrgEx(hdc, P.x, P.y, PrevP);
}

