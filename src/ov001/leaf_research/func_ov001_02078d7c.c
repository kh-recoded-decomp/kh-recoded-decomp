#include "nitro/types.h"

typedef struct NNSG2dPaletteData {
    u32 fmt;
    BOOL extended;
    u32 szByte;
    void *pRawData;
} NNSG2dPaletteData;

extern BOOL G2D_GetPaletteFromFile_02014d84(void *file, NNSG2dPaletteData **out);
extern void DC_FlushRange_0200344c(const void *addr, u32 size);
extern void func_02007250(void *addr, u32 val, u32 size);
extern u32 func_ov027_020ba1d8();
extern void func_ov027_020ba1e0(u32 entry, u32 flag);
extern void func_ov001_0207a1d0(u32 field);

extern u32 g_activeContext_020a04c4;

void func_ov001_02078d7c(u32 entry, u32 unused1, u32 unused2, u32 unused3)
{
    u32 context;
    u32 unused;
    NNSG2dPaletteData *palette;
    u32 file;

    context = g_activeContext_020a04c4;
    unused = unused3;
    if (*(u32 *)(g_activeContext_020a04c4 + 0xf8) != 0) {
        func_ov027_020ba1e0(entry, 1);
        return;
    }
    file = func_ov027_020ba1d8();
    G2D_GetPaletteFromFile_02014d84((void *)file, &palette);
    DC_FlushRange_0200344c(palette->pRawData, 0x200);
    func_02007250(palette->pRawData, 0, 0x1a0);
    func_ov027_020ba1e0(entry, 1);
    func_ov001_0207a1d0(context + 4);
}
