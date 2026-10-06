#include "nitro/types.h"

extern unsigned int data_ov001_020a0480;
extern unsigned int data_ov033_020baae0;
extern unsigned int SetPanelEnabled();
extern unsigned int StoreToGlobalPtr4Field28();
extern unsigned int FadeBgmVolume();
extern unsigned int ReleaseSeqArcHeapLevel();
extern unsigned int SetFieldStateValue();
extern unsigned int Set_SessionFlagBit0();
extern unsigned int func_ov039_020bbe80();

unsigned int func_ov033_020ba74c(void) {
  unsigned int mode;

  func_ov039_020bbe80(0);
  FadeBgmVolume(0x7f,10);
  mode = 1;
  SetPanelEnabled(1);
  if ((*(u32 *)(data_ov001_020a0480 + 0x214) << 0x12 >> 0x1f) == 0) {
    if (*(int *)(data_ov033_020baae0 + 0xc) != 0) {
      if (*(int *)(data_ov033_020baae0 + 8) == 6) {
        mode = 3;
      }
      SetFieldStateValue((int)*(short *)(data_ov033_020baae0 + 4),mode);
    }
    Set_SessionFlagBit0();
  }
  ReleaseSeqArcHeapLevel(1);
  StoreToGlobalPtr4Field28(1);
  *(u16 *)(data_ov033_020baae0 + 6) = *(u16 *)(data_ov033_020baae0 + 6) | 0x8000;
  return 3;
}
