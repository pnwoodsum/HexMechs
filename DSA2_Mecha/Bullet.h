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
	int timer;
	float startTime;

	//void move();
	//void render(matrix4, matrix4);
	void fire(vector3, glm::quat,float);

	void Update(float);

	//bool exist;
};

