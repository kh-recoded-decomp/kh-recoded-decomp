#include "nitro/types.h"

extern u32 data_ov059_020cffc4;
extern u32 Actor_SetCommandType();

void func_ov059_020cd384(u32 command) {
  switch(command) {
  case 0x1f8:
    Actor_SetCommandType(data_ov059_020cffc4,0);
    return;
  case 0x1f9:
    Actor_SetCommandType(data_ov059_020cffc4,1);
    return;
  case 0x1fa:
    Actor_SetCommandType(data_ov059_020cffc4,2);
    return;
  case 0x1fb:
    Actor_SetCommandType(data_ov059_020cffc4,3);
  }
}
