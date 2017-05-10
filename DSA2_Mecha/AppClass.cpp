#include "AppClass.h"

void AppClass::InitWindow(String a_sWindowName) {
	super::InitWindow("HexMechs"); // Window Name
}
void AppClass::InitVariables(void) {

	fTimer = 0.0f; //Global Timer in Seconds
	
	cockpitTexture = new TextureClass();
	cockpitTexture->LoadTexture("Cockpit.png");

	pause = false;

	//Environment Setup
	//********
	envCount = 10;
	environment = new PrimitiveClass[envCount];
	environ_Matrix = new matrix4[envCount];
	
	//create the bullets
	for (int i = 0; i < 40; i++) {
		objects.push_back(new Projectile());
	}
	
	objects.push_back(new Pillar(vector3(-600, 0, -600)));
	objects.push_back(new Pillar(vector3(-600, 0, 0)));
	objects.push_back(new Pillar(vector3(-600, 0, 600)));
	objects.push_back(new Pillar(vector3(600, 0, -600)));
	objects.push_back(new Pillar(vector3(600, 0, 0)));
	objects.push_back(new Pillar(vector3(600, 0, 600)));
	objects.push_back(new DestructObj(vector3(300, 0, 300)));
	objects.push_back(new DestructObj(vector3(200, 0, 300)));
	objects.push_back(new DestructObj(vector3(100, 0, 300)));
	//Enemy* enemy = new Enemy(vector3(400, 0, 300), m_Camera);
	//enemy->targetPoint = vector3(400, 100, 300);
	EnemyRandom* enemy = new EnemyRandom(vector3(400, 0, 300), m_Camera);
	enemy->boxCenter = vector3(0, 100, 0);
	enemy->boxDimmensions = vector3(800, 200, 800);
	objects.push_back(enemy);

	EnemyPath* enemy2 = new EnemyPath(m_Camera);
	enemy2->pathPoints.push_back(vector3(100, 0, 0));
	enemy2->pathPoints.push_back(vector3(100, 0, 100));
	enemy2->pathPoints.push_back(vector3(0, 0, 100));
	objects.push_back(enemy2);


	environment[6].GenerateCuboid(vector3(6000.f, 400.f, 30.f), REORANGE);
	environ_Matrix[6] = glm::translate(vector3(0, 0, 3000));

	environment[7].GenerateCuboid(vector3(6000.f, 400.f, 30.f), REORANGE);
	environ_Matrix[7] = glm::translate(vector3(0, 0, -3000));

	environment[8].GenerateCuboid(vector3(30.f, 400.f, 6000.f), REORANGE);
	environ_Matrix[8] = glm::translate(vector3(3000, 0, 0));

	environment[9].GenerateCuboid(vector3(30.f, 400.f, 6000.f), REORANGE);
	environ_Matrix[9] = glm::translate(vector3(-3000, 0, 0));
	
	//*******

	// Sound manager
	sManager = SoundManager::GetInstance();
	
	//Generate the Cone
	m_pCone = new PrimitiveClass();
	m_pCone->GenerateCube(70.0f, RERED);
	
	m_pPlane = new PrimitiveClass();
	m_pPlane->GeneratePlane(10000.0f, REBLUE);

	// Gun model
	m_pMeshMngr->LoadModel("Mechs\\ChainGun.fbx", "ChainGun");

	//Calculate the first projections
	m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	//Find Center of Scrren
	UINT	CenterX, CenterY;
	CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
	CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;
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
	sManager->PlaySounds();

	// Update gun matrix
	m_m4GunMat = glm::translate(-m_Camera->GetPos()) *
		glm::transpose(glm::toMat4(m_Camera->orientation)) * 
		glm::translate(IDENTITY_M4, -vector3(-8.0f,4.0f,20.0f)) * 
		ToMatrix4(glm::angleAxis(180.0f, REAXISY));

	m_pMeshMngr->SetModelMatrix(m_m4GunMat,
		"ChainGun");

	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	//m_pMeshMngr->AddInstanceToRenderList("ALL");
	m_pMeshMngr->AddInstanceToRenderList("ChainGun");

}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	m_pCameraMngr->SetProjectionMatrix(m_m4Projection);
	m_pCameraMngr->SetViewMatrix(m_m4View);

	//Render the cone
	m_pCone->Render(m_m4Projection, m_m4View, glm::translate(IDENTITY_M4, REAXISY * -65.0f));

	for (int i = 0; i < (int)objects.size(); i++) {
		objects[i]->Render(m_m4Projection, m_m4View);
	}

	for (int n = 0; n < envCount; n++) {
		environment[n].Render(m_m4Projection, m_m4View, environ_Matrix[n]);
	}

	m_pPlane->Render(m_m4Projection,m_m4View, glm::translate(IDENTITY_M4, REAXISY * -155.0f) * glm::rotate(90.0f,1.0f,0.0f,0.0f));
	
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(std::to_string(m_Camera->velocity.x) + "," + std::to_string(m_Camera->velocity.y) + "," + std::to_string(m_Camera->velocity.z));
	m_pMeshMngr->PrintLine(std::to_string(glm::length(m_Camera->velocity)));
	m_pMeshMngr->PrintLine(std::to_string(m_Camera->energy));

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->RenderTexture(cockpitTexture->GetGLTextureID());
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