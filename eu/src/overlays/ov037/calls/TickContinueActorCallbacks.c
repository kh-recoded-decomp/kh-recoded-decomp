#include "nitro/types.h"

extern u32 ActorRegistry_ForEachCallback();

void TickContinueActorCallbacks(void) {
  ActorRegistry_ForEachCallback(0x1000);
}
