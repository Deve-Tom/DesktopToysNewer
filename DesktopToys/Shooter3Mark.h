#pragma once
#include "IMark.h"
class CShooter3Mark :public IMark{
public:
	CShooter3Mark(float x, float y);
	virtual ~CShooter3Mark();
	//根据自己当前的属性画自己
	virtual void Draw(Gdiplus::Graphics &gh);
	//状态是否在改变中
	virtual bool IsChanging() const;
private:
	//固定图片
	Image *m_img;
	//图片的角度
	float m_degree;
	//动态下落的东西
	typedef struct {
		Image *m_img2;
		//位置
		PointF m_pos;
		//速度(包含方向)
		PointF m_speed{ 10.0f, 15.0f };
		//当前角度(用于自射旋转)
		float m_dir{ 0.0f };
		//是否显示
		bool m_bShow{ true };
	} SDynamic;
	std::vector<SDynamic> m_vD;
};

