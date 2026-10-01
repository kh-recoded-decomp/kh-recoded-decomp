#include "nitro/types.h"

typedef struct { u8 low : 4; u8 high : 4; } NibbleFlags;
extern unsigned int data_0205fe0c;
extern unsigned int DestroyAllContainerElements_020b900c();
extern unsigned int DestroyFndObjectList_020014f0();
extern unsigned int FreePointerIfSet_020ba294();
extern unsigned int ReleaseRecordSlot_02051dfc();
extern unsigned int ReleaseStatusPage_020bece0();
extern unsigned int SweepElements_020b831c();
extern unsigned int func_02050a44();
extern unsigned int func_02051cdc();
extern unsigned int func_ov027_020b903c();
extern unsigned int func_ov039_020bc1a4();
extern unsigned int func_ov039_020bc1cc();
extern unsigned int func_ov073_020c02d4();

void func_ov073_020bfbcc(char *work) {
  void *container;
  int records;

  container = (void *)func_ov039_020bc1cc();
  if (*work == '\x04') {
    ReleaseStatusPage_020bece0(work,work + 0xb44);
  }
  DestroyFndObjectList_020014f0((int)(work + 0xe28));
  DestroyFndObjectList_020014f0((int)(work + 0xdf4));
  DestroyFndObjectList_020014f0((int)(work + 0xdc0));
  FreePointerIfSet_020ba294(work + 0x11cc);
  func_02050a44();
  ReleaseRecordSlot_02051dfc(3);
  func_02051cdc();
  func_ov073_020c02d4(work + 0x16c,((NibbleFlags *)(data_0205fe0c + 0x28d7))->low);
  records = func_ov039_020bc1a4();
  SweepElements_020b831c(records);
  DestroyAllContainerElements_020b900c(container);
  func_ov027_020b903c(container);
}
