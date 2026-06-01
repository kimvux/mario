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
		mciSendString(L"open \"audio/sfx/yeahoo.wav\" type mpegvideo alias dash", NULL, 0, NULL);
		mciSendString(L"open \"audio/music/main.wav\" type mpegvideo alias maintheme", NULL, 0, NULL);
		mciSendString(L"open \"audio/music/underwater.wav\" type mpegvideo alias 2", NULL, 0, NULL);
	}
	void PlaySFX(const std::wstring& sfxAlias);
	void PlayMusic(const std::wstring& musicAlias);
	static SoundManager* GetInstance();
	~SoundManager() {
		mciSendString(L"close coin", NULL, 0, NULL);
		mciSendString(L"close jumpsmall", NULL, 0, NULL);
		mciSendString(L"close jumpsuper", NULL, 0, NULL);
		mciSendString(L"close worldclear", NULL, 0, NULL);
	}
};
typedef SoundManager* LPSOUNDMANAGER;

