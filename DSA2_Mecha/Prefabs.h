#pragma once
#include "GameObject.h"
#include "Collider.hpp"
#include "Camera.h"

class Pillar : public GameObject
{
public:
	Pillar();
	Pillar(vector3);
	~Pillar();
};

class DestructObj : public GameObject
{
public:
	int health;
	DestructObj();
	DestructObj(vector3);
	~DestructObj();
	static void HandleCollision(Collider*, Collider*);
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

	glm::quat lastOrient;
	int timer;
	float startTime;

	static void fire(vector3, glm::quat, float);
	virtual void Update(float deltaTime);

	static float lastBullet;
	static int bulletIndex;
	static std::vector<Bullet*> bulletList;
};
