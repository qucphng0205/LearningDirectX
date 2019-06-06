#include "gnhpSound.h"

gnhpSound *gnhpSound::instance = NULL;

gnhpSound::gnhpSound() {
	g_pDS = NULL;
}

gnhpSound::~gnhpSound() {
}

gnhpSound * gnhpSound::GetInstance() {
	if (instance == NULL)
		instance = new gnhpSound();
	return instance;
}

void gnhpSound::LoadSound(HWND hwnd) {
	if (!InitDirectSound(hwnd))
	{
		MessageBox(NULL, "Unable to init DirectSound", "ERROR", MB_OK);
	}
	DSBuffer[SOUND_MUSIC31] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/soundtrack31.wav");
	DSBuffer[SOUND_MUSIC32] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/soundtrack32.wav");
	DSBuffer[SOUND_MUSIC33] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/soundtrack33.wav");
	DSBuffer[SOUND_GAMEOVER] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/gameover.wav");
	DSBuffer[SOUND_SLASH] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/slash.wav");
	DSBuffer[SOUND_JUMP] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/jump.wav");
	DSBuffer[SOUND_INJURED] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/injured.wav");
	DSBuffer[SOUND_EATITEM] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/eatitem.wav");
	DSBuffer[SOUND_DAMAGE] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/damage.wav");
	DSBuffer[SOUND_BIGBULLET] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/bigbullet.wav");
	DSBuffer[SOUND_BASAQUER] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/basaquer.wav");
	DSBuffer[SOUND_BULLET] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/bullet.wav");
	DSBuffer[SOUND_EARN] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/earn.wav");
	DSBuffer[SOUND_BASAQUEREXPLOSION] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/basaquerexplosion.wav");
	

	if (!DSBuffer)
	{
		MessageBox(NULL, "Unable to load sound", "ERROR", MB_OK);
	}
}

bool gnhpSound::InitDirectSound(HWND hwnd) {
	HRESULT res;
	res = DirectSoundCreate8(NULL, &g_pDS, NULL);
	if (FAILED(res))
		return false;

	res = g_pDS->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if (FAILED(res))
		return false;

	currentBackground = -1;
}

LPDIRECTSOUNDBUFFER gnhpSound::LoadWaveToSoundBuffer(char * wavFilename) {
	LPDIRECTSOUNDBUFFER sound = NULL;
	CWaveFile *wavFile;
	HRESULT res;

	wavFile = new CWaveFile();
	wavFile->Open(wavFilename, NULL, WAVEFILE_READ);

	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = 0;
	dsbd.dwBufferBytes = wavFile->GetSize();
	dsbd.guid3DAlgorithm = GUID_NULL;
	dsbd.lpwfxFormat = wavFile->m_pwfx;

	res = g_pDS->CreateSoundBuffer(&dsbd, &sound, NULL);

	if (FAILED(res)) {
		MessageBox(NULL, "unable to create sound buffer", "ERROR", MB_OK);
		return NULL;
	}
	VOID*   pDSLockedBuffer = NULL; // Pointer to locked buffer memory
	DWORD   dwDSLockedBufferSize = 0;    // Size of the locked DirectSound buffer
	DWORD   dwWavDataRead = 0;    // Amount of data read from the wav file 

	res = sound->Lock(0, wavFile->GetSize(),
		&pDSLockedBuffer, &dwDSLockedBufferSize,
		NULL, NULL, 0L);

	if (FAILED(res))
		return NULL;
	// Reset the wave file to the beginning 
	wavFile->ResetFile();

	// Read the wave file
	res = wavFile->Read((BYTE*)pDSLockedBuffer,
		dwDSLockedBufferSize,
		&dwWavDataRead);

	// Check to make sure that this was successful
	if (FAILED(res))
		return NULL;

	// Check to make sure the wav file is not empty
	if (dwWavDataRead == 0)
	{
		// Wav is blank, so just fill with silence
		FillMemory((BYTE*)pDSLockedBuffer,
			dwDSLockedBufferSize,
			(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
	}

	else if (dwWavDataRead < dwDSLockedBufferSize)
	{
		// Don't repeat the wav file, just fill in silence 
		FillMemory((BYTE*)pDSLockedBuffer + dwWavDataRead,
			dwDSLockedBufferSize - dwWavDataRead,
			(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
	}

	// Unlock the buffer, we don't need it anymore.
	sound->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0);

	// Clean up
	delete wavFile;
	wavFile = NULL;

	return sound;
}

void gnhpSound::PlayFX(int id) {
	DSBuffer[id]->Play(0, 0, 0);
}

void gnhpSound::StopFX(int id) {
	DSBuffer[id]->Stop();
}

void gnhpSound::PlayMusic(int id) {
	StopMusic();
	currentBackground = id;
	DSBuffer[currentBackground]->Play(0, 0, DSBPLAY_LOOPING);
}

void gnhpSound::StopMusic() {
	if (currentBackground != -1)
		DSBuffer[currentBackground]->Stop();
}
