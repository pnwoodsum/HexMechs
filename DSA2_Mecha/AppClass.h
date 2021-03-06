/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include "Camera.h"
#include "GameObject.h"
#include "Prefabs.h"
#include "iostream"
#include "SoundManager.h"
#include <SFML\Graphics.hpp>
//#include <chrono>

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class AppClass : public ReEngAppClass
{
	//CollisionManager* m_pBOMngr;
	std::vector<GameObject*> objects;
	std::vector<Enemy*> enemies;
	//BulletManager* bulletMngr;


	//Textures for main menu
	TextureClass* cockpitTexture;
	TextureClass* mainMenuBG[25];
	TextureClass* failTexture;
	TextureClass* notFailTexture;
	TextureClass* pauseTexture;

	//simple shapes used in scene
	PrimitiveClass* m_pCone = nullptr;
	PrimitiveClass* m_pPlane = nullptr;
	PrimitiveClass* m_pCylinder = nullptr;
	PrimitiveClass* m_pCylinder2 = nullptr;

	//handles all sound
	SoundManager* sManager;

	//an array to hold all bullets so they don't have to be created every time
	std::vector<Projectile> bullets;
	int curr = 0;

	//pointer to camera
	Camera* m_Camera = new Camera();

	//variables for controlling game
	uint state = 0;
	int timer;
	float fTimer;
	bool pause;
	bool firing = false;
	bool lastPressed = false;
	matrix4 m_m4GunMat;

	bool m_bCockPitUp = true;
	bool m_bCockPitRight = true;

	matrix4 m_m4CockPitPlaneMat;
	vector3 m_v3CockPitPlane;

	sf::Vector2i cM;

	matrix4 m_m4Projection;
	matrix4 m_m4View;
public:
	typedef ReEngAppClass super;

	/* Constructor */
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow) : super(hInstance, lpCmdLine, nCmdShow) {}

	/*
	InitWindow
	Initialize ReEng variables necessary to create the window
	*/
	virtual void InitWindow(String a_sWindowName);

	/*
	InitVariables
	Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	*/
	virtual void InitVariables(void);



	/*
	Update
	Updates the scene
	*/
	virtual void Update(void);

	/*
	Display
	Displays the scene
	*/
	virtual void Display(void);

	/*
	ProcessKeyboard
	Manage the response of key presses
	*/
	virtual void ProcessKeyboard(void);

	/*
	Release
	Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	*/
	virtual void Release(void);

	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ReadConfig(void) final {}

	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void WriteConfig(void) final {}

	//Toggles the bounding objects display
	void ToggleDebug();

	//Toggles the Seperation Axis Theorem
	void ToggleSAT();
};

#endif //__APPLICATION_H_
