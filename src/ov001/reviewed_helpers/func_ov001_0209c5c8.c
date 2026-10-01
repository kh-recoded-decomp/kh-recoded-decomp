#include "nitro/types.h"

extern unsigned int data_ov001_020a0508;
extern unsigned int GetEventGroupState_02098ea8();
extern unsigned int GetStageObjectHandle_0209c0c4();

unsigned int func_ov001_0209c5c8(int objectIndex,u32 event,u32 value) {
  void *group;
  int state;
  u32 index;

  if (objectIndex != 0xffff) {
    group = GetStageObjectHandle_0209c0c4(objectIndex + 1U & 0xffff);
    state = GetEventGroupState_02098ea8(group,event & 0xffff,value);
    if (state == 1) {
      return 1;
    }
    return 0;
  }
  index = 0;
  if (index < (u32)*(u16 *)(data_ov001_020a0508 + 0x18de8)) {
    do {
      state = GetEventGroupState_02098ea8
                        ((void *)(*(int *)(data_ov001_020a0508 + 0x208) + index * 0x28),
                         event & 0xffff,value);
      if ((state != 0) && (state == -1)) {
        return 0;
      }
      index = index + 1 & 0xffff;
    } while (index < *(u16 *)(data_ov001_020a0508 + 0x18de8));
  }
  return 1;
}
