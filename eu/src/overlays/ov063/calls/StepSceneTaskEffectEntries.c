#include "nitro/types.h"

extern unsigned int UpdateEntrySource();

void StepSceneTaskEffectEntries(unsigned int unused,int entry,unsigned int value) {

  (*UpdateEntrySource)(*(unsigned int *)(entry + 88),value);
}
