#include "GameObject.h"
#include "Component.hpp"

GameObject::GameObject()
{
	components = std::vector<Component*>();
	//colMngr = CollisionManager::GetInstance();

	//collider = new BoundingObject(colMngr->m_pMeshMngr->GetVertexList(instanceName), 0);
	//colMngr->AddObject(*collider);

	bGravityEnabled = false;
	bCanCollide = false;

	position = vector3(0, 0, 0);
	orientation = vector3(0, 0, 0);

	matrix = glm::translate(position);

	collisionType = ColliderType::object;
	destructible = false;
	enemy = false;
}

GameObject::GameObject(matrix4 transform) {
	this->transform = transform;
	components = std::vector<Component*>();
	bGravityEnabled = false;
	bCanCollide = false;

	position = vector3(0, 0, 0);
	orientation = vector3(0, 0, 0);

	matrix = glm::translate(position);

	collisionType = ColliderType::object;
	destructible = false;
	enemy = false;
}

//Literally breaks everything V
/*GameObject::GameObject(const GameObject& other) {
components = std::vector<Component*>();
	int numComps = other.components.size();

	for (int i = 0; i < numComps; i++){
		Component* newComp = other.components[i]->clone();
		if (newComp){
			components.push_back(newComp);
			newComp->setGameObject(this);
			transform = other.transform;
		}
	}
}*/

GameObject::~GameObject() {}

void GameObject::addComponent(Component* component) {
	components.push_back(component);
	component->setGameObject(this);
}

void GameObject::SetMatrix(matrix4 newMatrix) 
{
	//colMngr->m_pMeshMngr->SetModelMatrix(newMatrix, instanceName);
	matrix = newMatrix;
	//collider->m_v3Position = -position;
//	collider->SetModelMatrix(newMatrix);
}


void GameObject::AddOffset(vector3 delta)
{
	position += delta;
	//collider->m_v3Position = position;
}

void GameObject::HandleCollision()
{
	if (destructible) {
		std::cout << "hit destruct" << std::endl;
		health -= 10;
		if (health <= 0) {
			visible = false;
		}
	}
}


void GameObject::Start() {
	int numComponents = components.size();
	for (int i = 0; i < numComponents; i++)
		components[i]->Start();
}

void GameObject::Update(float deltaTime) {
	int numComponents = components.size();
	for (int i = 0; i < numComponents; i++)
		components[i]->Update(deltaTime);

	if (enemy) {
		vector3 cm = m_Camera->GetPos();
		vector3 newposition = glm::lerp(position, cm, 0.1f * deltaTime);
		SetMatrix(glm::translate(newposition));
		position = newposition;
	}
}

void GameObject::Render(matrix4 projection, matrix4 view) {
	int numComponents = components.size();
	for (int i = 0; i < numComponents; i++)
		components[i]->Render();

	//if (visible)
	visible;
		model->Render(projection, view, glm::translate(position));
}
