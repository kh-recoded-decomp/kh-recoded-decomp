#include "nitro/types.h"

extern u32 func_ov001_020641d4();
extern u32 func_ov038_020bbce8();

u32 func_ov038_020ba568(void) {
  int ready;

  ready = func_ov038_020bbce8();
  if (ready != 0) {
    func_ov001_020641d4(2);
    return 4;
  }
  return 0xffffffff;
}
