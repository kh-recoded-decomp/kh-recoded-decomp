#include "nitro/types.h"

extern int contextData_020c0068[];
#define activeContext_020c006c contextData_020c0068[1]
extern u32 func_02023dbc();

void SetGroupMenuProgress_020bb9b8(int percent)

{
  int menu;
  int targetCount;
  
  menu = activeContext_020c006c;
  if (activeContext_020c006c != 0) {
    if (0 < percent) {
      targetCount = func_02023dbc(percent * 0x57,100);
      *(int *)(menu + 0x24) = targetCount;
      return;
    }
    *(u32 *)(activeContext_020c006c + 0x24) = 0;
  }
  return;
}
