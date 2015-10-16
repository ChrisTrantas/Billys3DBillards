/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __ANIMATIONCLASS_H_
#define __ANIMATIONCLASS_H_

#include "RE\System\SystemSingleton.h"
#include "RE\Animation\FrameClass.h"

namespace ReEng
{

class ReEngDLL AnimationClass
{
public:
	AnimationClass(void);
	AnimationClass(const AnimationClass& other);
	AnimationClass& operator=(const AnimationClass& other);
	~AnimationClass(void);
	void Init(void);
	void Release(void);
	
	void Swap(AnimationClass& other);

	AnimationClass(FrameClass *a_pFrame, int a_nFrames);
	void CheckInterpolation(FrameClass *a_pFrame, int a_nFrames) const;
private:
	void Interpolation(FrameClass *a_pFrame, int a_nFirstKeyFrame, int a_nLastKeyFrame) const;
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<AnimationClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<AnimationClass*>;

}
#endif //__ANIMATIONCLASS_H__