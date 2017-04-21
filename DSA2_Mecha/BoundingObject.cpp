#include "BoundingObject.h"


BoundingObject::BoundingObject(std::vector<vector3> vertexList, int objectType)
{
	m_iBoundingObjectType = 0;
	m_bColliding = false;
	m_fRadius = 0.0f;
	m_v3CenterGlobal = vector3(0.0f);
	v3Color = REBLUE;

	if (vertexList.size() < 1)
		return;

	m_v3Min = vertexList[0];
	m_v3Max = vertexList[0];

	for (int i = 1; i < vertexList.size(); i++)
	{
		if (m_v3Min.x > vertexList[i].x)
		{
			m_v3Min.x = vertexList[i].x;
		}
		else if (m_v3Max.x < vertexList[i].x)
		{
			m_v3Max.x = vertexList[i].x;
		}

		if (m_v3Min.y > vertexList[i].y)
		{
			m_v3Min.y = vertexList[i].y;
		}
		else if (m_v3Max.y < vertexList[i].y)
		{
			m_v3Max.y = vertexList[i].y;
		}

		if (m_v3Min.z > vertexList[i].z)
		{
			m_v3Min.z = vertexList[i].z;
		}
		else if (m_v3Max.z < vertexList[i].z)
		{
			m_v3Max.z = vertexList[i].z;
		}
	}

	m_v3CenterLocal = m_v3CenterGlobal = (m_v3Max + m_v3Min) / 2.0f;
	m_fRadius = glm::distance(m_v3CenterGlobal, m_v3Max);
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_v3Size = m_v3Max - m_v3Min;

	m_v3MinG = m_v3Min;
	m_v3MaxG = m_v3Max;

	p_v3Min = m_v3Min;
	p_v3Max = m_v3Max;

	one = vector3(m_v3Max.x, m_v3Max.y, m_v3Max.z);
	two = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	three = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	four = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);

	five = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);
	six = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	seven = vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z);
	eight = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);

	points.push_back(one);
	points.push_back(two);
	points.push_back(three);
	points.push_back(four);

	points.push_back(five);
	points.push_back(six);
	points.push_back(seven);
	points.push_back(eight);

	pointsG.push_back(one);
	pointsG.push_back(two);
	pointsG.push_back(three);
	pointsG.push_back(four);

	pointsG.push_back(five);
	pointsG.push_back(six);
	pointsG.push_back(seven);
	pointsG.push_back(eight);
}

void BoundingObject::SetColor(vector3 vidya) {

	v3Color = vidya;
}

void BoundingObject::RenderBO()
{
	if (m_iBoundingObjectType > 3) {
		m_iBoundingObjectType = 0;
	}
	if (m_iBoundingObjectType == 0 || m_iBoundingObjectType == 2) {
		m_pMeshMngr->AddCubeToRenderList(
			m_m4ToWorld *
			glm::translate(m_v3CenterLocal) *
			glm::scale(m_v3Size),
			v3Color, WIRE);

		m_pMeshMngr->AddLineToRenderList(p_v3Max, p_v3Min, RERED, RERED);

		m_pMeshMngr->AddCubeToRenderList(
			glm::translate(m_v3Position) *
			m_m4ToWorld *
			glm::translate(m_v3CenterLocal) *
			glm::inverse(m_m4ToWorld) *
			glm::scale(p_v3Size),
			v3Color, WIRE);
	}

	if (m_iBoundingObjectType == 1 || m_iBoundingObjectType == 2) {
		m_pMeshMngr->AddSphereToRenderList(
			glm::translate(m_v3CenterGlobal) *
			glm::scale(vector3(m_fRadius) * 2.0f), v3Color, WIRE);
	}

	// else, don't render
}

void BoundingObject::SetModelMatrix(matrix4 a_m4ToWorld)
{
	if (m_m4ToWorld == a_m4ToWorld)
		return;
	m_pMeshMngr->RenderTexture(1);
	m_m4ToWorld = a_m4ToWorld;
	m_v3CenterGlobal = vector3(m_m4ToWorld * vector4(m_v3CenterLocal, 1.0f));
	m_v3MinG = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	m_v3MaxG = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	//m_v3SizeG = m_v3MaxG - m_v3MinG;
	p_v3Min = vector3(10000000.0f, 10000000.0f, 10000000.0f);
	p_v3Max = vector3(-10000000.0f, -10000000.0f, -10000000.0f);

	for (int i = 0; i < points.size(); i++) {
		pointsG[i] = vector3(m_m4ToWorld * vector4(points[i], 1.0f));
	}

	for (int i = 0; i < pointsG.size(); i++) {
		if (p_v3Min.x > pointsG[i].x)
		{
			p_v3Min.x = pointsG[i].x;
		}
		if (p_v3Max.x < pointsG[i].x)
		{
			p_v3Max.x = pointsG[i].x;
		}

		if (p_v3Min.y > pointsG[i].y)
		{
			p_v3Min.y = pointsG[i].y;
		}
		if (p_v3Max.y < pointsG[i].y)
		{
			p_v3Max.y = pointsG[i].y;
		}

		if (p_v3Min.z > pointsG[i].z)
		{
			p_v3Min.z = pointsG[i].z;
		}
		if (p_v3Max.z < pointsG[i].z)
		{
			p_v3Max.z = pointsG[i].z;
		}
	}

	p_v3Size = p_v3Max - p_v3Min;
}

bool BoundingObject::IsColliding(BoundingObject* a_other)
{
	float fDistance = glm::distance(m_v3CenterGlobal, a_other->m_v3CenterGlobal);
	float fRadiiSum = m_fRadius + a_other->m_fRadius;
	if (fDistance > fRadiiSum) {
		return false;
	}
	else {
		if (p_v3Max.x < a_other->p_v3Min.x)
			return false;
		if (p_v3Min.x > a_other->p_v3Max.x)
			return false;

		if (p_v3Max.y < a_other->p_v3Min.y)
			return false;
		if (p_v3Min.y > a_other->p_v3Max.y)
			return false;

		if (p_v3Max.z < a_other->p_v3Min.z)
			return false;
		if (p_v3Min.z > a_other->p_v3Max.z)
			return false;

		return true;
	}
}

void BoundingObject::SetColliding(bool input) { m_bColliding = input; }
void BoundingObject::SetCenterLocal(vector3 input) { m_v3CenterLocal = input; }
void BoundingObject::SetCenterGlobal(vector3 input) { m_v3CenterGlobal = input; }
void BoundingObject::SetRadius(float input) { m_fRadius = input; }
bool BoundingObject::GetColliding(void) { return m_bColliding; }
vector3 BoundingObject::GetCenterLocal(void) { return m_v3CenterLocal; }
vector3 BoundingObject::GetCenterGlobal(void) { return m_v3CenterGlobal; }
float BoundingObject::GetRadius(void) { return m_fRadius; }
matrix4 BoundingObject::GetModelMatrix(void) { return m_m4ToWorld; }

BoundingObject::~BoundingObject()
{
}