#pragma once
#include "RE\ReEngAppClass.h"
#include "BoundingObject.h"
#include "CollisionManager.h"

using namespace ReEng;

enum ColliderType { projectile, environment, object };

class GameObject
{
	bool bGravityEnabled;
	bool bCanCollide;

	std::string instanceName;
	matrix4 matrix;
	vector3 position;
	vector3 orientation;

	ColliderType collisionType;
	BoundingObject* collider;

	CollisionManager* colMngr;
	
public:
	GameObject(std::string modelPath, std::string instName);
	~GameObject();

	void SetMatrix(matrix4 newMatrix);
	void AddOffset(vector3 delta);

	void Render();

};
