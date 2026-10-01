#include "nitro/types.h"

extern u32 data_ov093_020c4d34;
extern u32 func_02001154();
extern u32 func_02051cdc();
extern u32 func_02051dfc();
extern u32 func_ov039_020bc688();
extern u32 func_ov093_020bf8c0();
extern u32 func_ov093_020bfa94();
extern u32 func_ov093_020bfcf0();
extern u32 func_ov093_020c02c0();
extern u32 func_ov093_020c1d24();
extern u32 func_ov093_020c3c0c();

void func_ov093_020bed38(int work) {
  func_ov093_020c3c0c(*(u32 *)(work + 0xd1c8));
  func_02001154(1,&data_ov093_020c4d34,0);
  func_ov093_020c1d24(work);
  func_ov093_020c02c0(work);
  func_ov093_020bfcf0(work);
  func_ov093_020bfa94(work);
  func_ov093_020bf8c0(work);
  func_02051dfc(9);
  func_02051dfc(0);
  func_02051cdc();
  func_ov039_020bc688(0,5);
}
