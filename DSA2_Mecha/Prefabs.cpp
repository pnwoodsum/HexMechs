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
	m_Camera = cam;
	model = new PrimitiveClass();
	model->GenerateCube(50.0f, RERED);

	transform = glm::translate(pos);
	//collider already there from Destructable obj?
	/*
	BoundingObject* collider = new BoundingObject(model->GetVertexList(), 0);
	collider->SetModelMatrix(transform);
	this->addComponent(collider);
	//reuse the destructobj handle collision method we inherit
	collider->onCollisionEnterFunction = &DestructObj::HandleCollision;
	*/
	visible = true;
	health = 50;
}

Enemy::~Enemy(){}

void Enemy::Update(float fDeltaTime) {
	DestructObj::Update(fDeltaTime);
	transform = glm::translate(glm::lerp(glm::vec3(transform[3]), m_Camera->cameraPos, 1*fDeltaTime));
	
	getComponent<BoundingObject>()->SetModelMatrix(transform);
}
#pragma endregion

#pragma region Bullet
int Bullet::bulletIndex;
std::vector<Bullet*> Bullet::bulletList;
float Bullet::lastBullet;
const float Bullet::BULLET_SPEED = 20.0f;
const float Bullet::FIRE_RATE = 0.2f;

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

void Bullet::Update(float time)
{
	GameObject::Update(time);
	transform = glm::translate(transform, vector3(0.0f, 0.0f, -BULLET_SPEED) * lastOrient);
	//TODO this should update automatically in BO code
	getComponent<BoundingObject>()->SetModelMatrix(transform);
	//timer++;

	//if(time - startTime > 2) visible = false;
	//if (timer > 100) visible = false;
	//collider->SetModelMatrix(glm::translate(position));
	//bulletPos += vector3(0.0f, 0.0f, 20.0f) * lastOrient;
	
	
}

#pragma endregion