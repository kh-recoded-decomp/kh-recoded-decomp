#include "nitro/types.h"

typedef struct NNSG2dPaletteData {
    u32 fmt;
    BOOL extended;
    u32 szByte;
    void *pRawData;
} NNSG2dPaletteData;

extern BOOL NNS_G2dGetUnpackedPaletteData(void *file, NNSG2dPaletteData **out);
extern void DC_FlushRange(const void *addr, u32 size);
extern void GX_LoadBGPltt(void *addr, u32 val, u32 size);
extern u32 func_ov027_020ba1f8();
extern void func_ov027_020ba200(u32 entry, u32 flag);
extern void func_ov001_0207a1d0(u32 field);

extern u32 data_ov001_020a04e4;

void func_ov001_02078d7c(u32 entry, u32 unused1, u32 unused2, u32 unused3)
{
    u32 context;
    u32 unused;
    NNSG2dPaletteData *palette;
    u32 file;

    context = data_ov001_020a04e4;
    unused = unused3;
    if (*(u32 *)(data_ov001_020a04e4 + 0xf8) != 0) {
        func_ov027_020ba200(entry, 1);
        return;
    }
    file = func_ov027_020ba1f8();
    NNS_G2dGetUnpackedPaletteData((void *)file, &palette);
    DC_FlushRange(palette->pRawData, 0x200);
    GX_LoadBGPltt(palette->pRawData, 0, 0x1a0);
    func_ov027_020ba200(entry, 1);
    func_ov001_0207a1d0(context + 4);
}
