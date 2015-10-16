/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MESHDRAWERSINGLETON_H_
#define __MESHDRAWERSINGLETON_H_

#include "RE\System\SystemSingleton.h"
#include "RE\Mesh\MeshClass.h"
#include <map>

namespace ReEng
{
struct ReEngDLL MeshHandler
{
	int m_nInstances = 0;	//Number of intances to draw
	std::vector<matrix4> m_lToWorld;//List that holds the matrix per object

	/* Constructor */
	MeshHandler(void);
	/* Copy Constructor */
	MeshHandler(MeshHandler& other);
	/* Copy Assignment operator */
	MeshHandler& operator=(MeshHandler& other);
	/* Destructor */
	~MeshHandler(void);
	/* Converts the list of matrix into an array of floats */
	void GetMatrixArray(float* a_fArray);
};

//System Class
class ReEngDLL MeshDrawerSingleton
{
	int m_nMeshes; //number of elements in the list
	static MeshDrawerSingleton* m_pInstance; // Singleton pointer
	std::vector<MeshClass*> m_lMesh; //list of meshes
	std::vector<MeshHandler*> m_lMeshHandler; //list of mesh handlers
	float* m_fMatrix;	//List of matrices to render in float form;
	std::map<String,int> m_map; //Identifies the objects in the list.
public:

	/* Gets/Constructs the singleton pointer */
	static MeshDrawerSingleton* GetInstance();

	/* Destroys the singleton */
	static void ReleaseInstance(void);

	/* Adds a mesh to the mesh list*/
	int AddMesh(MeshClass* a_pMesh);

	/* Gets the mesh pointer from the vector specified by name */
	MeshClass* GetMesh(String a_sName);

	/* Gets the mesh pointer from the vector specified by index */
	MeshClass* GetMesh(int a_nIndex);

	/* Gets the mesh index from the vector specified by name */
	int GetMeshIndex(String a_sName);

	/* Renders a mesh on the specified space */
	void AddMeshToRenderList(MeshClass* a_pMesh, matrix4& a_m4ToWorld);

	/* Renders a mesh on the specified space */
	void AddMeshToRenderList(int  a_nIndex, matrix4& a_m4ToWorld);

	/* Renders the list of meshes */
	void Render(void);

private:
	/* Constructor */
	MeshDrawerSingleton(void);

	/* Copy Constructor */
	MeshDrawerSingleton(MeshDrawerSingleton const& other);

	/* Copy Assignment Operator */
	MeshDrawerSingleton& operator=(MeshDrawerSingleton const& other);

	/* Destructor */
	~MeshDrawerSingleton(void);

	/* Returns the index of the mesh in the list of meshes */
	int IdentifyMesh(MeshClass* a_pMesh);

	/* Initializates the objects fields */
	void Init(void);

	/* Releases the objects memory */
	void Release(void);

	/* Resets the render list */
	void ResetList(void);
};

}

#endif //__MESHRAWERSINGLETON_H_