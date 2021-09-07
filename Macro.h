#pragma once
template <typename T>
inline void SafeDelete(T& obj)
{
	if (obj)
	{
		delete obj;
		obj = nullptr;
	}
}

template <typename T>
inline void SafeFree(T& obj)
{
	if (obj)
	{
		free(obj);
		obj = nullptr;
	}
}

inline POINT PointPlus(const POINT pointA, const POINT pointB)
{
	return{ pointA.x + pointB.x, pointA.y + pointB.y };
}

inline POINT PointMinus(const POINT pointA, const POINT pointB)
{
	POINT pointC;
	pointC.x = pointA.x - pointB.x;
	pointC.y = pointA.y - pointB.y;
	return pointC;
}

inline RECT RectPointPlus(RECT rect, POINT point)
{
	RECT rectResult =
	{
		point.x + rect.left,
		point.y + rect.top,
		point.x + rect.right,
		point.y + rect.bottom
	};
	return rectResult;
}

inline int Pow(int under, int upper)
{
	int p = 1;
	while (upper > 1)
	{
		p = p * under;
		upper--;
	}
	return p;
}

inline RECT SizeDown(RECT rc, int len)
{
	len = min(rc.right / 2, len);
	rc = { rc.left + len, rc.top + len, rc.right - len, rc.bottom - len };
	return rc;
}

inline void DrawLineBox(HDC mainDC, RECT rc,
	COLORREF main_RGB, COLORREF Line_RGB, int LineLen, bool Type)
{
	SetDCBrushColor(mainDC, main_RGB);
	FillRect(mainDC, &rc, (HBRUSH)GetStockObject(DC_BRUSH));

	rc = SizeDown(rc, LineLen);
	SetDCBrushColor(mainDC, Line_RGB);

	FrameRect(mainDC, &rc, (HBRUSH)GetStockObject(DC_BRUSH));

	if (Type == true)
	{
		rc = SizeDown(rc, 2);
		FillRect(mainDC, &rc, (HBRUSH)GetStockObject(DC_BRUSH));
	}
}
extern HWND gHWnd;
#define MESSAGE_BOX(ErrorName)				\
MessageBox(gHWnd, ErrorName, nullptr, MB_OK);		


#define CONSOLE_LOG(text) wprintf(L"function:%S %S\n", __FUNCTION__, text)
#define CONSOLE_ERROR_LOG(text) wprintf(L"[ERROR] function:%S %S\n", __FUNCTION__, text)