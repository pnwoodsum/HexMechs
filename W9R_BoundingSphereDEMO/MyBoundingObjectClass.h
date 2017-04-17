#pragma once
#include "RE\ReEng.h"

class MyBoundingObjectClass
{
	
public:
	MyBoundingObjectClass();
	~MyBoundingObjectClass();

	void SetMatrix(matrix4 newMatrix);
	matrix4 GetMatrix();
	void SetVisibility(bool visibility);
	vector3 GetCentroid();
	vector3 GetMinimum();
	vector3 GetMaximum();
	void SetColor(vector3 newColor);
	bool CheckCollision(MyBoundingObjectClass other);

	void Render();
};

