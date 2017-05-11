#pragma once

#include <SFML\Audio.hpp>

// A singleton to contain all of the sound buffers, music and sound variables.
// Also contains enum for player movement state and methods to play each sound.
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

public:
	static SoundManager* GetInstance();

	static void ReleaseInstance(void);

	// Method to combine sounds to be played on update.
	void PlaySounds(float dt);

	// Handle the sounds of the machine gun firing
	void ShootingSound();

	// Handle sounds of boosting and footsteps
	void MoveSounds(float dt);

	// Handle sound of bullets impacting
	void BulletCollision();

	// Is the play currently shooting?
	bool m_bShooting;
	bool m_bShootingSecond;

	// Is the player walking or boosting?
	enum PlayerMoveState {
		None,
		Walk,
		Boost
	};
	
	PlayerMoveState currentMoveState = None;

private:

	float footStepTimer; // Keep track of when to play footstep sound

	SoundManager(void);

	SoundManager(SoundManager const& other);

	SoundManager& operator=(SoundManager const& other);

	~SoundManager(void);

	void Release(void);

	void Init(void);

};