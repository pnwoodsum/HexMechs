#pragma once
#include "RE\ReEngAppClass.h"

class Bullet
{
public:
	Bullet(void);
	~Bullet();

	PrimitiveClass* bullet = nullptr;
	vector3 bulletPos;
	glm::quat lastOrient;

	void move();
	void render(matrix4, matrix4);
	void fire(vector3, glm::quat);

	bool exist;
};

