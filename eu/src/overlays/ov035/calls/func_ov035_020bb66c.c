#include "nitro/types.h"

extern unsigned int data_ov035_020bc504;
extern unsigned int ReleaseResourceAndDetach();

void func_ov035_020bb66c(void) {
  int actor;

  actor = data_ov035_020bc504;
  if (*(u8 *)(data_ov035_020bc504 + 0x10b) != '\0') {
    ReleaseResourceAndDetach(data_ov035_020bc504);
    *(u8 *)(actor + 0x10b) = 0;
  }
}
