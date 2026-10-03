#include "nitro/types.h"

typedef struct {
    u16 width;
    u16 height;
    u32 pixelFormat;
    u32 mappingType;
    u32 characterFormat;
    u32 size;
    void *data;
} CharacterData;

typedef struct {
    u32 format;
    u32 extended;
    u32 size;
    void *data;
} PaletteData;

typedef struct {
    u16 width;
    u16 height;
    u16 colorMode;
    u16 screenFormat;
    u32 size;
    u8 data[4];
} ScreenData;

typedef struct {
    ScreenData *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

extern int data_ov039_020bea00;
extern unsigned int BuildSlotImageParams_020bc220(int slot, unsigned int low);
extern void *func_0202c478(unsigned int fileId, int flags);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex,
                                          int characterIndex, int paletteIndex);
extern void GXS_LoadBGPltt_020072b4(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG3Char_02007be0(const void *src, u32 offset, u32 size);
extern void *UpdateWidgetLayerDefault_020b9df0(int layers, int id);
extern void MarkTileTableRowDirty_020b9e00(int layers, int id);
extern void func_01ff869c(const void *src, void *dest, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void LoadSlotSubBgImage_020bc55c(int slot, unsigned int low, int screenIndex, int paletteIndex)
{
    BgGraphicsData bg;
    void *file = func_0202c478(BuildSlotImageParams_020bc220(slot, low), 14);
    int layers = data_ov039_020bea00 + 0xc9a0;
    u32 size;
    void *dest;

    GetBgDataFromArchive_0202b554(&bg, file, screenIndex, 0, paletteIndex);
    GXS_LoadBGPltt_020072b4(bg.palette->data, 0, bg.palette->size);
    GXS_LoadBG3Char_02007be0(bg.character->data, 0, bg.character->size);
    size = bg.screen->size;
    dest = UpdateWidgetLayerDefault_020b9df0(layers, 0x1b);
    func_01ff869c(bg.screen->data, dest, size);
    MarkTileTableRowDirty_020b9e00(layers, 0x1b);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
}
