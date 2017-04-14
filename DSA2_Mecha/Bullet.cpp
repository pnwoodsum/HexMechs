#include "Bullet.h"



Bullet::Bullet(void)
{
	bullet = new PrimitiveClass();
	bullet->GenerateSphere(5.0f, 20, RERED);

	exist = false;
}


Bullet::~Bullet()
{
}

void Bullet::fire(vector3 pos, glm::quat or) {
	bulletPos = pos;
	lastOrient = or ;

	exist = true;
}

void Bullet::move() 
{
	if (exist) {
		bulletPos += vector3(0.0f, 0.0f, 20.0f) * lastOrient;
	}
}

void Bullet::render(matrix4 projection, matrix4 view)
{
	if (exist) {
		bullet->Render(projection, view, glm::translate(-bulletPos));
	}
}
