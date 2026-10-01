#include "nitro/types.h"

extern u32 func_0202a9d0();
extern char *func_02052280();
extern u32 func_ov002_020663d0();
extern u32 func_ov002_02069e8c();

void InitPanelRecordFromProfile_02072d00(int context,int value)

{
  char *profileOrIndex;
  u8 variant;
  int randomValue;
  u32 chance;
  int entryAddress;
  
  randomValue = func_0202a9d0(0x32);
  profileOrIndex = func_02052280();
  func_ov002_020663d0(context + 0x10,*(u32 *)(profileOrIndex + 0x38),10);
  func_ov002_020663d0(context + 0x26,*(u32 *)(profileOrIndex + 0x3c),0x1a);
  if (*(short *)(profileOrIndex + 4) != -1) {
    *(char *)(context + 0x65) = (char)*(short *)(profileOrIndex + 4);
  }
  if (*(short *)(profileOrIndex + 6) != -1) {
    *(char *)(context + 0x66) = (char)*(short *)(profileOrIndex + 6);
  }
  if (*(short *)(profileOrIndex + 8) != -1) {
    *(char *)(context + 0x67) = (char)*(short *)(profileOrIndex + 8);
  }
  if (*(short *)(profileOrIndex + 10) != -1) {
    *(char *)(context + 0x68) = (char)*(short *)(profileOrIndex + 10);
  }
  *(u8 *)(context + 0x6c) = 2;
  func_ov002_02069e8c(context,profileOrIndex);
  chance = func_0202a9d0(1000);
  if (chance < 10) {
    *(u8 *)(context + 100) = 1;
  }
  variant = func_0202a9d0(9);
  *(u8 *)(context + 0x6b) = variant;
  if (value == 1) {
    *(u8 *)(context + 0x5e) = randomValue;
    for (int index = 1; index < 6; index++) {
      *(u8 *)(context + index + 0x5e) = 0xff;
    }
    return;
  }
  return;
}
