/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __LINECLASS_H_
#define __LINECLASS_H_

#include "RE\Mesh\MeshClass.h"

namespace ReEng
{

class ReEngDLL LineClass : public MeshClass
{
	typedef MeshClass super;
public:
	//Constructor
	LineClass();

	LineClass(vector3 a_vMin, vector3 a_vMax);

	//Copy Constructor
	LineClass(const LineClass& other);

	//Copy Assignment Operator
	virtual LineClass& operator=(const LineClass& other);

	//Destructor
	~LineClass(void);
		
	//Renders the content of the shape
	void Render(vector3 a_vStart, vector3 a_vEnd, vector3 a_v3Color = REGREEN);

	void CompileForColor(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<LineClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<LineClass*>;

}
#endif //LINECLASS