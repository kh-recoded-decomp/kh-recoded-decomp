#include "nitro/types.h"

extern u16 data_02060500;
extern unsigned int func_02027304();
extern unsigned int func_02027348();
extern unsigned int func_0204d924();
extern unsigned int func_ov078_020c48dc();
extern unsigned int func_ov078_020c4b18();

void func_ov078_020c4dd8(int work) {
  int extraPage;
  int pageCount;
  int oldPage;

  oldPage = *(int *)(work + 0x5d4);
  pageCount = *(int *)(work + 0x5d0);
  extraPage = func_02027304(pageCount + 0xa01);
  pageCount = func_02027348(pageCount * 2 + 0x9f7,2);
  if ((u32)(extraPage != 0) + pageCount != 0) {
    if (*(int *)(work + 0x5d4) == 0) {
      if ((data_02060500 & 0x40) != 0) {
        pageCount = *(int *)(work + 0x5d0);
        extraPage = func_02027304(pageCount + 0xa01);
        pageCount = func_02027348(pageCount * 2 + 0x9f7,2);
        *(u32 *)(work + 0x5d4) = (u32)(extraPage != 0) + pageCount + -1;
      }
    }
    else {
      *(int *)(work + 0x5d4) = *(int *)(work + 0x5d4) + -1;
    }
    if (oldPage != *(int *)(work + 0x5d4)) {
      func_0204d924(0,0);
      func_ov078_020c48dc(work);
      func_ov078_020c4b18(work);
    }
  }
}
