#include "stdafx.h"
#include "ScreenTools.h"


CScreenTools::CScreenTools(){}

CScreenTools::~CScreenTools(){}

int CScreenTools::GetBits(){
	//显示当前分辨率下每个像素所占字节数
	int iBits;
	HDC hDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);//为屏幕创建设备描述
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);//获得字节数
	DeleteDC(hDC);
	return iBits;
	
}

int CScreenTools::GetBitCount(int iBits){
	int wBitCount;
	if (iBits <= 1) {
		wBitCount = 1;
	}
	else if (iBits <= 4) {
		wBitCount = 4;
	}
	else if (iBits <= 8) {
		wBitCount = 8;
	}
	else if (iBits <= 24) {
		wBitCount = 24;
	}
	else {
		wBitCount = 32;
	}
	return wBitCount;
}

BOOL CScreenTools::WriteBmpDataToFile(PCTSTR szFileName, PBITMAPINFOHEADER pBitmapInfoHeader, DWORD dwPaletteSize, DWORD dwBmBitsSize){
	//写入的字节数
	DWORD dwWrite;
	//位图文件头结构,创建一个文件句柄
	HANDLE hFile = CreateFile(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return FALSE;
	}
	BITMAPFILEHEADER bitmapFileHeader;
	//设置位图文件头，即bmp文件头的设置
	bitmapFileHeader.bfType = 0x4D42;//0x4D42即"BM"
	bitmapFileHeader.bfSize = sizeof(BITMAPFILEHEADER) +
		sizeof(BITMAPINFOHEADER) +
		dwPaletteSize + dwBmBitsSize;
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	bitmapFileHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) +
		(DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

	//写入位图文件头
	WriteFile(hFile, (LPSTR)&bitmapFileHeader, sizeof(BITMAPFILEHEADER),
		&dwWrite, NULL);
	//写入位图文件其余内容
	WriteFile(hFile, (LPSTR)pBitmapInfoHeader, sizeof(BITMAPINFOHEADER) +
		dwPaletteSize + dwBmBitsSize,
		&dwWrite, NULL);
	//关闭文件句柄
	CloseHandle(hFile);
	return TRUE;
}

int CScreenTools::SaveBitmapToFile(HBITMAP hBitmap, LPCTSTR lpFileName){
	/*
	bitmap 文件结构如下:
	BITMAPFILEHEADER
	BITMAPINFOHEADER
	RGBQUAD array
	Color-index array
	*/
	//返回值
	BOOL bRet = FALSE;
	//位图中每个像素所占字节数
	WORD wBitCount;
	//定义调色板大小， 位图中像素字节大小 ， 位图文件大小 ， 写入文件字节数
	DWORD dwPaletteSize = 0;
	DWORD dwBmBitsSize;
	BITMAP Bitmap;//位图属性结构
	BITMAPINFOHEADER bitmapInfoHeader;//位图信息头结构
	LPBITMAPINFOHEADER pBitmapInfoHeader;//指向位图信息头结构
	wBitCount = GetBitCount(GetBits());//调用GetBitCount函数确定多几位(1,4,8,24,32)位图

	if (wBitCount <= 8) { 							//计算调色板大小
		dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD);
	}
	//设置位图信息头结构
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biWidth = Bitmap.bmWidth;
	bitmapInfoHeader.biHeight = Bitmap.bmHeight;
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = wBitCount;
	bitmapInfoHeader.biCompression = BI_RGB;
	bitmapInfoHeader.biSizeImage = 0;
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.biYPelsPerMeter = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;

	// 像素数据的大小
	// 每一行的大小(必须是4的整数倍)
	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4
		* Bitmap.bmHeight;
	HANDLE hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize +
		sizeof(BITMAPINFOHEADER));
	pBitmapInfoHeader = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*pBitmapInfoHeader = bitmapInfoHeader;

	//获取调色板下新的像素值
	{
		HDC hDC;//设备描述表
		HPALETTE hOldPal = NULL;//获取旧的调色板
		hDC = ::GetDC(NULL);//获取屏幕DC
		HANDLE hPal = GetStockObject(DEFAULT_PALETTE);//获取默认调色板
		if (hPal) {
			hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
			RealizePalette(hDC);
		}
		//获取该调色板下新的像素值
		GetDIBits(hDC, hBitmap
			, 0
			, (UINT)Bitmap.bmHeight
			, (LPSTR)pBitmapInfoHeader + sizeof(BITMAPINFOHEADER) +
			dwPaletteSize
			, (BITMAPINFO *)pBitmapInfoHeader
			, DIB_RGB_COLORS);//位图属性结构
		if (hOldPal) {//恢复调色板
			SelectPalette(hDC, hOldPal, TRUE);
			RealizePalette(hDC);
		}
		::ReleaseDC(NULL, hDC);//释放屏幕DC
	}
	//创建位图文件,并写入
	{
		if (!WriteBmpDataToFile(lpFileName, pBitmapInfoHeader, dwPaletteSize,
			dwBmBitsSize)) {
			goto __Cleanup;
		}
	}
	bRet = TRUE;
