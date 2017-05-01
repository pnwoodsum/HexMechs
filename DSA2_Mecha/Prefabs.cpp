#include "Prefabs.h"

//PILLAR
//******************
Pillar::Pillar()
{
	model = new PrimitiveClass();
	model->GenerateCylinder(50.0f, 300.0f, 10, REGREEN);

	collider = new BoundingObject(model->GetVertexList(), 0);

	position = vector3(0, 0, 0);
	//collider->SetModelMatrix(glm::translate(position));

	bCanCollide = true;
	collisionType = ColliderType::environment;

	visible = true;
}

Pillar::Pillar(vector3 pos)
{
	model = new PrimitiveClass();
	model->GenerateCylinder(50.0f, 300.0f, 10, REGREEN);

	position = pos;

	collider = new BoundingObject(model->GetVertexList(), 0);
	collider->SetModelMatrix(glm::translate(position));

	bCanCollide = true;
	collisionType = ColliderType::environment;

	visible = true;
}


Pillar::~Pillar()
{
}


void Pillar::Update()
{
	if (visible = false)
		visible = true;
}
void Pillar::HandleCollision()
{
}

//******************


//DESTRUCTOBJ
//******************
DestructObj::DestructObj()
{
	model = new PrimitiveClass();
	model->GenerateCube(50.0f, REBROWN);

	collider = new BoundingObject(model->GetVertexList(), 0);

	position = vector3(0, 0, 0);
	collider->SetModelMatrix(glm::translate(position));

	bCanCollide = true;
	collisionType = ColliderType::environment;

	visible = true;
	destructible = true;
	health = 1000;
}

DestructObj::DestructObj(vector3 pos)
{
	model = new PrimitiveClass();
	model->GenerateCube(50.0f, REBROWN);

	position = pos;

	collider = new BoundingObject(model->GetVertexList(), 0);
	collider->SetModelMatrix(glm::inverse(glm::translate(pos)));

	bCanCollide = true;
	collisionType = ColliderType::environment;

	visible = true;
	destructible = true;
	health = 1000;
}


DestructObj::~DestructObj()
{
}

void DestructObj::HandleCollision()
{
	std::cout << "hit destruct" << std::endl;

	health -= 10;

	if (health <= 0) {
		visible = false;
	}
}

void DestructObj::Update()
{
}

//******************