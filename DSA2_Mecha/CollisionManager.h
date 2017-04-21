#ifndef _COLLISIONMANAGER_H
#define _COLLISIONMANAGER_H

#include "RE\ReEng.h"
#include "BoundingObject.h"
#include <iostream>
#include <vector>
#include <string>

#endif

class CollisionManager
{
public:
	std::vector<BoundingObject> objectList;
	MeshManagerSingleton* m_pMeshMngr;

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
	static void AddObject(BoundingObject temp) {
		instance->objectList.push_back(temp);
	}

	static void SetColorAtIndex(int index, vector3 color) {
		instance->objectList[index].SetColor(color);
	}

	static void SetVisibilityAtIndex(int index, bool visible) {
		if (visible) {
			instance->objectList[index].m_iBoundingObjectType = 3;
		}
		else {
			instance->objectList[index].m_iBoundingObjectType = 2;
		}
	}


	static void RenderAtIndex(int index) {
		instance->objectList[index].RenderBO();
	}
	static void RenderAll() {
		for (int i = 0; i < instance->objectList.size(); i++) {
			instance->objectList[i].RenderBO();
		}
	}

	static void CheckCollisions() {

		for (int i = 0; i < instance->objectList.size(); i++) {
			instance->objectList[i].SetColor(REPURPLE);
			instance->objectList[i].m_bColliding = false;
		}

		for (int i = 0; i < instance->objectList.size() - 1; i++) {
			for (int j = i + 1; j < instance->objectList.size(); j++) {
				BoundingObject* temp = &instance->objectList[j];
				if (instance->objectList[i].IsColliding(temp)) {
					instance->objectList[i].SetColor(RERED);
					instance->objectList[j].SetColor(RERED);
					instance->objectList[i].m_bColliding = true;
					instance->objectList[j].m_bColliding = true;
				}
			}
		}
	}

private:
	static CollisionManager* instance;
	CollisionManager() {
		m_pMeshMngr = MeshManagerSingleton::GetInstance();
	};
	~CollisionManager() {};
};