__Cleanup://清除
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	return bRet;
}

HBITMAP CScreenTools::CopyScreenToBitmap(LPRECT lpRect){
	HDC hScrDC, hMemDC;
	HBITMAP hBitmap, hOldBitmap;//屏幕和内存设备描述表
	int nX, nY, nX2, nY2;//位图句柄
	int nWidth, nHeight;//选定区域坐标
	int xScrn, yScrn;//位图宽度和高度
	//确保选定区域不为空矩形
	if (IsRectEmpty(lpRect)) {
		return NULL;
	}
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);//为屏幕创建设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);//为屏幕设备描述表创建兼容的内存设备描述表
	//获得选定区域坐标
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	//获得屏幕分辨率
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//确保选定区域是可见的
	if (nX < 0) {
		nX = 0;
	}
	if (nY < 0) {
		nY = 0;
	}
	if (nX2 > xScrn) {
		nX2 = xScrn;
	}
	if (nY2 > yScrn) {
		nY2 = yScrn;
	}
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	//创建一个与屏幕设备描述表兼容的位图
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
	//把新位图选到内存设备描述表中
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	//把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, nX, nY, SRCCOPY);
	//得到屏幕位图的句柄
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	//清除
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	//返回位图句柄
	return hBitmap;
}

HBITMAP CScreenTools::PrintScreen(){
	CRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = GetSystemMetrics(SM_CXSCREEN);
	rect.bottom = GetSystemMetrics(SM_CYSCREEN);
	return CopyScreenToBitmap(rect);
}

HBITMAP CScreenTools::PrintWindow(HWND hwnd){
	RECT rrrr;
	LPRECT lpRect = &rrrr;
	::GetWindowRect(hwnd, &rrrr);
	HDC hScrDC, hMemDC;//屏幕和内存设备描述表
	HBITMAP hBitmap, hOldBitmap;//位图句柄
	hScrDC = ::GetWindowDC(hwnd);//为屏幕创建设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);//为屏幕设备描述表创建兼容的内存设备描述表
	int nWidth = lpRect->right - lpRect->left;//位图宽度和高度
	int nHeight = lpRect->bottom - lpRect->top;;
	//创建一个与屏幕设备描述表兼容的位图
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
	//把新位图选到内存设备描述表中
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	//把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, 0, 0, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);//得到屏幕位图的句柄
	DeleteDC(hScrDC);//释放资源
	DeleteDC(hMemDC);
	return hBitmap;//返回位图句柄
}

void CScreenTools::DawMouse(POINT pnt){
	HWND DeskHwnd = ::GetDesktopWindow();//取得桌面句柄
	HDC DeskDC = ::GetWindowDC(DeskHwnd);//取得桌面设备场景
	int oldRop2 = SetROP2(DeskDC, R2_NOTXORPEN);
	HPEN newPen = ::CreatePen(0, 1, RGB(255, 0, 0));//建立新画笔,载入DeskDC
	HGDIOBJ oldPen = ::SelectObject(DeskDC, newPen);//选定画笔,并保存旧画笔
	::MoveToEx(DeskDC, pnt.x - 10, pnt.y, NULL);//在窗口四周田一个方框
	::LineTo(DeskDC, pnt.x + 10, pnt.y);//在窗口四周田一个方框
	::MoveToEx(DeskDC, pnt.x, pnt.y + 10, NULL);//在窗口四周田一个方框
	::LineTo(DeskDC, pnt.x, pnt.y - 10);//在窗口四周田一个方框
	::SetROP2(DeskDC, oldRop2);
	::SelectObject(DeskDC, oldPen);//恢复为旧画笔
	::DeleteObject(newPen);//释放资源,删除画笔
	::ReleaseDC(DeskHwnd, DeskDC);//释放资源,释放设备
	DeskDC = NULL;
}


