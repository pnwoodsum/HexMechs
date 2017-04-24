#pragma once
#include "RE\ReEngAppClass.h"
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(void);
	~Enemy();
	glm::quat lastOrient;
	void Update() override;
private:
	MeshManagerSingleton* m_pMeshMngr = nullptr;//Mesh Manager
};


