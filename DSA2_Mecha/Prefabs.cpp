#include "Prefabs.h"
#include "BoundingObject.h"

#pragma region Pillar
Pillar::Pillar() : Pillar(vector3(0, 0, 0)) {}

Pillar::Pillar(vector3 pos)
{
	model = new PrimitiveClass();
	model->GenerateCylinder(50.0f, 300.0f, 10, REGREEN);

	transform = glm::translate(pos);

	BoundingObject* collider = new BoundingObject(model->GetVertexList(), 0);
	collider->SetModelMatrix(transform);
	this->addComponent(collider);

	visible = true;
}

Pillar::~Pillar() {}
#pragma endregion

#pragma region DestructObj
DestructObj::DestructObj() : DestructObj(vector3(0, 0, 0)) {}

DestructObj::DestructObj(vector3 pos)
{
	model = new PrimitiveClass();
	model->GenerateCube(50.0f, REBROWN);

	transform = glm::translate(pos);

	BoundingObject* collider = new BoundingObject(model->GetVertexList(), 0);
	collider->SetModelMatrix(transform);
	this->addComponent(collider);
	collider->onCollisionEnterFunction = &DestructObj::HandleCollision;

	visible = true;
	health = 100;
}


DestructObj::~DestructObj() {}

void DestructObj::HandleCollision(Collider* mainobj, Collider* other)
{
	DestructObj* me = static_cast<DestructObj*>(mainobj->getGameObject());
	
	Bullet* castedOther = dynamic_cast<Bullet*>(other->getGameObject());
	if (!castedOther) return;
	
	me->health -= 10;

	if (me->health <= 0) {
		std::cout << "dead" << std::endl;
		me->SetActive(false);
	}
}
#pragma endregion

#pragma region Enemy
Enemy::Enemy(Camera* cam) : Enemy(vector3(0, 0, 0), cam) {}

Enemy::Enemy(vector3 pos, Camera* cam)
{
	m_pMeshMngr->LoadModel("Mechs\\buzzer_bot.obj", std::to_string(this->GetInstanceID()));
	m_Camera = cam;
	model = nullptr;

	transform = glm::translate(pos);
	getComponent<Collider>()->onCollisionEnterFunction = &DestructObj::HandleCollision;
	
	//default RequestNextPoint
	RequestNextPoint = &Enemy::RequestDefault;
	targetPoint = pos;

	speed = 100;
	visible = true;
	health = 50;
}

Enemy::~Enemy(){}

void Enemy::Start() {
	SetGoal();
}

vector3 Enemy::RequestDefault(Enemy* me) {
	//just return current location
	return vector3(me->transform[3]);
}

void Enemy::SetGoal() {
	//either move to the next point or stay at the last target
	lastTargetPoint = targetPoint;
	targetPoint = RequestNextPoint(this);

	if (lastTargetPoint == targetPoint) distanceBetweenPoints = 0;
	else 
		distanceBetweenPoints = sqrtf(
			pow(lastTargetPoint.x - targetPoint.x, 2) +
			pow(lastTargetPoint.y - targetPoint.y, 2) +
			pow(lastTargetPoint.z - targetPoint.z, 2)
		);
	timeAtLastTargetReached = time;
}

bool Enemy::Update(float fDeltaTime) {
	if (!DestructObj::Update(fDeltaTime)) return false;

	float timeElapsed = time - timeAtLastTargetReached;
	if (timeElapsed != 0 && distanceBetweenPoints != 0) {
		float percent = timeElapsed / (distanceBetweenPoints / speed);
		vector3 newPosition = glm::lerp(lastTargetPoint, targetPoint, percent);
		transform = glm::translate(newPosition);

		if (percent > 1) {
			SetGoal();
		}
	}
	/*
	matrix4 rotmatrix = glm::lookAt(vector3(400, 0, 300), m_Camera->cameraPos, vector3(0, 1, 0));
	rotmatrix = glm::inverse(rotmatrix);
	rotmatrix = glm::mat4_cast(glm::quat_cast(rotmatrix));
	transform = glm::translate(targetPoint) * rotmatrix * glm::rotate(180.0f, vector3(0, 1, 0));
	*/
	getComponent<BoundingObject>()->SetModelMatrix(transform);
	m_pMeshMngr->SetModelMatrix(transform, std::to_string(this->GetInstanceID()));
	return true;
}

