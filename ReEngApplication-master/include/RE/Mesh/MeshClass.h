/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MESHCLASS_H_
#define __MESHCLASS_H_

#include "RE\System\SystemSingleton.h"
#include "RE\Camera\CameraManagerSingleton.h"
#include "RE\Materials\MaterialManagerSingleton.h"
#include "RE\Light\LightManagerSingleton.h"
#include "RE\System\ShaderManagerSingleton.h"
#include <vector>

namespace ReEng
{

//System Class
class ReEngDLL MeshClass
{
protected:
	bool m_bBinded = false; //Binded flag
	bool m_bCopy = false;	//Checks to see if this Mesh is a copy or the original
	bool m_bWire = false;	//Checks to see if the Mesh is going to be drawn in wires
	int m_nVertexCount = 0; //Number of vertices in this Mesh
	int m_nMaterial = 0; //Material index of this mesh

	GLuint m_vao = 0;			//OpenGL Vertex Array Object
	GLuint m_VertexBuffer = 0;	//OpenGL Buffer (Will hold the vertex buffer pointer)
	GLuint m_ColorBuffer = 0;	//OpenGL Buffer (Will hold the color buffer pointer)
	GLuint m_UVBuffer = 0;		//OpenGL Buffer (Will hold the UV buffer pointer)
	GLuint m_NormalBuffer = 0;	//OpenGL Buffer (will hold the Normal Buffer)
	GLuint m_TangentBuffer = 0;	//OpenGL Buffer (will hold the Tangent Buffer)
	GLuint m_BinormalBuffer = 0;//OpenGL Buffer (will hold the Binormal Buffer)
	GLuint m_nShader = 0;	//Index of the shader
	GLuint m_nShaderO = 0;	//Index of the original shader

	CameraManagerSingleton* m_pCamera = nullptr;				//Pointer to the singleton of CameraSingleton
	MaterialManagerSingleton* m_pMatMngr = nullptr;		//Material Manager
	LightManagerSingleton* m_pLightMngr = nullptr;		//Light Manager
	ShaderManagerSingleton* m_pShaderMngr = nullptr;	//Shader Manager

	String m_sName = "NULL";	//Identifier of the Mesh
	vector3 m_v3Tint; //Color modifier
	
	std::vector<vector3> m_lVertexPos;	//List of Vertices
	std::vector<vector3> m_lVertexCol;	//List of Colors
	std::vector<vector3> m_lVertexNor;	//List of Normals
	std::vector<vector3> m_lVertexTan;	//List of Tangents
	std::vector<vector3> m_lVertexBin;	//List of Binormals
	std::vector<vector3> m_lVertexUV;		//List of UVS
	
public:
	/* Constructor */
	MeshClass(void);
	/* Copy Constructor */
	MeshClass(MeshClass const& other);
	/* Copy Assignment Operator*/
	MeshClass& operator=(MeshClass const& other);
	/* Destructor */
	~MeshClass(void);

	/* Swaps the contents of the object with another object's content */
	void Swap(MeshClass& other);

	/* Compiles the Mesh for OpenGL 3.X use*/
	void CompileOpenGL3X(void);

	/* Asks the Mesh if it has been binded */
	bool GetBinded(void);
	/* Property GetBinded */
	__declspec(property(get = GetBinded)) bool Binded;

	/* Set the shader to the newly loaded shader */
	void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName, vector3 a_v3Tint = REDEFAULT);

	/* Sets the shader of the Shape to a loaded shader */
	void SetShaderProgram(String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);
	/* Property SetShaderProgram */
	__declspec(property(put = SetShaderProgram)) String ShaderProgram;

	/* Sets the material of the shape by name */
	void SetMaterial(String a_sMaterialName);

	/* Returns the total number of vertices in this Mesh */
	int GetVertexTotal(void);

	/* Property SetMaterialIndex/GetMaterialIndex */
	__declspec(property(put = SetMaterialIndex, get = GetMaterialIndex)) int MaterialIndex;
	/* Sets the material index by index in the material manager */
	void SetMaterialIndex(int a_nIndex);
	/* Gets the material used in the shape by index of the material manager */
	int GetMaterialIndex(void);
	

	/* Asks the mesh for the Shader program used */
	GLuint GetShaderIndex (void);

	/* Adds a new point to the vector of vertices */
	void AddVertexPosition(vector3 a_v3Input);

	/* Adds a new color to the vector of vertices */
	void AddVertexColor(vector3 a_v3Input);

	/* Adds a new normal to the vector of vertices */
	void AddVertexNormal(vector3 a_v3Input);

	/* Adds a new binormal to the vector of vertices */
	void AddVertexBinormal(vector3 a_v3Input);

	/* Adds a new tangent to the vector of vertices */
	void AddVertexTangent(vector3 a_v3Input);

	/* Adds a new uv to the vector of vertices */
	void AddVertexUV(vector3 a_v3Input);

	/* Asks the shape for the list of vertices */
	std::vector<vector3> GetVertices(void);

	/* Asks the shape for the list of Color vertices */
	std::vector<vector3> GetColor(void);

	/* Asks the shape for the list of UV vertices */
	std::vector<vector3> GetUVs(void);

	/* Asks the shape for the list of Normal vertices */
	std::vector<vector3> GetNormals(void);

	/* Asks the shape for the list of tangents */
	std::vector<vector3> GetTangents(void);

	/* Asks the shape for the list of bitangents */
	std::vector<vector3> GetBitangets(void);

	/* Asks the Mesh for its name */
	String GetName(void);
	/* Sets the Mesh's name */
	void SetName(String a_sName);
	/* Property SetName/GetName */
	__declspec(property(put = SetName, get = GetName)) String Name;

	/* Renders the shape */
	virtual void Render(float* a_fMatrixArray, int a_nInstances);

	/* Renders the shape asking for its position in the world and a color */
	virtual void RenderWire( matrix4 a_mToWorld, vector3 a_v3Color);

	/* Renders the shape asking for its position in the world and a color */
	virtual void RenderSolid( matrix4 a_mToWorld, vector3 a_v3Color);

	/* Renders the shape asking for its position in the world */
	virtual void Render( matrix4 a_mToWorld);

protected:
	/* Initialize the object's fields */
	void Init(void);
	/* Releases the object from memory */
	void Release(void);
	/* Completes the information missing to create the mesh */
	void CompleteMesh(void);
	/* Disconects OpenGL3.x from the Mesh without releasing the buffers*/
	void DisconnectOpenGL3X(void);

public:
	/* Completes the triangle information */
	void CompleteTriangleInfo(bool a_bAverageNormals = false);

	/* Calculates the missing tangets */
	void CalculateTangents(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<MeshClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<MeshClass*>;

}

#endif //__MESHCLASS_H_