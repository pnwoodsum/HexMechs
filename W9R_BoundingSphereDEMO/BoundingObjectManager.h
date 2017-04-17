#ifndef _BOUNDINGOBJECTMANAGER_H
#define _BOUNDINGOBJECTMANAGER_H

#include "RE\ReEng.h"
#include "MyBoundingObjectClass.h"
#include <iostream>
#include <vector>
#include <string>

#endif

class BoundingObjectManager
{
public:
	std::vector<MyBoundingObjectClass> objectList;

	static BoundingObjectManager* GetInstance() {
		if (instance == nullptr)
			instance = new BoundingObjectManager();
		return instance;
	}
	static void ReleaseInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}

	}
	static void AddObject(MyBoundingObjectClass temp) {
		instance->objectList.push_back(temp);
	}
	static void SetColorAtIndex(int index, vector3 color) {
		instance->objectList[index].SetColor(color);
	}
	static void SetVisibilityAtIndex(int index, bool visible) {
		instance->objectList[index].SetVisibility(visible);
	}


	static void RenderAtIndex(int index) {
		instance->objectList[index].Render();
	}
	static void RenderAll() {
		for (int i = 0; i < instance->objectList.size(); i++) {
			instance->objectList[i].Render();
		}
	}	
	
	static void CheckCollisions() {
		for (int i = 0; i < instance->objectList.size() - 1; i++) {
			for (int j = i + 1; j < instance->objectList.size(); j++) {
				if (instance->objectList[i].CheckCollision(instance->objectList[j])) {
					instance->objectList[i].SetColor(RERED);
					instance->objectList[j].SetColor(RERED);
				}
			}
		}
	}

private:
	static BoundingObjectManager* instance;
	BoundingObjectManager() {};
	~BoundingObjectManager() {};

};
BoundingObjectManager* BoundingObjectManager::instance = nullptr;