#include "nitro/types.h"
#include "src/overlays/ov027/FileLoadQueue.h"

typedef struct NNSG2dPaletteData {
    u32 fmt;
    BOOL extended;
    u32 szByte;
    void *pRawData;
} NNSG2dPaletteData;

extern BOOL NNS_G2dGetUnpackedPaletteData(void *file, NNSG2dPaletteData **out);
extern void DC_FlushRange(const void *addr, u32 size);
extern void GX_LoadBGPltt(void *addr, u32 val, u32 size);
extern void OpenMessageWindowLayers(u32 field);

extern u32 gMessageWindowWork;

void UploadMessageWindowPaletteCallback(u32 entry, u32 unused1, u32 unused2, u32 unused3)
{
    u32 context;
    u32 unused;
    NNSG2dPaletteData *palette;
    u32 file;

    context = gMessageWindowWork;
    unused = unused3;
    if (*(u32 *)(gMessageWindowWork + 0xf8) != 0) {
        DestroyFileLoadRequest((FileLoadRequest *)entry, TRUE);
        return;
    }
    file = (u32)GetFileLoadRequestBuffer((const FileLoadRequest *)entry);
    NNS_G2dGetUnpackedPaletteData((void *)file, &palette);
    DC_FlushRange(palette->pRawData, 0x200);
    GX_LoadBGPltt(palette->pRawData, 0, 0x1a0);
    DestroyFileLoadRequest((FileLoadRequest *)entry, TRUE);
    OpenMessageWindowLayers(context + 4);
}
