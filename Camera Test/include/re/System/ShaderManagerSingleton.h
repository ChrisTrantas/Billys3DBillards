/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __SHADERMANAGERSINGLETON_H_
#define __SHADERMANAGERSINGLETON_H_

#include "RE\system\ShaderClass.h"
#include <vector>
#include <assert.h>
#include <map>
namespace ReEng
{

//System Class
class ReEngDLL ShaderManagerSingleton
{
	int m_nShaders = 0; //Number of shaders

	static ShaderManagerSingleton* m_pInstance; // Singleton
	
	std::vector<ShaderClass> m_vShader; //vector of shaders
	std::map<String, int> m_map;//Indexer of Shaders

public:
	/* Singleton accessor */
	static ShaderManagerSingleton* GetInstance(); 

	/* Singleton Release */
	static void ReleaseInstance(void);
	
	/* Compiles a shader program and returns the OpenGL identifier */
	GLuint CompileShader(String a_sVertexShader, String a_sFragmentShader, String a_sName = "");

	/* Asks the manager for the OpenGL identifier for the specified name*/
	GLuint GetShaderID(String a_sName);

	/* Asks the manager for the OpenGL identifier for the specified index*/
	GLuint GetShaderID(int a_nIndex);

	/* Ask for the Index in the vector of the specified shader name*/
	int IdentifyShader(String a_sName);

private:
	/* Constructor */
	ShaderManagerSingleton(void);

	/* Copy Constructor */
	ShaderManagerSingleton(ShaderManagerSingleton const& other);

	/* Copy Assignment Operator */
	ShaderManagerSingleton& operator=(ShaderManagerSingleton const& other);

	/* Destructor */
	~ShaderManagerSingleton(void);

	/* Release Memory */
	void Release(void);

	/* Initialize variables */
	void Init(void);
};

}
#endif //__SHADERMANAGERSINGLETON_H_