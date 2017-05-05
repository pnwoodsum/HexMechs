#include "SoundManager.h"

//  SoundManager
SoundManager* SoundManager::m_pInstance = nullptr;

void SoundManager::Init(void)
{
	// Music
	m_mSoundBGM1.openFromFile("Data\\Audio\\panther.ogg");
	m_mSoundBGM1.setVolume(25.0f);
	m_mSoundBGM1.play();
	m_mSoundBGM1.setLoop(true);

	m_sbShooting.loadFromFile("Data\\Audio\\minigunFiring.wav");
	m_sShooting.setBuffer(m_sbShooting);
	m_sShooting.setVolume(75.0f);

	
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

void SoundManager::PlaySounds() {
	ShootingSound();
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