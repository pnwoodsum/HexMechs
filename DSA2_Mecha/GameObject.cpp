#include "GameObject.h"


GameObject::GameObject(std::string modelPath, std::string instName)
{
	instanceName = instName;

	colMngr = CollisionManager::GetInstance();
	colMngr->m_pMeshMngr->LoadModel(modelPath, instanceName);
	collider = new BoundingObject(colMngr->m_pMeshMngr->GetVertexList(instanceName), 0);
	colMngr->AddObject(*collider);

	bGravityEnabled = false;
	bCanCollide = false;

	position = vector3(0, 0, 0);
	orientation = vector3(0, 0, 0);

	matrix = glm::translate(position);

	collisionType = ColliderType::object;
}

GameObject::~GameObject()
{
}

void GameObject::SetMatrix(matrix4 newMatrix) 
{
	colMngr->m_pMeshMngr->SetModelMatrix(newMatrix, instanceName);
	collider->m_v3Position = position;
	collider->SetModelMatrix(newMatrix);
}


void GameObject::AddOffset(vector3 delta)
{

}

void GameObject::Render()
{

}