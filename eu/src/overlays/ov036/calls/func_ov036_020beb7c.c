#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 sOv036_TextFontEu10Nftr_020c38fc;
extern u32 sOv036_TextFontJp10Nftr_020c3914;
extern u32 LoadUtf16FontResource();

void func_ov036_020beb7c(void) {
  LoadUtf16FontResource(gTextWindowResourceTable + 0x644c,&sOv036_TextFontEu10Nftr_020c38fc);
  LoadUtf16FontResource(gTextWindowResourceTable + 0x68a8,&sOv036_TextFontJp10Nftr_020c3914);
}
