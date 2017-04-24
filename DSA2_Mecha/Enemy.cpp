#include "Enemy.hpp"

Enemy::Enemy(void)
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_pMeshMngr->LoadModel("Sorted\\enemy.obj", "enemy");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(0, -100, 200)), "enemy");
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	//TODO: move logic here
}
