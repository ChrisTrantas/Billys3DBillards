/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __ExampleSingleton_H_
#define __ExampleSingleton_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{

//System Class
class ReEngDLL ExampleSingleton
{
	int m_nData = 0; //number of elements in the list
	static ExampleSingleton* m_pInstance; // Singleton pointer
	std::vector<int> m_lData; //list of elements
public:
	/* Gets/Constructs the singleton pointer */
	static ExampleSingleton* GetInstance();
	/* Destroys the singleton */
	static void ReleaseInstance(void);

	/* Asks the singleton for the number of elements in the list */
	int GetData(void);
	/* Sets a value in the list */
	void SetData( int a_nData = 1);
	/* Property GetData/SetData */
	__declspec(property(get = GetData, put = SetData)) int Data;

	/* Set data on the list at the end */
	void SetDataOnVector(int a_nData);
	/* Gets data out of the list at the specified index */
	int& GetDataOnVector(int a_nIndex);

private:
	/* Constructor */
	ExampleSingleton(void);
	/* Copy Constructor */
	ExampleSingleton(ExampleSingleton const& other);
	/* Copy Assignment Operator */
	ExampleSingleton& operator=(ExampleSingleton const& other);
	/* Destructor */
	~ExampleSingleton(void);

	/* Releases the objects memory */
	void Release(void);
	/* Initializates the objects fields */
	void Init(void);
	
	
};

}

#endif //__EXAMPLECLASS_H__