/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __REDEFINITIONS_H_
#define __REDEFINITIONS_H_

// Include standard headers
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <vector>

// Include GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\ext.hpp>
#include <glm\gtc\quaternion.hpp>

#ifdef EXP_STL
#	define ReEngDLL __declspec(dllexport)
#	define EXPIMP_TEMPLATE
#else
#	define ReEngDLL __declspec(dllimport)
#	define EXPIMP_TEMPLATE extern
#endif

namespace ReEng
{
typedef std::string String;
typedef glm::vec2 vector2;
typedef glm::vec3 vector3;
typedef glm::vec4 vector4;
typedef glm::mat4 matrix4;
typedef unsigned int uint;
typedef glm::quat quaternion;

#define SafeDelete(p){ if(p) { delete p; p = nullptr; } }
////https://stackoverflow.com/questions/10240161/reason-to-pass-a-pointer-by-reference-in-c/20188970#20188970
//template<typename T>
//void SafeDelete(T*& p)
//{
//	if(p != nullptr)
//	{
//		delete p;
//		p = nullptr;
//	} 
//}
#define PI 3.14159265358979323846
#define IDENTITY 1.0f
#define REIDENTITY matrix4()

#define REBLACK vector3(0.0f, 0.0f, 0.0f)
#define REWHITE vector3(1.0f, 1.0f, 1.0f)
#define REGRAY vector3(0.3f, 0.3f, 0.3f)

#define RERED vector3(1.0f, 0.0f, 0.0f)
#define REMAGENTA vector3(1.0f, 0.0f, 1.0f)
#define REBROWN vector3(0.6f,0.3f,0.0f)

#define REGREEN vector3(0.0f, 1.0f, 0.0f)
#define REGREENDARK vector3(0.0f, 5.0f, 0.0f)
#define RELIME vector3(0.33f,0.90f,0.33f)

#define REBLUE vector3(0.0f, 0.0f, 1.0f)
#define RECYAN vector3(0.0f,1.0f,1.0f)

#define REYELLOW vector3(1.0f, 1.0f, 0.0f)
#define REORANGE vector3(1.0f,0.5f,0.0f)
#define REVIOLET vector3(0.54f,0.16f,0.88f)
#define REPURPLE vector3(0.50f,0.0f,0.50f)

#define REDEFAULT vector3(-1.0f, -1.0f, -1.0f)

#define REVECTORZERO vector3(0.0f, 0.0f, 0.0f)
#define REAXISX vector3(1.0f, 0.0f, 0.0f)
#define REAXISY vector3(0.0f, 1.0f, 0.0f)
#define REAXISZ vector3(0.0f, 0.0f, 1.0f)

//-----------------------------------------------------------------------------------------------------------
// Enumerations
//-----------------------------------------------------------------------------------------------------------
enum REOptions
{
	NO = 0,
	YES = 1,
	ASK = 2,
	OPENGL2X = 3,
	OPENGL3X = 4,
	DIRECTX = 5
};
enum REERRORS
{
	ERROR_FREE = 0,
	ERROR_FILE_MISSING = 1,
	ERROR_CONTEXT = 2,
	ERROR_MEMORY = 3,
	ERROR_GENERAL = 4,
	ERROR_NAME = 5,
	ERROR_NOT_INITIALIZED = 6,
	ERROR_FILE = 7,
	DONE = 8,
	RUNNING = 9,
};
enum REAXIS
{
	NONE = 0,
	XY = 1,
	XZ = 2,
	YZ = 4,
};
enum RERENDER
{
	SOLID = 1,
	WIRE = 2,
};


}

#endif //__REDEFINITIONS_H__