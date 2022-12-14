#include "stdafx.h"
#include "DMenu.h"

CDMenu::CDMenu(HWND hWnd):m_hWnd(hWnd){
	//载入菜单子项,载入图片，创建智能指针
	m_box = make_shared<CMenuItem>(100.0f, 100.0f,
		_T("images/Menu Center01.png"), _T(""));
	m_cover = make_shared<CMenuItem>(100.0f, 100.0f,
		_T("images/Menu Center02.png"), _T(""));
	m_cover2 = make_shared<CMenuItem>(100.0f, 100.0f,
		_T("images/Menu Center02.png"), _T(""));
	m_item0 = make_shared<CMenuItem>(200.0f, 100.0f,
		_T("images/MenuItem00.png"), _T("I'm 钢铁侠"));
	m_item1 = make_shared<CMenuItem>(300.0f, 100.0f,
		_T("images/MenuItem01.png"), _T("你敢小看粉刷匝??"));
	m_item2 = make_shared<CMenuItem>(400.0f, 100.0f,
		_T("images/MenuItem02.png"), _T("其实我不是锤子"));
	m_item3 = make_shared<CMenuItem>(500.0f, 100.0f,
		_T("images/MenuItem03.png"), _T("同桌的橡皮"));

	{
		//获取屏幕大小并通过上下左右相减获得屏幕中心位置
		RECT rc;
		GetWindowRect(m_hWnd, &rc);
		PointF pt((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) / 2.0f);//设置菜单到中间位置
		//将中心位置进行保存
		SetCenterPos(pt);
	}

	InitAnimateInfo0();
}


CDMenu::~CDMenu(){}

void CDMenu::InitAnimateInfo0(){
   //获取屏幕中心点位置，并设置各项位置
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	//中心点
	PointF pt = GetCenterPos();
	//设置各项的中心点
	m_box->SetCenterPos(pt);
	//菜单的中心点在箱子中心
	m_item0->SetCenterPos(pt);
	m_item1->SetCenterPos(pt);
	m_item2->SetCenterPos(pt);
	m_item3->SetCenterPos(pt);

	//设置盖子的位置
	//盖子的中心点在箱子的上面
	{
		PointF pt2 = pt;
		pt2.Y -= 30;
		m_cover->SetCenterPos(pt2);	//m_cover为打开的盖子
	}

	//设置盖子的位置
	{
		PointF pt2 = pt;
		pt2.Y -= 30;
		m_cover2->SetCenterPos(pt2);// m_cover2为关闭的盖子
	}

	//初始化动画信息
	m_box->InitAnimateInfo3(pt.X, pt.Y);
	m_cover->InitAnimateInfo1(pt.X, pt.Y - 100, PI(0.5f));
	//初始化四个菜单子项的动画
	m_item0->InitAnimateInfo0(pt.X, pt.Y, 0.0f);
	m_item1->InitAnimateInfo0(pt.X, pt.Y, PI(0.5f));
	m_item2->InitAnimateInfo0(pt.X, pt.Y, PI(1.0f));
	m_item3->InitAnimateInfo0(pt.X, pt.Y, PI(1.5f));
	//初始化动画信息
	m_cover2->InitAnimateInfo1(pt.X, pt.Y - 100, PI(0.5f));
	m_cover2->InitAnimateInfoReverse();
}

void CDMenu::Draw(Gdiplus::Graphics & gh){
	switch (m_eStatus) {
	case EStatusOverCover1: {//当前状态为盖子打开过程
		PointF pt = GetCenterPos();
		if (m_cover->IsAnimateEnd()) {//如果动画完毕
			m_eStatus = EStatusItem0;//转化为第一个菜单项飞出过程动画
			break;
		}
		m_box->Draw(gh);//此时需要画盒子
		m_cover->Draw(gh);//此时需要画盖子(打开状态)
		break;
	}
	case EStatusItem0: {//菜单项一飞出过程
		if (m_item0->IsAnimateEnd()) {
			m_eStatus = EStatusItem1;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		break;
	}
	case EStatusItem1: {//菜单项二飞出过程
		if (m_item1->IsAnimateEnd()) {
			m_eStatus = EStatusItem2;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		break;
	}
	case EStatusItem2: {//菜单项三飞出过程
		if (m_item2->IsAnimateEnd()) {
			m_eStatus = EStatusItem3;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		break;
	}
	case EStatusItem3: {//菜单项四飞出过程
		if (m_item3->IsAnimateEnd()) {
			m_eStatus = EStatusOverCover2;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		m_item3->Draw(gh);
		break;
	}
	case EStatusOverCover2: {//盒子关闭过程
		if (m_cover2->IsAnimateEnd()) {
			m_eStatus = EStatusAll;
			break;
		}
		m_box->Draw(gh);//画盒子
		m_cover2->Draw(gh);//盖子
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		m_item3->Draw(gh);
		break;
	}
	case EStatusAll: {//到此,动画过程结束
		m_box->Draw(gh);
		m_cover2->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		m_item3->Draw(gh);
		break;
	}
	default:
		break;
	}
}

void CDMenu::EndAnimate(){//调用此函数结束所有的动画过程
	m_eStatus = EStatusAll;//设置状态为动画全部结束
	m_item0->EndAnimate();//结束菜单项一动画过程
	m_item1->EndAnimate();//结束菜单项二动画过程
	m_item2->EndAnimate();//结束菜单项三动画过程
	m_item3->EndAnimate();//结束菜单项四动画过程
	m_cover->EndAnimate();//结束盖子动画过程
	m_cover2->EndAnimate();//结束盖子动画过程
}

//鼠标左键按下
bool CDMenu::OnLButtonDown(UINT nFlags, CPoint point){
	//查看命中了哪个菜单
	if (m_item0->OnLButtonDown(nFlags, point)) {
		//结束动画
		EndAnimate();
		//进入游戏进入游戏阶段，并设置当前工具为CShooter0
		g_game->SetStatusNormal(make_shared<CShooter0>(), TRUE);
		return true;
	}
	if (m_item1->OnLButtonDown(nFlags, point)) {
		//结束动画
		EndAnimate();

		//获得屏幕高度
		RECT rc;
		GetClientRect(m_hWnd, &rc);
		g_game->SetStatusNormal(make_shared<CShooter1>(static_cast<int>(rc.bottom - rc.top)), FALSE); 
		return true;
	}
	if (m_item2->OnLButtonDown(nFlags, point)) {
		//结束动画
		EndAnimate();
		g_game->SetStatusNormal(make_shared<CShooter2>(),TRUE);
		return true;
	}
	if (m_item3->OnLButtonDown(nFlags, point)) {
		//结束动画
		EndAnimate();
		g_game->SetStatusNormal(make_shared<CShooter3>(), FALSE);
		return true;
	}

	return false;
}

//鼠标右键按下
bool CDMenu::OnRButtonDown(UINT nFlags, CPoint point){
	return false;
}

//鼠标移动
bool CDMenu::OnMouseMove(UINT nFlags, CPoint point)
{
	//调用各个菜单项的函数, 把鼠标消息转发过去,使各个菜单子项各自处理
	if (m_item0->OnMouseMove(nFlags, point)) {
		return true;
	}
	if (m_item1->OnMouseMove(nFlags, point)) {
		return true;
	}
	if (m_item2->OnMouseMove(nFlags, point)) {
		return true;
	}
	if (m_item3->OnMouseMove(nFlags, point)) {
		return true;
	}

	return false;
}