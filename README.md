# DesktopToysImage-master

## 项目更改

本项目在原有的基础上增添了MusicPlay类，用来给该项目增添音乐，该类的定义如下：

```c++
class MusicPlay
{
public:
	enum class status {
		ninjaShock,//忍者喷漆音乐
		eraseShock,//橡皮擦音乐
		painterShock,//画笔音乐
		hammerShock//锤子碎玻璃的音乐
	};

public:
	static BOOL playMusic(status sta);
private:
	//忍者音乐
	static BOOL playMusic_1();
	//橡皮擦音乐
	static BOOL playMusic_2();
	//画笔音乐
	static BOOL playMusic_3();
	//锤子碎玻璃的音乐
	static BOOL playMusic_4();
};
```

该类定义了游戏种所有的音乐类型，通过status执行不同的函数，借此执行不同的音乐播放。

由于播放音乐和操作是两个独立的过程，为此将音乐播放和操作过程进行分开，采用多线程的方式，这样播放音乐的同时可以进行操作，避免音乐播放的时候使得操作卡顿。
