#include "nitro/types.h"

typedef unsigned int code();

extern unsigned char data_ov038_020bbd24;
extern unsigned int InitOv038SlotPools_020bb104();
extern unsigned int func_ov038_020bb65c();

unsigned int func_ov038_020bbce8(void) {
  int state;
  unsigned int result;

  state = func_ov038_020bb65c();
  result = (**(code **)(&data_ov038_020bbd24 + state * 4))();
  InitOv038SlotPools_020bb104();
  return result;
}
