#pragma once
#include "Collider.hpp"
#include <iostream>

Collider::Collider() {}

Collider::~Collider() {}

std::vector<Collider*> Collider::ColliderCollection;

void Collider::onCollisionEnter(void* other) {
	onCollisionEnterFunction(other);
	//Collider pointerInstance;
	//(pointerInstance.*onCollisionEnterFunction)();
}

void Collider::onCollisionExit(void* other) {
	onCollisionExitFunction(other);
	//Collider pointerInstance;
	//(pointerInstance.*onCollisionExitFunction)();
}

void Collider::onCollisionStay(void* other) {
	onCollisionStayFunction(other);
	//Collider pointerInstance;
	//(pointerInstance.*onCollisionStayFunction)();
}

void Collider::onTriggerEnter(void* other) {
	onTriggerEnter(other);
	//Collider pointerInstance;
	//(pointerInstance.*onTriggerEnterFunction)();
}

void Collider::onTriggerExit(void* other) {
	onTriggerExitFunction(other);
	//Collider pointerInstance;
	//(pointerInstance.*onTriggerExitFunction)();
}

void Collider::onTriggerStay(void* other) {
	onTriggerStayFunction(other);
	//Collider pointerInstance;
	//(pointerInstance.*onTriggerStayFunction)();
}

void Collider::emptyFunction(void* ptr) { return; }


void Collider::Start() {
	onCollisionEnterFunction = &Collider::emptyFunction;
	onCollisionExitFunction = &Collider::emptyFunction;
	onCollisionStayFunction = &Collider::emptyFunction;
	onTriggerEnterFunction = &Collider::emptyFunction;
	onTriggerExitFunction = &Collider::emptyFunction;
	onTriggerStayFunction = &Collider::emptyFunction;
}

void Collider::subUpdate() {}
void Collider::callCallbacks(bool contact, void* other) {
	if (contact) {
		if (!isTrigger) {
			if (previouslyCollided) {
				onCollisionStay(other);
			}
			else {
				onCollisionEnter(other);
				previouslyCollided = true;
			}
		}
		else {
			if (previouslyTriggered) {
				onTriggerStay(other);
			}
			else {
				onTriggerEnter(other);
				previouslyTriggered;
			}
		}
	}
	else {
		if (isTrigger) {
			if (previouslyTriggered) {
				onTriggerExit(other);
				previouslyTriggered = false;
			}
		}
		else {
			if (previouslyCollided) {
				onCollisionExit(other);
				previouslyCollided = false;
			}
		}
	}
}
void Collider::testCollision(Collider* other) {}
void Collider::Update(float deltaTime) {
	
	subUpdate();
	for (auto singleCollid : ColliderCollection) {
		if (singleCollid == this)
			continue;
		testCollision(singleCollid);
	}
	
}

void Collider::Render() {}