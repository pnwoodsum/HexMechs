#include "BoundingObject.h"


BoundingObject::BoundingObject(std::vector<vector3> vertexList, int objectType)
{
	ColliderCollection.push_back(this);
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
	m_v3HalfWidth = (m_v3Max - m_v3Min) / 2.0f;
}

void BoundingObject::SetColor(vector3 vidya) {

	v3Color = vidya;
}

void BoundingObject::Render() {
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
	m_v3HalfWidth = (m_v3Max - m_v3Min) / 2.0f;
}

bool BoundingObject::IsColliding(BoundingObject* a_other, bool isProjectile)
{

	float fDistance = glm::distance(m_v3CenterGlobal, a_other->m_v3CenterGlobal);
	float fRadiiSum = m_fRadius + a_other->m_fRadius;
	//Bounding Spheres
	if (fDistance > fRadiiSum) {
		return false;
	}

	//Realigned
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

	//SAT
	return SAT(a_other);
}

bool BoundingObject::SAT(BoundingObject* const a_pOther)
{
	
	// Get the information of this object
	vector3 v3CenterGlobalA = GetCenterGlobal();
	matrix4 mToWorldA = GetModelMatrix();
	vector3 v3RotationA[3];
	v3RotationA[0] = vector3(mToWorldA[0][0], mToWorldA[0][1], mToWorldA[0][2]);
	v3RotationA[1] = vector3(mToWorldA[1][0], mToWorldA[1][1], mToWorldA[1][2]);
	v3RotationA[2] = vector3(mToWorldA[2][0], mToWorldA[2][1], mToWorldA[2][2]);

	//Get the information of the other object
	vector3 v3CenterGlobalB = a_pOther->GetCenterGlobal();
	matrix4 mToWorldB = a_pOther->GetModelMatrix();
	vector3 v3RotationB[3];
	v3RotationB[0] = vector3(mToWorldB[0][0], mToWorldB[0][1], mToWorldB[0][2]);
	v3RotationB[1] = vector3(mToWorldB[1][0], mToWorldB[1][1], mToWorldB[1][2]);
	v3RotationB[2] = vector3(mToWorldB[2][0], mToWorldB[2][1], mToWorldB[2][2]);

	float fCenterAToMiddle, fCenterBToMiddle;
	glm::mat3 m3Rotation, m3RotationAbs;

	// Compute rotation matrix expressing b in a's coordinate frame
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m3Rotation[i][j] = glm::dot(v3RotationA[i], v3RotationB[j]);

	// Compute translation vector v3Distance (this is the distance between both centers)
	vector3 v3Distance = v3CenterGlobalB - v3CenterGlobalA; //distance in global space
															// Bring translation into a's coordinate frame
	v3Distance = vector3(glm::dot(v3Distance, v3RotationA[0]), glm::dot(v3Distance, v3RotationA[1]), glm::dot(v3Distance, v3RotationA[2])); //distance in A's local
																																			// their cross product is (near) null (see the orange book for details)
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m3RotationAbs[i][j] = std::abs(m3Rotation[i][j]) + 0.0001f;

	// Test axes L = AX <- 0
	fCenterAToMiddle = m_v3HalfWidth.x;
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[0][0] + a_pOther->m_v3HalfWidth.y * m3RotationAbs[0][1] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[0][2];
	if (std::abs(v3Distance.x) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axes L = AY <- 1
	fCenterAToMiddle = m_v3HalfWidth.y;
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[1][0] + a_pOther->m_v3HalfWidth.y * m3RotationAbs[1][1] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[1][2];
	if (std::abs(v3Distance.y) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axes L = AZ <- 2
	fCenterAToMiddle = m_v3HalfWidth.z;
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[2][0] + a_pOther->m_v3HalfWidth.y * m3RotationAbs[2][1] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[2][2];
	if (std::abs(v3Distance.z) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axes L = BX <- 3
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[0][0] + m_v3HalfWidth.y * m3RotationAbs[1][0] + m_v3HalfWidth.z * m3RotationAbs[2][0];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x;
	if (std::abs(v3Distance.x * m3Rotation[0][0] + v3Distance.y * m3Rotation[1][0] + v3Distance.z * m3Rotation[2][0]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axes L = BY <- 4
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[0][1] + m_v3HalfWidth.y * m3RotationAbs[1][1] + m_v3HalfWidth.z * m3RotationAbs[2][1];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.y;
	if (std::abs(v3Distance.x * m3Rotation[0][1] + v3Distance.y * m3Rotation[1][1] + v3Distance.z * m3Rotation[2][1]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axes L = BZ <- 5
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[0][2] + m_v3HalfWidth.y * m3RotationAbs[1][2] + m_v3HalfWidth.z * m3RotationAbs[2][2];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.z;
	if (std::abs(v3Distance.x * m3Rotation[0][2] + v3Distance.y * m3Rotation[1][2] + v3Distance.z * m3Rotation[2][2]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AX x BX <- 6
	fCenterAToMiddle = m_v3HalfWidth.y * m3RotationAbs[2][0] + m_v3HalfWidth.z * m3RotationAbs[1][0];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.y * m3RotationAbs[0][2] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[0][1];
	if (std::abs(v3Distance.z * m3Rotation[1][0] - v3Distance.y * m3Rotation[2][0]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AX x BY <- 7
	fCenterAToMiddle = m_v3HalfWidth.y * m3RotationAbs[2][1] + m_v3HalfWidth.z * m3RotationAbs[1][1];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[0][2] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[0][0];
	if (std::abs(v3Distance.z * m3Rotation[1][1] - v3Distance.y * m3Rotation[2][1]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AX x BZ <- 8
	fCenterAToMiddle = m_v3HalfWidth.y * m3RotationAbs[2][2] + m_v3HalfWidth.z * m3RotationAbs[1][2];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[0][1] + a_pOther->m_v3HalfWidth.y * m3RotationAbs[0][0];
	if (std::abs(v3Distance.z * m3Rotation[1][2] - v3Distance.y * m3Rotation[2][2]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AY x BX <- 9
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[2][0] + m_v3HalfWidth.z * m3RotationAbs[0][0];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.y * m3RotationAbs[1][2] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[1][1];
	if (std::abs(v3Distance.x * m3Rotation[2][0] - v3Distance.z * m3Rotation[0][0]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AY x BY <- 10
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[2][1] + m_v3HalfWidth.z * m3RotationAbs[0][1];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[1][2] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[1][0];
	if (std::abs(v3Distance.x * m3Rotation[2][1] - v3Distance.z * m3Rotation[0][1]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AY x BZ <- 11
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[2][2] + m_v3HalfWidth.z * m3RotationAbs[0][2];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[1][1] + a_pOther->m_v3HalfWidth.y * m3RotationAbs[1][0];
	if (std::abs(v3Distance.x * m3Rotation[2][2] - v3Distance.z * m3Rotation[0][2]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AZ x BX <- 12
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[1][0] + m_v3HalfWidth.y * m3RotationAbs[0][0];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.y * m3RotationAbs[2][2] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[2][1];
	if (std::abs(v3Distance.y * m3Rotation[0][0] - v3Distance.x * m3Rotation[1][0]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AZ x BY <- 13
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[1][1] + m_v3HalfWidth.y * m3RotationAbs[0][1];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[2][2] + a_pOther->m_v3HalfWidth.z * m3RotationAbs[2][0];
	if (std::abs(v3Distance.y * m3Rotation[0][1] - v3Distance.x * m3Rotation[1][1]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Test axis L = AZ x BZ <- 14
	fCenterAToMiddle = m_v3HalfWidth.x * m3RotationAbs[1][2] + m_v3HalfWidth.y * m3RotationAbs[0][2];
	fCenterBToMiddle = a_pOther->m_v3HalfWidth.x * m3RotationAbs[2][1] + a_pOther->m_v3HalfWidth.y * m3RotationAbs[2][0];
	if (std::abs(v3Distance.y * m3Rotation[0][2] - v3Distance.x * m3Rotation[1][2]) > fCenterAToMiddle + fCenterBToMiddle)
	{
		return false;
	}

	// Since no separating axis found, the OBBs must a_pOther->m_v3HalfWidth intersecting
	return true;
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
void BoundingObject::subUpdate() {};
void BoundingObject::testCollision(Collider* other) {
	//this is probably not a good idea
	BoundingObject* castedOther = dynamic_cast<BoundingObject*>(other);
	callCallbacks(IsColliding(castedOther), other);
}

bool BoundingObject::IsCollidingRay(vector3 pos, vector3 dir) 
{
	float xMin, xMax, yMin, yMax, zMin, zMax;

	if (dir.x > 0) {
		xMin = (m_v3MinG.x - pos.x) / dir.x;
		xMax = (m_v3MaxG.x - pos.x) / dir.x;
	}
	else {
		xMin = (m_v3MaxG.x - pos.x) / dir.x;
		xMax = (m_v3MinG.x - pos.x) / dir.x;
	}

	if (dir.y > 0) {
		yMin = (m_v3MinG.y - pos.y) / dir.y;
		yMax = (m_v3MaxG.y - pos.y) / dir.y;
	}
	else {
		yMin = (m_v3MaxG.y - pos.y) / dir.y;
		yMax = (m_v3MinG.y - pos.y) / dir.y;
	}

	if (dir.z > 0) {
		zMin = (m_v3MinG.z - pos.z) / dir.z;
		zMax = (m_v3MaxG.z - pos.z) / dir.z;
	}
	else {
		zMin = (m_v3MaxG.z - pos.z) / dir.z;
		zMax = (m_v3MinG.z - pos.z) / dir.z;
	}

	if ((xMin > yMax) || (yMin > xMax)) return false;
	if (yMin > xMin) xMin = yMin;
	if (yMax < xMax)xMax = yMax;
	if ((xMin > zMax) || (zMin > xMax)) return false;
	if (zMin > xMin) xMin = zMin;
	if (zMax < xMax)xMax = zMax;

	return true;

}