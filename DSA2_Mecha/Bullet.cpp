#include "Bullet.h"


Bullet::Bullet(void)
{
	model = new PrimitiveClass();
	model->GenerateSphere(5.0f, 20, RERED);

	collider = new BoundingObject(model->GetVertexList(), 0);

	bCanCollide = true;
	collisionType = ColliderType::projectile;

	visible = false;
	//timer = 0;
}


Bullet::~Bullet()
{
}

void Bullet::fire(vector3 pos, glm::quat or, float time) {
	position = pos - vector3(45.0f, -22.0f, -220.0f) * or;
	collider->SetModelMatrix(glm::inverse(glm::translate(position)));
	collider->orientation = or;

	//bulletPos = pos - (vector3(0.0f,0.0f,2.0f) * or);
	lastOrient = or ;
	//timer = 0;
	startTime = time;

	visible = true;
}

void Bullet::Update(float time) 
{
	if (visible) {
		position += vector3(0.0f, 0.0f, 20.0f) * lastOrient;
		collider->Update();
		//timer++;

		if(time - startTime > 2) visible = false;
		//if (timer > 100) visible = false;
		//collider->SetModelMatrix(glm::translate(position));
		//bulletPos += vector3(0.0f, 0.0f, 20.0f) * lastOrient;
	}
}
/*
void Bullet::render(matrix4 projection, matrix4 view)
{
	if (exist) {
		bullet->Render(projection, view, glm::translate(-bulletPos));
	}
}
*/
