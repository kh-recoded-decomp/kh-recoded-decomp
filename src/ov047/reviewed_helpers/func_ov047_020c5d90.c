#include "nitro/types.h"

typedef unsigned int code();

extern u16 data_02060500;
extern unsigned int GetBoundedEntryField_0206db5c();
extern unsigned int func_020c1a48();
extern unsigned int func_ov046_020c1a70();
extern unsigned int func_ov046_020c2ab8();

void func_ov047_020c5d90(int work,int entry) {
  u32 target;
  int blocked;
  unsigned int value;
  u32 flags;

  if ((((*(u32 *)(entry + 0xf0) & 0x40000) == 0) && ((*(u32 *)(entry + 0xf0) & 0x200) == 0))
     && ((data_02060500 & 4) != 0)) {
    flags = 0;
    target = GetBoundedEntryField_0206db5c(0);
    if (*(code **)(target + 0x21c) != (code *)0x0) {
      flags = (**(code **)(target + 0x21c))(target);
    }
    if (((flags & 8) == 0) && (blocked = func_ov046_020c2ab8(entry), blocked == 0)) {
      *(u32 *)(entry + 0xf0) = *(u32 *)(entry + 0xf0) ^ 0x80000;
      value = func_ov046_020c1a70(*(unsigned int *)(entry + 0xe4));
      *(unsigned int *)(work + 0x94) = value;
      value = func_020c1a48(*(unsigned int *)(entry + 0xe4));
      *(unsigned int *)(work + 0x9c) = value;
    }
  }
  *(unsigned int *)(work + 0xc) = *(unsigned int *)(work + 0x94);
}
