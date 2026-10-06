#include "nitro/types.h"

extern unsigned int data_ov001_020a0528;
extern unsigned int GetEventGroupState();
extern unsigned int GetStageObjectHandle();

unsigned int func_ov001_0209c5f0(int objectIndex,u32 event,u32 value) {
  void *group;
  int state;
  u32 index;

  if (objectIndex != 0xffff) {
    group = GetStageObjectHandle(objectIndex + 1U & 0xffff);
    state = GetEventGroupState(group,event & 0xffff,value);
    if (state == 1) {
      return 1;
    }
    return 0;
  }
  index = 0;
  if (index < (u32)*(u16 *)(data_ov001_020a0528 + 0x18de8)) {
    do {
      state = GetEventGroupState
                        ((void *)(*(int *)(data_ov001_020a0528 + 0x208) + index * 0x28),
                         event & 0xffff,value);
      if ((state != 0) && (state == -1)) {
        return 0;
      }
      index = index + 1 & 0xffff;
    } while (index < *(u16 *)(data_ov001_020a0528 + 0x18de8));
  }
  return 1;
}
