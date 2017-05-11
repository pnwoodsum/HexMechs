#pragma once
#include "RE\ReEng.h"
#include "Collider.hpp"

class BoundingObject : public Collider
{
private:
	float m_fRadius = 0.0f; //radius of the sphere
	vector3 m_v3CenterLocal = vector3(0.0f); //center of the sphere in local space
	
	matrix4 m_m4ToWorld = IDENTITY_M4; //matrix that takes you from local to global space
	MeshManagerSingleton* m_pMeshMngr = nullptr; //for drawing the sphere

	vector3 m_v3Max;
	vector3 m_v3Min;
	vector3 m_v3Size;

	vector3 m_v3MaxG;
	vector3 m_v3MinG;
	vector3 m_v3SizeG;

	vector3 p_v3Size;

	vector3 one;
	vector3 two;
	vector3 three;
	vector3 four;
	vector3 five;
	vector3 six;
	vector3 seven;
	vector3 eight;

	std::vector<vector3> points;
	std::vector<vector3> pointsG;

public:
	static bool doSAT;
	vector3 m_v3CenterGlobal = vector3(0.0f); //center of the sphere in global space
	virtual void subUpdate();
	//virtual void Update(float);
	virtual void Render();
	virtual void testCollision(Collider* other);

	bool m_bColliding = false;
	vector3 v3Color;

	BoundingObject(std::vector<vector3> vertexList, int objectType);
	~BoundingObject();

	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides
	bool SAT(BoundingObject* const a_pOther);
	/*
	Sets Colliding
	*/
	void SetColliding(bool input);
	/*
	Sets Center of the sphere in local space
	*/
	void SetCenterLocal(vector3 input);
	/*
	Sets Center of the sphere in global space
	*/
	void SetCenterGlobal(vector3 input);
	/*
	Sets the radius of the sphere
	*/
	void SetRadius(float input);

	//Sets Color
	void SetColor(vector3 gem);

	/*
	Gets Colliding
	*/
	bool GetColliding(void);
	/*
	Gets center of the sphere in local space
	*/
	vector3 GetCenterLocal(void);
	/*
	Gets center of the sphere in global space
	*/
	vector3 GetCenterGlobal(void);
	/*
	Gets model to world matrix of the sphere
	*/
	matrix4 GetModelMatrix(void);
	/*
	Gets radius of the sphere
	*/
	float GetRadius(void);
	/*
	Renders the sphere based on the radius and the center in global space
	*/
	//void RenderBO();
	/*
	Sets the transform from the local to world matrix
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);

	/*
	Will check the collision with another object
	*/
	bool IsColliding(BoundingObject* a_other, bool isProjectile = false);
	/*
	Will check the collision with a ray(position and direction)
	*/
	bool IsCollidingRay(vector3, vector3);

	/*
	Sets the type of bounding object
	0 = box;
	1 = sphere;
	*/
	int m_iBoundingObjectType;

	vector3 m_v3Position;
	vector3 p_v3Max;
	vector3 p_v3Min;
	glm::quat orientation;
};

