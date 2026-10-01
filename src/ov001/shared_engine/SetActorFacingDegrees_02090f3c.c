#include "nitro/types.h"

typedef struct {
    u8 pad[0x2e6];
    u16 facing;
    u16 targetFacing;
} Actor;

extern s64 Mul64_02023d9c(s64 a, s64 b);

void SetActorFacingDegrees_02090f3c(Actor *actor, int degrees) {
    actor->facing = (u16)((Mul64_02023d9c(degrees, 0xB60B60B60BLL) + 0x80000000000LL) >> 44);
    actor->targetFacing = actor->facing;
}
