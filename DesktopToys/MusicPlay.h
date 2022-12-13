#pragma once
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
class MusicPlay{
public:
	enum class status {
		ninjaShock,//ÈÌÕßÅçÆáÒôÀÖ
		eraseShock,//ÏğÆ¤²ÁÒôÀÖ
		painterShock,//»­±ÊÒôÀÖ
		hammerShock//´¸×ÓËé²£Á§µÄÒôÀÖ
	};

public:
	static BOOL playMusic(status sta);
private:
	//ÈÌÕßÒôÀÖ
	static BOOL playMusic_1();
	//ÏğÆ¤²ÁÒôÀÖ
	static BOOL playMusic_2();
	//»­±ÊÒôÀÖ
	static BOOL playMusic_3();
	//´¸×ÓËé²£Á§µÄÒôÀÖ
	static BOOL playMusic_4();
};

