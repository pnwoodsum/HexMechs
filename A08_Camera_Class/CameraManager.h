#pragma once
#include "Camera.h";

class CameraManager
{
public:
	Camera cam;
	static CameraManager* getInstance() {
		if (instance == nullptr) {
			instance = new CameraManager();
		}
		return instance;
	}
	static void releaseInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}
private:
	static CameraManager* instance;
	CameraManager() {};
	~CameraManager() {};
};

