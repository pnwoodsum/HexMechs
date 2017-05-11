#include "AppClass.h"
#include "BoundingObject.h"

void AppClass::InitWindow(String a_sWindowName) {
	super::InitWindow("HexMechs"); // Window Name
}
void AppClass::InitVariables(void) {

	fTimer = 0.0f; //Global Timer in Seconds

	//screens for displaying game state
	failTexture = new TextureClass();
	failTexture->LoadTexture("fail.jpg");
	notFailTexture = new TextureClass();
	notFailTexture->LoadTexture("notFail.jpg");
	pauseTexture = new TextureClass();
	pauseTexture->LoadTexture("pause.png");

	//loads all the screen textures
	for (int i = 0; i < 25; i++) {
		mainMenuBG[i] = new TextureClass();
		std::string num = "dream" + std::to_string(i + 1) + ".jpg";
		mainMenuBG[i]->LoadTexture(num);
	}

	pause = false;
	
	// Sound manager
	sManager = SoundManager::GetInstance();
		
	//create the bullets
	for (int i = 0; i < 40; i++) {
		objects.push_back(new Projectile());
	}

	//creates some objects in the environment and the player
	objects.push_back(new Player(m_Camera));
	objects.push_back(new Pillar(vector3(-600, 0, -600)));
	objects.push_back(new Pillar(vector3(-600, 0, 0)));
	objects.push_back(new Pillar(vector3(-600, 0, 600)));
	objects.push_back(new Pillar(vector3(600, 0, -600)));
	objects.push_back(new Pillar(vector3(600, 0, 0)));
	objects.push_back(new Pillar(vector3(600, 0, 600)));
	objects.push_back(new Wall(vector3(6000.f, 400.f, 30.f), vector3(0, 0, -3000)));
	objects.push_back(new Wall(vector3(6000.f, 400.f, 30.f), vector3(0, 0, 3000)));
	objects.push_back(new Wall(vector3(30.f, 400.f, 6000.f), vector3(-3000, 0, 0)));
	objects.push_back(new Wall(vector3(30.f, 400.f, 6000.f), vector3(3000, 0, 0)));
	objects.push_back(new DestructObj(vector3(300, 0, 300)));
	objects.push_back(new DestructObj(vector3(200, 0, 300)));
	objects.push_back(new DestructObj(vector3(100, 0, 300)));

	//randomly moving enemies
	for (int i = 0; i < 3; i++) {
		EnemyRandom* enemy = new EnemyRandom(vector3(400, 0, 300), m_Camera);
		enemy->boxCenter = vector3(0, 100, 0);
		enemy->boxDimmensions = vector3(800, 200, 800);
		objects.push_back(enemy);
	}
	
	//point to point enemies
	for (int i = 0; i < 4; i++) {
		EnemyPath* enemy = new EnemyPath(m_Camera);
		enemy->pathPoints.push_back(vector3(3000.f, 100.f, i * 1000));
		enemy->pathPoints.push_back(vector3(-3000.f, 100.f, i * 1000));
		enemy->speed = enemy->speed + i * 20;
		objects.push_back(enemy);
	}

	//Generate the Cone
	m_pCone = new PrimitiveClass();
	m_pCone->GenerateCube(70.0f, RERED);
	
	// loading models used in game
	m_pMeshMngr->LoadModel("Mechs\\ChainGun.fbx", "ChainGun");
	m_pMeshMngr->LoadModel("Mechs\\panel.obj", "panel");
	m_pMeshMngr->LoadModel("Mechs\\wall.obj", "wall");
	m_pMeshMngr->LoadModel("Mechs\\floor.obj", "floor");
	m_pMeshMngr->LoadModel("Mechs\\cockpitPlane.obj", "CockPitPlane");

	m_v3CockPitPlane = vector3(0.0f, 0.0f, 11.0f);

	//Calculate the first projections
	m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	//Find Center of Scrren
	UINT	CenterX, CenterY;
	CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
	CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;

	//intializes all objects in game
	for (int i = 0; i < (int)objects.size(); i++) {
		objects[i]->Start();
	}
}


