#pragma once
#ifndef __SOUND_BUFFERS_H__
#define __SOUND_BUFFERS_H__

#include "common.h"

class CSoundBuffers {
private:
	std::unordered_map<SoundBufferID, sf::SoundBuffer*> sound_buffers;

public:
	CSoundBuffers();
	virtual ~CSoundBuffers();

	void LoadSoundBuffersFromJson(json& data);

	sf::SoundBuffer* GetSoundBuffer(SoundBufferID id);
	sf::SoundBuffer* CreateSoundBuffer(SoundBufferID id);
	void DestroySoundBuffer(SoundBufferID id);
	void ClearSoundBuffers();
};
typedef CSoundBuffers* pSoundBuffers;

#endif // !__SOUND_BUFFERS_H__
