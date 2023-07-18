#pragma once
#ifndef __SOUNDS_H__
#define __SOUNDS_H__

#include "sound_buffers.h"

class CSounds {
private:
	CSoundBuffers& sound_buffers;

	std::unordered_map<SoundID, sf::Sound*> sounds;

public:
	CSounds(CSoundBuffers& sound_buffers);
	virtual ~CSounds();

	CSoundBuffers& GetSoundBuffers() { return sound_buffers; }

	void LoadSoundsFromJson(json& data);

	sf::Sound* GetSound(SoundID id);
	sf::Sound* CreateSound(SoundID id);
	void DestroySound(SoundID id);
	void ClearSounds();
};
typedef CSounds* pSounds;

#endif // !__SOUNDS_H__
