/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __TEXTURECLASS_H_
#define __TEXTURECLASS_H_

#include "RE\system\SystemSingleton.h"
#include "SOIL\SOIL.h"

namespace ReEng
{

class ReEngDLL TextureClass
{
	GLuint m_nTextureID = 0;
	SystemSingleton* m_pSystem = nullptr;
	String m_sName = "NULL";
	String m_sFileName = "NULL";
public:
	TextureClass(void); //Constructor
	TextureClass(const TextureClass& other); //Copy Constructor
	TextureClass& operator=(const TextureClass& other); //Copy Assignment Operator
	void Release(void); //Release the fields in the class
	~TextureClass(void); //Destructor

	void LoadTexture(String a_sFileName);
//Accessors
	GLuint GetGLTextureID(void); //Returns the OpenGL Identifier
	__declspec(property(get = GetGLTextureID)) GLuint GLTextureID;
	String GetTextureName(void); //Returns the name of the texture
	__declspec(property(get = GetTextureName)) String TextureName;
	String GetTextureFileName(void); //Returns the filename of the texture
	__declspec(property(get = GetTextureFileName)) String TextureFileName;

private:
	void Init(void); //Initializes the variables
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<TextureClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<TextureClass*>;

}
#endif //_TEXTURECLASS_H
