#include "Prefabs.h"
#include "BoundingObject.h"

#pragma region Pillar
Pillar::Pillar() : Pillar(vector3(0, 0, 0)) {}

Pillar::Pillar(vector3 pos)
{
	model = new PrimitiveClass();
	model->GenerateCylinder(50.0f, 300.0f, 10, REGREEN);

	position = pos;

	BoundingObject* collider = new BoundingObject(model->GetVertexList(), 0);
	collider->SetModelMatrix(glm::translate(position));
	this->addComponent(collider);

	bCanCollide = true;
	collisionType = ColliderType::environment;
	visible = true;
}


Pillar::~Pillar()
{
}


void Pillar::Update(float fDeltaTime)
{
	if (visible = false)
		visible = true;
}
/*
void Pillar::HandleCollision()
{
}*/
#pragma endregion

#pragma region DestructObj
DestructObj::DestructObj() : DestructObj(vector3(0, 0, 0)) {}

DestructObj::DestructObj(vector3 pos)
{
	model = new PrimitiveClass();
	model->GenerateCube(50.0f, REBROWN);

	position = pos;

	BoundingObject* collider = new BoundingObject(model->GetVertexList(), 0);
	collider->SetModelMatrix(glm::translate(position));
	this->addComponent(collider);
	collider->onCollisionEnterFunction = &DestructObj::HandleCollision;

	bCanCollide = true;
	collisionType = ColliderType::environment;
	visible = true;
	destructible = true;
	health = 1000;
}


DestructObj::~DestructObj() {}

void DestructObj::HandleCollision(Collider* mainobj, Collider* other)
{
	DestructObj* me = static_cast<DestructObj*>(mainobj->getGameObject());
	std::cout << "hit destruct actually" << std::endl;
	
	Bullet* castedOther = dynamic_cast<Bullet*>(other->getGameObject());
	if (!castedOther) return;
	
	me->health -= 10;

	if (me->health <= 0) {
		std::cout << "dead" << std::endl;
		me->visible = false;
	}
}

//void DestructObj::Update(float fDeltaTime){}
#pragma endregion

#pragma region Enemy
Enemy::Enemy(Camera* cam)
{
	m_Camera = cam;
	model = new PrimitiveClass();
	model->GenerateCube(50.0f, RERED);

	//collider = new BoundingObject(model->GetVertexList(), 0);

	position = vector3(0, 0, 0);
	//collider->SetModelMatrix(glm::translate(position));

	bCanCollide = true;
	collisionType = ColliderType::environment;

	visible = true;
	destructible = true;
	enemy = true;
	health = 1000;
}

Enemy::Enemy(Camera* cam, vector3 pos)
{
	m_Camera = cam;
	model = new PrimitiveClass();
	model->GenerateCube(50.0f, RERED);

	position = pos;

	//collider = new BoundingObject(model->GetVertexList(), 0);
	//collider->SetModelMatrix(glm::inverse(glm::translate(pos)));

	bCanCollide = true;
	collisionType = ColliderType::environment;

	visible = true;
	destructible = true;
	enemy = true;
	health = 1000;
}


Enemy::~Enemy(){}
/*
void Enemy::HandleCollision()
{
	std::cout << "hit destruct" << std::endl;

	health -= 10;

	if (health <= 0) {
		visible = false;
	}
}

void Enemy::Update(float fDeltaTime)
{
	std::cout << "Update" << std::endl;
	position = glm::lerp(position, m_Camera->cameraPos, 0.1f);
}*/
#pragma endregion

#pragma region Bullet
int Bullet::bulletIndex;
std::vector<Bullet*> Bullet::bulletList;

Bullet::Bullet(void)
{
	model = new PrimitiveClass();
	model->GenerateSphere(5.0f, 20, RERED);

	position = vector3(0,0,0);

	BoundingObject* collider = new BoundingObject(model->GetVertexList(), 0);
	collider->SetModelMatrix(glm::translate(position));
	this->addComponent(collider);

	bCanCollide = true;
	collisionType = ColliderType::projectile;
	visible = true;
	//timer = 0;

	bulletList.push_back(this);
}


Bullet::~Bullet() {}

void Bullet::fire(vector3 pos, glm::quat or , float time) {
	Bullet* ptr = bulletList[bulletIndex];
	bulletIndex = (bulletIndex + 1) % bulletList.size();

	ptr->position = pos - vector3(45.0f, -22.0f, -220.0f) * or ;
	//collider->SetModelMatrix(glm::inverse(glm::translate(position)));
	//collider->orientation = or;

	//bulletPos = pos - (vector3(0.0f,0.0f,2.0f) * or);
	ptr->lastOrient = or ;
	//timer = 0;
	ptr->startTime = time;

	ptr->visible = true;
}

void Bullet::Update(float time)
{
	GameObject::Update(time);
	if (visible) {
	position += vector3(0.0f, 0.0f, 20.0f) * lastOrient;
	//TODO this should update automatically in BO code
	getComponent<BoundingObject>()->SetModelMatrix(glm::translate(position));
	//timer++;

	if(time - startTime > 2) visible = false;
	//if (timer > 100) visible = false;
	//collider->SetModelMatrix(glm::translate(position));
	//bulletPos += vector3(0.0f, 0.0f, 20.0f) * lastOrient;
	}
	
}
/*
void Bullet::Render(matrix4 projection, matrix4 view)
{
	if (exist) {
		bullet->Render(projection, view, glm::translate(-bulletPos));
	}
}*/

#pragma endregion