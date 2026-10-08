#include "nitro/types.h"

extern void AdvancePool0Timer(void); /* AdvancePool0Timer */
extern void StepLinearPathMotion(void); /* StepLinearPathMotion */
extern void StepOrbitMotion(void); /* StepOrbitMotion */
extern void StepBouncingCollisionMotion(void);
extern void UpdateOwnerFall(void); /* UpdateOwnerFall */

void (*const gPoolMotionHandlers[5])(void) = {
    AdvancePool0Timer, /* AdvancePool0Timer */
    StepLinearPathMotion, /* StepLinearPathMotion */
    StepOrbitMotion, /* StepOrbitMotion */
    StepBouncingCollisionMotion,
    UpdateOwnerFall, /* UpdateOwnerFall */
};
