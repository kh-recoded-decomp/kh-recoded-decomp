#include "nitro/types.h"

extern void PXI_Init_020c2240(void *viewer, int menuMode);
extern BOOL IsEntryFlagSet_020c168c(int list, int index);
extern void func_ov099_020bf818(int mode, u8 *work);
extern void SetViewerMode_020c1760(u32 mode, u8 *work);

void RunViewerIntroMode_020c1788(u8 *work) {
  switch (*(int *)(work + 0xd6f0)) {
  case 0:
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1600;
    PXI_Init_020c2240(work + 0xd0ec, *(int *)(work + 0xcf04));
    (*(int *)(work + 0xd6f0))++;
    break;
  case 1:
    if (IsEntryFlagSet_020c168c(0, *(int *)(work + 0xcf04))) {
      *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1700;
    } else {
      *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1600;
    }
    func_ov099_020bf818(1, work);
    SetViewerMode_020c1760(0, work);
    break;
  }
}
