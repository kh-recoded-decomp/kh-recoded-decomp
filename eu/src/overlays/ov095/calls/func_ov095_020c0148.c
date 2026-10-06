#include "nitro/types.h"

extern unsigned char data_ov095_020c18b4;
extern unsigned int InitObjManager();
extern unsigned int CreateGridEntry();

void func_ov095_020c0148(int work) {
  int index;
  u32 configuration [4];

  index = 0;
  configuration[0] = (*(int *)(work + 8) + 0x8000U & 0xfffffc) << 7 | 0x80000031;
  configuration[1] = 1;
  configuration[2] = 0;
  configuration[3] = 0;
  InitObjManager(work + 0x180,configuration);
  do {
    CreateGridEntry(0,index,&data_ov095_020c18b4 + index * 0x14,work);
    index = index + 1;
  } while (index < 0xd);
}
