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

public:
	String m_sLine = ""; //Line of file

	/* constructor */
	FileReaderClass(void);
	/* Copy constructor */
	FileReaderClass(const FileReaderClass& other);
	/* Copy assignment operator */
	FileReaderClass& operator=(const FileReaderClass& other);
	/* Destructor */
	~FileReaderClass(void);
	
	/* Dealocate object from memory */
	void Release(void);

	/* Rewinds the file */
	void Rewind(void) const;

	/* Reads Files and allocates it on the string */
	REERRORS ReadFile(String a_sFileName);

	/* Saves a file with the specified name and location */
	REERRORS SaveFile(String a_sFileName);

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

	/* reads a line of the file and saves it in the string */
	REERRORS ReadNextLine(bool a_bSkipComments = true);
	/* 
	Removes the blank spaces of the line
		Modified by AndrewWilkinson88@gmail.com
	*/
	REERRORS RemoveBlanks(char** a_szInput) const; 
	/* Gets the first word of the line */
	String GetFirstWord(bool a_bToUpper = false);

	/*Gets a file name from a explorer window*/
	String RetriveFileNameFromExplorer(LPCWSTR mFilter = L"Plain Text Files (*.txt)\0*.txt\0 All Files (*.*)\0*.*\0", LPCWSTR mDefaultExt = L"txt") const;
	/*Tells a file name from explorer window*/
	char* IndicateFileNameOnExplorer(LPWSTR mSuggested = NULL, LPCWSTR mFilter = L"Plain Text Files (*.txt)\0*.txt\0 All Files (*.*)\0*.*\0", LPCWSTR mDefaultExt = L"txt") const;

	/*Gets the filename with extention from the name */
	String GetFileNameAndExtension(String a_sFileName);

	/*Gets the filename from the name */
	String GetFileName(String a_sFileName);

	/* Gets the absolute route from a file name */
	String GetAbsoluteRoute(String a_sFileName);

private:
	/* Initializates the variables of the object*/
	void Init(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<FileReaderClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<FileReaderClass*>;

}
#endif //_EMPTY_H
