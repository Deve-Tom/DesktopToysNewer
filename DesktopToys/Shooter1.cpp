#include "stdafx.h"
#include "Shooter1.h"


CShooter1::CShooter1(int height):m_nHeight(height){
	//载入图片,梯子
	m_img0 = Image::FromFile(_T("images/Pablo The Painter 00.png"));
	m_img1 = Image::FromFile(_T("images/Pablo The Painter 01.png"));
	m_img2 = Image::FromFile(_T("images/Pablo The Painter 02.png"));
	m_img3 = Image::FromFile(_T("images/Pablo The Painter 03.png"));
	m_img4 = Image::FromFile(_T("images/Pablo The Painter 04.png"));
	m_img5 = Image::FromFile(_T("images/Pablo The Painter 05.png"));
}


CShooter1::~CShooter1(){}

void CShooter1::Draw(Gdiplus::Graphics & gh){
	//先画梯子,是拼接成的
	//画图片
	auto drawImg = [&](Image * img) {
		RectF rc;
		rc.X = m_mousePos.X;
		rc.Y = m_mousePos.Y;
		rc.Width = (float)img->GetHeight();
		rc.Height = (float)img->GetWidth();
		rc.Offset(-(rc.Width / 3.0f - 10.0f), 0);
		gh.DrawImage(img, rc);
	};

	//重复画出相同的图片，拼接成一个梯子
	{
		//获得图片大小
		float h = (float)m_img0->GetHeight();
		float w = (float)m_img0->GetWidth();

		RectF rc;
		rc.Width = w;
		rc.Height = h;
		rc.X = m_mousePos.X;
		//循环绘制，X位置不变，y位置一直增加，直到屏幕高为止
		for (int y = 0; y < m_nHeight; ++y) {
			rc.Y = y * h;
			gh.DrawImage(m_img0, rc);
		}
	}

	//根据当前状态，绘制不同的图片
	switch (m_status) {
	case 0: {
		break;
	}
	case 1: {
		drawImg(m_img1);
		break;
	}
	case 2: {
		drawImg(m_img2);
		break;
	}
	case 3: {
		drawImg(m_img3);
		break;
	}
	case 4: {
		drawImg(m_img4);
		break;
	}
	case 5: {
		drawImg(m_img5);
		break;
	}
	default:
		break;
	}
}

bool CShooter1::OnLButtonDown(UINT nFlags, CPoint point){
	//粉刷状态
	m_status = 5;
	MusicPlay::playMusic(MusicPlay::status::painterShock);
	return true;
}

bool CShooter1::OnLButtonUp(UINT nFlags, CPoint point){
	//恢复前一种状态
	m_status = 1;
	return true;
}

bool CShooter1::OnRButtonDown(UINT nFlags, CPoint point){
	if (1 + m_iColorIndex >= 6) {
		m_iColorIndex = 0;
	}
	else
	{
		m_iColorIndex++;
	}
	return false;
}

bool CShooter1::OnMouseMove(UINT nFlags, CPoint point){
	//记录当前的位置
	m_mousePos.X = (float)point.x;
	m_mousePos.Y = (float)point.y;

	//切换到粉刷状态
	if (m_status == 5) {
		m_status = 5;
		//判断是否需要增加一个mark
		RectF rc;
		rc.X = m_mousePosLast.X;
		rc.Y = m_mousePosLast.Y;
		rc.Width = 1;
		rc.Height = 1;
		if (!rc.Contains(m_mousePos)) {
			//记录位置
			m_mousePosLast = m_mousePos;
			//在背景图上增加一个标记
			g_game->Append(std::make_shared<CShooter1Mark>(m_mousePos.X, m_mousePos.Y, m_iColorIndex));
		}
		return true;
	}

	/* 不是粉刷状态 绘制人物的移动动画*/
	//判断是否需要换腿
	//向下移动
	if ((point.y > m_lastChangePos.Y) &&
		(m_distanceChange <= abs(point.y - m_lastChangePos.Y))) {

		// 0:梯子; 1:右,2:右回头; 3:左,4左回头;5:粉刷
		switch (m_status) {
		case 1: {
			m_status = 3;
			break;
		}
		case 2: {
			m_status = 3;
			break;
		}
		case 3: {
			m_status = 1;
			break;
		}
		case 4: {
			m_status = 1;
			break;
		}
		default:
			break;
		}
		//记录最后一次的位置
		m_lastChangePos = m_mousePos;
	}
	//向上移动
	else if ((point.y < m_lastChangePos.Y) &&
		(m_distanceChange <= abs(point.y - m_lastChangePos.Y))) {
		//0:梯子; 1:右,2:右回头; 3:左,4左回头;5:粉刷
		switch (m_status) {
		case 1: {
			m_status = 3;
			break;
		}
		case 2: {
			m_status = 3;
			break;
		}
		case 3: {
			m_status = 1;
			break;
		}
		case 4: {
			m_status = 1;
			break;
		}
		default:
			break;
		}

		//记录最后一次的位置
		m_lastChangePos = m_mousePos;
	}
	else {
		//移动距离过小，不变换状态
	}
	return true;
}

