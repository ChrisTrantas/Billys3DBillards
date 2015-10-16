/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __BoundingObjectCLASS_H_
#define __BoundingObjectCLASS_H_

#include "RE\Mesh\PrimitiveManagerSingleton.h"
using namespace ReEng;
//System Class
class ReEngDLL BoundingObjectClass 
{
	bool m_bVisibleOBB = false;		//Visibility of the Oriented Bounding Box
	bool m_bVisibleAABB = false;	//Visibility of the Axis Aligned Bounding Box
	bool m_bVisibleBS = false;		//Visibility of the Bounding Sphere

	float m_fRadius = 0.0f;		//Radius of the BS

	PrimitiveManagerSingleton* m_pPrimitiveMngr = nullptr;

	String m_sInstance = "NULL";		//The name of the instance related to this box

	vector3 m_v3ColorAABB;	//Color of the Axis Aligned Bounding Box
	vector3 m_v3ColorOBB;	//Color of the Oriented Bounding Box
	vector3 m_v3ColorBS;	//Color of the Bounding Sphere
	vector3 m_v3CentroidL;	//Centroid of the BO in local space
	vector3 m_v3MaxAABBG;	//Max of the AABB in global space
	vector3 m_v3MinAABBG;	//Min of the AABB in global space
	vector3 m_v3HalfWidth;	//half the( width(x) , height(y), depth(z) )of the box

	matrix4 m_m4ToWorld;	//Model matrix of the box
	matrix4 m_mOBB;			//Oriented Bounding Box Mesh
	matrix4 m_mAABB;		//Axis Aligned Bounding Box Mesh
	matrix4 m_mBS;			//Bounding Sphere Mesh

	std::vector<int> m_lOctant; //List of octants

public:
	/* Constructor 	*/
	BoundingObjectClass(std::vector<vector3> a_lVertex, matrix4 a_m4ToWorld, String a_sInstanceName);
	/* Constructor 	*/
	BoundingObjectClass(vector3 a_v3Center, float a_fSize);
	/* Copy Constructor */
	BoundingObjectClass(BoundingObjectClass const& other);
	/* Copy Assignment Operator	*/
	BoundingObjectClass& operator=(BoundingObjectClass const& other);
	/*	Destructor	*/
	~BoundingObjectClass(void);

	/* Gets the name of the model associated with this bounding box from model manager */
	String GetInstanceName(void);
	/* Property:
	GetInstanceName()*/
	__declspec(property(get = GetInstanceName)) String InstanceName;

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
	void SetVisibleOBB(bool a_bVisible);
	/*Gets the visibility of the OBB
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	bool GetVisibleOBB(void);
	/* Property: GetVisibleBS/SetVisibleOBB()*/
	__declspec(property(get = GetVisibleOBB, put = SetVisibleOBB)) bool VisibleOBB;
	
	/*Sets the visibility of the AABB
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	void SetVisibleAABB(bool a_bVisible);
	/*Gets the visibility of the AABB
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	bool GetVisibleAABB(void);
	/* Property: GetVisibleAABB/SetVisibleAABB()*/
	__declspec(property(get = GetVisibleAABB, put = SetVisibleAABB)) bool VisibleAABB;

	/*Sets the visibility of the BS
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	void SetVisibleBS(bool a_bVisible);
	/*Gets the visibility of the OBB
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	bool GetVisibleBS(void);
	/* Property: GetVisibleBS/SetVisibleBS() */
	__declspec(property(get = GetVisibleBS, put = SetVisibleBS)) bool VisibleBS;

	/* Gets the color vector of the AABB */
	vector3 GetColorAABB(void);
	/* Sets the color vector of the AABB */
	void SetColorAABB(vector3 a_v3Color);
	/* Property:
	GetColorAABB() or SetColorAABB() */
	__declspec(property(get = GetColorAABB, put = SetColorAABB)) vector3 ColorAABB;

	/* Gets the color vector of the OBB */
	vector3 GetColorOBB(void);
	/* Sets the color vector of the OBB */
	void SetColorOBB(vector3 a_v3Color);
	/* Property:
	GetColorOBB() or SetColorOBB() */
	__declspec(property(get = GetColorOBB, put = SetColorOBB)) vector3 ColorOBB;

