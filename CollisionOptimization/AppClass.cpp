#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Collision Optimization"); // Window Name 

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	spatialTree = new SpatialTree();
	m_bArcBallZ = false;

	cubeCount = 150;
	radius = 15;
	cube = new PrimitiveClass();
	positions = new matrix4[cubeCount];
	bObjects = new MyBOClass[cubeCount];

	cube->GenerateCube(2, REWHITE);

	for (int i = 0; i < cubeCount; i++) {
		
		float xRot = (float)(rand() % 360);// *PI / 180;
		float yRot = (float)(rand() % 360);// *PI / 180;
		float x = radius * cos(xRot) * sin(yRot);
		float y = radius * sin(xRot) * sin(yRot);
		float z = radius * cos(yRot);

		positions[i] = glm::translate(vector3(x, z, y));

		bObjects[i] = MyBOClass(cube->GetVertexList());
		bObjects[i].SetModelMatrix(glm::translate(vector3(x, z, y)));

		spatialTree->addObject(&bObjects[i]);
	}
	
	spatialTree->generateTree(3);
	spatialTree->cleanTree(spatialTree->head);

	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 0.0f);

	m_pBOMngr = MyBOManager::GetInstance();
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("Steve"), "Steve");
	m_pBOMngr->GetBoundingObject(0)->isControlledUnit = true;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();
	ArcBallZ();

	//Object Movement
	static float fTimer = 0.0f;
	static int nClock = m_pSystem->GenClock();
	float fDeltaTime = static_cast<float>(m_pSystem->LapClock(nClock));
	fTimer += fDeltaTime;
	static vector3 v3Start = vector3(2.5f, 0.0f, 0.0f);
	static vector3 v3End = vector3(5.0, 0.0, 0.0);
	float fPercentage = MapValue(fTimer, 0.0f, 3.0f, 0.0f, 1.0f);
	m_v3O2 = glm::lerp(v3Start, v3End, fPercentage);
	matrix4 mTranslation = glm::translate(m_v3O2);

	spatialTree->checkCollisions();
	//spatialTree->displayTree(m_pMeshMngr);
	spatialTree->displayTree(m_pMeshMngr, spatialTree->head);

	m_pBOMngr->Update();//Update collision detection

						//m_pBOMngr->DisplaySphere(-1, REWHITE);
	m_pBOMngr->DisplayReAlligned();
	m_pBOMngr->DisplayOriented(-1, REWHITE);

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	if (fPercentage > 1.0f)
	{
		fTimer = 0.0f;
		std::swap(v3Start, v3End);
	}

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
										  //Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	std::vector<int> list = m_pBOMngr->GetCollidingVector(0);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->Print("Optimize:");
	m_pMeshMngr->Print(spatialTree->optimize == 0 ? "False" : "True", REYELLOW);
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->Print("Node::ColCount:");
	m_pMeshMngr->Print(std::to_string(spatialTree->head->colCount), REGREEN);
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->Print("Tree::ColCount:");
	m_pMeshMngr->Print(std::to_string(spatialTree->colCount), REGREEN);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:

	for (int i = 0; i < cubeCount; i++) {
		m_pMeshMngr->AddCubeToRenderList(positions[i]);
		//cubes[i].Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), positions[i]);
		if (bObjects[i].colliding)
			bObjects[i].DisplayReAlligned(RERED);
		else bObjects[i].DisplayReAlligned(REBLUE);
	}

	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
	MyBOManager::ReleaseInstance();
}

void AppClass::ArcBallZ(float a_fSensitivity)
{
	//If the arcball is not enabled return
	if (!m_bArcBallZ)
		return;

	//static quaternion qArcBall;
	UINT	MouseX, MouseY;		// Coordinates for the mouse

								//Calculate the position of the mouse and store it
	POINT pt;
	GetCursorPos(&pt);
	MouseX = pt.x;
	MouseY = pt.y;

	if (MouseLastX != 0 && MouseLastY != 0)
	{
		//Calculate the difference in position and update the quaternion orientation based on it
		float DeltaMouse;
		if (MouseX < MouseLastX)
		{
			DeltaMouse = static_cast<float>(MouseLastX - MouseX);
			m_qArcBall = quaternion(vector3(0.0f, 0.0f, glm::radians(a_fSensitivity * DeltaMouse))) * m_qArcBall;
		}
		else if (MouseX > MouseLastX)
		{
			DeltaMouse = static_cast<float>(MouseX - MouseLastX);
			m_qArcBall = quaternion(vector3(0.0f, 0.0f, glm::radians(-a_fSensitivity * DeltaMouse))) * m_qArcBall;
		}
	}
	SetCursorPos(MouseLastX, MouseLastY);
}