#pragma once
#include "RE\ReEngAppClass.h"
#include "Collider.h"

enum ColliderType { projectile, environment, object };

class GameObject
{
	bool bGravityEnabled;
	bool bCanCollide;

	PrimitiveClass* shape;
	matrix4 matrix;
	vector3 position;
	vector3 orientation;

	ColliderType collisionType;
	Collider collider;
	
public:
	GameObject();
	~GameObject();

	void AddOffset(vector3 delta);

};
