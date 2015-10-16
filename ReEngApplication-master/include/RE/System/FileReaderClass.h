/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __FILEREADERCLASS_H_
#define __FILEREADERCLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{

class ReEngDLL FileReaderClass
{
	SystemSingleton* m_pSystem = nullptr; //System pointer
	FILE* m_pFile; //File pointer
	std::ifstream m_iStream;
	std::ofstream m_oStream;

public:
	String m_sLine = ""; //Line of file
	String m_sFirstWord = "";

	/* constructor */
	FileReaderClass(void);
	/* Copy constructor */
	FileReaderClass(const FileReaderClass& other);
	/* Copy assignment operator */
	FileReaderClass& operator=(const FileReaderClass& other);
	/* Destructor */
	~FileReaderClass(void);
	
	/* Deallocate object from memory */
	void Release(void);

	/* Rewinds the file */
	void Rewind(void) const;

	/* Reads Files and allocates it on the string */
	REERRORS ReadFile(String a_sFileName);

	/* Saves a file with the specified name and location */
	REERRORS SaveFile(String a_sFileName);

	/* Saves a file in binary mode */
	REERRORS SaveBinaryFile(String a_sFileName);

	/* Reads Binary Files */
	REERRORS ReadBinaryFile(String a_sFileName);

	/* closes the file */
	void CloseFile(void);

	/* writes a line of the file and saves it in the string */
	REERRORS WriteLine(String a_sStringInput);

	/* writes a line of the file and saves it in the char array */
	REERRORS WriteLine(const char * _Format, ...);
	
	/* writes on the same line of the file and saves it in the string */
	REERRORS Write(String a_sStringInput);

	/* writes on the same line of the file and saves it in the char array */
	REERRORS Write(const char * _Format, ...);

	void WriteInt(int input);

	void WriteFloat(float input);

	void WriteBool(bool input);

	void WriteString(String input);


	int ReadInt(void);

	float ReadFloat(void);

	bool ReadBool(void);

	String ReadString(void);

	/* Removes all tabs from the string (it makes regular spaces)*/
	REERRORS RemoveTabs(String* a_sInput);

	/* reads a line of the file and saves it in the string */
	REERRORS ReadNextLine(bool a_bSkipComments = true);
	/* 
	Removes the blank spaces of the line
		Modified by AndrewWilkinson88@gmail.com
	*/
	REERRORS RemoveBlanks(char** a_szInput);

	/*Removes the blank spaces of the line and returns a new copy*/
	REERRORS RemoveBlanks(char* a_szInput);

	/*Removes the blank spaces of the line and returns a new copy*/
	REERRORS RemoveBlanks(String* a_sInput);

	/* Gets the first word of the line */
	String GetFirstWord(bool a_bToUpper = false);

	/*Gets a file name from a explorer window*/
	String RetriveFileNameFromExplorer(LPCWSTR mFilter = L"Plain Text Files (*.txt)\0*.txt\0 All Files (*.*)\0*.*\0", LPCWSTR mDefaultExt = L"txt") const;

	/*Tells a file name from explorer window*/
	String IndicateFileNameOnExplorer(LPCWSTR mFilter = L"Plain Text Files (*.txt)\0*.txt\0 All Files (*.*)\0*.*\0", LPCWSTR mDefaultExt = L"txt") const;

	/*Gets the filename with extension from the name */
	static String GetFileNameAndExtension(String a_sFileName);

	/*Gets the filename from the name */
	static String GetFileName(String a_sFileName);

	/*Gets the extension from the filename*/
	static String GetExtension(String a_sFileName);

	/* Gets the absolute route from a file name */
	static String GetAbsoluteRoute(String a_sFileName);

	/* Returns the string in uppercase */
	static String ToUpper(String a_sInput);

private:
	/* Initializates the variables of the object*/
	void Init(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<FileReaderClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<FileReaderClass*>;

}
#endif //_EMPTY_H
