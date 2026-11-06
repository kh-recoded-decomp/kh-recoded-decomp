#include "nitro/types.h"

extern u32 gFieldSessionWork;

int GetScriptHandlerSlot7Index(void) {
  return (int)*(char *)(gFieldSessionWork + 0x18);
}
