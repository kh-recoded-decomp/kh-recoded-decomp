#include "nitro/types.h"

extern unsigned int ResetEntryStates();

void ResetSceneTaskEffectEntries(unsigned int unused,int entry) {

  (*ResetEntryStates)(*(unsigned int *)(entry + 88));
}
