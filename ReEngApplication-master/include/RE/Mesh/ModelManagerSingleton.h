/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MODELMANAGERSINGLETON_H_
#define __MODELMANAGERSINGLETON_H_

#include <string>
#include "RE\Mesh\InstanceClass.h"
#include "RE\Mesh\LineManagerSingleton.h"
#include "RE\Physics\OctreeSingleton.h"

namespace ReEng
{

class ReEngDLL ModelManagerSingleton
{
	//Member variables
	bool m_bVisibleOctree = false; //Visibility of the Octree flag

	uint m_nInstances = 0;		//Number of instances
	uint m_nModels = 0;			//Number of models

	static ModelManagerSingleton* m_pInstance;
	MaterialManagerSingleton* m_pMatMngr = nullptr; //Material Manager pointer
	LineManagerSingleton* m_pLineMngr =  nullptr;	//Line Manager Pointer
	OctreeSingleton* m_pOctree = nullptr;		//Octree pointer

	std::vector<vector4> m_lCollidingGroup; //List of colliding Objects
	std::vector<ModelClass*> m_lModel; //Vector of Models
	std::vector<InstanceClass*> m_lInstance; //Vetor of Model Instances

	std::map<String,int> m_mapModel;
	std::map<String,int> m_mapInstance;
public:
	//Accessors
	/* Gets/Constructs the singleton pointer */
	static ModelManagerSingleton* GetInstance();

	/* Destroys the singleton */
	static void ReleaseInstance();
	
	/* Asks the Manager for the number of models */
	int GetNumberOfModels(void);
	/* Asks the Manager for the number of instances */
	int GetNumberOfInstances(void);
	
	/* Sets the shader program of an specific instance */
	void SetShaderProgram(String a_sInstanceName, String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName);
	/* Sets the shader program of an specific instance by name */
	void SetShaderProgramByName(String a_sInstanceName = "ALL", String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);
	/* Sets the shader program of an specific instance by index */
	void SetShaderProgramByNumber(int a_nInstance = -1, int a_nGroup = -1, String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);

	/* Sets the model matrix of an specific instance finding it by name */
	void SetModelMatrix(matrix4 a_mMatrix, String a_sInstance = "ALL", bool a_bUpdateOctree = false);

	/* Sets the model matrix of an specific instance finding it by index */
	void SetModelMatrix(matrix4 a_mMatrix, int a_nInstance = -1, bool a_bUpdateOctree = false);
	
	/* Asks the manager for an specific instance's model to world matrix */
	matrix4 GetModelMatrix(String a_sInstance);

	/* Asks the manager for the list of vertices of an specified instance */
	std::vector<vector3> GetVertices(String a_sInstanceName);
	
	/* Sets the visibility of the octree */
	void SetVisibleOctree(bool a_bVisibleOctree);

		/* Sets the Visibility of the Grand Bounding object of an specified instance by name*/
	void SetVisibleGrandBoundingObject(bool a_bVisibleOB, String a_sInstance = "ALL");
	/* Sets the Visibility of the Grand Bounding object of an specified instance by group*/
	void SetVisibleGrandBoundingObject(bool a_bVisibleOB, int a_nIndex);

	/* Sets the Visibility of the Frame Bounding object of an specified instance by name*/
	void SetVisibleFrameBoundingObject(bool a_bVisibleOB, String a_sInstance = "ALL", String a_sGroup = "ALL");
	/* Sets the Visibility of the Frame Bounding object of an specified instance by group*/
	void SetVisibleFrameBoundingObject(bool a_bDebug, int a_nIndex, int a_nGroupIndex);
	
	/* Asks the manager for the name of an instance by index returns empty if nothing found */
	String GetInstanceName(uint a_nIndex);

	/*
		Gets the current state of the model
		input:
			a_sInstanceName: Name of the model to look
		output: -1 if model does not exist
	*/
	int GetCurrentState(String a_sInstanceName);

	/*
		Gets the current state of the model
		input:
			a_nInstanceIndex: Index of the model to look
		output: -1 if model does not exist
	*/
	int GetCurrentState(uint a_nInstanceIndex);

	/* Sets the next state of the specified instance */
	void SetNextState(String a_sIntance, int a_nNextState);

	/* Sets the visibility of an specified instance axis */
	void SetVisibleAxis(bool a_bVisible, String a_sInstanceName = "ALL", bool a_bGroups = false);
	
	/* Loads the specified level file */
	void LoadLevel(String a_sFileName);

	/* Saves the model as a ATO do not add the extension unless it's an absolute route*/
	REERRORS SaveATO(String a_sFileName, bool a_bAbsoluteRoute, String a_sInstance);

	/* Saves the model as a BTO do not add the extension unless it's an absolute route*/
	REERRORS SaveBTO(String a_sFileName, bool a_bAbsoluteRoute, String a_sInstance);

	/* Loads the specified model file in a separate thread*/
	REERRORS LoadModel (	String a_sFileName,
							String a_sInstanceName,
							bool a_bAbsoluteRoute = false,
							matrix4 a_m4ToWorld = matrix4(1.0),
							int a_nVisibility = 1,
							int a_nCollidable = 1,
							int a_nState = 0); //Creates an instance of the specified model.

