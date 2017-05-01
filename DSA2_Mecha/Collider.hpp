#pragma once
#include "Component.hpp"
#include "GameObject.h"
#include <vector>

class Collider : public Component {
public:
	Collider();
	~Collider();

	float contactOffset;
	bool enabled;
	bool isTrigger;

	//will probably want to move this typdef to a separate class
	typedef void(Collider::*call_back) ();
	call_back onCollisionEnterFunction;
	call_back onCollisionExitFunction;
	call_back onCollisionStayFunction;
	call_back onTriggerEnterFunction;
	call_back onTriggerExitFunction;
	call_back onTriggerStayFunction;

	virtual void start();
	virtual void update(float deltaTime);
	virtual void render();

protected:
	bool previouslyCollided;
	bool previouslyTriggered;
	vector3 positionOffset;

	void onCollisionEnter();
	void onCollisionExit();
	void onCollisionStay();
	void onTriggerEnter();
	void onTriggerExit();
	void onTriggerStay();

	void emptyFunction();

	static std::vector<Collider*> ColliderCollection;
	virtual void subUpdate();
	virtual void callCallbacks(bool contact);
	virtual void testCollision(Collider* other);
};