#include "nitro/types.h"

extern unsigned int func_ov039_020bc084();
extern unsigned int func_ov076_020c5be0();
extern unsigned int func_ov076_020c8490();

void func_ov076_020c5c80(int work) {
  func_ov039_020bc084(0);
  func_ov076_020c5be0(work);
  *(u8 *)(work + 0x49857) = *(u8 *)(work + 0x49857) + -1;
  if (*(u8 *)(work + 0x49857) == '\0') {
    func_ov076_020c8490(work);
  }
}