	/* Removes the specified instance from the list */
	void DeleteInstance(String a_sInstance = "ALL");
	
	/* Asks the manager for the index of the model in the model list, -1 if the model is not part of it */
	int IdentifyModel(String a_sFileName);
	/* Asks the manager for the index of the instance in the instance list, -1 if the instance is not part of it */
	int IdentifyInstance(String a_sName);

	/* Modifies the material of the specified instance */
	void ModifyMaterial(	String a_sInstance,
							String a_sOldMaterialName,
							String a_sNewMaterialName,
							String a_sDiffuseTexture = "Original",
							String a_sNormalTexture = "Original",
							String a_sSpecularTexture = "Original");

	/* Loads an add-on file for the specified instance*/
	REERRORS LoadAddOn(String a_sInstanceName, String a_sFileName);

	/* Sets the list of octants an instance is located on */
	void SetOctantList(std::vector<int> a_lOctant, String a_sInstance);

	/* Plays the specified animation */
	void PlayAnimation(String a_sInstanceName, int a_nSequenceIndex = -1);
	
	/* Checks if the instance in done animating*/
	bool IsInstanceInLastFrame(String a_sInstanceName);

	/* Updates the model map*/
	void UpdateMap(void);

	/* Updates the model manager */
	void Update(bool a_bCheckCollisions = true);

	/* Renders the specified instance */
	void AddInstanceToRenderList(String a_sInstance = "ALL");

	/* Generate the octree based on the currently loaded instances*/
	void GenerateOctree(void);
	
	/* Checks the collision of all the instances (only optimized if GenerateOctree has been previously called*/
	void CollisionCheck(void);

	/* Responds to the collision of all the instances */
	void CollisionResponse(void);
	/*
	Asks the manager for the collision list
	Return:
			This method returns a list of vector4 containg the list of objects colliding, the format of the v4 is as follows:
				<Instance1Index, GroupIndexOfInstance1, Instance2Index, GroupIndexOfInstance2>
			The list will be empty if no collisions are detected
	*/
	std::vector<vector4> GetCollisionList(void);
	/* 
	Aks the manager for the colliding groups of two instances by name
	Return:
			This method returns a list of vector2 containing the colliding groups of the first instance vs the groups that are colliding with from the second one
			<Instance1GroupIndex, Instance2GroupIndex>
			The list will be empty if no collisions are detected
	*/
	std::vector<vector2> GetCollidingGroups(String a_sInstanceName1, String a_sInstanceName2);
	/* 
	Aks the manager for the colliding groups of two instances by index
	Return:
			This method returns a list of vector2 containing the colliding groups of the first instance vs the groups that are colliding with from the second one
			<Instance1GroupIndex, Instance2GroupIndex>
			The list will be empty if no collisions are detected
	*/
	std::vector<vector2> GetCollidingGroups(int a_nInstance1, int a_nInstance2);

	/* Asks the manager to generate a ray from the point of vew of the camera and the mouse coordinates, last argument will aks if the method should draw the ray*/
	vector2 ShootRay(vector4 a_v4RayOrigin, vector4 a_v4RayEnd, int a_nIgnoreInstance = -1, bool a_bDrawRay = false);
	vector2 ShootRay(vector4 a_v4RayOrigin, vector4 a_v4RayEnd, String a_sInstanceName, bool a_bDrawRay = false);
	vector2 ShootRay(int a_nMouseX, int a_nMouseY, CameraManagerSingleton* a_pCamera, int a_nIgnoreInstance = -1, bool a_bDrawRay = false);
	vector2 ShootRay(int a_nMouseX, int a_nMouseY, CameraManagerSingleton* a_pCamera, String a_sInstanceName, bool a_bDrawRay = false);
	
	/* Asks the manager for the instance and group a ray is colliding with. will return -1 for both instance or group if no collision is detected */
	vector2 CheckCollission(vector3 a_v3RayOrigin, vector3 a_v3RayDirection, int a_nIgnoreInstance = -1);

	/* Updates the position of the specified instance in the octree */
	void UpdatePositionInOctree(String a_sInstance = "ALL");

	/* Updates the position of the specified instance in the octree */
	void UpdatePositionInOctree(int a_nInstance = -1);

	/* Asks the Manager for an instance using the provided index, nullptr if not found*/
	InstanceClass* GetInstanceByIndex(uint a_nIndex);

	/* Asks the Manager for an instance using the provided name, nullptr if not found*/
	InstanceClass* GetInstanceByName(String a_sInstanceName);

	/* Asks the Manager for an instance using the provided index, nullptr if not found*/
	ModelClass* GetModelByIndex(uint a_nIndex);

	/* Pushes an Instance into the Instance list*/
	void PushInstance(InstanceClass* a_pInstance);
private:
	//Rule of Three
	/* Constructor */
	ModelManagerSingleton(void);
	/* Copy Constructor */
	ModelManagerSingleton(const ModelManagerSingleton& other);
	/* Copy Assignment Operator */
	ModelManagerSingleton& operator=(const ModelManagerSingleton& other);
	/* Destructor */
	~ModelManagerSingleton(void);
	
	//Member Functions
	/* Releases the object from memory */
	void Release(void);
	/* Initializes the objec's fields */
	void Init(void);
};

}

#endif //__MODELMANAGERSINGLETON_H_