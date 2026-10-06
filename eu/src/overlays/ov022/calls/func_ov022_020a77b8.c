#include "nitro/types.h"

#define data_04000304 (*(volatile u16 *)0x04000304)
extern unsigned int ResetDisplayHardware();
extern unsigned int SetBrightnessAndSyncMain();
extern unsigned int SetSecondaryBrightness();
extern unsigned int func_02029f5c();
extern unsigned int func_02029f6c();
extern unsigned int SetupMovieScreenHardware();

void func_ov022_020a77b8(void) {
  int brightness;

  brightness = func_02029f5c();
  if (brightness != -0x10 && brightness != 0x10) {
    brightness = -0x10;
  }
  SetBrightnessAndSyncMain(brightness);
  brightness = func_02029f6c();
  if (brightness != -0x10 && brightness != 0x10) {
    brightness = -0x10;
  }
  SetSecondaryBrightness(brightness);
  ResetDisplayHardware();
  SetupMovieScreenHardware(1);
  data_04000304 |= 0x8000;
}
