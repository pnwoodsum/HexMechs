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
	void(*onCollisionEnterFunction)(Collider*, Collider*);
	void(*onCollisionExitFunction)(Collider*, Collider*);
	void(*onCollisionStayFunction)(Collider*, Collider*);
	void(*onTriggerEnterFunction)(Collider*, Collider*);
	void(*onTriggerExitFunction)(Collider*, Collider*);
	void(*onTriggerStayFunction)(Collider*, Collider*);

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Render();

protected:
	bool previouslyCollided;
	bool previouslyTriggered;
	vector3 positionOffset;

	void onCollisionEnter(Collider* other);
	void onCollisionExit(Collider* other);
	void onCollisionStay(Collider* other);
	void onTriggerEnter(Collider* other);
	void onTriggerExit(Collider* other);
	void onTriggerStay(Collider* other);

	static std::vector<Collider*> ColliderCollection;
	virtual void subUpdate();
	virtual void callCallbacks(bool contact, Collider* other);
	virtual void testCollision(Collider* other);
};