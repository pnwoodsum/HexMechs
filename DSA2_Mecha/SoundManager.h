#pragma once

#include <SFML\Audio.hpp>

class SoundManager
{
	static SoundManager* m_pInstance;

	sf::Music m_mSoundBGM1;

	sf::SoundBuffer m_sbShooting;
	sf::Sound m_sShooting;
	sf::SoundBuffer m_sbFootStep;
	sf::Sound m_sFootStep;

public:
	static SoundManager* GetInstance();

	static void ReleaseInstance(void);

	void PlaySounds();

	void ShootingSound();

	bool m_bShooting;

private:

	SoundManager(void);

	SoundManager(SoundManager const& other);

	SoundManager& operator=(SoundManager const& other);

	~SoundManager(void);

	void Release(void);

	void Init(void);

};