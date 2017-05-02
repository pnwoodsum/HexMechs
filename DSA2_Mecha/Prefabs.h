#pragma once
#include "GameObject.h"
#include "Camera.h"

class Pillar : public GameObject
{
public:
	Pillar();
	Pillar(vector3);
	~Pillar();
	void Update(float fDeltaTime) override;
	//void HandleCollision() override;
};

class DestructObj : public GameObject
{
public:
	int health;
	DestructObj();
	DestructObj(vector3);
	~DestructObj();
	//void Update(float fDeltaTime) override;
	static void HandleCollision(void* ptr);
};

class Enemy : public DestructObj
{
public:
	int health;
	Enemy(Camera* cam);
	Enemy(Camera* cam, vector3);
	~Enemy();
	//Camera* m_Camera;

	//virtual void Update(float fDeltaTime) override;
	//virtual void HandleCollision() override;
};

class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	//PrimitiveClass* bullet = nullptr;
	//vector3 bulletPos;
	glm::quat lastOrient;
	int timer;
	float startTime;

	//void move();
	//virtual void Render(matrix4, matrix4);
	static void fire(vector3, glm::quat, float);
	//static void HandleCollision(void* ptr);

	virtual void Update(float deltaTime);

	//bool exist;
	static float lastBullet;
	static int bulletIndex;
	static std::vector<Bullet*> bulletList;
};
