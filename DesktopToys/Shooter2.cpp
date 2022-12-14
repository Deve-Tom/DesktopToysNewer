#include "stdafx.h"
#include "Shooter2.h"


CShooter2::CShooter2(){
	//载入图片
	m_img0 = Image::FromFile(_T("images/The Toolbox01.png"));
	m_img1 = Image::FromFile(_T("images/The Toolbox02.png"));
	m_img2 = Image::FromFile(_T("images/The Toolbox03.png"));
}


CShooter2::~CShooter2(){}

static void DrawImageRotate(PointF mousePt, Graphics &gh, Image *img, float degree)
{
	//旋转绘图平面
	PointF center = mousePt;
	center.X += img->GetWidth() / 2.0f;
	center.Y += img->GetHeight() / 2.0f;

	//1.平移变换 : 移动坐标点到 坦克中心
	gh.TranslateTransform(center.X, center.Y);
	//2.旋转变换 : 使作标系，跟坐标旋转"degree"度
	gh.RotateTransform(degree);
	//3.恢复原点
	gh.TranslateTransform(-center.X, -center.Y);

	//方法退出时恢复对坐标系和平移的转换
	ON_SCOPE_EXIT([&]() {
		//重置坐标变换 : 精度是否够呢？
		//1.移动到中心点
		gh.TranslateTransform(center.X, center.Y);
		//2.逆向转
		gh.RotateTransform(-degree);
		//3.再移动回去
		gh.TranslateTransform(-center.X, -center.Y);
		//ScaleTransform : 缩放
	});


	//画出图像
	{
		RectF rc;
		rc.X = mousePt.X;
		rc.Y = mousePt.Y;
		rc.Width = (float)img->GetWidth();
		rc.Height = (float)img->GetHeight();
		gh.DrawImage(img, rc);
	}
}
void CShooter2::Draw(Gdiplus::Graphics & gh)
{
	switch (m_status) {
		//锤子
	case EStatus::EStatusHammer: {
		switch (m_eStatusHammer) {
			//鼠标左键第一次点击 :  发射子弹,同时锤子图片变化
		case EStatusHammer::EStatusHammerDownFirst: {
			//发射一个子弹
			g_game->Append(std::make_shared<CShooter2Mark>(
				m_mousePos.X, m_mousePos.Y));
			m_eStatusHammer = EStatusHammer::EStatusHammerDown;
			/*break; 注意这里没有break;会接下来执行下面一个case部分*/
		}
	    //鼠标左键点击
		case EStatusHammer::EStatusHammerDown: {
			auto img = m_img1;
			RectF rc;
			rc.X = m_mousePos.X;
			rc.Y = m_mousePos.Y;
			rc.Width = (float)img->GetWidth();
			rc.Height = (float)img->GetHeight();
			gh.DrawImage(img, rc);
			break;
		}
		//鼠标键左键抬起
		case EStatusHammer::EStatusHammerUp: {
			auto img = m_img2;
			RectF rc;
			rc.X = m_mousePos.X;
			rc.Y = m_mousePos.Y;
			rc.Width = (float)img->GetWidth();
			rc.Height = (float)img->GetHeight();
			gh.DrawImage(img, rc);
			break;
		}
		default: {
			//不会走到这里
			assert(false);
			break;
		}
		}
		break;
	}
	default: {
		break;
	}
	}
}

bool CShooter2::OnLButtonDown(UINT nFlags, CPoint point){
	switch (m_status) {
	case EStatus::EStatusHammer: {
		//锤子砸下
		MusicPlay::playMusic(MusicPlay::status::hammerShock);
		m_eStatusHammer = EStatusHammer::EStatusHammerDownFirst;
		break;
	}
	case EStatus::EStatusSaw: {
		//电锯开始割东西啦
		m_eStatusSaw = EStatusSaw::EStatusSawStart;
		//当前位置
		m_sawPos = m_mousePos;
		break;
	}
	default: {
		break;
	}
	}

	return false;
}

bool CShooter2::OnLButtonUp(UINT nFlags, CPoint point){
	switch (m_status) {
	case EStatus::EStatusHammer: {
		//锤子抬起
		m_eStatusHammer = EStatusHammer::EStatusHammerUp;
		break;
	}
	case EStatus::EStatusSaw: {
		//电锯停止
		m_eStatusSaw = EStatusSaw::EStatusSawStop;
		break;
	}
	default: {
		break;
	}
	}

	return false;
}

bool CShooter2::OnRButtonDown(UINT nFlags, CPoint point){
	m_status = EStatus::EStatusHammer;
	return true;
}

//计算两点间距离
float distance(PointF pt1, PointF pt2){
	return sqrt(pow(pt1.X - pt2.X, 2) + pow(pt1.Y - pt2.Y, 2));
}

//鼠标移动
bool CShooter2::OnMouseMove(UINT nFlags, CPoint point){
	//记录鼠标位置
	m_mousePos.X = (float)point.x;
	m_mousePos.Y = (float)point.y;

	//根据不同的情况进行处理
	switch (m_status) {
	case EStatus::EStatusHammer: {
		//锤子，维持原状态
		break;
	}
	case EStatus::EStatusSaw: {
		//如果没有锯东西，变换角度
		if (m_eStatusSaw == EStatusSaw::EStatusSawStop) {
			//记录锯子的位置
			m_sawPos = m_mousePos;
			//变换角度
			if (distance(m_mousePosLast, m_mousePos) > 10) {
				//计算角度
				float theta = (atan2(m_mousePos.Y - m_mousePosLast.Y,
					m_mousePos.X - m_mousePosLast.X));
				if (theta < 0.0f) {
					theta = PI(2.0f) + theta;
				}
				//角度:单位(度)
				m_sawDegree = Radian2Degree(theta);
				//记住本次位置
				m_mousePosLast = m_mousePos;
			}
		}
		break;
	}
	default: {
		break;
	}
	}

	return true;
}