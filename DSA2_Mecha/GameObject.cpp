#include "GameObject.h"
#include "Component.hpp"

GameObject::GameObject() {
	components = std::vector<Component*>();
}

GameObject::GameObject(matrix4 transform) {
	components = std::vector<Component*>();
	
	this->transform = transform;
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

void GameObject::Start() {
	for (int i = 0; i < components.size(); i++)
		components[i]->Start();
}

void GameObject::Update(float deltaTime) {
	if (!active) return;
	for (int i = 0; i < components.size(); i++)
		components[i]->Update(deltaTime);
}

void GameObject::Render(matrix4 projection, matrix4 view) {
	if (!active) return;
	for (int i = 0; i < components.size(); i++)
		components[i]->Render();

	if (visible)
		model->Render(projection, view, transform);
}

void GameObject::SetActive(bool value) {
	active = value;
	for (int i = 0; i < components.size(); i++)
		components[i]->active = value;
}