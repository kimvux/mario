#include "SoundManager.h"

SoundManager* SoundManager::__instance = NULL;

SoundManager* SoundManager::GetInstance() {
	if (__instance == NULL) __instance = new SoundManager();
	return __instance;
}

void SoundManager::PlaySFX(const std::wstring& sfxAlias) {
	mciSendString((L"play " + sfxAlias + L" from 0").c_str(), NULL, 0, NULL);
}

void SoundManager::PlayMusic(const std::wstring& musicAlias) {
	if (currentMusic == musicAlias) return;
	if (currentMusic != L"")
		mciSendString((L"stop " + currentMusic).c_str(), NULL, 0, NULL);
	mciSendString((L"play " + musicAlias + L" from 0 repeat").c_str(), NULL, 0, NULL);
	currentMusic = musicAlias;
}