/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __STATECLASS_H_
#define __STATECLASS_H_

#include "RE\system\SystemSingleton.h"
#include <vector>

namespace ReEng
{

class ReEngDLL StateClass
{
	
	bool m_bTransitionState = false;//Is this a transition state
	bool m_bRepeatSequence	= true;	//Does the sequence repeats
	bool m_bBreakableState = true;	//Can I break out of this state without finishing the animation?
	int m_nSequence = 0;			//Sequence being played
	int m_nExits = 0;				//Number of exits of this state
	
	std::vector<StateClass*> m_lExit;//Exits of the state

	String m_sName;
public:
	StateClass();	//Constructor
	StateClass( String a_sName, int a_nSequence = 0, bool a_bBreakableState = false, bool a_bTransitionState = false, bool a_bRepeatSequence = false);
	StateClass(const StateClass& other);
	StateClass& operator=(const StateClass& other);
	~StateClass();	//Destructor

	void Init();		//Initialices variable values
	void Release();		//Releases the memory and deallocate space.

	void SetName(String a_sName);
	String GetName(void);
	__declspec(property(put = SetName, get = GetName)) String Name;

	void SetSequence(int a_nSequence);
	int GetSequence(void);
	__declspec(property(put = SetSequence, get = GetSequence)) int Sequence;

	void SetBreakable(bool a_bRepeatSequence);
	bool GetBreakable(void);

	void SetRepeatSequence(bool a_bRepeatSequence);
	bool GetRepeatSequence(void);
	__declspec(property(put = SetRepeatSequence, get = GetRepeatSequence)) bool RepeatSequence;

	int GetNumberOfExits(void);
	__declspec(property(get = GetNumberOfExists)) int Exits;

	int AddExit(StateClass* a_pState);

	int GetExitIndex(StateClass* a_pState);

	bool IsTransitionState(void);

	StateClass* GetAutoExit(void);

	StateClass* GetExit(int a_nIndex);

private:
	void Swap(StateClass& other);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<StateClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<StateClass*>;

}

#endif //__STATECLASS_H__