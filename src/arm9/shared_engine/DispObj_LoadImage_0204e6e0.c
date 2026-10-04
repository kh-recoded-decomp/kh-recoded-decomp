#include "nitro/types.h"

typedef struct CharacterData {
    u32 pad_00;
    u32 width;
    u32 height;
    u32 pad_0c;
    u32 format;
} CharacterData;

typedef struct PaletteData {
    int fmt;
    BOOL bExtendedPlt;
    u32 szByte;
    void *pRawData;
} PaletteData;

typedef struct ImageInfo {
    u32 format;
    u32 width;
    u32 height;
    void *cellBank;
    void *animBank;
} ImageInfo;

typedef struct DispObjImage {
    u32 pad_00;
    ImageInfo info;
    void *cellFile;
    void *animFile;
    void *archive;
    u8 paletteProxy[0x14];
    u8 imageProxy[0x24];
    u32 blockCount;
    u8 pad_60[4];
    s16 paletteSlot;
} DispObjImage;

typedef struct DispManager {
    u8 pad_0000[0x4612];
    u16 paletteFlags;
    u8 pad_4614[2];
    u16 paletteOffset;
    u8 pad_4618[0x6020 - 0x4618];
    BOOL useAltLoader;
} DispManager;

extern int func_0204e588(DispManager *manager);
extern void *func_0202c478(int fileId, int kind);
extern void *func_0202c48c(int fileId, int kind);
extern void func_0202d314(void *archive, int mode);
extern void *func_0202d3e0(void *archive, int index, int arg);
extern BOOL func_02014cec(void *file, CharacterData **out);
extern u32 FindFreeVramGapOffset_0204e65c(DispManager *manager, CharacterData *data);
extern void G2D_LoadCharacterImage_020152e4(CharacterData *data, u32 offset, int vramType, void *proxy);
extern BOOL G2D_GetCellBankFromFile_02014bec(void *file, void **out);
extern BOOL PXI_Init_02014a5c(void *file, void **out);
extern u32 DispObj_GetCharBlockCount_0204e5ac(DispManager *manager, DispObjImage *image);
extern BOOL G2D_GetPaletteFromFile_02014d84(void *file, PaletteData **out);
extern int FindFirstClearFlag_0204e634(DispManager *manager);
extern void NNS_G2dLoadPalette_020154fc(PaletteData *data, u32 addr, int vramType, void *proxy);

void DispObj_LoadImage_0204e6e0(DispManager *manager, int fileId, DispObjImage *image)
{
    CharacterData *charData;
    PaletteData *palette;
    void *archive;
    void *paletteFile;
    void *charFile;
    int vramType;
    ImageInfo *info = &image->info;

    func_0204e588(manager);
    if (manager->useAltLoader) {
        archive = func_0202c48c(fileId, 0xe);
    } else {
        archive = func_0202c478(fileId, 0xe);
    }
    image->archive = archive;
    func_0202d314(archive, 1);
    vramType = func_0204e588(manager);
    if (vramType == 0) {
        charFile = func_0202d3e0(archive, 2, 0);
    } else {
        charFile = func_0202d3e0(archive, 1, 0);
    }
    func_02014cec(charFile, &charData);
    image->info.format = charData->format;
    image->info.width = charData->width;
    image->info.height = charData->height;
    G2D_LoadCharacterImage_020152e4(charData, FindFreeVramGapOffset_0204e65c(manager, charData), vramType, image->imageProxy);
    image->cellFile = func_0202d3e0(archive, 3, 0);
    image->animFile = func_0202d3e0(archive, 5, 0);
    G2D_GetCellBankFromFile_02014bec(image->cellFile, &info->cellBank);
    PXI_Init_02014a5c(image->animFile, &info->animBank);
    image->blockCount = DispObj_GetCharBlockCount_0204e5ac(manager, image);
    image->paletteSlot = -1;
    paletteFile = func_0202d3e0(archive, 0, 0);
    if (paletteFile != NULL) {
        G2D_GetPaletteFromFile_02014d84(paletteFile, &palette);
        if (palette->bExtendedPlt) {
            palette->szByte = 0x200;
            image->paletteSlot = FindFirstClearFlag_0204e634(manager);
            manager->paletteFlags |= (u16)(1 << image->paletteSlot);
            NNS_G2dLoadPalette_020154fc(palette, image->paletteSlot << 9, vramType, image->paletteProxy);
        } else {
            NNS_G2dLoadPalette_020154fc(palette, manager->paletteOffset, vramType, image->paletteProxy);
            manager->paletteOffset += palette->szByte;
        }
    }
}
