#include "nitro/types.h"

extern u32 sOv001_TextFontEu10Nftr_0209ed2c;
extern u32 sOv001_TextFontEu08Nftr_0209ed44;
extern u32 sOv001_TextFontEu08sNftr_0209ed5c;
extern u32 sOv001_TextFontEu10sNftr_0209ed74;
extern void func_0200146c(u32 context, u32 *table);

void func_ov001_0206f1a0(u32 context)
{
    func_0200146c(context + 0x9c, &sOv001_TextFontEu10Nftr_0209ed2c);
    func_0200146c(context + 0x78, &sOv001_TextFontEu08Nftr_0209ed44);
    func_0200146c(context + 0x84, &sOv001_TextFontEu08sNftr_0209ed5c);
    func_0200146c(context + 0x90, &sOv001_TextFontEu10sNftr_0209ed74);
}
