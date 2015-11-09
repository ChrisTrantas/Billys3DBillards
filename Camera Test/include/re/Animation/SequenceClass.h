/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __SEQUENCECLASS_H_
#define __SEQUENCECLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{

class ReEngDLL SequenceClass
{
	bool m_bDirectAnimation = true;//Secuence going from a low to a high frame number?
	int m_nID = 0;					//Secuence Identifier
	int m_nFirstFrame = 0;			//First frame of the secuence;
	int m_nLastFrame = 0;			//Last frame of the secuence;
	int m_nFrameRate = 0;			//How many frames a secuence is playing
	int m_nFrames = 0;				//Number of frames in this sequence;
	String m_sName = "NULL";		//Secuence Name
	
public:
	SequenceClass();	//Constructor
	SequenceClass(String a_sName, int a_nID, int a_nFirstFrame, int a_nLastFrame, int a_nFrameRate);
	SequenceClass(const SequenceClass& other);
	SequenceClass& operator=(const SequenceClass& other);;
	~SequenceClass();	//Destructor

	void Init();		//Initialices variable values
	void Release();		//Releases the memory and deallocate space.
	
	void SetID(int a_nID);
	int getID(void);
	__declspec(property(put = SetID, get = GetID)) int ID;

	void SetName(String a_sName);
	String GetName(void);
	__declspec(property(put = SetName, get = GetName)) String Name;

	void SetFirstFrame(int a_nFirstFrame);
	int GetFirstFrame(void);
	__declspec(property(put = SetFirstFrame, get = GetFirstFrame)) int FirstFrame;

	void SetLastFrame(int a_nLastFrame);
	int GetLastFrame(void);
	__declspec(property(put = SetLastFrame, get = GetLastFrame)) int LastFrame;

	void SetDirectAnimation(bool a_bDirectAnimation);
	bool IsDirectAnimation(void);
	__declspec(property(put = SetDirectAnimation, get = IsDirectAnimation)) bool DirectAnimation;

	void setFrameRate(int a_nFrameRate);
	int GetFrameRate(void);
	__declspec(property(put = SetFrameRate, get = GetFrameRate)) int FrameRate;

	int GetNumberOfFrames(void);

private:
	void Swap(SequenceClass& other);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<SequenceClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<SequenceClass*>;

}
#endif //__SEQUENCECLASS_H__