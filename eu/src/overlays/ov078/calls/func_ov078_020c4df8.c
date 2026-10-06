#include "nitro/types.h"

extern u16 data_02060500;
extern unsigned int IsGlobalPackedBitSet();
extern unsigned int ReadGlobalPackedBits();
extern unsigned int PlaySoundEffect();
extern unsigned int RefreshPageTabs();
extern unsigned int DrawPageHeader();

void func_ov078_020c4df8(int work) {
  int extraPage;
  int pageCount;
  int oldPage;

  oldPage = *(int *)(work + 0x5d4);
  pageCount = *(int *)(work + 0x5d0);
  extraPage = IsGlobalPackedBitSet(pageCount + 0xa01);
  pageCount = ReadGlobalPackedBits(pageCount * 2 + 0x9f7,2);
  if ((u32)(extraPage != 0) + pageCount != 0) {
    if (*(int *)(work + 0x5d4) == 0) {
      if ((data_02060500 & 0x40) != 0) {
        pageCount = *(int *)(work + 0x5d0);
        extraPage = IsGlobalPackedBitSet(pageCount + 0xa01);
        pageCount = ReadGlobalPackedBits(pageCount * 2 + 0x9f7,2);
        *(u32 *)(work + 0x5d4) = (u32)(extraPage != 0) + pageCount + -1;
      }
    }
    else {
      *(int *)(work + 0x5d4) = *(int *)(work + 0x5d4) + -1;
    }
    if (oldPage != *(int *)(work + 0x5d4)) {
      PlaySoundEffect(0,0);
      RefreshPageTabs(work);
      DrawPageHeader(work);
    }
  }
}
