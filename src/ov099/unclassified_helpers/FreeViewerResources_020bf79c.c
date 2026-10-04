#include "nitro/types.h"

typedef struct HandleBuffer {
  u8 data[0xc];
} HandleBuffer;

typedef struct ObjectList {
  u8 data[0x34];
} ObjectList;

extern void CallVirtualHandlerSlot1_02001574(void *object, int arg);
extern void FlushBufferAndRunCallback_0200153c(void *object);
extern void DestroyFndObjectList_020014f0(void *object);
extern void FreePointerIfSet_020ba294(void *slot);
extern void FreeResourceBufferAndProbeHeap_02001474(void *buffer);

void FreeViewerResources_020bf79c(u8 *work) {
  int index;
  int slot;

  for (index = 0; index < 4; index++) {
    CallVirtualHandlerSlot1_02001574((ObjectList *)(work + 0x31c) + index, 0);
    FlushBufferAndRunCallback_0200153c((ObjectList *)(work + 0x31c) + index);
    DestroyFndObjectList_020014f0((ObjectList *)(work + 0x31c) + index);
  }
  FreePointerIfSet_020ba294(work + 0xcef8);
  for (slot = 0; slot < 2; slot++) {
    FreePointerIfSet_020ba294((HandleBuffer *)(work + 0xcee0) + slot);
  }
  FreeResourceBufferAndProbeHeap_02001474(work + 0x310);
}
