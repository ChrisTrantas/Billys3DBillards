/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __TEXTUREMANAGERSINGLETON_H_
#define __TEXTUREMANAGERSINGLETON_H_

#include "RE\materials\TextureClass.h"
#include <vector>
#include <map>

namespace ReEng
{

class ReEngDLL TextureManagerSingleton
{
	std::map<String,int> m_map;//indexer

public:
	std::vector<TextureClass*> m_lTextures; //Vector of Textures

	static TextureManagerSingleton* GetInstance(); //Singleton Accessor
	static void ReleaseInstance();	//Singleton Destructor
	
	int IdentifyTexure(String sName); //Returns the ID number of the texture, -1 if it does not exist.
	int LoadTexture(String sName);	//Loads a texture and returns the ID of where its stored in the vector

	int GetNumberOfTextures(void); //Returns the number of texures in the vector
	GLuint ReturnGLIndex(int a_nIndex); //Returns the OpenGL Buffer ID in the vector location of the provided Index
private:
	static TextureManagerSingleton* m_pInstance; //Singleton
	TextureManagerSingleton(void); //Constructor	
	TextureManagerSingleton(const TextureManagerSingleton& other); //Copy Constructor
	TextureManagerSingleton& operator=(const TextureManagerSingleton& other);//Copy Assignment Operator
	~TextureManagerSingleton(void); //Destructor

	void Release(void); //Release the fields in the class
	void Init(void); //Initialize variables
};

}
#endif __TEXTUREMANAGERSINGLETON_H_