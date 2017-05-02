#pragma once
#include "Collider.hpp"
#include <iostream>

Collider::Collider() {}

Collider::~Collider() {}

std::vector<Collider*> Collider::ColliderCollection;

void Collider::onCollisionEnter(Collider* other) {
	if(onCollisionEnterFunction == nullptr) return;
	onCollisionEnterFunction(this, other);
	//Collider pointerInstance;
	//(pointerInstance.*onCollisionEnterFunction)();
}

void Collider::onCollisionExit(Collider* other) {
	if (onCollisionExitFunction == nullptr) return;
	onCollisionExitFunction(this, other);
	//Collider pointerInstance;
	//(pointerInstance.*onCollisionExitFunction)();
}

void Collider::onCollisionStay(Collider* other) {
	if (onCollisionStayFunction == nullptr) return;
	onCollisionStayFunction(this, other);
	//Collider pointerInstance;
	//(pointerInstance.*onCollisionStayFunction)();
}

void Collider::onTriggerEnter(Collider* other) {
	if (onTriggerEnterFunction == nullptr) return;
	onTriggerEnterFunction(this, other);
	//Collider pointerInstance;
	//(pointerInstance.*onTriggerEnterFunction)();
}

void Collider::onTriggerExit(Collider* other) {
	if (onTriggerExitFunction == nullptr) return;
	onTriggerExitFunction(this, other);
	//Collider pointerInstance;
	//(pointerInstance.*onTriggerExitFunction)();
}

void Collider::onTriggerStay(Collider* other) {
	if (onTriggerStayFunction == nullptr) return;
	onTriggerStayFunction(this, other);
	//Collider pointerInstance;
	//(pointerInstance.*onTriggerStayFunction)();
}



void Collider::Start() {
	/*
	onCollisionEnterFunction = &Collider::emptyFunction;
	onCollisionExitFunction = &Collider::emptyFunction;
	onCollisionStayFunction = &Collider::emptyFunction;
	onTriggerEnterFunction = &Collider::emptyFunction;
	onTriggerExitFunction = &Collider::emptyFunction;
	onTriggerStayFunction = &Collider::emptyFunction;
	*/
}

void Collider::subUpdate() {}
void Collider::callCallbacks(bool contact, Collider* other) {
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