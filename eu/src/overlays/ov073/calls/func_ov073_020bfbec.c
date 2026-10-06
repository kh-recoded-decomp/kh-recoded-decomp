#include "nitro/types.h"

typedef struct { u8 low : 4; u8 high : 4; } NibbleFlags;
extern unsigned int data_0205fe0c;
extern unsigned int DestroyAllContainerElements();
extern unsigned int DestroyFndObjectList();
extern unsigned int FreePointerIfSet();
extern unsigned int ReleaseRecordSlot();
extern unsigned int ReleaseStatusPage();
extern unsigned int func_ov027_020b833c();
extern unsigned int func_02050a58();
extern unsigned int ReleaseRecordManager();
extern unsigned int ReleaseIfMarked();
extern unsigned int func_ov039_020bc1c4();
extern unsigned int func_ov039_020bc1ec();
extern unsigned int func_ov073_020c02f4();

void func_ov073_020bfbec(char *work) {
  void *container;
  int records;

  container = (void *)func_ov039_020bc1ec();
  if (*work == '\x04') {
    ReleaseStatusPage(work,work + 0xb44);
  }
  DestroyFndObjectList((int)(work + 0xe28));
  DestroyFndObjectList((int)(work + 0xdf4));
  DestroyFndObjectList((int)(work + 0xdc0));
  FreePointerIfSet(work + 0x11cc);
  func_02050a58();
  ReleaseRecordSlot(3);
  ReleaseRecordManager();
  func_ov073_020c02f4(work + 0x16c,((NibbleFlags *)(data_0205fe0c + 0x28d7))->low);
  records = func_ov039_020bc1c4();
  func_ov027_020b833c(records);
  DestroyAllContainerElements(container);
  ReleaseIfMarked(container);
}
