/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __PRIMITIVEWIRECLASS_H_
#define __PRIMITIVEWIRECLASS_H_

#include "RE\Mesh\MeshClass.h"

namespace ReEng
{

class ReEngDLL PrimitiveWireClass : public MeshClass
{
	typedef MeshClass super;

public:
	/* Constructor */
	PrimitiveWireClass();
	/* Copy Constructor */
	PrimitiveWireClass(const PrimitiveWireClass& other);
	/* Copy Assignment Operator */
	virtual PrimitiveWireClass& operator=(const PrimitiveWireClass& other);

	/* Destructor */
	~PrimitiveWireClass(void);

	/* Generates an Axis shape */
	void GenerateAxis(void);
	/* Generates a cube shape */
	void GenerateCube(float a_fSize, vector3 a_v3Color);
	/* Generates a cone shape */
	void GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color);
	/* Generates a cylinder shape */
	void GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color);
	/* Generates a Tube shape */
	void GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color);
	/* Generates a Torus shape */
	void GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionHeigh, int a_nSubdivisionAxis, vector3 a_v3Color);
	/* Generates a sphere shape */
	void GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color);

	/* Renders the primitive asking for its position in the world and a color */
	virtual void Render(matrix4 a_m4ToWorld, vector3 a_v3Color);
	/* Renders the primitive asking for its position in the world */
	virtual void Render(matrix4 a_m4ToWorld);

private:
	/* Compiles the object with an specific color and name */
	void CompileObject(vector3 a_v3Color, String a_sName);
	/* Adds a quad to the list points in the buffer to be compiled*/
	void AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight);
	/* Adds a tri to the list points in the buffer to be compiled*/
	void AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTop);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<PrimitiveWireClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<PrimitiveWireClass*>;

}

#endif //__PRIMITIVEWIRECLASS_H_