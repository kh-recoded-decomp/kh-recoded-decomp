#include "nitro/types.h"

typedef struct {
    u8 pad00[8];
    u32 size;
    void *data;
} PaletteData;

typedef struct {
    u8 pad00[0x10];
    u32 size;
    void *data;
} CharacterData;

typedef struct BgGraphicsData {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void func_02007250(void *dest, u32 srcOffset, u32 size);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern BOOL func_02014d38(void *file, CharacterData **characterOut);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *memory);

void LoadBg3Graphics_020be5e0(void *archive, int characterIndex, int paletteIndex, BOOL loadPalette,
                              void *characterFile, u32 characterOffset)
{
    CharacterData *character;
    BgGraphicsData bg;

    if (!loadPalette) {
        paletteIndex = -1;
    }
    GetBgDataFromArchive_0202b554(&bg, archive, -1, characterIndex, paletteIndex);
    if (loadPalette) {
        func_02007250(bg.palette->data, 0, bg.palette->size);
    }
    if (characterFile == NULL) {
        GX_LoadBG3Char_02007b70(bg.character->data, 0, bg.character->size);
        character = bg.character;
    } else {
        func_02014d38(characterFile, &character);
        if (characterIndex >= 0) {
            GX_LoadBG3Char_02007b70(bg.character->data, 0, bg.character->size);
        }
        GX_LoadBG3Char_02007b70(character->data, characterOffset, character->size);
    }
    if (archive != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
    }
    if (characterFile != NULL) {
        if (characterFile != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(characterFile);
        }
    }
}

