#include "nitro/types.h"

extern u32 gFieldSessionWork;

int GetScriptHandlerSlot8Index(void) {
  return (int)*(char *)(gFieldSessionWork + 0x19);
}
