/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MESHMANAGERSINGLETON_H_
#define __MESHMANAGERSINGLETON_H_

#include "RE\Mesh\MeshDrawerSingleton.h"
#include "RE\Mesh\PrimitiveManagerSingleton.h"
#include "RE\Mesh\ModelManagerSingleton.h"

namespace ReEng
{
//MeshManagerSingleton
class ReEngDLL MeshManagerSingleton
{
	static MeshManagerSingleton* m_pInstance; // Singleton pointer
public:
	MeshDrawerSingleton* m_pMeshDrawer = nullptr;//pointer to the Mesh Drawer singleton
	PrimitiveManagerSingleton* m_pPrimitiveMngr = nullptr; //pointer to the Primitive Manager singleton
	LineManagerSingleton* m_pLineManager = nullptr;//Singleton for the Lines manager
	ModelManagerSingleton* m_pModelMngr = nullptr; //pointer to the Model Manager singleton

	/* Gets/Constructs the singleton pointer */
	static MeshManagerSingleton* GetInstance();

	/* Destroys the singleton */
	static void ReleaseInstance(void);

	/* Saves the specified model file, needs to specify the file extension (ATO or BTO) */
	REERRORS SaveModel(	String a_sFileName,
						String a_sInstanceName,
						bool a_bAbsoluteRoute = false);

	/* Loads the specified model file */
	REERRORS LoadModel (	String a_sFileName,
							String a_sInstanceName,
							bool a_bAbsoluteRoute = false,
							matrix4 a_m4ToWorld = matrix4(1.0),
							int a_nVisibility = 1,
							int a_nCollidable = 1,
							int a_nState = 0);

	/* Loads the specified level file */
	void LoadLevel(String a_sFileName);

	/* Loads an add-on file for the specified instance*/
	REERRORS LoadAddOn(String a_sInstanceName, String a_sFileName);

	/* Sets the model matrix of an specific instance finding it by name */
	void SetModelMatrix(matrix4 a_m4ToWorld, String a_sInstance = "ALL", bool a_bUpdateOctree = false);

	/* Sets the model matrix of an specific instance finding it by index */
	void SetModelMatrix(matrix4 a_m4ToWorld, int a_nIndex, bool a_bUpdateOctree = false);

	/* Asks the manager for an specific instance's model to world matrix */
	matrix4 GetModelMatrix(String a_sInstance);

	/* Updates the model manager */
	void Update(bool a_bCheckCollisions = true);

	/* Renders a line on with the specified vectors and color */
	void AddLineToRenderList(vector3 a_v3Origin, vector3 a_v3Ending, vector3 a_v3Color = REYELLOW);

	/* Renders a mesh on the specified space */
	void AddMeshToRenderList(MeshClass* a_pMesh, matrix4& a_m4ToWorld);

	/* Renders a mesh on the specified space */
	void AddMeshToRenderList(int a_nIndex, matrix4& a_m4ToWorld);

	/* Render the axis on the specified position */
	void AddAxisToQueue(matrix4 a_m4ToWorld);

	/* Renders the cube on the specified position*/
	void AddPlaneToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT);

	/* Renders the cube on the specified position*/
	void AddCubeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the cone on the specified position*/
	void AddConeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the cylinder on the specified position*/
	void AddCylinderToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the tube on the specified position*/
	void AddTubeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the torus on the specified position*/
	void AddTorusToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the sphere on the specified position*/
	void AddSphereToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the CameraMesh on the specified position*/
	void AddCameraToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT);

	/* Renders the specified instance */
	void AddInstanceToRenderList(String a_sInstance = "ALL");

	/* Renders the list of meshes */
	void Render(void);

	/* Asks the Manager for the number of models */
	int GetNumberOfModels(void);

	/* Asks the Manager for the number of instances */
	int GetNumberOfInstances(void);

	/* Asks the name of the specified instance by its index returns empty if not found */
	String GetNameOfInstanceByIndex(int a_nIndex);

	/* Gets the Instance by an index number */
	InstanceClass* GetInstanceByIndex(int a_nIndex);

	/* Gets the Instance by a name */
	InstanceClass* GetInstanceByName(String a_sInstanceName);

	/* Asks for the Bounding Object of the specified instance by index*/
	BoundingObjectClass* GetBoundingObject(int a_nIndex);

	/* Asks for the Bounding Object of the specified instance by name*/
	BoundingObjectClass* GetBoundingObject(String a_sInstanceName);

	/* Asks the manager for the list of vertices of an specified instance */
	std::vector<vector3> GetVertices(String a_sInstanceName);

	/* Asks the manager if an instance with this name has been created */
	bool IsInstanceCreated(String a_sInstanceName);

	/* Sets the visibility flag of the Bounding Object */
	void SetVisibleBoundingObject(bool a_bVisible, String a_sInstanceName = "ALL");

	/* Sets the visibility flag of the Bounding Object */
	void SetVisibleBoundingObject(bool a_bVisible, int a_nInstanceIndex);

	/* Returns a vector4 with the indices of the Instances and groups colliding */
	std::vector<vector4> GetCollisionList(void);

	/* Returns the index of the specified instance name, -1 if not found */
	int IdentifyInstance(String a_sInstanceName);

	/* Sets the shader program of an specific instance by name */
	void SetShaderProgramByName(String a_sInstanceName = "ALL", String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);

	/* Sets the shader program of an specific instance by index */
	void SetShaderProgramByNumber(int a_nInstance = -1, int a_nGroup = -1, String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);

	/* Sets the visibility of the axis of the instance */
	void SetVisibleAxis(bool a_bVisible, String a_sInstanceName = "ALL", bool a_bAllGroups = false);

	/* Sets the visibility of the hierarchical Bounding Object */
	void SetVisibleBoundingObjectHierarchy(bool a_bVisible, String a_sInstanceName = "ALL");

private:
	/* Constructor */
	MeshManagerSingleton(void);

	/* Copy Constructor */
	MeshManagerSingleton(MeshManagerSingleton const& other);

	/* Copy Assignment Operator */
	MeshManagerSingleton& operator=(MeshManagerSingleton const& other);

	/* Destructor */
	~MeshManagerSingleton(void);

	/* Initializates the objects fields */
	void Init(void);

	/* Releases the objects memory */
	void Release(void);
};

}

#endif //__MESHMANAGERSINGLETON_H_