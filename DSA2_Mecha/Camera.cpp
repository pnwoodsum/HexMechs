#include "Camera.h"
#include "RE\ReEng.h"
using namespace ReEng;

Camera::Camera()
{
	cameraPos = vector3(0.0f, 0.0f, -700.0f);
	cameraProjO = glm::ortho(-1080.0f, 1080.0f, -768.0f, 768.0f, 0.01f, 100000.0f);
	cameraProjP = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 100000.0f);
	cameraUp = vector3(0.0f,1.0f,0.0f);
	cameraForward = vector3(0.0f,0.0f,1.0f);
	cameraTarget = vector3(0.0f, 0.0f, 0.0f);
	orientation = glm::quat();
	cameraYaw = 0;
	cameraPitch = 0.0f;
	cameraRoll = 0;
	mouseUse = false;
	ortho = false;

	accelf = 7.0f;
	accel = vector3(0.0f, 0.0f, 0.0f);
	accelV = vector3(0.0f, 0.0f, 0.0f);
	velocity = vector3(0.0f, 0.0f, 0.0f);

	x = 0.0f;
	y = 0.0f;

	energy = 5000;
	boost = false;
	decel = false;
}


Camera::~Camera()
{
}

void Camera::SwitchMouseUse() {
	mouseUse = !mouseUse;
}

void Camera::SwitchProjection() {
	ortho = !ortho;
}

vector3 Camera::GetPos() {
	return cameraPos;
}

matrix4 Camera::GetView(vector2 mouse) {
	y = y + mouse.y;
	x = x + mouse.x;
	if (mouseUse) {
		orientation = glm::quat(vector3(cameraPitch, cameraYaw, cameraRoll));
	}
	else {
		orientation = glm::quat(vector3(glm::radians(y/20.0f), 0.0f, 0.0f)) * glm::quat(vector3(0.0f, glm::radians(x/20.0f), 0.0f));
	}
	cameraView = glm::toMat4(orientation) * glm::translate(cameraPos);
	cameraForward = vector3(0, 0, 1.0f) * orientation;
	return cameraView;
}

matrix4 Camera::GetProjection(bool ort) {
	if (ortho) {
		return cameraProjO;
	}
	else {
		return cameraProjP;
	}
}

void Camera::SetPosition(vector3 pos) {
	cameraPos = pos;
}

void Camera::SetTarget(vector3 tar) {
	cameraTarget = tar;
}

void Camera::SetUp(vector3 up) {
	cameraUp = up;
}

//Moves camera forward
void Camera::MoveForward(float z, bool b) {
	vector3 moveDir = vector3(0.0f, 0.0f, z) * orientation;

	if (b) {
		if (energy > 0) {
			accelf = 7.0f;
			accel += moveDir * accelf;
			if (accel.y < 0) {
				inAir = true;
			}
			else if (accel.y >= 0) {
				accel.y = 0.0f;
			}
			boost = true;
		}
		else {
			boost = false;
			if (inAir) return;
			if (glm::length(velocity) > 5) return;
			accelf = 2.0f;
		}
	}
	else {
		if (inAir) return;
		if (glm::length(velocity) > 5) return;
		accelf = 1.0f;
		accel += moveDir * accelf;
		accel.y = 0.0f;
	}
}

//moves Camer sideways
void Camera::MoveSideways(float x, bool b) {
	cameraRight = vector3(x, 0.0f, 0.0f) * orientation;
	
	
	if (b) {
		if (energy > 0) {
			accelf = 7.0f;
			boost = true;
		}
		else {
			if (inAir) return;
			boost = false;
			if (glm::length(velocity) > 5) return;
			accelf = 2.0f;
		}
	}
	else {
		if (inAir) return;
		if (glm::length(velocity) > 5) return;
		accelf = 2.0f;
	}

	accel += cameraRight * accelf;
	accel.y = 0.0f;
}

//Direct vertical movement
void Camera::MoveVertical(float y, bool b) {
	vector3 upVector = vector3(0.0f, y, 0.0f) * orientation;

	if (energy <= 0) {
		boost = false;
		return;
	}
	if (b) {
		accelf = 7.0f;
	}
	else {
		accelf = 0.7f;
	}
	boost = true;
	accelV -= upVector * accelf;
	accelV.x = 0.0f;
	accelV.z = 0.0f;
}

void Camera::ChangePitch(float p) {
	cameraPitch += p;
}

void Camera::ChangeRoll(float r) {
	cameraRoll += r;
}

void Camera::ChangeYaw(float y) {
	cameraYaw += y;
}

void Camera::Move(float timer) {
	//Timer currently not used

	velocity += accel;
	velocity += accelV;
	cameraPos += velocity;

	//Acts as friction or Air resistance
	if (decel)velocity -= (vector3(velocity.x, 0.0f, velocity.z) * 0.02f);
	else velocity -= (vector3(velocity.x, 0.0f, velocity.z) * 0.06f);

	//Clamps velocity
	if (glm::length(velocity) > 5) {
		if(!boost && !inAir && !decel) velocity = glm::normalize(velocity) * 5.0f;
		else if (glm::length(velocity) > 20) {
			decel = true;
			if (velocity.y < 0) {
				velocity = glm::normalize(velocity) * 20.0f;
			}
			else {
				velocity.x = vector3((glm::normalize(velocity) * 20.0f)).x;
				velocity.z = vector3((glm::normalize(velocity) * 20.0f)).z;
			}
		}
	}
	if (glm::length(velocity) < 5) {
		decel = false;
	}
	else if (glm::length(velocity) < 0) {
		velocity = vector3(0,0,0);
	}
	if (inAir) {
		velocity.y += 0.4f;
		if (cameraPos.y > 0) {
			velocity.y = 0;
			inAir = false;
			cameraPos.y = 0;
		}
	}
	accel = vector3(0, 0, 0);
	accelV = vector3(0, 0, 0);

	//Extremely Simple Energy System
	if (boost) {
		energy -= 51;
		if (energy <= 0) boost = false;
	}
	else if(energy < 10000)energy += 11;

	boost = false;
}