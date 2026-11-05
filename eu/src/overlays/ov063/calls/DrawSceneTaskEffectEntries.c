#include "nitro/types.h"

extern unsigned int DrawEntrySource();

void DrawSceneTaskEffectEntries(unsigned int unused,int entry) {

  (*DrawEntrySource)(*(unsigned int *)(entry + 88));
}
