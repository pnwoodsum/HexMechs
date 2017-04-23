#pragma once
#include "RE\ReEngAppClass.h"
#include "BoundingObject.h"

using namespace ReEng;

enum ColliderType { projectile, environment, object };

class GameObject
{

public:
	bool bGravityEnabled;
	bool bCanCollide;
	bool visible;

	std::string instanceName;
	matrix4 matrix;
	vector3 position;
	vector3 orientation;

	ColliderType collisionType;
	BoundingObject* collider;

	PrimitiveClass* model = nullptr;

	
public:
	GameObject();
	~GameObject();

	void SetMatrix(matrix4);
	void AddOffset(vector3);

	void Render(matrix4, matrix4 );
	virtual void Update();

};
