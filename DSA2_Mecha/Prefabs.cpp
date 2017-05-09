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
	
	getComponent<Collider>()->onCollisionEnterFunction = &Enemy::HandleCollision;
	
	visible = true;
	health = 50;
}

Enemy::~Enemy(){}

bool Enemy::Update(float fDeltaTime) {
	if (!DestructObj::Update(fDeltaTime)) return false;
	transform = glm::translate(glm::lerp(glm::vec3(transform[3]), m_Camera->cameraPos, 1*fDeltaTime));
	
	getComponent<BoundingObject>()->SetModelMatrix(transform);
	m_pMeshMngr->SetModelMatrix(transform, std::to_string(this->GetInstanceID()));
	return true;
}

bool Enemy::Render(matrix4 projection, matrix4 view) {
	if (!DestructObj::Render(projection, view)) return false;
	m_pMeshMngr->AddInstanceToRenderList("ALL");
	return true;
}

void Enemy::HandleCollision(Collider* mainobj, Collider* other)
{
	Enemy* me = static_cast<Enemy*>(mainobj->getGameObject());

	Bullet* castedOther = dynamic_cast<Bullet*>(other->getGameObject());
	if (!castedOther) return;

	me->health -= 10;

	if (me->health <= 0) {
		std::cout << "dead" << std::endl;
		
		//Hack to set model to invisible
		me->m_pMeshMngr->SetModelMatrix(glm::scale(vector3(0,0,0)), std::to_string(me->GetInstanceID()));
		
		me->SetActive(false);
		//me->transform = glm::scale(0, 0, 0);
		
	}
}

#pragma endregion

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