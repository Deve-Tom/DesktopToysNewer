/*游戏总体类*/
#pragma once
#include "DMenu.h"
#include "Shooter.h"

class IMark; //前向声明
class CGame{
public:
	CGame(HWND hWnd,float x,float y,float w,float h);
	~CGame();
public:
	//游戏的一帧
	bool EnterFrame(DWORD dwTime);
	//处理鼠标消息
	//鼠标左键按下
	void OnLButtonDown(UINT nFlags, CPoint point);
	//鼠标左键抬起
	void OnLButtonUp(UINT nFlags, CPoint point);
	//鼠标左键双击
	void OnLButtonDblClk(UINT nFlags, CPoint point);
	//鼠标右键按下
	void OnRButtonDown(UINT nFlags, CPoint point);
	//鼠标右键抬起
	void OnRButtonUp(UINT nFlags, CPoint point);
	//鼠标右键双击
	void OnRButtonDblClk(UINT nFlags, CPoint point);
	//鼠标移动
	void OnMouseMove(UINT nFlags, CPoint point);

	//按下 ESC 键时的处理: 返回FALSE 不处理，则由父窗口处理
	BOOL OnESC();
	void SetStatusNormal(std::shared_ptr<CShooter> pTool, BOOL bCursor = FALSE);
	//增加一个 破坏物
	void Append(std::shared_ptr<IMark> pMark){
		m_vMarks.push_back(pMark);
	}

	//获得游戏窗口的宽度
	float GetWidth() const{
		return m_width;
	}

	//获得游戏窗口的高度
	float GetHeigth() const{
		return m_height;
	}

	//获得范围
	RectF GetRectF() const{
		return RectF(m_x, m_y, m_width, m_height);
	}
private:
	HWND m_hWnd;
	// 窗口的起始位置
	float m_x;
	float m_y;

	// 游戏窗口的宽高
	float m_width;
	float m_height;

	// 游戏只分为两个阶段: 菜单选择阶段，正式游戏阶段
	typedef enum EGameStatus { EGameStatusSelect, EGameStatusNormal } EGameStatus;
	EGameStatus  m_eStatus{ EGameStatusSelect };

private:
	//客户区大小
	CRect m_rcClient;

	//记录游戏每秒多少帧
	int m_fps{ 0 };
	//输出FPS文字用到的画刷
	SolidBrush m_brush{ Color(254, 0xFF, 0x00, 0x00) };
	//输出FPS文字字体
	Gdiplus::Font m_font{ L"宋体", 10.0 };
	//在左上角显示
	PointF origin{ 0.0f, 0.0f };
	//画出所有对象
	void Draw();

	//输出fps
	void DrawFps(Gdiplus::Graphics &gh);

	// 破坏窗口留下的东西
	std::vector<std::shared_ptr<IMark>> m_vMarks;

	// 背景图
	Gdiplus::Bitmap *m_imgBk;
	std::shared_ptr<CDMenu> m_menu;  //菜单
	std::shared_ptr<CShooter> m_pTool;//当前选择的工具
};

