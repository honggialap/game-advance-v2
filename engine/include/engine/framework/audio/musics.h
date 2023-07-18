#pragma once
#ifndef __MUSICS_H__
#define __MUSICS_H__

#include "common.h"

class CMusics {
private:
	typedef std::pair<sf::Music*, std::string> MusicData;
	std::unordered_map<MusicID, MusicData> musics;

public:
	CMusics();
	virtual ~CMusics();

	void LoadMusicsFromJson(json& data);

	sf::Music* GetMusic(MusicID id);
	sf::Music* CreateMusic(MusicID id, std::string file_path);
	sf::Music* LoadMusic(MusicID id);
	void DestroyMusic(MusicID id);
	void ClearMusics();
};
typedef CMusics* pMusics;

#endif // !__MUSIC_H__
