#include "nitro/types.h"

extern u32 data_ov059_020cffa4;
extern u32 Actor_SetCommandType_020c99dc();

void func_ov059_020cd364(u32 command) {
  switch(command) {
  case 0x1f8:
    Actor_SetCommandType_020c99dc(data_ov059_020cffa4,0);
    return;
  case 0x1f9:
    Actor_SetCommandType_020c99dc(data_ov059_020cffa4,1);
    return;
  case 0x1fa:
    Actor_SetCommandType_020c99dc(data_ov059_020cffa4,2);
    return;
  case 0x1fb:
    Actor_SetCommandType_020c99dc(data_ov059_020cffa4,3);
  }
}
