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
    void *screen;
    CharacterData *character;
    void *palette;
} BgGraphicsData;

extern unsigned int BuildSlotImageParams_020bc220(int slot, unsigned int low);
extern void *func_0202c478(unsigned int fileId, int flags);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex,
                                          int characterIndex, int paletteIndex);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void LoadSlotBgCharacters_020bc414(int slot, unsigned int low, u32 tile)
{
    BOOL wide;
    void *file;
    BgGraphicsData bg;

    file = func_0202c478(BuildSlotImageParams_020bc220(slot, low), 14);
    GetBgDataFromArchive_0202b554(&bg, file, -1, 0, -1);
    wide = FALSE;
    if (bg.character->pixelFormat != 3) {
        wide = TRUE;
    }
    GX_LoadBG3Char_02007b70(bg.character->data, tile << ((u8)wide + 5), bg.character->size);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
}
