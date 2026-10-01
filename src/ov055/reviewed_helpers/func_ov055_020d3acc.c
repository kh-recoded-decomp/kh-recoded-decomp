#include "nitro/types.h"

extern unsigned int func_0202a1c4();
extern unsigned int func_ov021_020ae6c8();
extern unsigned int func_ov021_020af1fc();

void func_ov055_020d3acc(int work) {
  if (*(char *)(*(int *)(work + 0x50) + 0x3d) == '\x04') {
    func_ov021_020af1fc(*(int *)(work + 0x50));
  }
  func_ov021_020ae6c8(*(unsigned int *)(work + 0x50));
  func_0202a1c4(*(unsigned int *)(work + 0x50));
}
