#pragma once
class Component;
#include "RE\ReEngAppClass.h"
//#include "BoundingObject.h"
#include "Camera.h"
#include <vector>
#include "Object.hpp"

using namespace ReEng;

enum ColliderType { projectile, environment, object };

class GameObject : public Object {
public:
	bool bGravityEnabled;
	bool bCanCollide;
	bool visible = true;
	bool destructible;
	bool enemy;
	Camera* m_Camera;

	std::string instanceName;
	matrix4 matrix;
	vector3 position;
	vector3 orientation;

	ColliderType collisionType;
	//BoundingObject* collider;

	PrimitiveClass* model = nullptr;
	int health;

	matrix4 transform;
	std::vector<Component*> components;
	
	GameObject();
	GameObject(matrix4 transform);
	//breaks everything V
	//GameObject(const GameObject& other);
	~GameObject();
	
	template<class T>
	T* getComponent() {
		for (unsigned int i = 0; i < components.size(); i++) {
			T* type = dynamic_cast<T*>(components[i]);
			if (type)
				return type;
		}
		return nullptr;
	}

	void addComponent(Component* component);

	void SetMatrix(matrix4);
	void AddOffset(vector3);
	//virtual void HandleCollision();

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Render(matrix4, matrix4);
};