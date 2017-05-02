#pragma once
#include "Component.hpp"
#include "GameObject.h"
#include <vector>
//typedef void(*call_back)();
class Collider : public Component {
public:
	Collider();
	~Collider();

	float contactOffset;
	bool enabled;
	bool isTrigger;

	//will probably want to move this typdef to a separate class
	//typedef void(Collider::*call_back) ();
	/*
	call_back onCollisionEnterFunction;
	call_back onCollisionExitFunction;
	call_back onCollisionStayFunction;
	call_back onTriggerEnterFunction;
	call_back onTriggerExitFunction;
	call_back onTriggerStayFunction;
	*/
	//void(*)(void* ptr)
	void(*onCollisionEnterFunction)(void *ptr);
	void(*onCollisionExitFunction)(void *ptr);
	void(*onCollisionStayFunction)(void *ptr);
	void(*onTriggerEnterFunction)(void *ptr);
	void(*onTriggerExitFunction)(void *ptr);
	void(*onTriggerStayFunction)(void *ptr);

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Render();

protected:
	bool previouslyCollided;
	bool previouslyTriggered;
	vector3 positionOffset;

	void onCollisionEnter(void* other);
	void onCollisionExit(void* other);
	void onCollisionStay(void* other);
	void onTriggerEnter(void* other);
	void onTriggerExit(void* other);
	void onTriggerStay(void* other);

	static void emptyFunction(void* ptr);

	static std::vector<Collider*> ColliderCollection;
	virtual void subUpdate();
	virtual void callCallbacks(bool contact, void* other);
	virtual void testCollision(Collider* other);
};