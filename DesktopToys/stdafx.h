
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持
#include "ScopeGuard.h"
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <string>
#include <assert.h>
#include "ScreenTools.h"
#include "GameTimer.h"

using namespace std;
#include <gdiplus.h>  //引入GDIPlus库
#include <gdipluseffects.h>
#pragma comment(lib,"Gdiplus.lib") //链接库
using namespace Gdiplus;

#define BACK_GROUND_LAYER RGB(0x00,0x00,0x00)
#define PI(n) (3.1415926f * n) 						// 定义一个宏,代表圆周率的一个近值
#define Radian2Degree(r) ((180.0f * (r)) / PI(1.0f)) 	// 弧度->角度
#define Degree2Radian(a) ((a) * PI(1.0f) / 180.0f) 		// 角度->弧度

#include "Game.h"
extern CGame* g_game;									// 声明全局的CGame类变量

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

