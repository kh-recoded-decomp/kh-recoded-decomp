#include "nitro/types.h"

extern void func_01ffad00(void); /* func */
extern void func_01ffae7c(void); /* func */
extern void func_01ffa624(void); /* func */
extern void NNSi_G3dGetJointScaleMaya(void); /* func */

void (*gMaterialAnimationDispatch[4])(void) = {
    func_01ffad00, /* func */
    NULL,
    func_01ffae7c, /* func */
    NULL,
};

void (*gJointAnimationNodeDispatch[3])(void) = {
    func_01ffa624, /* func */
    NNSi_G3dGetJointScaleMaya, /* func */
    NULL,
};
