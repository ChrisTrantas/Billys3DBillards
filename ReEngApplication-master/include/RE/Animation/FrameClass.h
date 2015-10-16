/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __FRAMECLASS_H_
#define __FRAMECLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{

class ReEngDLL FrameClass
{
	bool m_bKeyframe = true;
	bool m_bVisible = true;
	vector3 m_v3Translation = vector3(0.0f);
	vector3 m_v3Rotation = vector3(0.0f);
	vector3 m_v3Scale = vector3(1.0f);
	matrix4 m_m4Transformation = matrix4(1.0f);
public:
	
	//Constructor
	FrameClass();
	//Copy Constructor
	FrameClass(const FrameClass& other);
	//Copy Assignment Operator
	virtual FrameClass& operator=(const FrameClass& other);

	//Destructor
	~FrameClass(void);

	matrix4 GetTransformation(void);
	matrix4 ComputeTransformation(	vector3 a_v3Translation,
									vector3 a_v3Pivot,
									vector3 a_v3Rotation,
									vector3 a_v3Scale,
									bool a_bVisible,
									bool a_bKeyFrame,
									matrix4 a_m4ToParent = matrix4(1.0f));
	matrix4 ComputeTransformation(matrix4 a_m4ToParent);
	matrix4 ComputeTransformation(vector3 a_v3Pivot);
	
	bool IsKeyframe(void);
	void SetVisible(bool a_bVisible);
	bool IsVisible(void);
	void SetKeyframe(bool a_bKeyframe);

	void SetPosX( float a_fValue );
	void SetPosY( float a_fValue );
	void SetPosZ( float a_fValue );

	void SetAngX( float a_fValue );
	void SetAngY( float a_fValue );
	void SetAngZ( float a_fValue );

	void SetSizeX( float a_fValue );
	void SetSizeY( float a_fValue );
	void SetSizeZ( float a_fValue );

	/* Gets the Position */
	vector3 GetPos(void);
	/* Gets the Rotation */
	vector3 GetAng(void);
	/* Gets the Scale */
	vector3 GetSize(void);

	float GetPosX( void );
	float GetPosY( void );
	float GetPosZ( void );

	float GetAngX( void );
	float GetAngY( void );
	float GetAngZ( void );

	float GetSizeX( void );
	float GetSizeY( void );
	float GetSizeZ( void );
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<FrameClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<FrameClass*>;

}
#endif //__ANIMATIONFRAMECLASS_H_