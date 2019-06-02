#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <dsound.h>
#include "dsutil.h"

class gnhpSound {
private:
	int currentBackground;
	int counter[100];
	static gnhpSound *instance;
public:
	LPDIRECTSOUND8 g_pDS;
	LPDIRECTSOUNDBUFFER DSBuffer[30];

	gnhpSound();
	~gnhpSound();
	static gnhpSound *GetInstance();

	void LoadSound(HWND hwnd);
	bool InitDirectSound(HWND hwnd);
	LPDIRECTSOUNDBUFFER LoadWaveToSoundBuffer(char* wavFilename);
	void PlayFX(int id);
	void StopFX(int id);
	void PlayMusic(int id);
	void StopMusic();
};