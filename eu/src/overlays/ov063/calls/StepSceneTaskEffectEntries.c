#include "nitro/types.h"

extern unsigned int func_ov021_020aafe4();

void StepSceneTaskEffectEntries(unsigned int unused,int entry,unsigned int value) {

  (*func_ov021_020aafe4)(*(unsigned int *)(entry + 88),value);
}
