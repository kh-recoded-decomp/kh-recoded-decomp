#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ProximityTrigger {
    u8 pad_00[0x74];
    fx32 radius;
    VecFx32 position;
} ProximityTrigger;

extern int GetActorCount_0206dc38(void);
extern VecFx32 *GetActorPosition_0206dc4c(int slot);
extern fx32 VecFx32_Distance_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

BOOL IsLeadActorWithinRadius_02080e30(ProximityTrigger *trigger)
{
    if (GetActorCount_0206dc38() > 0) {
        if (trigger->radius >= VecFx32_Distance_01ffa0f4(&trigger->position, GetActorPosition_0206dc4c(0))) {
            return TRUE;
        }
    }
    return FALSE;
}
