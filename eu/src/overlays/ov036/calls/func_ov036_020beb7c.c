#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 sOv036_TextFontEu10Nftr_020c38fc;
extern u32 sOv036_TextFontJp10Nftr_020c3914;
extern u32 func_0200146c();

void func_ov036_020beb7c(void) {
  func_0200146c(gTextWindowResourceTable + 0x644c,&sOv036_TextFontEu10Nftr_020c38fc);
  func_0200146c(gTextWindowResourceTable + 0x68a8,&sOv036_TextFontJp10Nftr_020c3914);
}
