/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __LINEMANAGERSINGLETON_H_
#define __LINEMANAGERSINGLETON_H_

#include "RE\Mesh\LineClass.h"

namespace ReEng
{

//System Class
class ReEngDLL LineManagerSingleton
{
	int m_nLines = 0;//Number of lines in the manager
	LineClass* m_pLine = nullptr; //Line object
	std::vector<vector3> m_lStart;	//Start of the line
	std::vector<vector3> m_lEnd;	//Start of the line
	std::vector<vector3> m_lColor;	//Color of the line

public:
	static LineManagerSingleton* GetInstance(); // Singleton accessor
	static void ReleaseInstance(void); //Singleton Release

	void ClearLines(void);
	void RenderLines(void);
	void AddLine(vector3 a_v3Start, vector3 a_v3End, vector3 a_v3Color = vector3( 0.0f, 1.0f, 0.0f));
	void CompileOpenGL3X(void);

private:
	LineManagerSingleton(void); // Constructor
	LineManagerSingleton(LineManagerSingleton const& other); //Copy Constructor
	LineManagerSingleton& operator=(LineManagerSingleton const& other); // Copy Assignment Operator
	~LineManagerSingleton(void); // Destructor

	void Release(void); // Release Memory
	void Init(void); // Initialize variables
	
	static LineManagerSingleton* m_pInstance; // Singleton
};

}
#endif //__LINEMANAGERSINGLETON_H_