#include "nitro/types.h"

typedef struct {
    u8 pad[0x2ea];
    u16 tilt;
    u16 targetTilt;
} Actor;

extern s64 Mul64_02023d9c(s64 a, s64 b);

void SetActorTiltDegrees_02090f70(Actor *actor, int degrees) {
    actor->tilt = (u16)((Mul64_02023d9c(degrees, 0xB60B60B60BLL) + 0x80000000000LL) >> 44);
    actor->targetTilt = actor->tilt;
}
