/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __OCTREESINGLETON_H_
#define __OCTREESINGLETON_H_

#include "RE\system\SystemSingleton.h"
#include "RE\Physics\OctantClass.h"

namespace ReEng
{

//System Class
class ReEngDLL OctreeSingleton
{
	int m_nOctants = 0;			//Number of octants in the Tree
	int m_nMaxSubtrees = 0;		//Maximum sublevel of the tree
	int m_nMaxObjects = 0;		//Maximum number of objects per octant
	OctantClass* m_pRoot = nullptr;	//Root of the Tree
	static OctreeSingleton* m_pInstance; // Singleton pointer

public:
	/* Gets/Constructs the singleton pointer */
	static OctreeSingleton* GetInstance();
	/* Destroys the singleton */
	static void ReleaseInstance(void);

	/* Gets an octant from the tree by ID*/
	OctantClass* GetOctant(int a_nOctantID);

	/* Generates the Tree using the provided Bounding Object List and maximum levels and objects per octant */
	void GenerateOctree(std::vector<BoundingObjectClass*> a_lBoundingObject, int a_nMaxSubtrees = 4, int a_nMaxObjects = 2);
	
	/* Calculates the Octant(s) the provided Bounding object is currently located without reconstructing the tree*/
	void UpdatePositionInTree(BoundingObjectClass* a_pBO);

	/* Renders the Non-empty leaf octant nodes of the Octree*/
	void Render(void);

private:
	/* Constructor */
	OctreeSingleton(void);
	/* Copy Constructor */
	OctreeSingleton(OctreeSingleton const& other);
	/* Copy Assignment Operator */
	OctreeSingleton& operator=(OctreeSingleton const& other);
	/* Destructor */
	~OctreeSingleton(void);

	/* Releases the objects memory */
	void Release(void);
	/* Initializates the objects fields */
	void Init(void);

	/* Taverses the tree finding the octant nodes the provided Bounding Object collides with*/
	void TraverseUpdatePosition(OctantClass* a_pNode, BoundingObjectClass* a_pBO);

	/* Traverse the tree for rendering */
	void TraverseRender(OctantClass* a_pNode);

	/* Traverses the tree filling internal information */
	void TraverseInfo(OctantClass* a_pNode);

	/* Traverses finding the node that contains the specidied ID, it will store it in a_pOutput */
	void TraverseGet(OctantClass* a_pNode, OctantClass*& a_pOutput, int a_nID);

	/* Generates the 8 octant nodes for the specified a_pNode with a maximum level of subdivisions and max objects per node */
	void GenerateSubTree(OctantClass* a_pNode, bool a_bResetCount = false);

	/* Deletes the specidied node and subtrees */
	void DeleteNode(OctantClass*& a_pNode);
};

}

#endif //__OCTREESINGLETON_H_