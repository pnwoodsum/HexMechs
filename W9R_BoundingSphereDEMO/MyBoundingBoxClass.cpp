#include "MyBoundingBoxClass.h"

MyBoundingBoxClass::MyBoundingBoxClass(std::vector<vector3> vertexList)
{
	m_bColliding = false;
	m_fRadius = 0.0f;
	m_v3CenterGlobal = vector3(0.0f);

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

	//m_v3SizeG = m_v3MaxG - m_v3MinG;
	
	//m_v3Size.x = glm::distance(vector3(m_v3Min.x, 0.0, 0.0), vector3(m_v3Max.x, 0.0, 0.0));
	//m_v3Size.y = glm::distance(vector3(0.0, m_v3Min.y, 0.0), vector3(0.0, m_v3Max.y, 0.0));
	//m_v3Size.z = glm::distance(vector3(0.0, 0.0, m_v3Min.z), vector3(0.0, 0.0, m_v3Max.z));
}

void MyBoundingBoxClass::RenderSphere()
{
	vector3 v3Color = REGREEN;
	if (true == m_bColliding)
		v3Color = RERED;

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
		REBLUE, WIRE);

}
void MyBoundingBoxClass::SetModelMatrix(matrix4 a_m4ToWorld)
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
		else if (p_v3Max.x < points[i].x)
		{
			p_v3Max.x = pointsG[i].x;
		}

		if (p_v3Min.y > pointsG[i].y)
		{
			p_v3Min.y = pointsG[i].y;
		}
		else if (p_v3Max.y < pointsG[i].y)
		{
			p_v3Max.y = pointsG[i].y;
		}

		if (p_v3Min.z > pointsG[i].z)
		{
			p_v3Min.z = pointsG[i].z;
		}
		else if (p_v3Max.z < points[i].z)
		{
			p_v3Max.z = points[i].z;
		}
	}

	p_v3Size = p_v3Max - p_v3Min;
}

bool MyBoundingBoxClass::IsColliding(MyBoundingBoxClass* a_other)
{
	if (this->m_v3MaxG.x < a_other->m_v3MinG.x)
		return false;
	if (this->m_v3MinG.x > a_other->m_v3MaxG.x)
		return false;

	if (this->m_v3MaxG.y < a_other->m_v3MinG.y)
		return false;
	if (this->m_v3MinG.y > a_other->m_v3MaxG.y)
		return false;

	if (this->m_v3MaxG.z < a_other->m_v3MinG.z)
		return false;
	if (this->m_v3MinG.z > a_other->m_v3MaxG.z)
		return false;

	return true;
}

void MyBoundingBoxClass::SetColliding(bool input) { m_bColliding = input; }
void MyBoundingBoxClass::SetCenterLocal(vector3 input) { m_v3CenterLocal = input; }
void MyBoundingBoxClass::SetCenterGlobal(vector3 input) { m_v3CenterGlobal = input; }
void MyBoundingBoxClass::SetRadius(float input) { m_fRadius = input; }
bool MyBoundingBoxClass::GetColliding(void) { return m_bColliding; }
vector3 MyBoundingBoxClass::GetCenterLocal(void) { return m_v3CenterLocal; }
vector3 MyBoundingBoxClass::GetCenterGlobal(void) { return m_v3CenterGlobal; }
float MyBoundingBoxClass::GetRadius(void) { return m_fRadius; }
matrix4 MyBoundingBoxClass::GetModelMatrix(void) { return m_m4ToWorld; }