#include "nitro/types.h"

extern unsigned int data_ov035_020bc4e4;
extern unsigned int func_0202eee8();

void func_ov035_020bb64c(void) {
  int actor;

  actor = data_ov035_020bc4e4;
  if (*(u8 *)(data_ov035_020bc4e4 + 0x10b) != '\0') {
    func_0202eee8(data_ov035_020bc4e4);
    *(u8 *)(actor + 0x10b) = 0;
  }
}
