#include "stdafx.h"
#include "MusicPlay.h"
#include <thread>

BOOL MusicPlay::playMusic_1()
{

    /*mciSendString(TEXT("open music1.mp3"), 0, 0, 0);
    mciSendString(TEXT("play music1.mp3 repeat"), 0, 0, 0);
    Sleep(600);
    mciSendString(TEXT("close music1.mp3"), 0, 0, 0);*/
    return 0;
}

BOOL MusicPlay::playMusic_2()
{
    return 0;
}

BOOL MusicPlay::playMusic_3()
{
    return 0;
}

BOOL MusicPlay::playMusic_4()
{
    return 0;
}

BOOL MusicPlay::playMusic(status sta)
{
    switch (sta) {
    case status::ninjaShock:{
        //»Ã’ﬂ“Ù¿÷
        thread playMusicBegin(MusicPlay::playMusic_1);
        playMusicBegin.detach();
        break;
    }
    case status::eraseShock: {
        //œ∆§≤Ó“Ù¿÷
        thread playMusicBegin(MusicPlay::playMusic_2);
        playMusicBegin.detach();
        break;
    }
    case status::hammerShock: {
        //¥∏◊”ÀÈ≤£¡ßµƒ“Ù¿÷
        thread playMusicBegin(MusicPlay::playMusic_3);
        playMusicBegin.detach();
        break;
    }
    case status::painterShock: {
        //ª≠± µƒ“Ù¿÷
        thread playMusicBegin(MusicPlay::playMusic_4);
        playMusicBegin.detach();
        break;
    }
    }
    return 0;
}