	/* Gets the color vector of the BS */
	vector3 GetColorBS(void);
	/* Sets the color vector of the BS */
	void SetColorBS(vector3 a_v3Color);
	/* Property:
	GetColorBS() or SetColorBS() */
	__declspec(property(get = GetColorBS, put = SetColorBS)) vector3 ColorBS;

	/* Gets the centroid of the Bounding object in Local coordinates */
	vector3 GetCentroidLocal(void);
	/* Property:
	GetCentroidLocal() */
	__declspec(property(get = GetCentroidLocal)) vector3 CentroidLocal;
	/* Gets the  centroid of the Bounding object in Global coordinates*/
	vector3 GetCentroidGlobal(void);
	/* Property:
	GetCentroidGlobal() */
	__declspec(property(get = GetCentroidGlobal)) vector3 CentroidGlobal;
	/* Gets the HalfWidth vector of the object (half the size of each side)*/
	vector3 GetHalfWidth(void);
	/* Property:
	GetHalfWidth() */
	__declspec(property(get = GetHalfWidth)) vector3 HalfWidth;

	/* Gets the Radius size of the Bounding Sphere*/
	float GetRadius(void);
	/* Property:
	GetRadius() */
	__declspec(property(get = GetRadius)) float Radius;

	/* Reinitialize the Bounding Object from a subset of different Bounding Objects
	Args:
		a_vBO a List of the sub bounding objects
	*/
	void Reinitialize(std::vector<BoundingObjectClass*> a_vBO);

	/* Reinitialize the Bounding Object using the incomming BO with the specidied matrix)*/
	void Reinitialize(BoundingObjectClass& a_pBO, matrix4 a_m4ToWorld);

	/* Test agains another Bounding Object
		Args:
			other -> incoming object to test */
	bool IsColliding( BoundingObjectClass& other, bool a_bCheckOctants = true);
	/* Test agains a ray
		Args:
			a_v3RayOrigin -> The origin of the ray
			a_v3RayDirection -> The direction in which the ray is moving
			a_fDistance -> the distance in which the collision is happening from the origin
	*/
	bool IsColliding( vector3 a_v3RayOrigin, vector3 a_v3RayDirection, float& a_fDistance);

	/*
	SetsThe name of the Bounding Object
	*/
	void SetName(String a_sName);
	/*
	Gets the name of the Bounding Object
	*/
	String GetName(void);

	/*
		Sets the current object to know its in the specified octant
	*/
	void SetInOctantList(int a_nOctant);
	/*
		Sets the current object to know its in the specified octant list
	*/
	void SetOctantList(std::vector<int> a_vOctantList);
	/*
		Gets the octant list this object is into
	*/
	std::vector<int> GetOctantList(void);

	/*
		Clears the Octant List in this Bounding Object
	*/
	void ClearOctantList(void);

	/*
		Asks if the incomming Bounding Object is in at least one of the same octants
	*/
	bool InTheSameOctant(BoundingObjectClass& other);
	
	/* Renders the bounding box
		Args:
			a_v3Color -> determinate the color of the box to be rendered, if REDEFAULT
			it will render the shape in the constructed color (white) */
	void AddToRenderList( bool bForceDraw = false );

	/*
		Gets the Max vector of the AABB in global space
	*/
	vector3 GetAABBMax(void);

	/*
		Gets the Min vector of the AABB in global space
	*/
	vector3 GetAABBMin(void);

private:
	/* Released Memory and objects allocated. */
	void Release(void);
	/* Calculates the Oriented Bounding Box, Axis Alligned Bounding Box and the Bounding Sphere from the instance
	Args:
		a_lVertex: The vertices for which we want to create the BO from */
	void Initializate(std::vector<vector3> a_lVertex);

	/* Calculates the Axis Aligned Bounding Box from the instance from the OBB*/
	void CalculateAABB();
};
//
//EXPIMP_TEMPLATE template class ReEngDLL std::vector<BoundingObjectClass>;
//EXPIMP_TEMPLATE template class ReEngDLL std::vector<BoundingObjectClass*>;

#endif //__BoundingObjectClass_H__