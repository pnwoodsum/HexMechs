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
	velocity = vector3(0.0f, 0.0f, 0.0f);

	x = 0.0f;
	y = 0.0f;
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

void Camera::MoveForward(float z, bool b) {
	cameraForward = vector3(0.0f, 0.0f, z) * orientation;
	accel = cameraForward * accelf;
	velocity += accel;

	if (b) {
		velocity = glm::clamp(velocity, -20, 20);
	}
	else {
		velocity = glm::clamp(velocity, -3, 3);
	}

	velocity.y = 0.0f;
}

void Camera::MoveSideways(float x, bool b) {
	cameraRight = vector3(x, 0.0f, 0.0f) * orientation;
	accel = cameraRight * accelf;
	velocity += accel;

	if (b) {
		velocity = glm::clamp(velocity, -20, 20);
	}
	else {
		velocity = glm::clamp(velocity, -3, 3);
	}

	velocity.y = 0.0f;
}

void Camera::MoveVertical(float y) {
	cameraPos.y += y;
	cameraTarget.y += y;
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

