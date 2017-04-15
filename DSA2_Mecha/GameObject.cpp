#include "GameObject.h"



GameObject::GameObject()
{
	bGravityEnabled = false;
	bCanCollide = false;

	shape = new PrimitiveClass();
	shape->GenerateCube(75.0f, REYELLOW);

	position = vector3(0, 0, 0);
	orientation = vector3(0, 0, 0);

	matrix = glm::translate(position);

	collisionType = ColliderType::environment;
}


GameObject::~GameObject()
{
}


void GameObject::AddOffset(vector3 delta)
{

}