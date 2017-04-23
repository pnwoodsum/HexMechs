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
	//collider->SetModelMatrix(glm::translate(position));

	collider = new BoundingObject(model->GetVertexList(), 0);

	bCanCollide = true;
	collisionType = ColliderType::environment;

	visible = true;
}


Pillar::~Pillar()
{
}


void Pillar::Update()
{
	if(visible = false)
		visible = true;
}

//******************