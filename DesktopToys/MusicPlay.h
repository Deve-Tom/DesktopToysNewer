#pragma once
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
class MusicPlay{
public:
	enum class status {
		ninjaShock,//������������
		eraseShock,//��Ƥ������
		painterShock,//��������
		hammerShock//�����鲣��������
	};

public:
	static BOOL playMusic(status sta);
private:
	//��������
	static BOOL playMusic_1();
	//��Ƥ������
	static BOOL playMusic_2();
	//��������
	static BOOL playMusic_3();
	//�����鲣��������
	static BOOL playMusic_4();
};

