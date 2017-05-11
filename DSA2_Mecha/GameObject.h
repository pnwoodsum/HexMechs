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
	static float time;
	bool bGravityEnabled;
	
	Camera* m_Camera;
	MeshManagerSingleton* m_pMeshMngr = MeshManagerSingleton::GetInstance();

	std::string instanceName;

	//TODO: should handle both primitives and loaded models
	PrimitiveClass* model = nullptr;

	matrix4 transform;
	std::vector<Component*> components;
	
	GameObject();
	GameObject(matrix4 transform);
	GameObject(const GameObject& other);
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

	virtual void Start();
	virtual bool Update(float deltaTime);
	virtual bool Render(matrix4, matrix4);
	void SetActive(bool);
};