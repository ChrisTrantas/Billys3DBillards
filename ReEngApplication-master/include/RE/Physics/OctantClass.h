/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __OCTANTCLASS_H_
#define __OCTANTCLASS_H_

#include "RE\System\SystemSingleton.h"
#include "RE\Mesh\PrimitiveManagerSingleton.h"
#include "RE\Physics\BoundingObjectClass.h"

namespace ReEng
{

//System Class
class ReEngDLL OctantClass
{
	/* The fields of this class will be declared as public to reduce the overhead of the accessors, thus sacrificing security over speed
	 this shouldnt represent an issue due the fact that octants are not meant to be used as individual objects but as part of an octree class*/
public:
	bool m_bEmpty = true;	//Is the octant Empty?
	bool m_bLeaf = true;	//Is the octant a leaf?
	
	int m_nLevel = 0;	//Level of the octant in the tree
	int m_nID = 0;		//ID of the octant
	
	float m_fSize = 0.0f;	//Size of the octant m_fSize^3 is its volume

	OctantClass* m_pParent = nullptr;	//Parent of the octant in the tree
	OctantClass* m_pChild[8];	//Children of the octant
	BoundingObjectClass* m_pBO = nullptr;	//Bounding object of the octant

	vector3 m_v3CenterG;//Center of the Octant in world coordinates

	std::vector<BoundingObjectClass*> m_lBoundingObject;//List of bounding objects inside the octant
	
// Methods

	/* Constructor */
	OctantClass(void);
	/* Copy constructor */
	OctantClass(OctantClass const& other);
	/* Copy Assignment Operator */
	OctantClass& operator=(OctantClass const& other);
	/* Destructor */
	~OctantClass(void);

	////Properties
	///* Asks the Octant if its a Leaf */
	//bool IsLeaf(void);
	///* Asks the octant if its colliding with any Bounding Objects */
	//bool IsEmpty(void);
	///* Asks the octant for its bounding object list */
	//std::vector<BoundingObjectClass*> GetBoundingObjectList(void);
	///* Sets the Bounding Object List for the octant */
	//void SetBoundingObjectList(std::vector<BoundingObjectClass*> a_lBoundingObject);
	///* Sets the size of the octant */
	//void SetSize(float a_fSize);
	///* Sets the center of the octant */
	//void SetCenter(vector3 a_v3Center);
	///* Gets the specified child of the octant */
	//OctantClass* GetChild(int a_nOctant);

	
	/* Renders the AABB of the octant if its not empty */
	void Render();
	
	/* Calculates the collider of the octant based on the center and its size */
	void CalculateCollider(void);
	
private:
	/* Releases the object from memory */
	void Release(void);

	/* Initialize the object's fields */
	void Init(void);

	/* Swaps the content of one octant with another */
	void Swap(OctantClass& other);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<OctantClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<OctantClass*>;

}

#endif //__OctantClass_H__