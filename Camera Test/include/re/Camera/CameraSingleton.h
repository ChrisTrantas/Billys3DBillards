/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __CAMERASINGLETON_H_
#define __CAMERASINGLETON_H_

#include "RE\system\SystemSingleton.h"

//Quaternion implementation based on the quaternion camera:
//http://hamelot.co.uk/visualization/moderngl-camera/
namespace ReEng
{

class ReEngDLL CameraSingleton
{
	float m_fFieldOfView = 0.0f;//Field of view of the camera
	float m_fAspectRatio = 0.0f;//Aspect ratio of the view
	float m_fNear = 0.01f;		//Near clipping plane
	float m_fFar = 1000.0f;		//Far clipping plane

	float m_fHeading = 0.0f;	//Heading orientation
	float m_fPitch = 0.0f;		//Pitch orientation

	float m_fPitchRateMax = 0.0f;	//Maximum pitch displacement
	float m_fHeadingRateMax = 0.0f;	//Maximum heading displacement

	static CameraSingleton* m_pInstance;	//Singleton
	SystemSingleton* m_pSystem = nullptr;	//System pointer

	vector3 m_v3Position; //CameraPosition
	vector3 m_v3Forward; //Camera view vector
	vector3 m_v3Up; //Camera up vector

	vector3 m_v3PositionDelta; //Difference in position
	vector3 m_v3LookAt; //Point to which the camera is looking at

	matrix4 m_m4Projection; //Projection
	matrix4 m_m4View; //View
	matrix4 m_m4MVP; //MVP

	matrix4 m_m4ViewInverse; //Inverse of the view
	matrix4 m_m4VPInverse; // Inverse of the View-Projection matrix

public:
	/*
		Gets/Constructs the singleton pointer
	*/
	static CameraSingleton* GetInstance();
	/*
		Destroys the singleton
	*/
	static void ReleaseInstance(void);

	/*
		Translates the camera forward or backward
	*/
	void MoveForward(float a_fDistance = 0.1f);
	/*
		Translates the camera horizontally
	*/
	void MoveSideways(float a_fDistance = 0.1f);
	/*
		Translates the camera vertically
	*/
	void MoveVertical(float a_fDistance = 0.1f);

	/*
		Sets the camera position by the specified vector3
	*/
	void SetPosition(vector3 a_v3Position);
	/*
		Gets the position of the camera in world space
	*/
	vector3 GetPosition(void);

	/*
		Gets the point the camera is looking at
	*/
	vector3 GetTarget(void);

	/*
		Sets the camera at the specified position looking at the specified point
	*/
	void SetPositionAndView(vector3 a_v3Position, vector3 a_v3Target);

	/*
		Sets the direction of the view vector of the camera
	*/
	void SetForwardVector(vector3 a_v3Forward);
	/*
		Gets the view direction vector in world space
	*/
	vector3 GetForwardVector(void);

	/*
		Sets the up vector of the camera
	*/
	void SetUpVector(vector3 a_v3Direction);
	/*
		Gets the up vector of the camera in world space
	*/
	vector3 GetUpVector(void);

	/*
		Calculates the view of the camera
	*/
	void CalculateView();
	/*
		Sets the view of the camera by the specified matrix
	*/
	void SetView(matrix4 a_m4View);
	/*
		Gets the view of the camera singleton
	*/
	matrix4 GetView(void);

	/*
		Gets the view of the camera singleton
	*/
	matrix4 GetViewInverse(void);

	/*
		Returns a matrix that would position a 1x1 plane right in front of camera
	*/
	matrix4 GetCameraPlane(void);

	/*
		Returns the space 1.2085 units in front of camera (where 1 is the top border and -1 is the bottom border
	*/
	matrix4 GetCameraSpaceAdjusted(void);

	/*
		Calculates the projection of the camera
	*/
	void CalculateProjection();
	/*
		Sets the projection of the camera by the specified matrix
	*/
	void SetProjection(matrix4 a_m4Projection);
	/*
		Asks the camera singleton for the projection
	*/
	matrix4 GetProjection();
	
	/*
		Gets the inverse of the View Projection matrix of the camera
	*/
	matrix4 GetInverseVP();
	/*
		Gets the View-Projection matrix of the camera
	*/
	matrix4 GetVP();
	/*
		Gets the Model-View-Projection matrix of the camera specifying the model view matrix
	*/
	matrix4 GetMVP(matrix4 a_m4ToWorld);

	/*
		Sets the camera to be looking at the specified point in global space
	*/
	void SetView(vector3 a_v3Target);

	/*
		Asks the camera for its field of view
	*/
	float GetFieldOfView(void);
	/*
		Asks the camera for its near clipping plane
	*/
	float GetNear(void);
	/*
		Asks the camera for its far clipping plane
	*/
	float GetFar(void);
	/*
		Prints the information of the camera in the console
	*/
	void PrintInfo(void);

	/*
		Changes the pitch by the degree input
	*/
	void ChangePitch(float degrees);
	/*
		Changes the heading by the degree input
	*/
	void ChangeHeading(float degrees);

private:
	/* Constructor */
	CameraSingleton(void);
	/* Copy Constructor*/
	CameraSingleton(CameraSingleton const& other);
	/* Copy Assignment Operator*/
	CameraSingleton& operator=(CameraSingleton const& other);
	/* Destructor */
	~CameraSingleton(void);

	/* Releases the object from memory */
	void Release(void);
	/* Initialized the object's fields*/
	void Init(void);
};

}
#endif //_CAMERA_H