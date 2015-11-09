/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __AxisClass_H_
#define __AxisClass_H_

#include "RE\Mesh\PrimitiveManagerSingleton.h"
using namespace ReEng;
//System Class
class ReEngDLL AxisClass 
{
	bool m_bVisibleOrigin = false;	//Visibility of the Origin of the object
	bool m_bVisibleCenter = false;	//Visibility of the Center of the object
	bool m_bVisiblePivot =  false;	//Visibility of the Pivot of the object

	float m_fSize = 0.0f;

	vector3 m_v3Pivot;		//Pivot of rotation in local space
	vector3 m_v3Centroid;	//Centroid of shape in local space

	matrix4 m_m4ToWorld;//Model to World maatrix
	matrix4 m_mPivot;	//Pivot origin in global coordinates
	matrix4 m_mCentroid;//Centroid in global coordinates

	PrimitiveManagerSingleton* m_pPrimitiveMngr = nullptr;
public:
	/* Constructor 	*/
	AxisClass(void);
	/* Copy Constructor */
	AxisClass(AxisClass const& other);
	/* Copy Assignment Operator	*/
	AxisClass& operator=(AxisClass const& other);
	/*	Destructor	*/
	~AxisClass(void);


	/* Gets the "ModelToWorld" matrix associated with the bounding box */
	matrix4 GetModelMatrix(void);
	/* Sets the "ModelToWorld" matrix associated with the bounding box */
	void SetModelMatrix(matrix4 a_m4ToWorld);
	/* "ModelToWorld"
	GetModelMatrix() or SetModelMatrix() */
	__declspec(property(get = GetModelMatrix, put = SetModelMatrix)) matrix4 ModelMatrix;

	/*Sets the visibility of the OBB the AABB and the BS
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	void SetVisible(bool a_bVisible);
	/* Property:
	SetVisibleOBB()*/
	__declspec(property(put = SetVisible)) bool Visible;

	/*Sets the visibility of the OBB
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	void SetVisibleOrigin(bool a_bVisible);
	/* Property:
	SetVisibleOBB()*/
	__declspec(property(put = SetVisibleOrigin)) bool VisibleOrigin;
	
	/*Sets the visibility of the AABB
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	void SetVisiblePivot(bool a_bVisible);
	/* Property:
	SetVisibleAABB()*/
	__declspec(property(put = SetVisiblePivot)) bool VisiblePivot;

	/*Sets the visibility of the BS
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	void SetVisibleCentroid(bool a_bVisible);
	/* Property:
	SetVisibleBS()*/
	__declspec(property(put = SetVisibleCentroid)) bool VisibleCentroid;

	void SetCentroid(vector3 a_v3Centroid);
	void SetPivot(vector3 a_v3Pivot);
	void SetSize(float a_fSize);

	/* Renders the bounding box
		Args:
			a_v3Color -> determinate the color of the box to be rendered, if REDEFAULT
			it will render the shape in the constructed color (white) */
	void AddToRenderList( bool bForceDraw = false );

private:
	/* Released Memory and objects allocated. */
	void Release(void);
};
//
//EXPIMP_TEMPLATE template class ReEngDLL std::vector<AxisClass>;
//EXPIMP_TEMPLATE template class ReEngDLL std::vector<AxisClass*>;

#endif //__AxisClass_H__