/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __EXAMPLECLASS_H_
#define __EXAMPLECLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{

//System Class
class ReEngDLL ExampleClass
{
	int m_nData = 0; //Number of elements in the list of elements
	std::vector<int> m_lData; //list of elements

public:
	/* Constructor */
	ExampleClass(void);
	/* Copy Constructor */
	ExampleClass(ExampleClass const& other);
	/* Copy Assignment Operator*/
	ExampleClass& operator=(ExampleClass const& other);
	/* Destructor */
	~ExampleClass(void);

	/* Swaps the contents of the object with another object's content */
	void Swap(ExampleClass& other);

	/* Gets the number of enties of the list */
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
	/* Releases the object from memory */
	void Release(void);
	/* Initialize the object's fields */
	void Init(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<ExampleClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<ExampleClass*>;

}

#endif //__EXAMPLECLASS_H__