#include "Enemy.hpp"

Enemy::Enemy(void)
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_pMeshMngr->LoadModel("Sorted\\enemy.obj", "enemy");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(0, -100, 200)), "enemy");
	collider = new BoundingObject(m_pMeshMngr->GetVertexList("enemy"), 0);

	position = vector3(0, 0, 0);

	collider->SetModelMatrix(glm::translate(position));
	collisionType = ColliderType::object;
	bCanCollide = true;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	//TODO: move logic here
}