void AppClass::Update(void)
{
	//TIME
	m_pSystem->UpdateTime();
	static int nClock = m_pSystem->GenClock();
	float fDeltaTime = static_cast<float>(m_pSystem->LapClock(nClock));
	fTimer += fDeltaTime;
	
	GameObject::time = fTimer;

	//Gameplay state
	if (state == 1) {
		if (!pause) {
			m_Camera->Move(fTimer); //Moves Camera/Player
			for (int i = 0; i < (int)objects.size(); i++) {
				objects[i]->Update(fDeltaTime);
			}
		}

		//Find Mouse Difference to move Camera
		cM = sf::Mouse::getPosition();

		UINT	CenterX, CenterY;
		CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
		CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;

		sf::Vector2i rem = sf::Vector2i(CenterX, CenterY);

		sf::Vector2i dis = rem - cM;
		vector2 mousePos = vector2(-dis.x, -dis.y);

		SetCursorPos(CenterX, CenterY);

		ArcBall();

		//Camera
		m_m4Projection = m_Camera->GetProjection(false);
		m_m4View = m_Camera->GetView(mousePos);

		// Handle Sounds
		sManager->PlaySounds(fDeltaTime);


		//sound effects for the character movement
		if (sManager->currentMoveState == sManager->Walk) {
			if (m_bCockPitUp) {
				m_v3CockPitPlane.y -= 0.04f;
				if (m_v3CockPitPlane.y <= -0.6) {
					m_bCockPitUp = false;
				}
			}
			else {
				m_v3CockPitPlane.y += 0.05f;
				if (m_v3CockPitPlane.y >= 0.5) {
					m_bCockPitUp = true;
				}
			}
			if (m_bCockPitRight) {
				m_v3CockPitPlane.x -= 0.005f;
				if (m_v3CockPitPlane.x <= -0.25) {
					m_bCockPitRight = false;
				}
			}
			else {
				m_v3CockPitPlane.x += 0.004f;
				if (m_v3CockPitPlane.x >= 0.25) {
					m_bCockPitRight = true;
				}
			}
		}

		m_m4CockPitPlaneMat = glm::translate(-m_Camera->GetPos()) *
			glm::transpose(glm::toMat4(m_Camera->orientation)) *
			glm::translate(IDENTITY_M4, -m_v3CockPitPlane) *
			glm::scale(vector3(0.5f, 0.5f, 0.0f));

		m_pMeshMngr->SetModelMatrix(m_m4CockPitPlaneMat, "CockPitPlane");

		// Update gun matrix
		m_m4GunMat = glm::translate(-m_Camera->GetPos()) *
			glm::transpose(glm::toMat4(m_Camera->orientation)) *
			glm::translate(IDENTITY_M4, -vector3(-8.0f, 4.0f, 20.0f)) *
			ToMatrix4(glm::angleAxis(180.0f, REAXISY));

		m_pMeshMngr->SetModelMatrix(m_m4GunMat,
			"ChainGun");
	}
	
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	//m_pMeshMngr->AddInstanceToRenderList("ALL");
	if (state == 1) {
		m_pMeshMngr->AddInstanceToRenderList("ChainGun");
		m_pMeshMngr->AddInstanceToRenderList("CockPitPlane");

		//Panels
		for (int i = 0; i < 4; i++) {
			m_pMeshMngr->SetModelMatrix(glm::translate(vector3(2850.f, 100.f, i * 1000)) * glm::scale(vector3(5, 5, 5)) * glm::rotate(-90.0f, vector3(0, 1, 0)),
				"panel");
			m_pMeshMngr->AddInstanceToRenderList("panel");
			m_pMeshMngr->SetModelMatrix(glm::translate(vector3(-2850.f, 100.f, i * 1000)) * glm::scale(vector3(5, 5, 5)) * glm::rotate(90.0f, vector3(0, 1, 0)),
				"panel");
			m_pMeshMngr->AddInstanceToRenderList("panel");
		}




		//Wall sections
		for (int x = 0; x <= 360; x += 90) {
			for (int z = -10; z < 10; z++) {
				m_pMeshMngr->SetModelMatrix(glm::rotate((float)x, vector3(0, 1, 0)) * glm::translate(vector3(-3100, -60, 4 * 90 * z)) * glm::scale(vector3(150, 150, 150)),
					"wall");
				m_pMeshMngr->AddInstanceToRenderList("wall");
			}
		}

		//Floor sections 
		for (int x = -8; x < 8; x++) {
			for (int z = -8; z < 8; z++) {
				m_pMeshMngr->SetModelMatrix(glm::translate(vector3(x * 500, -230, z * 500)) * glm::scale(vector3(500, 500, 500)),
					"floor");
				m_pMeshMngr->AddInstanceToRenderList("floor");
			}
		}

	}
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	m_pCameraMngr->SetProjectionMatrix(m_m4Projection);
	m_pCameraMngr->SetViewMatrix(m_m4View);

	//Render the cone
	//m_pCone->Render(m_m4Projection, m_m4View, glm::translate(IDENTITY_M4, REAXISY * -65.0f));

	for (int i = 0; i < (int)objects.size(); i++) {
		objects[i]->Render(m_m4Projection, m_m4View);
	}

	//m_pPlane->Render(m_m4Projection,m_m4View, glm::translate(IDENTITY_M4, REAXISY * -155.0f) * glm::rotate(90.0f,1.0f,0.0f,0.0f));
	
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(std::to_string(m_Camera->velocity.x) + "," + std::to_string(m_Camera->velocity.y) + "," + std::to_string(m_Camera->velocity.z));
	m_pMeshMngr->PrintLine(std::to_string(glm::length(m_Camera->velocity)));
	m_pMeshMngr->PrintLine(std::to_string(m_Camera->energy));

	m_pMeshMngr->Render(); //renders the render list
	//m_pMeshMngr->RenderTexture(cockpitTexture->GetGLTextureID());

	static int inte = 0;
	switch (state) {
	case 0:
		m_pMeshMngr->RenderTexture(mainMenuBG[inte]->GetGLTextureID());
		inte++;
		if (inte >= 25) inte = 0;
		break;
	case 2:
		m_pMeshMngr->RenderTexture(notFailTexture->GetGLTextureID());
		break;
	case 3:
		m_pMeshMngr->RenderTexture(failTexture->GetGLTextureID());
		break;

	}
	if (pause) {
		m_pMeshMngr->RenderTexture(pauseTexture->GetGLTextureID());
	}

	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	delete m_Camera;

	//Release the memory of the member fields
	SafeDelete(m_pCone);
	SafeDelete(m_pCylinder);

	//Release the memory of the inherited fields
	super::Release(); 
}

//Turns the bounding object lines on and off
void AppClass::ToggleDebug() {
	for (int i = 0; i < objects.size(); i++) {
		Collider* col = objects[i]->getComponent<Collider>();
		if (col) {
			col->visible = !col->visible;
		}
	}
}

//Turns SAT on and off
void AppClass::ToggleSAT() {
	BoundingObject::doSAT = !BoundingObject::doSAT;
}