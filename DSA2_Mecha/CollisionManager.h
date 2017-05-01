#ifndef _COLLISIONMANAGER_H
#define _COLLISIONMANAGER_H

#endif

#pragma once
#include "RE\ReEng.h"
#include "BoundingObject.h"
#include "Bullet.h"
#include <iostream>
#include <vector>
#include <string>
/*
class BulletManager
{
public:
	std::vector<Bullet> bulletList;

	static BulletManager* GetInstance() {
		if (instance == nullptr)
			instance = new BulletManager();
		return instance;
	}

	static void ReleaseInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}

	}

	static void RenderAll(matrix4 proj, matrix4 view) {
		for (int i = 0; i < instance->bulletList.size(); i++) {
			instance->bulletList[i].Render(proj, view);
			instance->bulletList[i].collider->RenderBO();
		}
	}

	static void Update(float time) {
		for (int i = 0; i < instance->bulletList.size(); i++) {
			if (instance->bulletList[i].visible) {
				instance->bulletList[i].Update(time);
			}
		}
	}

	static void ActivateBullet(vector3 pos, glm::quat or, float time) {
		if (time - instance->lastBullet > 0.1f) { //Timing
			if (instance->bulletList.size() > 0) {
				for (int i = 0; i < instance->bulletList.size(); i++) {
					if (!instance->bulletList[i].visible) {
						instance->bulletList[i].fire(pos, or , time);
						instance->lastBullet = time;
						return;
					}
				}
			}

			instance->bulletList.push_back(Bullet());
			instance->bulletList[instance->bulletList.size() - 1].fire(pos, or , time);
			instance->lastBullet = time;
			return;
		}
	}

	static void Populate() {
		for (int i = 0; i < 40; i++) {
			instance->bulletList.push_back(Bullet());
		}
	}

private:
	float lastBullet;
	static BulletManager* instance;
	BulletManager() {
	};
	~BulletManager() {};
};

class CollisionManager
{
public:
	std::vector<GameObject> objectList;
	//MeshManagerSingleton* m_pMeshMngr;
	BulletManager* bulltMngr;

	static CollisionManager* GetInstance() {
		if (instance == nullptr)
			instance = new CollisionManager();
		return instance;
	}
	static void ReleaseInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}

	}
	static void AddObject(GameObject temp) {
		instance->objectList.push_back(temp);
	}

	static void SetColorAtIndex(int index, vector3 color) {
		instance->objectList[index].collider->SetColor(color);
	}

	static void SetVisibilityAtIndex(int index, bool visible) {
		if (visible) {
			instance->objectList[index].collider->m_iBoundingObjectType = 3;
		}
		else {
			instance->objectList[index].collider->m_iBoundingObjectType = 2;
		}
	}


	static void RenderAtIndex(int index) {
		instance->objectList[index].collider->RenderBO();
	}

	static void RenderAll() {
		for (int i = 0; i < instance->objectList.size(); i++) {
			if (instance->objectList[i].visible)
				instance->objectList[i].collider->RenderBO();
		}
	}

	static void RenderObjects(matrix4 proj, matrix4 view) {
		for (int i = 0; i < instance->objectList.size(); i++) {
			instance->objectList[i].Render(proj, view);
		}
	}

	static void CheckCollisions() {

		for (int i = 0; i < instance->objectList.size(); i++) {
			instance->objectList[i].collider->SetColor(REPURPLE);
			instance->objectList[i].collider->m_bColliding = false;
		}

		for (int i = 0; i < instance->objectList.size() - 1; i++) {
			if (instance->objectList[i].collisionType == ColliderType::object || instance->objectList[i].collisionType == ColliderType::projectile)
				for (int j = i + 1; j < instance->objectList.size(); j++) {
					if (!(instance->objectList[i].collisionType == ColliderType::projectile && instance->objectList[j].collisionType == ColliderType::projectile)) {
						BoundingObject* temp = instance->objectList[j].collider;
						if (instance->objectList[i].collider->IsColliding(temp)) {
							instance->objectList[i].collider->SetColor(RERED);
							instance->objectList[j].collider->SetColor(RERED);
							instance->objectList[i].collider->m_bColliding = true;
							instance->objectList[j].collider->m_bColliding = true;
						}
					}
				}
		}

		for (int i = 0; i < instance->bulltMngr->bulletList.size(); i++) {
			if (instance->bulltMngr->bulletList[i].visible) {
				for (int j = 0; j < instance->objectList.size(); j++) {
					if (instance->bulltMngr->bulletList[i].collider->IsColliding(instance->objectList[j].collider, true)) {
						std::cout << "Collision" << std::endl;
						instance->bulltMngr->bulletList[i].visible = false;
						instance->objectList[j].HandleCollision();
					}
				}
			}
		}
	}

	static void Update(float fDeltaTime) {
		for (int i = 0; i < instance->objectList.size(); i++) {
			instance->objectList[i].Update(fDeltaTime);
		}
	}

private:
	static CollisionManager* instance;
	CollisionManager() {
		//m_pMeshMngr = MeshManagerSingleton::GetInstance();
		bulltMngr = BulletManager::GetInstance();
	};
	~CollisionManager() {};
};

*/