#pragma once
#include "IMark.h"
/*飞镖类*/
class CShooter0Mark:public IMark{
public:
	CShooter0Mark(float x,float y);
	virtual ~CShooter0Mark();
	//画自己
	virtual void Draw(Gdiplus::Graphics &gh);
	//状态是否在改变中
	virtual bool IsChanging() const ;

private:
	std::vector<Image *>m_img;//图片
	size_t m_index{ 0 };//第几幅图片,随机生成
	float m_dir;//旋转的角度
};

