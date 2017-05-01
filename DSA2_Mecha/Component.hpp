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
	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Render();

private:
	GameObject *gameObject;
};