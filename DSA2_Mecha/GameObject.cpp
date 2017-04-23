#include "GameObject.h"


GameObject::GameObject()
{
	//colMngr = CollisionManager::GetInstance();

	//collider = new BoundingObject(colMngr->m_pMeshMngr->GetVertexList(instanceName), 0);
	//colMngr->AddObject(*collider);

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
	//colMngr->m_pMeshMngr->SetModelMatrix(newMatrix, instanceName);
	matrix = newMatrix;
	collider->m_v3Position = position;
	collider->SetModelMatrix(newMatrix);
}


void GameObject::AddOffset(vector3 delta)
{
	position += delta;
	collider->m_v3Position = position;
}

void GameObject::Render(matrix4 projection, matrix4 view)
{
	if (visible)
		model->Render(projection, view, glm::translate(-position));
}

void GameObject::Update()
{
}