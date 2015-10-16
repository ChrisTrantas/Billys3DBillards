/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __GROUP_H_
#define __GROUP_H_

#include "RE\Materials\MaterialManagerSingleton.h"
#include "RE\Animation\FrameClass.h"
#include "RE\Animation\AnimationClass.h"
#include "RE\Physics\BoundingObjectClass.h"
#include "RE\Mesh\MeshDrawerSingleton.h"
#include "RE\mesh\AxisClass.h"

namespace ReEng
{

class ReEngDLL GroupClass
{	
	bool m_bVisible = true;	//Visibility flag
	bool m_bVisibleBO = false;	//Debug flag
	bool m_bCollidable = false;	//Collision flag
	bool m_bGlobalized = false;	//Global coordinates flag
	bool m_bModified = false;	//Modified flag

	int m_nHP = 0;			//Hit Points of this group
	uint m_nShapes = 0;		//number of shapes in this group
	uint m_nFrames = 0;		//Frames in this group
	
	SystemSingleton* m_pSystem = nullptr;	//System pointer
	MaterialManagerSingleton* m_pMatMngr = nullptr;//Material Manager Pointer
	MeshDrawerSingleton* m_pMeshDrawer = nullptr;//Mesh Manager Pointer
	GroupClass* m_pParent = nullptr;	//Parent group pointer
	FrameClass* m_pFrame = nullptr;	//List of frames of animation in the group
	BoundingObjectClass* m_pBO = nullptr;	//Bounding Object of the group
	AxisClass* m_pAxis = nullptr;		//Axis of the group
	
	String m_sName = "NULL";			//Name of the group
	String m_sParent = "NULL";		//Name of the parent of the group

	vector3 m_v3Pivot;		//Point in which the point is going to rotate around
	matrix4 m_m4ToWorld;	//Model to world matrix

	std::vector<MeshClass*> m_lMeshList;//List of shapes that compose the group
	std::vector<int> m_lMesh; //List of Meshes that compose a group
	std::vector<int> m_lMeshM; //List of Meshes that compose a group when modified
	matrix4 m_m4Mesh; //List of matrices for all Meshes that compose a group

public:
	GroupClass(void);
	GroupClass(const GroupClass& other);
	GroupClass& operator=(const GroupClass& other);
	~GroupClass(void);
	
	void Release(void);

	void Swap(GroupClass& other);

	int GetNumberOfShapes(void); //Returns the number of shapes in the vector of shapes
	String GetName(void); //Return the name of the group
	void SetName(String a_sName);
	__declspec(property(get = GetName, put = SetName)) String Name; //Name Property

	MeshClass* GetMesh(uint a_nIndex);//Returns the shape in the given index

	void RemoveEmptyMeshes(void);

	void AddShape(String a_sName);

	void CompileOpenGL3X( void );

	int IdentifyShapeByMaterial( String a_sName);

	bool CloneFromGroup(const GroupClass& other);

	void ReleaseOpenGL(); //DeleteOpenGL

	void CompleteMissingShapeInfo(bool a_bAverageNormals = false);

	void SwapMaterial( String a_sOldMaterialName, String a_sNewMaterialName);

	void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName, vector3 a_v3Tint = REDEFAULT);
	void SetShaderProgram(String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);

	void SetMaterial(String a_sMaterialName);

	vector3 GetPivot(void);
	void SetPivot(vector3 a_v3Pivot);

	void SetParent(GroupClass* a_pParent);

	void SetHP(int a_nHP);
	int GetHP(void);

	void SetCollidable(bool a_bCollidable);
	bool GetCollidable(void);

	void SetVisible(bool a_bVisible);
	bool GetVisible(void);

	String GetParentName(void);
	void SetParentName(String a_sParent);

	FrameClass GetFrame(uint nFrame);

	void SetGlobalized(bool a_bGlobalized);

	int GetNumberOfFrames(void);

	void GenerateFrames(int a_nFrames);

	void ReleaseFrames(void);

	void SetFrame(int a_nFrame, vector3 a_v3Translation, vector3 a_v3Rotation, vector3 a_v3Scale, bool a_bVisible, bool a_bKeyframe);

	void SetPosX( float a_fValue, int a_nFrame);
	void SetPosY( float a_fValue, int a_nFrame);
	void SetPosZ( float a_fValue, int a_nFrame);

	void SetAngX( float a_fValue, int a_nFrame);
	void SetAngY( float a_fValue, int a_nFrame);
	void SetAngZ( float a_fValue, int a_nFrame);

	void SetSizeX( float a_fValue, int a_nFrame);
	void SetSizeY( float a_fValue, int a_nFrame);
	void SetSizeZ( float a_fValue, int a_nFrame);

	void SetVisible( bool a_bValue, int a_nFrame);
	void SetKeyframe( bool a_bValue, int a_nFrame);
	void SetVisibleBO(bool a_bVisibleBO);
	void SetVisibleAxis(bool a_bVisible);

	void ComputeMatrix(void);

	void Interpolate(int a_nFrames);

	glm::mat4& GetModelMatrix(void);

	matrix4 TraverseHierarchy(GroupClass* a_Group, int a_nFrame = 0);

	std::vector<vector3> GetVertices(int a_nShape = -1);

	void Update(uint a_nFrame, matrix4 a_mToWorld);

	BoundingObjectClass* GetBoundingObject(void);
	void CompileBoundingObject(void);
	void SetBoundingObject(BoundingObjectClass* a_pBO);

	bool IsColliding( vector3 a_v3RayOrigin, vector3 a_v3RayDirection, float& a_fDistance );

	void DisconectAnimationFrames(void);

	void SetModelMatrix(matrix4 a_nMatrix);

	void AddToRenderList(uint a_nFrame = 0);//Add all shapes to the render list
	void AddBOToRenderList(bool a_bForce = false);//Render all debug
	void AddAxisToRenderList(bool a_bForce = false);//Render all debug

private:
	void Init(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<GroupClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<GroupClass*>;

}
#endif //__GROUP_H__