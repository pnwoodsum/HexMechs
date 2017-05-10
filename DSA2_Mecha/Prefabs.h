#pragma once
#include "GameObject.h"
#include "Collider.hpp"
#include "Camera.h"
#include <vector>

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
	
	vector3(*RequestNextPoint)(Enemy*);
	static vector3 RequestDefault(Enemy*);

	float fireRate;
	float timeAtLastFire;
	
	//movement related variables
	vector3 targetPoint;
	vector3 lastTargetPoint;
	float speed;
	float timeAtLastTargetReached;
	float distanceBetweenPoints;

	void SetGoal();

	virtual void Start();
	virtual bool Update(float fDeltaTime);
	virtual bool Render(matrix4, matrix4);
};
class EnemyPath : public Enemy
{
public:
	EnemyPath(Camera* cam);
	EnemyPath(vector3, Camera*);
	static vector3 RequestPath(Enemy*);
	std::vector<vector3> pathPoints;
	int pathIndex;
};
class EnemyRandom : public Enemy
{
public:
	EnemyRandom(Camera* cam);
	EnemyRandom(vector3, Camera*);
	static vector3 RequestRandomInBox(Enemy*);
	vector3 boxDimmensions;
	vector3 boxCenter;
};
class Projectile : public GameObject
{
public:
	Projectile();
	~Projectile();

	glm::quat lastOrient;
	int timer;
	float startTime;

	static void fire(vector3, glm::quat, float);
	virtual bool Update(float deltaTime);
	virtual bool Render(matrix4, matrix4);
	static void HandleCollision(Collider*, Collider*);

	const static float BULLET_SPEED;
	const static float FIRE_RATE;
	static float lastBullet;
	static int bulletIndex;
	static std::vector<Projectile*> bulletList;
};