bool Enemy::Render(matrix4 projection, matrix4 view) {
	if (!DestructObj::Render(projection, view)) return false;
	m_pMeshMngr->AddInstanceToRenderList("ALL");
	return true;
}
#pragma endregion

EnemyPath::EnemyPath(Camera* cam) : EnemyPath(vector3(0, 0, 0), cam) {}
EnemyPath::EnemyPath(vector3 pos, Camera* cam) : Enemy(pos, cam) {
	RequestNextPoint = &EnemyPath::RequestPath;
}

vector3 EnemyPath::RequestPath(Enemy* me_uncasted) {
	EnemyPath* me = static_cast<EnemyPath*>(me_uncasted);
	vector3 point = me->pathPoints[me->pathIndex];
	me->pathIndex = (me->pathIndex + 1) % me->pathPoints.size();
	return point;
}

EnemyRandom::EnemyRandom(Camera* cam) : EnemyRandom(vector3(0, 0, 0), cam) {}
EnemyRandom::EnemyRandom(vector3 pos, Camera* cam) : Enemy(pos, cam) {
	RequestNextPoint = &EnemyRandom::RequestRandomInBox;
}

vector3 EnemyRandom::RequestRandomInBox(Enemy* me_uncasted) {
	EnemyRandom* me = static_cast<EnemyRandom*>(me_uncasted);
	
	int randx = (float)rand() / (RAND_MAX/me->boxDimmensions.x) + me->boxCenter.x;
	int randy = (float)rand() / (RAND_MAX/me->boxDimmensions.x) + me->boxCenter.x;
	int randz = (float)rand() / (RAND_MAX/me->boxDimmensions.x) + me->boxCenter.x;
	return vector3(randx, randy, randz);
}

#pragma region Bullet
int Bullet::bulletIndex;
std::vector<Bullet*> Bullet::bulletList;
float Bullet::lastBullet;
const float Bullet::BULLET_SPEED = 30.0f;
const float Bullet::FIRE_RATE = 0.1f;

Bullet::Bullet(void)
{
	model = new PrimitiveClass();
	model->GenerateSphere(5.0f, 20, RERED);

	BoundingObject* collider = new BoundingObject(model->GetVertexList(), 0);
	collider->SetModelMatrix(transform);
	this->addComponent(collider);
	collider->onCollisionEnterFunction = &Bullet::HandleCollision;

	visible = true;
	SetActive(false);

	bulletList.push_back(this);
}


Bullet::~Bullet() {}

void Bullet::fire(vector3 pos, glm::quat or , float time) {
	if (time - lastBullet > Bullet::FIRE_RATE) {
		Bullet* ptr = bulletList[bulletIndex];
		bulletIndex = (bulletIndex + 1) % bulletList.size();

		ptr->SetActive(true);

		ptr->transform = glm::inverse(glm::translate(pos - vector3(45.0f, -22.0f, -220.0f) * or ));

		ptr->lastOrient = or ;
		ptr->startTime = time;

		lastBullet = time;
	}
}

void Bullet::HandleCollision(Collider* mainobj, Collider* other) {
	Bullet* me = static_cast<Bullet*>(mainobj->getGameObject());	

	me->SetActive(false);
}

bool Bullet::Update(float time)
{
	if (!GameObject::Update(time)) return false;
	transform = glm::translate(transform, vector3(0.0f, 0.0f, -BULLET_SPEED) * lastOrient);
	//TODO this should update automatically in BO code
	getComponent<BoundingObject>()->SetModelMatrix(transform);
	//timer++;

	//if(time - startTime > 2) visible = false;
	//if (timer > 100) visible = false;
	//collider->SetModelMatrix(glm::translate(position));
	//bulletPos += vector3(0.0f, 0.0f, 20.0f) * lastOrient;
	
	return true;
}

#pragma endregion


