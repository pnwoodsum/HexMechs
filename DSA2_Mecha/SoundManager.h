#pragma once

#include <SFML\Audio.hpp>

class SoundManager
{
	static SoundManager* m_pInstance;

	sf::Music m_mSoundBGM1;

	sf::SoundBuffer m_sbShooting;
	sf::Sound m_sShooting;
	sf::SoundBuffer m_sbMinigunStart;
	sf::Sound m_sMinigunStart;
	sf::SoundBuffer m_sbMinigunFinish;
	sf::Sound m_sMinigunFinish;
	sf::SoundBuffer m_sbFootStepsOne;
	sf::Sound m_sFootStepsOne;
	sf::SoundBuffer m_sbBulletImpact;
	sf::Sound m_sBulletImpact;
	sf::SoundBuffer m_sbBoostLoop;
	sf::Sound m_sBoostLoop;
	sf::SoundBuffer m_sbFireRocket;
	sf::Sound m_sFireRocket;
	sf::SoundBuffer m_sbRocketImpact;
	sf::Sound m_sRocketImpact;

public:
	static SoundManager* GetInstance();

	static void ReleaseInstance(void);

	void PlaySounds(float dt);

	void ShootingSound();

	void MoveSounds(float dt);

	void BulletCollision();

	void FireRocket();

	void RocketExplosion();

	bool m_bShooting;

	enum PlayerMoveState {
		None,
		Walk,
		Boost
	};
	
	PlayerMoveState currentMoveState = None;

private:

	float footStepTimer;

	SoundManager(void);

	SoundManager(SoundManager const& other);

	SoundManager& operator=(SoundManager const& other);

	~SoundManager(void);

	void Release(void);

	void Init(void);

};