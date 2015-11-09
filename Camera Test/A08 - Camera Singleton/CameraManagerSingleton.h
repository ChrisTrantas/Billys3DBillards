#ifndef __CAMERA_MANAGER_SINGLETON_H_
#define __CAMERA_MANAGER_SINGLETON_H_

#include "RE\ReEngAppClass.h"

class CameraManagerSingleton
{
private:
	static CameraManagerSingleton* instance;

	matrix4 m_m4Projection;
	matrix4 m_m4View;

	quaternion m_qOrientation;


	vector3 m_vEyePosition;	// The position of the camera.
	vector3 m_vUp;			// The up vector for the camera.
	vector3 m_vForward;		// The direction the camera is facing
	vector3 m_vRight;		// The direstion right of the camera
	vector3 m_vTarget;		// The position the camera is set to look at.


	CameraManagerSingleton();
	~CameraManagerSingleton();

	void GenerateViewMatrix();	// Generates a new view matrix

public:
	static CameraManagerSingleton* GetInstance();
	static void ReleaseInstance();


	matrix4 GetView();	//Gets the view matrix
	matrix4 GetProjection(bool bOrthographic);	// Gets the projection matrix

	quaternion GetOrientation();	// Gets the orientation quaternion of the camera
	vector3 GetUpVector();			// Gets the up vector

	void SetPosition(vector3 vEyePosition);//Sets the position of the camera
	void SetTarget(vector3 v3Target);//Sets the target of the camera
	void SetUp(vector3 v3Up);//Sets the up vector of the camera


	void MoveForward(float fIncrement);		//Move the camera forward (or backwards) depending on the “view vector”
	void MoveSideways(float fIncrement);	//Move the camera Right (or Left) depending on the “view vector”
	void MoveVertical(float fIncrement);	//Move the camera uo (or down) depending on the “view vector”

	void ChangePitch(float fIncrement);//Orient your camera (meaning the forward and up vectors) changing its angle in x
	void ChangeYaw(float fIncrement);//Orient your camera (meaning the forward and up vectors) changing its angle in x
	void ChangeRoll(float fIncrement);//Orient your camera (meaning the forward and up vectors) changing its angle in x
};

#endif //__CAMERA_MANAGER_SINGLETON_H_