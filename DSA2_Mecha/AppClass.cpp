#include "AppClass.h"
#include "Camera.h"
#include "GameObject.h"
#include "iostream"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("DSA2 Game"); // Window Name
}
void AppClass::InitVariables(void)
{
	//Environment Setup
	//********

	envCount = 10;
	environment = new PrimitiveClass[envCount];
	environ_Matrix = new matrix4[envCount];

	environment[0].GenerateCylinder(50.0f, 300.0f, 10, REGREEN);
	environ_Matrix[0] = glm::translate(vector3(-200, 0, -200));

	environment[1].GenerateCylinder(50.0f, 300.0f, 10, REGREEN);
	environ_Matrix[1] = glm::translate(vector3(-200, 0, -0));

	environment[2].GenerateCylinder(50.0f, 300.0f, 10, REGREEN);
	environ_Matrix[2] = glm::translate(vector3(-200, 0, 200));

	environment[3].GenerateCylinder(50.0f, 300.0f, 10, REGREEN);
	environ_Matrix[3] = glm::translate(vector3(200, 0, -200));

	environment[4].GenerateCylinder(50.0f, 300.0f, 10, REGREEN);
	environ_Matrix[4] = glm::translate(vector3(200, 0, 0));

	environment[5].GenerateCylinder(50.0f, 300.0f, 10, REGREEN);
	environ_Matrix[5] = glm::translate(vector3(200, 0, 200));

	environment[6].GenerateCuboid(vector3(2000.f, 400.f, 30.f), REORANGE);
	environ_Matrix[6] = glm::translate(vector3(0, 0, 1000));

	environment[7].GenerateCuboid(vector3(2000.f, 400.f, 30.f), REORANGE);
	environ_Matrix[7] = glm::translate(vector3(0, 0, -1000));

	environment[8].GenerateCuboid(vector3(30.f, 400.f, 2000.f), REORANGE);
	environ_Matrix[8] = glm::translate(vector3(1000, 0, 0));

	environment[9].GenerateCuboid(vector3(30.f, 400.f, 2000.f), REORANGE);
	environ_Matrix[9] = glm::translate(vector3(-1000, 0, 0));
	
	//*******


	//Generate the Cone
	m_pCone = new PrimitiveClass();
	m_pCone->GenerateCube(70.0f, RERED);

	m_pPlane = new PrimitiveClass();
	m_pPlane->GeneratePlane(10000.0f, REBLUE);

	//Static Cylinder that representsa gun, I guess...
	m_pCylinder2 = new PrimitiveClass();
	m_pCylinder2->GenerateCylinder(5.0f, 25.0f, 12, REORANGE);

	//Calculate the first projections
	m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	//Find Center of Scrren
	UINT	CenterX, CenterY;
	CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
	CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;

	
	//Create Object Pool for Bullets
	for (int i = 0; i < 50; i++) {
		bullets.push_back(Bullet());
	}

}


void AppClass::Update(void)
{
	//Do Bullet Stuff
	if (!bullets.empty()) {
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i].move();
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



	m_pMeshMngr->PrintLine("");

	m_pMeshMngr->PrintLine(std::to_string(m_Camera->x) + "," + std::to_string(m_Camera->y));
	m_pMeshMngr->PrintLine(std::to_string(dis.x) + "," + std::to_string(dis.y));

	ArcBall();

	//Camera
	m_m4Projection = m_Camera->GetProjection(false);
	m_m4View = m_Camera->GetView(mousePos);

	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	
	//Render the grid
	m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY);

	//Render the cone
	m_pCone->Render(m_m4Projection, m_m4View, glm::translate(IDENTITY_M4, REAXISY * -65.0f));

	m_pCylinder2->Render(m_m4Projection, m_m4View, glm::translate(-m_Camera->GetPos()) * glm::transpose(glm::toMat4(m_Camera->orientation)) * glm::translate(IDENTITY_M4, -vector3(-20.0f,10.0f,40.0f)) * glm::rotate(95.0f,1.0f,0.0f,0.0f));

	if (!bullets.empty()) {
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i].render(m_m4Projection, m_m4View);
		}
	}

	for (int n = 0; n < envCount; n++)
	{
		environment[n].Render(m_m4Projection, m_m4View, environ_Matrix[n]);
	}

	m_pPlane->Render(m_m4Projection,m_m4View, glm::translate(IDENTITY_M4, REAXISY * -100.0f) * glm::rotate(90.0f,1.0f,0.0f,0.0f));

	m_pMeshMngr->Render(); //renders the render list
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