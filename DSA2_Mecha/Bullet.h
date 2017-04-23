#pragma once
#include "RE\ReEngAppClass.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(void);
	~Bullet();

	//PrimitiveClass* bullet = nullptr;
	//vector3 bulletPos;
	glm::quat lastOrient;

	//void move();
	//void render(matrix4, matrix4);
	void fire(vector3, glm::quat);

	void Update() override;

	//bool exist;
};

