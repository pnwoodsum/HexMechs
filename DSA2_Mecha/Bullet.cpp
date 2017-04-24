#include "Bullet.h"


Bullet::Bullet(void)
{
	model = new PrimitiveClass();
	model->GenerateSphere(5.0f, 20, RERED);

	collider = new BoundingObject(model->GetVertexList(), 0);

	bCanCollide = true;
	collisionType = ColliderType::projectile;

	visible = true;
}


Bullet::~Bullet()
{
}

void Bullet::fire(vector3 pos, glm::quat or) {
	position = pos - vector3(45.0f, -22.0f, -220.0f) * or;

	//bulletPos = pos - (vector3(0.0f,0.0f,2.0f) * or);
	lastOrient = or ;

	visible = true;
}

void Bullet::Update() 
{
	if (visible) {
		position += vector3(0.0f, 0.0f, 20.0f) * lastOrient;
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
