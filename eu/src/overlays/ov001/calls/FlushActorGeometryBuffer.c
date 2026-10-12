#include "src/overlays/ov001/ActorBoxDisplayList.h"

extern void FlushGeometryCommandBuffer(const void *commands, u32 size);

void FlushActorGeometryBuffer(void)
{
    FlushGeometryCommandBuffer(&gActorBoxDisplayList, sizeof(gActorBoxDisplayList));
}
