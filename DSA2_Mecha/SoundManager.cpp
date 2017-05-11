#include "SoundManager.h"

//  SoundManager
SoundManager* SoundManager::m_pInstance = nullptr;

// Initialize all of the sounds and sound buffers
void SoundManager::Init(void)
{
	// Music
	m_mSoundBGM1.openFromFile("Data\\Audio\\panther.ogg");
	m_mSoundBGM1.setVolume(20.0f);
	m_mSoundBGM1.play();
	m_mSoundBGM1.setLoop(true);

	m_sbShooting.loadFromFile("Data\\Audio\\minigunFiring.wav");
	m_sShooting.setBuffer(m_sbShooting);
	m_sShooting.setVolume(75.0f);

	m_sbMinigunStart.loadFromFile("Data\\Audio\\minigunStart.wav");
	m_sMinigunStart.setBuffer(m_sbMinigunStart);
	m_sMinigunStart.setVolume(75.0f);

	m_sbMinigunFinish.loadFromFile("Data\\Audio\\minigunFinish.wav");
	m_sMinigunFinish.setBuffer(m_sbMinigunFinish);
	m_sMinigunFinish.setVolume(75.0f);

	m_sbFootStepsOne.loadFromFile("Data\\Audio\\footStepsOne.wav");
	m_sFootStepsOne.setBuffer(m_sbFootStepsOne);
	m_sFootStepsOne.setVolume(100.0f);

	m_sbBulletImpact.loadFromFile("Data\\Audio\\bulletImpact.wav");
	m_sBulletImpact.setBuffer(m_sbBulletImpact);
	m_sBulletImpact.setVolume(75.0f);

	m_sbBoostLoop.loadFromFile("Data\\Audio\\boostLoop.wav");
	m_sBoostLoop.setBuffer(m_sbBoostLoop);
	m_sBoostLoop.setVolume(60.0f);

	m_sbFireRocket.loadFromFile("Data\\Audio\\fireRocket.wav");
	m_sFireRocket.setBuffer(m_sbFireRocket);
	m_sFireRocket.setVolume(60.0f);

	m_sbRocketImpact.loadFromFile("Data\\Audio\\rocketImpact.wav");
	m_sRocketImpact.setBuffer(m_sbBoostLoop);
	m_sRocketImpact.setVolume(60.0f);
	
	footStepTimer = 0.0f;
}
void SoundManager::Release(void)
{

}

SoundManager* SoundManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new SoundManager();
	}
	return m_pInstance;
}
void SoundManager::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

SoundManager::SoundManager() { Init(); }
SoundManager::SoundManager(SoundManager const& other) { }
SoundManager& SoundManager::operator=(SoundManager const& other) { return *this; }
SoundManager::~SoundManager() { Release(); };

void SoundManager::PlaySounds(float dt) {
	ShootingSound();
	MoveSounds(dt);
}

void SoundManager::ShootingSound() {
	// Handle sound for the gun
	if (m_bShooting) {
		if (m_sShooting.getStatus() == sf::SoundSource::Status::Stopped) {
			m_sShooting.play();
		}
	}
	else {
		m_sShooting.stop();
	}
}

void SoundManager::BulletCollision() {
	m_sBulletImpact.play();
}

void SoundManager::FireRocket() {
	m_sFireRocket.play();
}

void SoundManager::RocketExplosion() {
	m_sRocketImpact.play();
}

void SoundManager::MoveSounds(float dt) {
	if (currentMoveState == None) {
		if (m_sBoostLoop.getStatus() == sf::SoundSource::Status::Playing) {
			m_sBoostLoop.stop();
		}
		return;
	}
	else if (currentMoveState == Walk) {
		footStepTimer += dt;
		if (footStepTimer >= 0.65f) {
			m_sFootStepsOne.play();
			footStepTimer = 0.0f;
		}
		if (m_sBoostLoop.getStatus() == sf::SoundSource::Status::Playing) {
			m_sBoostLoop.stop();
		}
	}
	else if (currentMoveState == Boost) {
		if (m_sBoostLoop.getStatus() == sf::SoundSource::Status::Stopped) {
			m_sBoostLoop.play();
		}
	}
	
}
