#include "AppClass.h"
#include "Camera.h"
#include "iostream"

void AppClass::ProcessKeyboard(void)
{
	//Flag for the modifier
	bool bModifier = false;

	//ON PRESS/RELEASE
#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

	//F1 Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		bModifier = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (bModifier) {
			m_Camera->MoveForward(1.0f,true); 
		}
		else {
			m_Camera->MoveForward(1.0f,false);
		}
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (bModifier) {
			m_Camera->MoveForward(-1.0f,true);
		}
		else {
			m_Camera->MoveForward(-1.0f,false);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (bModifier) {
			m_Camera->MoveSideways(1.0f, true);
		}
		else {
			m_Camera->MoveSideways(1.0f, false);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (bModifier) {
			m_Camera->MoveSideways(-1.0f, true);
		}
		else {
			m_Camera->MoveSideways(-1.0f, false);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) 
	{
		pause = true;
	}
	else pause = false;

	sManager->m_bShooting = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sManager->m_bShooting = true;
		Projectile::fire(m_Camera->GetPos(), m_Camera->orientation, fTimer);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_Camera->MoveVertical(1.0f, false);
		m_Camera->inAir = true;
	}
	//Exit the program
#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
#pragma endregion
}