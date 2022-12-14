
//DesktopToysDlg.h : 头文件

#pragma once
#include "Game.h"

//CDesktopToysDlg 对话框
class CDesktopToysDlg : public CDialogEx{
//构造
public:
	CDesktopToysDlg(CWnd* pParent = NULL);//标准构造函数

//对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DESKTOPTOYS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);//DDX/DDV 支持


//实现
protected:
	HICON m_hIcon;

	//生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	DECLARE_MESSAGE_MAP()
	Bitmap *bmp;//声明背景图片
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	std::shared_ptr<CGame> m_pGame; //所有游戏功能转发给CGame对象完成，此处为智能指针
};
