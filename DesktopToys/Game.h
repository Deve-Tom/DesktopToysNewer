/*
��Ϸ������
*/
#pragma once
#include "DMenu.h"
#include "Shooter.h"

class IMark; //ǰ������
class CGame
{
public:
	CGame(HWND hWnd,float x,float y,float w,float h);
	~CGame();
public:
	//��Ϸ��һ֡
	bool EnterFrame(DWORD dwTime);
	//���������Ϣ
	// ����������
	void OnLButtonDown(UINT nFlags, CPoint point);
	// ������̧��
	void OnLButtonUp(UINT nFlags, CPoint point);
	// ������˫��
	void OnLButtonDblClk(UINT nFlags, CPoint point);
	// ����Ҽ�����
	void OnRButtonDown(UINT nFlags, CPoint point);
	// ����Ҽ�̧��
	void OnRButtonUp(UINT nFlags, CPoint point);
	// ����Ҽ�˫��
	void OnRButtonDblClk(UINT nFlags, CPoint point);
	// ����ƶ�
	void OnMouseMove(UINT nFlags, CPoint point);

	// ���� ESC ��ʱ�Ĵ���: ����FALSE �����������ɸ����ڴ���
	BOOL OnESC();
	void SetStatusNormal(std::shared_ptr<CShooter> pTool, BOOL bCursor = FALSE);
	// ����һ�� �ƻ���
	void Append(std::shared_ptr<IMark> pMark)
	{
		m_vMarks.push_back(pMark);
	}

	// �����Ϸ���ڵĿ���
	float GetWidth() const
	{
		return m_width;
	}

	// �����Ϸ���ڵĸ߶�
	float GetHeigth() const
	{
		return m_height;
	}

	// ��÷�Χ
	RectF GetRectF() const
	{
		return RectF(m_x, m_y, m_width, m_height);
	}
private:
	HWND m_hWnd;
	// ���ڵ���ʼλ��
	float m_x;
	float m_y;

	// ��Ϸ���ڵĿ���
	float m_width;
	float m_height;

	// ��Ϸֻ��Ϊ�����׶�: �˵�ѡ��׶Σ���ʽ��Ϸ�׶�
	typedef enum EGameStatus { EGameStatusSelect, EGameStatusNormal } EGameStatus;
	EGameStatus  m_eStatus{ EGameStatusSelect };

private:
	//�ͻ�����С
	CRect m_rcClient;
	//��¼��Ϸÿ�����֡
	int m_fps{ 0 };
	//���FPS�����õ��Ļ�ˢ
	SolidBrush m_brush{ Color(254, 0xFF, 0x00, 0x00) };
	// ���FPS��������
	Gdiplus::Font m_font{ L"����", 10.0 };
	// �����Ͻ���ʾ
	PointF origin{ 0.0f, 0.0f };
	// �������ж���
	void Draw();

	// ���fps
	void DrawFps(Gdiplus::Graphics &gh);

	// �ƻ��������µĶ���
	std::vector<std::shared_ptr<IMark>> m_vMarks;

	// ����ͼ
	Gdiplus::Bitmap *m_imgBk;
	std::shared_ptr<CDMenu> m_menu;  //�˵�
	std::shared_ptr<CShooter> m_pTool;//��ǰѡ��Ĺ���
};
