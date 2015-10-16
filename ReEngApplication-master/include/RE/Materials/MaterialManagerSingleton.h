/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MATERIALMANAGERSINGLETON_H_
#define __MATERIALMANAGERSINGLETON_H_

#include "RE\system\SystemSingleton.h"
#include "RE\materials\MaterialClass.h"
#include <map>


namespace ReEng
{

class ReEngDLL MaterialManagerSingleton
{
	/* 
		The material vector is public for accessing speed reasons its more secure to have it as private
		and provide the right accessors for it, but its call so often that it creates overhead the other way
	*/
	std::map<String,int> m_map; //Map of the materials

public:
	std::vector<MaterialClass*> m_lMaterial; //Materials Vector
	

	static MaterialManagerSingleton* GetInstance(); // Singleton Accessor
	static void ReleaseInstance(void);	//Singleton Destructor

	int IdentifyMaterial(String a_sName); //Identifies the material, if found return its index -1 otherwise

	//returns the index number of the material if it created a new one, otherwise it returns the index
	int AddMaterial(String a_sName);
	int AddMaterial(MaterialClass a_InputMaterial);

	int GetNumberOfMaterials(void); //Return the number of materials in the vector

	void ReloadMaps(void); //Tries to load all the textures for all of the materials

	/* Gets a copy of the material specified by name */
	MaterialClass GetMaterialCopy(String a_sName);

	/* Returns the memory location containing the material specified by the name */
	MaterialClass* GetMaterial(String a_sName);

	/* Returns the memory location containing the material specified by the index */
	MaterialClass* GetMaterial(uint a_nIndex);

private:
	MaterialManagerSingleton(void); // Constructor
	MaterialManagerSingleton(MaterialManagerSingleton const& other); //Copy Constructor
	MaterialManagerSingleton& operator=(MaterialManagerSingleton const& other); // Copy Assignment Operator
	~MaterialManagerSingleton(void); // Destructor

	void Release(void); // Release Memory
	void Init(void); // Initialize variables
	
	SystemSingleton* m_pSystem; //System class Pointer
	static MaterialManagerSingleton* m_pInstance; // Singleton Pointer
};

}
#endif //_MATERIALMANAGERSINGLETON_H