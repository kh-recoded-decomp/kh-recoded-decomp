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

extern unsigned int BuildSlotImageParams_020bc220(int slot, unsigned int low);
extern void *func_0202c478(unsigned int fileId, int flags);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex,
                                          int characterIndex, int paletteIndex);
extern void func_02007250(void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void *UpdateScreenWidgetLayer_020bc1e4(int screen);
extern void func_01ff869c(const void *src, void *dest, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void LoadSlotBgImage_020bc26c(int slot, unsigned int low, int screenIndex, int paletteIndex, void **fileOut)
{
    BgGraphicsData bg;
    void *file = func_0202c478(BuildSlotImageParams_020bc220(slot, low), 14);
    u32 size;
    void *dest;

    GetBgDataFromArchive_0202b554(&bg, file, screenIndex, 0, paletteIndex);
    func_02007250(bg.palette->data, 0, bg.palette->size);
    GX_LoadBG3Char_02007b70(bg.character->data, 0, bg.character->size);
    size = bg.screen->size;
    dest = UpdateScreenWidgetLayer_020bc1e4(0xb);
    func_01ff869c(bg.screen->data, dest, size);
    if (fileOut != 0) {
        *fileOut = file;
        return;
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
}
