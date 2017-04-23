#pragma once
#include "GameObject.h"

class Pillar : public GameObject
{
public:
	Pillar();
	Pillar(vector3);
	~Pillar();
	void Update() override;
};

