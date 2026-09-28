#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct NearbyPoint {
    u8 pad_00[0x40];
    VecFx32 position;
} NearbyPoint;

extern VecFx32 *GetActorPosition_0206dc4c(int slot);
extern fx32 VecFx32_Distance_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

BOOL IsLeadActorNearPoint_02083d98(NearbyPoint *point)
{
    BOOL isNear = FALSE;

    if (VecFx32_Distance_01ffa0f4(&point->position, GetActorPosition_0206dc4c(0)) <= 0x2000) {
        isNear = TRUE;
    }
    return isNear;
}
