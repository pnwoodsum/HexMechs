#pragma once

#include "RE\ReEng.h"


class Ray
{
public:
	Ray(vector3, vector3);
	~Ray();

	vector3 origin;
	vector3 dir;
};

