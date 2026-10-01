#include "nitro/types.h"

#define data_04000304 (*(volatile u16 *)0x04000304)
extern unsigned int func_02029bfc();
extern unsigned int func_02029e7c();
extern unsigned int func_02029ed0();
extern unsigned int func_02029f48();
extern unsigned int func_02029f58();
extern unsigned int func_ov022_020a831c();

void func_ov022_020a7798(void) {
  int brightness;

  brightness = func_02029f48();
  if (brightness != -0x10 && brightness != 0x10) {
    brightness = -0x10;
  }
  func_02029e7c(brightness);
  brightness = func_02029f58();
  if (brightness != -0x10 && brightness != 0x10) {
    brightness = -0x10;
  }
  func_02029ed0(brightness);
  func_02029bfc();
  func_ov022_020a831c(1);
  data_04000304 |= 0x8000;
}
