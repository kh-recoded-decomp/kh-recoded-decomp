#include "nitro/types.h"

extern u32 data_ov099_020c28e0;
extern u32 data_ov099_020c2294;
extern u32 data_ov099_020c2754;
extern u32 AcquireRecordSlot_02051d3c();
extern u32 LoadMessageFiles_020bf3f0();
extern u32 Msg_OpenContainerAndReadHeader_0202cc6c();
extern u32 SetStateFlagBits_020bc688();
extern u32 func_01ff8740();
extern u32 func_02051c80();
extern u32 func_ov039_020bc828();
extern u32 func_ov099_020bf190();
extern u32 func_ov099_020bf45c();
extern u32 func_ov099_020bf5d4();
extern u32 func_ov099_020bf818();
extern u32 func_ov099_020c0648();
extern u32 func_ov099_020c0b3c();
extern u32 func_ov099_020c14b8();
extern u32 func_ov099_020c156c();
extern u32 func_ov099_020c16d0();
extern u32 func_ov099_020c1760();
extern u32 func_ov099_020c214c();

u32 func_ov099_020bec94(void *work) {
  u32 menuMode;
  void *messages;

  data_ov099_020c28e0 = work;
  SetStateFlagBits_020bc688('\x05','\0');
  func_01ff8740(0,work,0xd6f8);
  menuMode = func_ov039_020bc828();
  *(u32 *)((int)work + 0xcf04) = menuMode;
  *(u32 *)((int)work + 0xd050) = 0;
  *(u32 *)((int)work + 0xd6e4) = 0;
  *(u32 *)((int)work + 0xd6e8) = 0;
  *(u32 *)((int)work + 0xd6ec) = 0;
  *(u32 *)((int)work + 0xd6f4) = 0;
  *(u32 *)((int)work + 0xd6f0) = 0;
  func_ov099_020c16d0(work);
  messages = Msg_OpenContainerAndReadHeader_0202cc6c(&data_ov099_020c2754,0xe,0);
  *(void **)((int)work + 0x30c) = messages;
  func_02051c80();
  AcquireRecordSlot_02051d3c(0,1);
  AcquireRecordSlot_02051d3c(4,1);
  func_ov099_020bf190(work);
  LoadMessageFiles_020bf3f0(work);
  func_ov099_020bf45c(work);
  func_ov099_020c0b3c(&data_ov099_020c2294,work);
  func_ov099_020c14b8(work);
  func_ov099_020bf5d4(work);
  func_ov099_020bf818(0xffffffff,work);
  func_ov099_020c0648(work);
  func_ov099_020c156c(work);
  func_ov099_020c214c((int)work + 0xd0ec,0);
  func_ov099_020c1760(1,work);
  return 1;
}
