#pragma once
#include "GameObject.h"
#include "Collider.hpp"
#include "Camera.h"
#include <vector>
#include <SFML\Audio.hpp>

//A parent class for all objects that should block the player
class Environment : public GameObject
{
public:
	Environment();
	~Environment();
};

//Pillar objects in the world, block player movement
class Pillar : public Environment
{
public:
	Pillar();
	Pillar(vector3);
	~Pillar();
};

//Walls in the world, block the player
class Wall : public Environment
{
public:
	Wall();
	Wall(vector3, vector3);
	~Wall();
};

//Parents class for objects that take damage
class DestructObj : public GameObject
{
public:
	int health;
	DestructObj();
	DestructObj(vector3);
	~DestructObj();
	static void HandleCollision(Collider*, Collider*);
};

//Player class, can take damage
class Player : public GameObject
{
public:
	Camera* camRef;
	int health;
	bool dead;
	Player();
	Player(Camera*);
	~Player();
	bool Update(float fDeltaTime);
	static void HandleCollision(Collider*, Collider*);
};

//Enemy class, can be destroyed.
class Enemy : public DestructObj
{
public:
	Enemy(Camera* cam);
	Enemy(vector3, Camera*);
	~Enemy();
	Camera* m_Camera;
	
	//function pointer that will be called when updating enemy target
	vector3(*RequestNextPoint)(Enemy*);

	//Default to the above that causes enemies to stay in place
	static vector3 RequestDefault(Enemy*);

	float fireRate;
	float timeAtLastFire;
	
	//movement related variables
	vector3 targetPoint;
	vector3 lastTargetPoint;
	float speed;
	float timeAtLastTargetReached;
	float distanceBetweenPoints;

	//Called to invoke RequestNextPoint and update associated vars
	void SetGoal();

	virtual void Start();
	virtual bool Update(float fDeltaTime);
	virtual bool Render(matrix4, matrix4);
};

//Variant of Enemy that lerps between a list of points
class EnemyPath : public Enemy
{
public:
	EnemyPath(Camera* cam);
	EnemyPath(vector3, Camera*);
	static vector3 RequestPath(Enemy*);
	std::vector<vector3> pathPoints;
	int pathIndex;
	bool firstPass = true;
};

//Variant of Enemy that lerps to random points in an area
class EnemyRandom : public Enemy
{
public:
	EnemyRandom(Camera* cam);
	EnemyRandom(vector3, Camera*);
	static vector3 RequestRandomInBox(Enemy*);
	vector3 boxDimmensions;
	vector3 boxCenter;
};

//Bullets within the game
class Projectile : public GameObject
{

public:
	Projectile();
	~Projectile();

	glm::quat lastOrient;
	int timer;
	float startTime;

	sf::SoundBuffer m_sbFireRocket;
	sf::Sound m_sFireRocket;
	sf::SoundBuffer m_sbRocketImpact;
	sf::Sound m_sRocketImpact;

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
