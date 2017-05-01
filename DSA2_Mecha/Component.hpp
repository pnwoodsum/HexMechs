#pragma once
class GameObject;
#include "Object.hpp"

class Component : public Object {
public:
	//Constructors
	Component();

	//Destructor
	~Component();

	//Methods
	GameObject* getGameObject();
	void setGameObject(GameObject* gameobject);
	virtual Component* clone();
	virtual void start();
	virtual void update(float deltaTime);
	virtual void render();

private:
	GameObject *gameObject;
};