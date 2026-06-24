#pragma once
#include <windows.h>
#include <Windows.h>
#include <string>
#pragma comment(lib, "Winmm.lib")
class SoundManager
{
	std::wstring currentMusic;
	static SoundManager* __instance;
	HINSTANCE hInstance;
public:
	SoundManager() {
		currentMusic = L"";
		mciSendString(L"open \"audio/sfx/smb_coin.wav\" type mpegvideo alias coin", NULL, 0, NULL);
		mciSendString(L"open \"audio/sfx/smb_jump-small.wav\" type mpegvideo alias jumpsmall", NULL, 0, NULL);
		mciSendString(L"open \"audio/sfx/smb_jump-super.wav\" type mpegvideo alias jumpsuper", NULL, 0, NULL);
		mciSendString(L"open \"audio/sfx/smb_pipe.wav\" type mpegvideo alias pipe", NULL, 0, NULL);
		mciSendString(L"open \"audio/sfx/smb_powerup.wav\" type mpegvideo alias powerup", NULL, 0, NULL);
		mciSendString(L"open \"audio/sfx/smb_breakblock.wav\" type mpegvideo alias breakblock", NULL, 0, NULL);
		mciSendString(L"open \"audio/sfx/yeahoo.wav\" type mpegvideo alias dash", NULL, 0, NULL);
		mciSendString(L"open \"audio/sfx/Game_Over.wav\" type mpegvideo alias gameover", NULL, 0, NULL);
		mciSendString(L"open \"audio/music/demomap.wav\" type mpegvideo alias 1", NULL, 0, NULL);
		mciSendString(L"open \"audio/music/main.wav\" type mpegvideo alias 2", NULL, 0, NULL);
		mciSendString(L"open \"audio/music/underwater.wav\" type mpegvideo alias 3", NULL, 0, NULL);
		mciSendString(L"open \"audio/music/boss.wav\" type mpegvideo alias 4", NULL, 0, NULL);
		mciSendString(L"open \"audio/music/win.wav\" type mpegvideo alias 7", NULL, 0, NULL);
		mciSendString(L"open \"audio/music/star.wav\" type mpegvideo alias star", NULL, 0, NULL);
		mciSendString(L"open \"audio/music/mariodie.wav\" type mpegvideo alias mariodie", NULL, 0, NULL);
	}
	void PlaySFX(const std::wstring& sfxAlias);
	void PlayMusic(const std::wstring& musicAlias);
	static SoundManager* GetInstance();
	~SoundManager() {
		mciSendString(L"close coin", NULL, 0, NULL);
		mciSendString(L"close jumpsmall", NULL, 0, NULL);
		mciSendString(L"close jumpsuper", NULL, 0, NULL);
		mciSendString(L"close 1", NULL, 0, NULL);
		mciSendString(L"close 2", NULL, 0, NULL);
		mciSendString(L"close 3", NULL, 0, NULL);
		mciSendString(L"close star", NULL, 0, NULL);
		mciSendString(L"close mariodie", NULL, 0, NULL);
		mciSendString(L"close dash", NULL, 0, NULL);
		mciSendString(L"close powerup", NULL, 0, NULL);
		mciSendString(L"close breakblock", NULL, 0, NULL);
		mciSendString(L"close pipe", NULL, 0, NULL);
	}
};
typedef SoundManager* LPSOUNDMANAGER;

