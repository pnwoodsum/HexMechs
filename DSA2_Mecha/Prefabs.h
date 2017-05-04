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
	Enemy(Camera* cam);
	Enemy(vector3, Camera*);
	~Enemy();
	Camera* m_Camera;

	virtual void Update(float fDeltaTime);
	static void HandleCollision(Collider*, Collider*);
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
	static void HandleCollision(Collider*, Collider*);

	const static float BULLET_SPEED;
	const static float FIRE_RATE;
	static float lastBullet;
	static int bulletIndex;
	static std::vector<Bullet*> bulletList;
};
