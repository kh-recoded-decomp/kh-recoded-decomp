#include "src/overlays/ov081/BgTextTransfers.h"

extern void GX_LoadBG0Char(const void *source, u32 offset, u32 size);
extern void GX_LoadBG1Char(const void *source, u32 offset, u32 size);
extern void GX_LoadBG2Char(const void *source, u32 offset, u32 size);
extern void GX_LoadBG3Char(const void *source, u32 offset, u32 size);

const BgCharacterLoader gBgCharacterLoaders[4] = {
    GX_LoadBG0Char,
    GX_LoadBG1Char,
    GX_LoadBG2Char,
    GX_LoadBG3Char,
};
