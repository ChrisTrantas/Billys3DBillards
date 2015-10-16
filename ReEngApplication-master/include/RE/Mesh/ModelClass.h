/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MODELCLASS_H_
#define __MODELCLASS_H_

#include <thread>
#include "RE\Mesh\GroupClass.h"
#include "RE\System\FileReaderClass.h"
#include "RE\Animation\SequenceClass.h"
#include "RE\Animation\StateClass.h"

#include "RE\physics\BoundingObjectClass.h"

namespace ReEng
{

class ReEngDLL ModelClass
{	
	bool m_bLoaded = false;		//Loaded flag
	bool m_bBinded = false;		//Binded flag
	bool m_bVisible = true;	//Visibility flag
	bool m_bCollidable = false;	//Collidable flag

	uint m_nMaterials = 0;	//number of materials
	uint m_nGroups = 0;		//Number of groups
	uint m_nFrames = 0;		//Number of frames
	uint m_nStates = 0;		//Number of states
	uint m_nSequences = 0;	//Number of sequences
	int m_nHP = 1;			//Hit point of the model

	SystemSingleton* m_pSystem = nullptr;	//Pointer to the system
	MaterialManagerSingleton* m_pMatMngr = nullptr;	//Pointer to the Material Manager
	std::thread* m_Thread = nullptr;	//Thread on which the model is loading
	BoundingObjectClass* m_pBO = nullptr;	//Bounding Object

	String m_sName = "NULL";	//Name of the Model
		
	std::vector<GroupClass*> m_lGroup;	//List of groups
	std::vector<SequenceClass*> m_lSequence;	//List of sequences
	std::vector<BoundingObjectClass*> m_lBO;	//List of Bounding Objects (one per frame)
	std::vector<StateClass*> m_lState;	//List of states

	std::map<String,int> m_map;//Indexer of Groups
	std::map<String,int> m_mapStates;//Indexer of states
public:
	/* Constructor */
	ModelClass(void);
	/* Copy Constructor */
	ModelClass(const ModelClass& other);
	/* Copy Assignment operator*/
	ModelClass& operator=(const ModelClass& other);
	/* Destructor */
	~ModelClass(void);
	
	/* Releases the object from memory */
	void Release(void);

	/* Loads an obj file in memory */
	REERRORS CreateLoadOBJThread(String a_sFileName, bool a_bAbsoluteRoute);

	/* Swaps the information of one model object into another */
	void Swap(ModelClass& other);

	/* Asks the model for its number of groups */
	uint GetNumberOfGroups(void);
	/* Asks the model for its name */
	String GetName(void);
	/* Property GetName*/
	__declspec(property(get = GetName)) String Name;

	/* Asks the Model for a Group by index */
	GroupClass* GetGroup(uint a_nIndex);
	/* Asks the model identify the index of a group by name, -1 if not found*/
	int IdentifyGroup( String a_sName);

	/* Asks the model if its done loading */
	bool IsLoaded(void);

	/* Create a copy of a group by index */
	bool InstanceGroup(GroupClass* a_TargetGroup, uint a_nIndex);

	/* Binds the Model for opengl 3.x*/
	void CompileOpenGL3X(void);

	/* Sets the Hit Points of the model */
	void SetHP(int a_nHP);
	/* Asks the model for its Hit Points*/
	int GetHP(void);

	/* Sets the model to be collidable */
	void SetCollidable(bool a_bCollidable);
	/* Asks the model if its collidable */
	bool GetCollidable(void);

	/* Sets the model to be visible */
	void SetVisible(bool a_bVisible);
	/* Asks the model if its visible */
	bool GetVisible(void);

	/* 
	Asks the model for a list of vertices for a particular group's shape 
		Args:
			a_nGroup -> -1 for all groups
			a_nMesh -> -1 for all shapes
	*/
	std::vector<vector3> GetVertices(int a_nGroup = -1, int a_nMesh = -1);

	/* Get the number of frames of animation in this model */
	uint GetNumberOfFrames(void);

	/* Asks the model for its sequence List */
	std::vector<SequenceClass*> GetSequenceList(void);

	/* Asks the model for a sequence from its List of sequences */
	SequenceClass* GetSequence(uint a_nSequence);

	/* Asks the model for its number of states*/
	uint GetNumberOfStates(void);
	/* Asks the model for its number of states*/
	uint GetNumberOfSequences(void);
	/* Asks the model for a state by index */
	StateClass* GetState(uint a_nState);

	/* Asks the model the index of the provided state, -1 if not found */
	int IdentifyState(StateClass* a_pState);

	/* Asks the model the index of the provided state, -1 if not found */
	int IdentifyState(String a_sName);
	
	/*
	Asks the model for the Bounding Object of a particular frame of animation
		Args:
			a_nFrame -> -1 for the BO that contain the model at all frames
	*/
	BoundingObjectClass* GetBoundingObject(int a_nFrame = -1);

	/* Loads a model from an OBJ file*/
	REERRORS LoadOBJ(String a_sFileName, bool a_bAbsoluteRoute = false);

	/* Loads a model from an ATO file*/
	REERRORS LoadATO(String a_sFileName, bool a_bAbsoluteRoute = false);

	/* Loads a model from an ATO file*/
	REERRORS LoadBTO(String a_sFileName, bool a_bAbsoluteRoute = false);

	/* Saves a loaded model as an ATO file do not add the extension unless absolute route*/
	REERRORS SaveATO(String a_sFileName, bool a_bAbsoluteRoute);

	/* Saves a loaded model as an BTO file do not add the extension unless absolute route*/
	REERRORS SaveBTO(String a_sFileName, bool a_bAbsoluteRoute);

private:
	/* Initializates the model object */
	void Init(void);
	/* Loads the material file for this model */
	REERRORS LoadMTL(String a_sFileName);
	/* Loads the hierarchy file for this model */
	REERRORS LoadHIE(String a_sFileName);
	/* Loads the animation file for this model */
	REERRORS LoadANIM(String a_sFileName);
	/* Loads the sequence file for this model */
	REERRORS LoadSEQ(String a_sFileName);
	/* Loads the state file for this model */
	REERRORS LoadSTA(String a_sFileName);

	/* Asks the model for a group by name*/
	GroupClass* GetGroup(String a_sName);

	/* Asks the model for a state by name */
	StateClass* GetState(String a_sName);

	vector3 RoundVector(vector3 a_v3Vector, float fMargin = 0.0001f);

};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<ModelClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<ModelClass*>;

}

#endif //_MODEL_H