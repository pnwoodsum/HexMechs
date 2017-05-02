#pragma once
#include "Collider.hpp"
#include <iostream>

Collider::Collider() {}

Collider::~Collider() {}

std::vector<Collider*> Collider::ColliderCollection;

void Collider::onCollisionEnter() {
	Collider pointerInstance;
	(pointerInstance.*onCollisionEnterFunction)();
}

void Collider::onCollisionExit() {
	Collider pointerInstance;
	(pointerInstance.*onCollisionExitFunction)();
}

void Collider::onCollisionStay() {
	Collider pointerInstance;
	(pointerInstance.*onCollisionStayFunction)();
}

void Collider::onTriggerEnter() {
	Collider pointerInstance;
	(pointerInstance.*onTriggerEnterFunction)();
}

void Collider::onTriggerExit() {
	Collider pointerInstance;
	(pointerInstance.*onTriggerExitFunction)();
}

void Collider::onTriggerStay() {
	Collider pointerInstance;
	(pointerInstance.*onTriggerStayFunction)();
}

void Collider::emptyFunction() { return; }


void Collider::Start() {
	onCollisionEnterFunction = &Collider::emptyFunction;
	onCollisionExitFunction = &Collider::emptyFunction;
	onCollisionStayFunction = &Collider::emptyFunction;
	onTriggerEnterFunction = &Collider::emptyFunction;
	onTriggerExitFunction = &Collider::emptyFunction;
	onTriggerStayFunction = &Collider::emptyFunction;
}

void Collider::subUpdate() {}
void Collider::callCallbacks(bool contact) {
	if (contact) {
		if (!isTrigger) {
			if (previouslyCollided) {
				onCollisionStay();
			}
			else {
				onCollisionEnter();
				previouslyCollided = true;
			}
		}
		else {
			if (previouslyTriggered) {
				onTriggerStay();
			}
			else {
				onTriggerEnter();
				previouslyTriggered;
			}
		}
	}
	else {
		if (isTrigger) {
			if (previouslyTriggered) {
				onTriggerExit();
				previouslyTriggered = false;
			}
		}
		else {
			if (previouslyCollided) {
				onCollisionExit();
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