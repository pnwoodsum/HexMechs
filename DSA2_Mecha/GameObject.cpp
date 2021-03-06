#include "GameObject.h"
#include "Component.hpp"

float GameObject::time = 0;

GameObject::GameObject() {
	components = std::vector<Component*>();
}

GameObject::GameObject(matrix4 transform) {
	components = std::vector<Component*>();
	
	this->transform = transform;
}

GameObject::GameObject(const GameObject& other) {
	components = std::vector<Component*>();
	int numComps = other.components.size();

	//copy over the components and update their gameobject reference
	for (int i = 0; i < numComps; i++){
		Component* newComp = other.components[i]->clone();
		if (newComp){
			components.push_back(newComp);
			newComp->setGameObject(this);
			transform = other.transform;
		}
	}
}

GameObject::~GameObject() {}

void GameObject::addComponent(Component* component) {
	components.push_back(component);
	component->setGameObject(this);
}

void GameObject::Start() {
	for (int i = 0; i < (int)components.size(); i++)
		components[i]->Start();
}

bool GameObject::Update(float deltaTime) {
	//early return if not active
	//returning bools lets child classes also early return
	if (!active) return false;

	//update all components as well
	for (int i = 0; i < (int)components.size(); i++)
		components[i]->Update(deltaTime);
	return true;
}

bool GameObject::Render(matrix4 projection, matrix4 view) {
	if (!active || !visible) return false;
	for (int i = 0; i < (int)components.size(); i++) {
		if(components[i]->visible)
			components[i]->Render();
	}

	//render the primitive if it was set
	if (model)
		model->Render(projection, view, transform);
	return true;
}

void GameObject::SetActive(bool value) {
	active = value;

	//update all components
	for (int i = 0; i < (int)components.size(); i++)
		components[i]->active = value;
}