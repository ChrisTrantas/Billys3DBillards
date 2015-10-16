/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2015/08
Notes: This is a simplified version of MeshClass
inside of ReEng.dll, its stripped out of a lot
of functionality in order to focuss on important
concepts of OpenGL, please use a MeshClass object
for better functionality.
----------------------------------------------*/
#ifndef __MyMesh_H_
#define __MyMesh_H_

#include "RE\System\SystemSingleton.h"
#include "RE\Camera\CameraSingleton.h"
#include "RE\Materials\MaterialManagerSingleton.h"
#include "RE\Light\LightManagerSingleton.h"
#include "RE\System\ShaderManagerSingleton.h"
#include <vector>

using namespace ReEng;
//System Class
class MyMesh
{
protected:
	bool m_bBinded = false; //Binded flag
	int m_nVertexCount = 0; //Number of Vertices in this Mesh

	GLuint m_vao = 0;			//OpenGL Vertex Array Object
	GLuint m_VertexBuffer = 0;	//OpenGL Buffer (Will hold the vertex buffer pointer)
	GLuint m_ColorBuffer = 0;	//OpenGL Buffer (Will hold the color buffer pointer)

	CameraSingleton* m_pCamera = nullptr;				//Pointer to the singleton of CameraSingleton
	ShaderManagerSingleton* m_pShaderMngr = nullptr;	//Shader Manager

	std::vector<vector3> m_lVertexPos;	//List of Vertices
	std::vector<vector3> m_lVertexCol;	//List of Colors

public:
	/* Constructor */
	MyMesh(void);
	/* Copy Constructor */
	MyMesh(MyMesh const& other);
	/* Copy Assignment Operator*/
	MyMesh& operator=(MyMesh const& other);
	/* Destructor */
	~MyMesh(void);

	/* Swaps the contents of the object with another object's content */
	void Swap(MyMesh& other);

	/* Compiles the Mesh for OpenGL 3.X use*/
	void CompileOpenGL3X(void);

	/* Returns the total number of vertices in this Mesh */
	int GetVertexTotal(void);

	/* Adds a new point to the vector of vertices */
	void AddVertexPosition(vector3 a_v3Input);

	/* Adds a new color to the vector of vertices */
	void AddVertexColor(vector3 a_v3Input);

	/* Renders the shape */
	virtual void RenderList(float* a_fMatrixArray, int a_nInstances);

	/* Renders the shape asking for its position in the world and a color */
	virtual void Render(matrix4 a_mToWorld = MEIDENTITY);

protected:
	/* Initialize the object's fields */
	virtual void Init(void);
	/* Releases the object from memory */
	virtual void Release(void);
	/* Completes the information missing to create the mesh */
	void CompleteMesh(void);

public:
	/* Completes the triangle information */
	void CompleteTriangleInfo(void);
};

#endif //__MyMesh_H_