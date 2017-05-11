#pragma once
//Component and Gameobject ref eachother, 
//forward declaration avoids inf loop
class Component;
#include "RE\ReEngAppClass.h"
#include "Camera.h"
#include <vector>
#include "Object.hpp"

using namespace ReEng;

class GameObject : public Object {
public:
	//Time since the start of the game
	static float time;
	
	Camera* m_Camera;
	MeshManagerSingleton* m_pMeshMngr = MeshManagerSingleton::GetInstance();

	//TODO: should handle both primitives and loaded models
	PrimitiveClass* model = nullptr;

	//holds all position, rotation, and scale
	matrix4 transform;
	std::vector<Component*> components;
	
	GameObject();
	GameObject(matrix4 transform);
	GameObject(const GameObject& other);
	~GameObject();
	
	//provides accessor for getting components by type
	//NOTE: only gets first of type
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

	virtual void Start();
	virtual bool Update(float deltaTime);
	virtual bool Render(matrix4, matrix4);
	void SetActive(bool);
};