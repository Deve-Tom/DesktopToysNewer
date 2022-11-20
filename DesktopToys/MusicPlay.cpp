#include "stdafx.h"
#include "MusicPlay.h"
#include <thread>

BOOL MusicPlay::playMusic_1()
{
    mciSendString(TEXT("open music\\ninjamusic.mp3"), 0, 0, 0);
    mciSendString(TEXT("play music\\ninjamusic.mp3 repeat"), 0, 0, 0);
    Sleep(800);
    mciSendString(TEXT("close music\\ninjamusic.mp3"), 0, 0, 0);
    return 0;
}

BOOL MusicPlay::playMusic_2()
{
    mciSendString(TEXT("open music\\erase.mp3"), 0, 0, 0);
    mciSendString(TEXT("play music\\erase.mp3 repeat"), 0, 0, 0);
    Sleep(1500);
    mciSendString(TEXT("close music\\erase.mp3"), 0, 0, 0);
    return 0;
}

BOOL MusicPlay::playMusic_3()
{
    mciSendString(TEXT("open music\\hammer.mp3"), 0, 0, 0);
    mciSendString(TEXT("play music\\hammer.mp3 repeat"), 0, 0, 0);
    Sleep(1500);
    mciSendString(TEXT("close music\\hammer.mp3"), 0, 0, 0);
    return 0;
}

BOOL MusicPlay::playMusic_4()
{
    mciSendString(TEXT("open music\\brush.mp3"), 0, 0, 0);
    mciSendString(TEXT("play music\\brush.mp3 repeat"), 0, 0, 0);
    Sleep(800);
    mciSendString(TEXT("close music\\brush.mp3"), 0, 0, 0);
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
