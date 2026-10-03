#include "nitro/types.h"

extern void GX_LoadBG1Scr_02007630(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Scr_02007710(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Scr_020077f0(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG0Scr_020075c0(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG1Scr_020076a0(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG2Scr_02007780(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG3Scr_02007860(const void *src, u32 offset, u32 size);

BOOL LoadBgScreenData_020b989c(int bgId, u32 offset, const void *src, u32 size)
{
    BOOL loaded = TRUE;

    switch (bgId) {
    case 9:
        GX_LoadBG1Scr_02007630(src, offset, size);
        break;
    case 10:
        GX_LoadBG2Scr_02007710(src, offset, size);
        break;
    case 11:
        GX_LoadBG3Scr_020077f0(src, offset, size);
        break;
    case 24:
        GXS_LoadBG0Scr_020075c0(src, offset, size);
        break;
    case 25:
        GXS_LoadBG1Scr_020076a0(src, offset, size);
        break;
    case 26:
        GXS_LoadBG2Scr_02007780(src, offset, size);
        break;
    case 27:
        GXS_LoadBG3Scr_02007860(src, offset, size);
        break;
    default:
        loaded = FALSE;
        break;
    }
    return loaded;
}
