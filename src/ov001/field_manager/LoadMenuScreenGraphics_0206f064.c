#include "nitro/types.h"

typedef struct CharData {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharData;

typedef struct ScreenData {
    u8 pad_00[8];
    u32 size;
    void *data;
} ScreenData;

typedef struct BgGraphicsData {
    u32 unk0;
    CharData *character;
    ScreenData *screen;
} BgGraphicsData;

typedef struct PaletteData {
    u8 pad_00[0xc];
    void *raw;
} PaletteData;

typedef struct LayerConfig {
    u32 words[5];
} LayerConfig;

typedef struct CellConfig {
    u32 words[7];
} CellConfig;

typedef struct CellDesc {
    CellConfig *cells;
    int count;
    u16 width;
    u16 height;
    int flags;
} CellDesc;

typedef struct MenuScreen {
    u8 pad_000[0x1c];
    u8 layer[0x4c];
    int archiveBase;
    u8 pad_06c[0x404];
    void *palette;
    u8 pad_474[0x1a0];
    void *screenArchive;
    BgGraphicsData screenBg;
} MenuScreen;

extern const LayerConfig data_ov001_0209dc94;
extern const CellConfig data_ov001_0209dce4;
extern void func_ov027_020b9a0c(MenuScreen *screen, CellDesc *desc);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex, int paletteIndex);
extern void func_02007250(void *dest, u32 srcOffset, u32 size);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void func_ov027_020b7d58(void *container, LayerConfig *configuration);
extern void func_ov027_020b7e24(void *ctx, u32 fileId);
extern void *func_0202c478(u32 fileId, u32 mode);
extern void *func_0202c48c(u32 fileId, u32 mode);
extern BOOL G2D_GetPaletteFromFile_02014d84(void *pNclrFile, PaletteData **ppPltData);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_01ff878c(const void *src, void *dst, u32 size);

void LoadMenuScreenGraphics_0206f064(MenuScreen *screen, BgGraphicsData *bg, void *archive) {
    LayerConfig layer = data_ov001_0209dc94;
    CellConfig cells = data_ov001_0209dce4;
    CellDesc desc;
    PaletteData *palette;
    void *nclr;

    desc.cells = &cells;
    desc.count = 7;
    desc.width = 0x20;
    desc.height = 0x20;
    desc.flags = 0;
    func_ov027_020b9a0c(screen, &desc);
    GetBgDataFromArchive_0202b554(bg, archive, -1, 0, 0);
    func_02007250(bg->screen->data, 0, bg->screen->size);
    GX_LoadBG3Char_02007b70(bg->character->data, 0, bg->character->size);
    func_ov027_020b7d58(screen->layer, &layer);
    func_ov027_020b7e24(screen->layer, ((screen->archiveBase + 0x8000) & 0xfffffc) << 7 | 0x80000000);
    screen->screenArchive = func_0202c478(((screen->archiveBase + 0x8000) & 0xfffffc) << 7 | 0x80000003, 0xe);
    GetBgDataFromArchive_0202b554(&screen->screenBg, screen->screenArchive, -1, 0, 0);
    nclr = func_0202c48c(((screen->archiveBase + 0x8000) & 0xfffffc) << 7 | 0x80000068, 0xe);
    G2D_GetPaletteFromFile_02014d84(nclr, &palette);
    screen->palette = NNSi_FndAllocFromDefaultHeap_0202a178(0x80);
    func_01ff878c(palette->raw, screen->palette, 0x80);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(nclr);
}
