#pragma once
#include "GameObject.h"

class Pillar : public GameObject
{
public:
	Pillar();
	Pillar(vector3);
	~Pillar();
	void Update() override;
	void HandleCollision() override;
};

class DestructObj : public GameObject
{
public:
	int health;
	DestructObj();
	DestructObj(vector3);
	~DestructObj();
	void Update() override;
	void HandleCollision() override;
};

