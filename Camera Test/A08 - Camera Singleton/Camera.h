#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "RE\ReEngAppClass.h"

class Camera
{
private:
	matrix4 m_m4Projection;	// Projection Matrix
	matrix4 m_m4View;		// View Matrix

	vector3 m_v3Position;	// Position Vector3

	vector3  m_v3Orientation;	// Orientation vector3
	
	vector3 m_v3Up;		// The up vector. The direction the camera orients to make upward.
	vector3 m_v3Forward;// The forward vector. The direction the camera looks at.
	vector3 m_v3Right;	// The vector to the right of the camera. Used for side-to-side movement.

	bool m_bOrthogonal;	// When true, calculate projection matrix will crera
	 
	///<summary>
	/// When True, the camera will allows for Six Degrees of Freedom.
	/// The Up Direction will move with the orientation
	///<para> When False, the camera acts like a standard FPS where the Up direction stays constant.</para>
	///</summary>
	bool m_b6DoF;

	float m_fFOVy;			// The y-value of the field of view. Used in the perspective mode
	float m_fAspectRatio;	// The aspect ratio of the camera
	float m_fMinPlane;
	float m_fMaxPlane;
	float m_fHeight;		// Height of the orthographic mode 

	void Init();

	void CalculateView();	// Calculates the View Matrix
	void CalculateProjection();	// Calculates the Projection Matrix	
	void CalculateDirectionVectors(); // Calculates the direction vectors
public:
	Camera();
	~Camera();

	matrix4 GetView();
	matrix4 GetProjection();

	vector3 GetPosition();
	void SetPosition(vector3 a_v3Position);	// Sets the position, but does not change the orientation

	vector3 GetOrientation();
	void SetOrientation(vector3 a_v3Orientation);

	vector3 GetUp();
	void SetUp(vector3 a_v3Up);
	vector3 GetForward();
	void SetForward(vector3 a_v3Forward);


	// Focus Camera
	void LookAtDirection(vector3 a_v3Direction); // Sets the camera to look down a vector3
	void LookAtPosition(vector3 a_v3Target); // Sets the camera to look at a position in world space

	// Move Camera
	void MoveForward(float a_fIncrement);
	void MoveRight(float a_fIncrement);
	void MoveUp(float a_fIncrement);


	// Rotate Camera
	void ChangePitch(float a_fIncrement);
	void ChangeYaw(float a_fIncrement);
	void ChangeRoll(float a_fIncrement);
};

#endif //__CAMERA_H__