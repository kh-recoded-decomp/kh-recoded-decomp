#include "nitro/types.h"

extern u32 data_ov099_020c2900;
extern u32 data_ov099_020c22b4;
extern u32 sOv099_UiBtlStrLanguageP2_020c2774;
extern u32 AcquireRecordSlot();
extern u32 LoadMessageFiles();
extern u32 Msg_OpenContainerAndReadHeader();
extern u32 SetStateFlagBits();
extern u32 MIi_CpuClearFast();
extern u32 AcquireRecordManager();
extern u32 GetCurrentMenuStackEntry();
extern u32 func_ov099_020bf1b0();
extern u32 LoadViewerBackgrounds();
extern u32 func_ov099_020bf5f4();
extern u32 func_ov099_020bf838();
extern u32 CreateViewerSlotObjs();
extern u32 func_ov099_020c0b5c();
extern u32 func_ov099_020c14d8();
extern u32 func_ov099_020c158c();
extern u32 SyncEnemyEntryFlags();
extern u32 SetViewerMode();
extern u32 ResetModelViewer();

u32 func_ov099_020becb4(void *work) {
  u32 menuMode;
  void *messages;

  data_ov099_020c2900 = work;
  SetStateFlagBits('\x05','\0');
  MIi_CpuClearFast(0,work,0xd6f8);
  menuMode = GetCurrentMenuStackEntry();
  *(u32 *)((int)work + 0xcf04) = menuMode;
  *(u32 *)((int)work + 0xd050) = 0;
  *(u32 *)((int)work + 0xd6e4) = 0;
  *(u32 *)((int)work + 0xd6e8) = 0;
  *(u32 *)((int)work + 0xd6ec) = 0;
  *(u32 *)((int)work + 0xd6f4) = 0;
  *(u32 *)((int)work + 0xd6f0) = 0;
  SyncEnemyEntryFlags(work);
  messages = Msg_OpenContainerAndReadHeader(&sOv099_UiBtlStrLanguageP2_020c2774,0xe,0);
  *(void **)((int)work + 0x30c) = messages;
  AcquireRecordManager();
  AcquireRecordSlot(0,1);
  AcquireRecordSlot(4,1);
  func_ov099_020bf1b0(work);
  LoadMessageFiles(work);
  LoadViewerBackgrounds(work);
  func_ov099_020c0b5c(&data_ov099_020c22b4,work);
  func_ov099_020c14d8(work);
  func_ov099_020bf5f4(work);
  func_ov099_020bf838(0xffffffff,work);
  CreateViewerSlotObjs(work);
  func_ov099_020c158c(work);
  ResetModelViewer((int)work + 0xd0ec,0);
  SetViewerMode(1,work);
  return 1;
}
