/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __LIGHTMANAGERSINGLETON_H_
#define __LIGHTMANAGERSINGLETON_H_

#include "RE\light\LightClass.h"
#include <vector>
#include <assert.h>

namespace ReEng
{

//System Class
class ReEngDLL LightManagerSingleton
{
	//Private Fields
	int m_nLights = 0;		//Number of Lights
	float m_fAmbient = 0.0f;	//Ambient power
	static LightManagerSingleton* m_pInstance; // Singleton
	std::vector<LightClass*> m_lLight; //vector of lights

public:
	//Public Accessors
	/* Gets/Constructs the singleton pointer */
	static LightManagerSingleton* GetInstance();
	/* Releases the singleton pointer */
	static void ReleaseInstance(void);
	/* Adds a light to the list of lights */
	void AddLight(	vector3 a_v4Position = vector3(1,1,1),
					vector3 a_v3Color = vector3(1,1,1),
					float a_vIntensity = 10.0f);
	/* Gets a copy from a light in the list of lights */
	LightClass* GetLight(int a_nIndex = 1);
	/* Sets the position of a light in the list of lights*/
	void SetPosition(vector3 a_v4Position, int a_nLight = 1);
	/* Gets the position of a light in the list of lights*/
	vector3 GetPosition( int a_nLight = 1);
	/* Sets the color of a light in the list of lights*/
	void SetColor(vector3 a_v3Color, int a_nLight = 1);
	/* Gets the color of a light in the list of lights*/
	vector3 GetColor(int a_nLight = 1);
	/* Sets the intensity of a light in the list of lights*/
	void SetIntensity(float a_fIntensity, int a_nLight = 1);
	/* Gets the intensity of a light in the list of lights*/
	float GetIntensity(int a_nLight = 1);

private:
	/* Constructor */
	LightManagerSingleton(void);
	/* Copy Constructor */
	LightManagerSingleton(LightManagerSingleton const& other);
	/* Copy Assignment Operator */
	LightManagerSingleton& operator=(LightManagerSingleton const& other);
	/* Destructor */
	~LightManagerSingleton(void);

	/* Releases Memory */
	void Release(void);
	/* Initialize variables */
	void Init(void);
};

}
#endif //__LIGHTMANAGERSINGLETON_H__