#include "nitro/types.h"

#define data_04000304 (*(volatile u16 *)0x04000304)
extern unsigned int ResetDisplayHardware();
extern unsigned int SetBrightnessAndSyncMain();
extern unsigned int SetSecondaryBrightness();
extern unsigned int GetMainBrightnessSetting();
extern unsigned int GetSubBrightnessSetting();
extern unsigned int SetupMovieScreenHardware();

void SetupMovieDisplayAtFullFade(void) {
  int brightness;

  brightness = GetMainBrightnessSetting();
  if (brightness != -0x10 && brightness != 0x10) {
    brightness = -0x10;
  }
  SetBrightnessAndSyncMain(brightness);
  brightness = GetSubBrightnessSetting();
  if (brightness != -0x10 && brightness != 0x10) {
    brightness = -0x10;
  }
  SetSecondaryBrightness(brightness);
  ResetDisplayHardware();
  SetupMovieScreenHardware(1);
  data_04000304 |= 0x8000;
}
