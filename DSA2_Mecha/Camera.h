#pragma once
#include "RE\ReEng.h"

using namespace ReEng;
class Camera
{
public:
	matrix4 GetView(vector2); //Should get the View Matrix from your class
	matrix4 GetProjection(bool);  //Should get the Projection Matrix from your class, this function should let me choose between a Perspective or an Orthographic projection depending on the bool argument.
	void SetPosition(vector3); //Sets the position of the camera
	void SetTarget(vector3); //Sets the target of the camera
	void SetUp(vector3); //Sets the up vector of the camera
	void MoveForward(float); //Move the camera forward (or backwards) depending on the “view vector”
	void MoveSideways(float); //Move the camera based on the “right” vectordepending on the “view vec
	void MoveVertical(float); //Move the camera up or down depending on the “up vector”
	void ChangePitch(float);
	void ChangeRoll(float);
	void ChangeYaw(float);
	void SwitchMouseUse();
	void SwitchProjection();
	
	vector3 cameraForward;

	glm::quat orientation;
	vector3 GetPos();
	float x;
	float y;

	Camera();
	~Camera();
private:
	matrix4 cameraView;
	matrix4 cameraProjO;
	matrix4 cameraProjP;
	vector3 cameraUp;
	
	vector3 cameraRight;
	vector3 cameraPos;
	vector3 cameraTarget;
	
	float cameraYaw;
	float cameraPitch;
	float cameraRoll;
	bool mouseUse;
	bool ortho;
};

