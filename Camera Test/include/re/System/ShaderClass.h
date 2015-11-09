/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __SHADERCLASS_H_
#define __SHADERCLASS_H_

#include "RE\system\SystemSingleton.h"
#include "RE\system\ShaderCompiler.h"

namespace ReEng
{

class ReEngDLL ShaderClass
{
	String m_sProgramName = "NULL";
	String m_sVertexShaderName = "NULL";
	String m_sFragmentShaderName = "NULL";
	GLuint m_nProgram = 0;
public:
	ShaderClass(void);
	ShaderClass(const ShaderClass& other);
	ShaderClass& operator=(const ShaderClass& other);
	~ShaderClass(void);
	
	void Swap(ShaderClass& other);

	GLuint CompileShader(String a_sVertexShader, String a_sFragmentShader, String a_sName = "");

	//Attributes
	String GetProgramName();
	__declspec(property(get = GetProgramName)) String Name;

	String GetVertexShaderName();
	__declspec(property(get = GetVertexShaderName)) String VertexShader;

	String GetFragmentShaderName();
	__declspec(property(get = GetFragmentShaderName)) String FragmentShader;

	int GetProgramID();
	__declspec(property(get = GetProgramID)) int ProgramID;

	void Release(void);

protected:
	void Init(void);
	
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<ShaderClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<ShaderClass*>;

}

#endif //__SHADERCLASS_H__