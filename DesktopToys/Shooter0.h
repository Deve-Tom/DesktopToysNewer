#pragma once
#include "Shooter.h"
#include "Shooter0Mark.h"
#include "MusicPlay.h"
/*忍者类*/
class CShooter0 :public CShooter{
public:
	CShooter0();
	virtual ~CShooter0();
	// 根据自己当前的属性画自己
	virtual void Draw(Gdiplus::Graphics &gh);
	/// /////////////////////////////////////////////////////////
	/// 处理鼠标消息:需要在子类中处理
	/// 如果不处理，则返回false,父类可以具此判断是否继续进行处理
	//鼠标左键按下
	virtual bool OnLButtonDown(UINT nFlags, CPoint point);

	//鼠标左键抬起
	virtual bool OnLButtonUp(UINT nFlags, CPoint point){
		return false; //代表本类不处理该消息
	}

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
	virtual bool OnMouseMove(UINT nFlags, CPoint point){
		return false;//代表本类不处理该消息
	}
private:
	std::vector<Image *> m_vImage;
	//当前处于的阶段
	typedef enum {
		EStatus0 = 0,

		EStatusMove0,//移动向右
		EStatusMove1,//移动向右上
		EStatusMove2,//移动向上
		EStatusMove3,//移动向左上
		EStatusMove4,//移动向左
		EStatusMove5,//移动向左下
		EStatusMove6,//移动向下
		EStatusMove7,//移动向右下

		EStatusFireLeft,//开火向左
		EStatusFireRight,//开火向右
	} EStatus;
	EStatus m_eStatus{ EStatus0 };

	//当前显示的图片
	size_t m_index{ 0 };

	//无动作时，上下晃动
	CGameTimeval m_timer0{ 500 };

	//记录当前是向上，还是向下
	bool m_bUp{ false };


	/* 向某方向上移动
	开始移动
	到达后恢复静止状态
	*/
	void DrawMove(Gdiplus::Graphics &gh);

	//鼠标右键点击的位置
	PointF m_moveTo;

	//移动的方向
	float m_moveDir;


	/* 开火动画处理 : 开火共有 4 帧动画
	// 0 原地转身
	// 1 聚集能量
	// 2 聚集能量
	// 3 射击开始
	// 4 射击中
	// 5 射击完成
	*/

	//两帧图片之间的时间间隔
	CGameTimeval m_timerFire{ 100 };

	//当前显示第几幅图片
	size_t m_index_fire{ 0 };

	//绘制开火动画
	void DrawFire(Gdiplus::Graphics &gh);

	//鼠标右键点击的位置
	PointF m_fireTo;

};

