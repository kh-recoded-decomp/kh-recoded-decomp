#include "nitro/types.h"

extern u32 ResetObjectSlots();

void ResetCurrentScriptTaskSlots(void *actor,void *owner) {
  if (*(void **)((int)actor + 8) == owner) {
    ResetObjectSlots(actor,owner);
  }
}
