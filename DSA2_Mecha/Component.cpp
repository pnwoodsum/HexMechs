#include "Component.hpp"
#include "GameObject.h"

//Constructors
Component::Component() {
	gameObject = nullptr;
}

//Destructor
Component::~Component() {}

//Methods
GameObject* Component::getGameObject() { return gameObject; }
void Component::setGameObject(GameObject* go) {
	gameObject = go;
}
Component* Component::clone() { return new Component(); }
void Component::Start() {}
void Component::Update(float deltaTime) {}
void Component::Render() {}