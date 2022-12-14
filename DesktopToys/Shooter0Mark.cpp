#include "stdafx.h"
#include "Shooter0Mark.h"


CShooter0Mark::CShooter0Mark(float x, float y){
	//载入图片
	//161 * 139
	m_img.push_back(Image::FromFile(
		_T("images/Foton The Desktop Hero Left Fire Marks 0.png")));
	m_img.push_back(Image::FromFile(
		_T("images/Foton The Desktop Hero Left Fire Marks 1.png")));
	m_img.push_back(Image::FromFile(
		_T("images/Foton The Desktop Hero Left Fire Marks 2.png")));
	m_img.push_back(Image::FromFile(
		_T("images/Foton The Desktop Hero Left Fire Marks 3.png")));
	m_img.push_back(Image::FromFile(
		_T("images/Foton The Desktop Hero Left Fire Marks 4.png")));


	srand(GetTickCount());//生成[0,5)之间的随机整数
	m_index = rand() % 5;
	m_dir = Degree2Radian((rand() / 360));//生成[0,360)之间的随机整数

	//设置自己的大小
	RectF rc;
	rc.X = 0;//设置位置为屏幕左上角(0,0)
	rc.Y = 0;
	rc.Width = (float)m_img[0]->GetWidth();//设置宽度为图片本身的宽度
	rc.Height = (float)m_img[0]->GetHeight();//设置宽度为图片本身的宽度
	SetRect(rc);

	SetCenterPos(x, y);// 设置中心点
}


CShooter0Mark::~CShooter0Mark(){}

void CShooter0Mark::Draw(Gdiplus::Graphics & gh){
	gh.DrawImage(m_img[m_index], GetRect());//绘制代表自身的图片
}

bool CShooter0Mark::IsChanging() const{
	return false;//直接返回false,代表该标记没有变化
}
