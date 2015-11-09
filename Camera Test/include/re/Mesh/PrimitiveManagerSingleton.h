/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __PRIMITIVEMANAGERSINGLETON_H_
#define __PRIMITIVEMANAGERSINGLETON_H_

#include "RE\Mesh\PrimitiveClass.h"
#include "RE\Mesh\PrimitiveWireClass.h"
#include "RE\Mesh\MeshDrawerSingleton.h"


namespace ReEng
{

//System Class
class ReEngDLL PrimitiveManagerSingleton
{
	static PrimitiveManagerSingleton* m_pInstance; // Singleton of the class
	
	MeshClass* m_pAxis = nullptr; //Axis primitive
	MeshClass* m_pPlane = nullptr; //Plane primitive
	MeshClass* m_pCube = nullptr; //Cube primitive
	MeshClass* m_pCubeWire = nullptr; //Cube Wire primitive
	MeshClass* m_pCone = nullptr; //Cone primitive
	MeshClass* m_pConeWire = nullptr; //Cone Wire primitive
	MeshClass* m_pCylinder = nullptr; //Cylinder primitive
	MeshClass* m_pCylinderWire = nullptr; //Cylinder Wire primitive
	MeshClass* m_pTube = nullptr; //Tube primitive
	MeshClass* m_pTubeWire = nullptr; //Tube Wire primitive
	MeshClass* m_pTorus = nullptr; //Torus primitive
	MeshClass* m_pTorusWire = nullptr; //Torus Wire primitive
	MeshClass* m_pSphere = nullptr;//Sphere primitive
	MeshClass* m_pSphereWire = nullptr;//Sphere Wire primitive

	MeshDrawerSingleton* m_pMeshDrawer = nullptr;
	

public:
	/* Gets/Constructs the singleton pointer */
	static PrimitiveManagerSingleton* GetInstance();
	/* Destroys the singleton */
	static void ReleaseInstance(void); //Singleton Release

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
	
private:
	/* Constructor */
	PrimitiveManagerSingleton(void);
	/* Copy constructor */
	PrimitiveManagerSingleton(PrimitiveManagerSingleton const& other);
	/* Copy Assignment operator */
	PrimitiveManagerSingleton& operator=(PrimitiveManagerSingleton const& other);
	/* Destructor */
	~PrimitiveManagerSingleton(void);

	/* Releases the objects memory */
	void Release(void);
	/* Initializates the objects fields */
	void Init(void);
};

}

#endif //__PRIMITIVEMANAGERSINGLETON_H_