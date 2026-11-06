#include "nitro/types.h"

typedef struct { u8 low : 4; u8 high : 4; } NibbleFlags;
extern unsigned int gSaveIoStateDataTail;
extern unsigned int DestroyAllContainerElements();
extern unsigned int DestroyFndObjectList();
extern unsigned int FreePointerIfSet();
extern unsigned int ReleaseRecordSlot();
extern unsigned int ReleaseStatusPage();
extern unsigned int SweepElements();
extern unsigned int ReleaseMapLayoutReference();
extern unsigned int ReleaseRecordManager();
extern unsigned int ReleaseIfMarked();
extern unsigned int GetSecondaryMenuElement();
extern unsigned int GetMenuWidgetContainer();
extern unsigned int UpdateSlotFillCounts();

void DestroyStatusMenu(char *work) {
  void *container;
  int records;

  container = (void *)GetMenuWidgetContainer();
  if (*work == '\x04') {
    ReleaseStatusPage(work,work + 0xb44);
  }
  DestroyFndObjectList((int)(work + 0xe28));
  DestroyFndObjectList((int)(work + 0xdf4));
  DestroyFndObjectList((int)(work + 0xdc0));
  FreePointerIfSet(work + 0x11cc);
  ReleaseMapLayoutReference();
  ReleaseRecordSlot(3);
  ReleaseRecordManager();
  UpdateSlotFillCounts(work + 0x16c,((NibbleFlags *)(gSaveIoStateDataTail + 0x28d7))->low);
  records = GetSecondaryMenuElement();
  SweepElements(records);
  DestroyAllContainerElements(container);
  ReleaseIfMarked(container);
}
