#include "Prefabs.h"
#include "BoundingObject.h"

//ENVIRONMENT Definitions
#pragma region Environment
Environment::Environment() {}
Environment::~Environment() {}
#pragma endregion

//PILLAR Definitions
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

//WALL Definitions
#pragma region Wall
Wall::Wall() : Wall(vector3(0, 0, 0), vector3(0, 0, 0)) {}

Wall::Wall(vector3 size, vector3 pos)
{
	model = new PrimitiveClass();
	model->GenerateCuboid(size, REORANGE);

	transform = glm::translate(pos);

	BoundingObject* collider = new BoundingObject(model->GetVertexList(), 0);
	collider->SetModelMatrix(transform);
	this->addComponent(collider);

	visible = true;
}

Wall::~Wall() {}
#pragma endregion

//DestructObj Definitions
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
	
	Projectile* castedOther = dynamic_cast<Projectile*>(other->getGameObject());
	if (!castedOther) return;
	
	me->health -= 10;

	if (me->health <= 0) {
		std::cout << "dead" << std::endl;
		me->SetActive(false);
	}
}
#pragma endregion

//PLAYER Defintions
#pragma region Player
Player::Player() {
}
Player::Player(Camera* cam) {

	//using camera location to position bounding object
	camRef = cam;

	model = new PrimitiveClass();
	model->GenerateCube(25.0f, REBROWN);

	//set transform with camera
	transform = glm::inverse(glm::translate(camRef->GetPos()));

	BoundingObject* collider = new BoundingObject(model->GetVertexList(), 0);
	collider->SetModelMatrix(transform);
	this->addComponent(collider);
	collider->onCollisionEnterFunction = &Player::HandleCollision;

	transform = glm::translate(vector3(0, -100, 0));

	//intializing variables
	visible = true;
	health = 100;
	dead = false;
}
Player::~Player() {}
void Player::HandleCollision(Collider* mainobj, Collider* other)
{
	std::cout << "Hit a barrier" << std::endl;
	Player* me = static_cast<Player*>(mainobj->getGameObject());

	std::cout << "Hit a barrier" << std::endl;
	Projectile* castedOther = dynamic_cast<Projectile*>(other->getGameObject());
	if (castedOther) {
		me->health -= 5;

		if (me->health <= 0) {
			std::cout << "dead" << std::endl;
			me->dead = true;
		}
	}

	Environment* castedBarrier = dynamic_cast<Environment*>(other->getGameObject());
	if (castedBarrier) {
		me->camRef->velocity *= -1;
	}
}

bool Player::Update(float fDeltaTime) {
	getComponent<BoundingObject>()->SetModelMatrix(glm::inverse(glm::translate(camRef->GetPos())));
	return true;
}
#pragma endregion

//ENEMY Definitions
#pragma region Enemy
Enemy::Enemy(Camera* cam) : Enemy(vector3(0, 0, 0), cam) {}

Enemy::Enemy(vector3 pos, Camera* cam)
{
	//loads enemy model
	m_pMeshMngr->LoadModel("Mechs\\buzzer_bot.obj", std::to_string(this->GetInstanceID()));
	m_Camera = cam;
	model = nullptr;

	transform = glm::translate(pos);
	getComponent<Collider>()->onCollisionEnterFunction = &DestructObj::HandleCollision;
	
	//default RequestNextPoint
	RequestNextPoint = &Enemy::RequestDefault;
	targetPoint = pos;

	//intializes variables
	speed = 100;
	visible = true;
	health = 50;
	fireRate = 2.f;
	timeAtLastFire = GameObject::time;
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
	
	//update position
	float timeElapsed = time - timeAtLastTargetReached;
	if (timeElapsed != 0 && distanceBetweenPoints != 0) {
		float percent = timeElapsed / (distanceBetweenPoints / speed);
		vector3 newPosition = glm::lerp(lastTargetPoint, targetPoint, percent);
		transform = glm::translate(newPosition);

		if (percent > 1) {
			SetGoal();
		}
	}
	//recalc transform mats
	vector3 pos = vector3(transform[3]);
	matrix4 rotMat = glm::lookAt(vector3(0,0,0), m_Camera->cameraPos+pos, vector3(0, 1, 0));
	transform = glm::translate(pos) * glm::inverse(rotMat) * glm::rotate(180.0f, vector3(0, 1, 0));
	
	getComponent<BoundingObject>()->SetModelMatrix(transform);
	m_pMeshMngr->SetModelMatrix(transform, std::to_string(this->GetInstanceID()));

	return true;
}

