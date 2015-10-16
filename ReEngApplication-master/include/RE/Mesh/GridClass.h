/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __GRIDCLASS_H_
#define __GRIDCLASS_H_

#include "RE\Mesh\MeshClass.h"

namespace ReEng
{

class ReEngDLL GridClass
{
	MeshClass* m_pAxis = nullptr;
	MeshClass* m_pGrid = nullptr;

	float m_fSpots = 1000.0f; //number of spots in reticule

public:
	//Constructor
	GridClass(float a_fReticuleSpots = 1000.0f);
	//Copy Constructor
	GridClass(const GridClass& other);
	//Copy Assignment Operator
	virtual GridClass& operator=(const GridClass& other);

	//Destructor
	~GridClass(void);
		
	/* Renders the Grid with the specified axis and size (REAXIS::XY | REAXIS::XZ | REAXIS::YZ) */
	virtual void Render(float a_fSize = 1.0f, int a_Axis = REAXIS::XY);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<GridClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<GridClass*>;

}
#endif //GRIDCLASS