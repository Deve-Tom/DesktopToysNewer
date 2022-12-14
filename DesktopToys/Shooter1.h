#pragma once
#include "Shooter.h"
#include "Shooter1Mark.h"
#include "MusicPlay.h"
class CShooter1 :public CShooter{
public:
	CShooter1(int height);
	virtual ~CShooter1();

	//根据自己当前的属性画自己
	virtual void Draw(Gdiplus::Graphics &gh);
	/// ////////////////////////////////////////////////////////////////////////
	/// 处理鼠标消息 : 需要在子类中处理
	/// 如果不处理，则返回false,父类可以具此判断是否继续进行处理
	//鼠标左键按下
	virtual bool OnLButtonDown(UINT nFlags, CPoint point);

	//鼠标左键抬起
	virtual bool OnLButtonUp(UINT nFlags, CPoint point);

	//鼠标左键双击
	virtual bool OnLButtonDblClk(UINT nFlags, CPoint point){
		return false;//代表本类不处理该消息
	}

	//鼠标右键按下
	virtual bool OnRButtonDown(UINT nFlags, CPoint point);
	//鼠标右键抬起
	virtual bool OnRButtonUp(UINT nFlags, CPoint point){
		return false;//代表本类不处理该消息
	}

	//鼠标右键双击
	virtual bool OnRButtonDblClk(UINT nFlags, CPoint point){
		return false;//代表本类不处理该消息
	}

	//鼠标移动
	virtual bool OnMouseMove(UINT nFlags, CPoint point);
private:
	int m_nHeight{ 1024 };//梯子高度【0:梯子; 1:右,2:右回头; 3:左,4左回头;5:粉刷】
	int m_status{ 1 };
	//前一次的状态
	int m_statusLast{ 1 };

	//当前鼠标所在的位置
	PointF m_mousePos{ 0.0f, 0.0f };

	//上一步绘画之前鼠标所在的位置
	PointF m_mousePosLast{ 0.0f, 0.0f };

	//鼠标上下移动，小人也跟着移动:
	//这里记录上次换腿时的位置,和需要换腿的纵向距离
	PointF m_lastChangePos{ 0.0f, 0.0f };

	//变化的距离(纵向变化超过距离，换腿,即显示另一张图片)
	const float m_distanceChange{ 23.0f };

	//记录当前的颜色[0, 6)
	int m_iColorIndex{ 0 };

	//梯子的图片
	Image *m_img0;
	Image *m_img1;
	Image *m_img2;
	Image *m_img3;
	Image *m_img4;
	//绘画
	Image *m_img5;
};