bool Enemy::Render(matrix4 projection, matrix4 view) {
	if (!DestructObj::Render(projection, view)) return false;
	m_pMeshMngr->AddInstanceToRenderList(std::to_string(this->GetInstanceID()));
	return true;
}
#pragma endregion

//ENEMYVARIANTS Definitions
#pragma region EnemyVariants
EnemyPath::EnemyPath(Camera* cam) : EnemyPath(vector3(0, 0, 0), cam) {}
EnemyPath::EnemyPath(vector3 pos, Camera* cam) : Enemy(pos, cam) {
	RequestNextPoint = &EnemyPath::RequestPath;
}

vector3 EnemyPath::RequestPath(Enemy* me_uncasted) {
	EnemyPath* me = static_cast<EnemyPath*>(me_uncasted);
	vector3 point = me->pathPoints[me->pathIndex];
	me->pathIndex = (me->pathIndex + 1) % me->pathPoints.size();
	if (me->firstPass) {
		me->lastTargetPoint = point;
		me->firstPass = false;
		point = me->pathPoints[me->pathIndex];
		me->pathIndex = (me->pathIndex + 1) % me->pathPoints.size();
		return point;
	}
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
#pragma endregion

//BULLET Definitions
#pragma region Bullet
int Projectile::bulletIndex;
std::vector<Projectile*> Projectile::bulletList;
float Projectile::lastBullet;
const float Projectile::BULLET_SPEED = 30.0f;
const float Projectile::FIRE_RATE = 0.1f;

Projectile::Projectile(void)
{
	m_pMeshMngr->LoadModel("Mechs\\missle.obj", std::to_string(this->GetInstanceID()));

	BoundingObject* collider = new BoundingObject(m_pMeshMngr->GetVertexList(std::to_string(this->GetInstanceID())), 0);
	collider->SetModelMatrix(transform);
	this->addComponent(collider);
	collider->onCollisionEnterFunction = &Projectile::HandleCollision;

	model = nullptr;

	visible = true;
	SetActive(false);

	bulletList.push_back(this);
}


Projectile::~Projectile() {}

void Projectile::fire(vector3 pos, glm::quat or , float time) {
	if (time - lastBullet > Projectile::FIRE_RATE) {
		Projectile* ptr = bulletList[bulletIndex];
		bulletIndex = (bulletIndex + 1) % bulletList.size();

		ptr->SetActive(true);

		ptr->transform = glm::inverse(glm::translate(pos - vector3(45.0f, -22.0f, -220.0f) * or ));

		ptr->lastOrient = or ;
		ptr->startTime = time;

		lastBullet = time;
	}
}

void Projectile::HandleCollision(Collider* mainobj, Collider* other) {
	Projectile* me = static_cast<Projectile*>(mainobj->getGameObject());	

	me->SetActive(false);
}

bool Projectile::Update(float time)
{
	GameObject::Update(time);
	transform = glm::translate(transform, vector3(0.0f, 0.0f, -BULLET_SPEED) * lastOrient);
	//TODO this should update automatically in BO code
	getComponent<BoundingObject>()->SetModelMatrix(glm::translate(vector3(transform[3])) * glm::inverse(glm::mat4_cast(lastOrient)));
	//timer++;

	//if(time - startTime > 2) visible = false;
	//if (timer > 100) visible = false;
	//collider->SetModelMatrix(glm::translate(position));
	//bulletPos += vector3(0.0f, 0.0f, 20.0f) * lastOrient;
	m_pMeshMngr->SetModelMatrix( glm::translate(vector3(transform[3])) * glm::inverse(glm::mat4_cast(lastOrient)), std::to_string(this->GetInstanceID()));
	return true;
}
bool Projectile::Render(matrix4 projection, matrix4 view) {
	if (!GameObject::Render(projection, view)) return false;
	m_pMeshMngr->AddInstanceToRenderList(std::to_string(this->GetInstanceID()));
	return true;
}
#pragma endregion
