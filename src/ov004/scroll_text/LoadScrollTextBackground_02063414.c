#include "nitro/types.h"
#include "game/scroll_bg.h"

typedef struct ScrollBgScreenData {
    u16 width;
    u16 height;
    u32 format;
    u32 dataSize;
    u8 data[1];
} ScrollBgScreenData;

typedef struct ScrollBgCharacterData {
    u16 height;
    u16 width;
    u32 pixelFormat;
    u32 mappingType;
    u32 characterFormat;
    u32 dataSize;
    void *data;
} ScrollBgCharacterData;

typedef struct ScrollBgPaletteData {
    u32 pixelFormat;
    BOOL extendedPalette;
    u32 dataSize;
    void *data;
} ScrollBgPaletteData;

typedef struct ScrollBgGraphics {
    ScrollBgScreenData *screen;
    ScrollBgCharacterData *characters;
    ScrollBgPaletteData *palette;
} ScrollBgGraphics;

typedef struct ScrollBgScreen {
    void *activeCharacterFile;
    void *characterFile;
    void *screenFile;
    ScrollBgGraphics graphics;
    u8 reserved18[0x10918 - 0x18];
    s16 startX;
    s16 startY;
    u8 reserved1091c[0x10940 - 0x1091c];
} ScrollBgScreen;

/* The two screen-resource views within the larger scroll-text work area. */
typedef struct ScrollBgWork {
    u8 reserved00[0x14];
    ScrollBgScreen screens[2];
} ScrollBgWork;

/* The complete global descriptor occupies 32 bytes of BSS. */
typedef struct ScrollBgGlobals {
    u32 frameCount;
    ScrollBgWork *work;
    u32 reserved08[6];
} ScrollBgGlobals;

typedef char ScrollBgGlobalsSizeCheck[(sizeof(ScrollBgGlobals) == 32) ? 1 : -1];
typedef char ScrollBgScreenStrideCheck[(sizeof(ScrollBgScreen) == 0x10940) ? 1 : -1];

typedef struct ScrollWindowPlacement ScrollWindowPlacement;

extern ScrollBgGlobals gScrollTextGlobals;
extern void GetBgDataFromArchive(ScrollBgGraphics *out, void *archive, s32 screen,
    s32 characters, s32 palette);
extern BOOL NNS_GfdRegisterNewVramTransferTask(u32 task, u32 destination,
    const void *source, u32 size);
extern void SetWindowCorners(ScrollBgScreen *screen, const ScrollWindowPlacement *placement);
extern void CopyScrollTextTiles(ScrollBgGraphics *graphics, s32 screenIndex, s32 column, s32 row);

/* Load a layer's resources and enqueue its palette. A window placement builds
 * the visible scrolling tiles; a full background uploads characters and map. */
void LoadScrollTextBackground_02063414(void *archive, s32 layer, s32 entry,
    const ScrollWindowPlacement *placement)
{
    ScrollBgTransfers transfers = gScrollTextBackgroundTransfers;
    s32 screenIndex = layer >> 1;
    ScrollBgGraphics *graphics = &gScrollTextGlobals.work->screens[screenIndex].graphics;

    GetBgDataFromArchive(graphics, archive, entry, entry, entry);
    NNS_GfdRegisterNewVramTransferTask(transfers.layers[layer].paletteTask,
        transfers.layers[layer].paletteSlot << 13,
        graphics->palette->data, graphics->palette->dataSize);
    if (placement != NULL) {
        SetWindowCorners(&gScrollTextGlobals.work->screens[screenIndex], placement);
        CopyScrollTextTiles(graphics, screenIndex,
            gScrollTextGlobals.work->screens[screenIndex].startX >> 3,
            (gScrollTextGlobals.work->screens[screenIndex].startY >> 3) - 1);
        return;
    }
    NNS_GfdRegisterNewVramTransferTask(transfers.layers[layer].characterTask, 0,
        graphics->characters->data, graphics->characters->dataSize);
    NNS_GfdRegisterNewVramTransferTask(transfers.layers[layer].screenTask, 0,
        graphics->screen->data, graphics->screen->dataSize);
}
