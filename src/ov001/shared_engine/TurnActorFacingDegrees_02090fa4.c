#include "nitro/types.h"

typedef struct {
    u8 pad[0x2e6];
    u16 facing;
    u16 targetFacing;
} Actor;

extern s64 Mul64_02023d9c(s64 a, s64 b);
extern void SetActorFacingDegrees_02090f3c(Actor *actor, int degrees);

void TurnActorFacingDegrees_02090fa4(Actor *actor, int degrees, int smooth) {
    if (smooth == 0) {
        SetActorFacingDegrees_02090f3c(actor, degrees);
        return;
    }
    actor->targetFacing = (u16)((Mul64_02023d9c(degrees, 0xB60B60B60BLL) + 0x80000000000LL) >> 44);
}
