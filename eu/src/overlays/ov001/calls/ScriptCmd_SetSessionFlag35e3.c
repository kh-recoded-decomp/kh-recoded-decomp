#include "nitro/types.h"

extern u32 SetSessionFlag();

u32 ScriptCmd_SetSessionFlag35e3(void) {
  SetSessionFlag(0x35e3);
  return 1;
}
