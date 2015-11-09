/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MATERIALCLASS_H_
#define __MATERIALCLASS_H_

#include "RE\system\SystemSingleton.h"
#include "RE\materials\TextureManagerSingleton.h"

namespace ReEng
{

class ReEngDLL MaterialClass
{
	SystemSingleton* m_pSystem = nullptr;
	TextureManagerSingleton* m_pTextureMngr = nullptr;

	GLuint m_nMapDiffuse = 0;
	GLuint m_nMapNormal = 0;
	GLuint m_nMapSpecular = 0;

	vector3 m_vKd;

	String m_sName = "NULL";
	String m_sMapDiffuse = "NULL";
	String m_sMapNormal = "NULL";
	String m_sMapSpecular = "NULL";
	
public:
	MaterialClass(String a_sName);
	MaterialClass(const MaterialClass& other);
	MaterialClass& operator=(const MaterialClass& other);
	~MaterialClass(void);
	
	void Release(void);

	void	SetName(String a_sName);
	String	GetName(void);
	__declspec(property(put = SetName, get = GetName)) String Name;

	void	SetDiffuseMapName(String a_sFileName);
	String	GetDiffuseMapName(void);
	__declspec(property(put = SetDiffuseMapName, get = GetDiffuseMapName)) String DiffuseMapName;

	void	SetNormalMapName(String a_sFileName);
	String	GetNormalMapName(void);
	__declspec(property(put = SetNormalMapName, get = GetNormalMapName)) String NormalMapName;

	void	SetSpecularMapName(String a_sFileName);
	String	GetSpecularMapName(void);
	__declspec(property(put = SetSpecularMapName, get = GetSpecularMapName)) String SpecularMapName;

	GLuint	GetDiffuseMap(void);
	__declspec(property(get = GetDiffuseMap)) GLuint DiffuseMap;

	GLuint	GetNormalMap(void);
	__declspec(property(get = GetNormalMap)) GLuint NormalMap;

	GLuint	GetSpecularMap(void);
	__declspec(property(get = GetSpecularMap)) GLuint SpecularMap;

	void	SetDiffuse(vector3 a_Kd);
	vector3	GetDiffuse(void);
	__declspec(property(put = SetDiffuse, get = GetDiffuse)) vector3 Kd;

	REERRORS LoadDiffuse(String a_sFileName);

	REERRORS LoadNormal(String a_sFileName);

	REERRORS LoadSpecular(String a_sFilename);

	REERRORS LoadMaps(void);
private:
	void Init(void);
};

}
#endif //_EMPTY_H
