#include "nitro/types.h"

extern void EmitBasicJointTransform(void); /* func */
extern void EmitJointAnimationResult(void); /* EmitJointAnimationResult */

void (*gJointAnimationResultDispatch[3])(void) = {
    EmitBasicJointTransform, /* func */
    EmitJointAnimationResult, /* EmitJointAnimationResult */
    NULL,
};
