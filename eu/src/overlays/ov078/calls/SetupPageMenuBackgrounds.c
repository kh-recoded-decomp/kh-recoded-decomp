#include "nitro/types.h"

typedef struct PageMenu {
    void *questText;
    void *languageText;
    void *battleText;
    int messageView[3];
} PageMenu;

typedef struct ScreenData {
    u8 pad_00[8];
    u32 size;
    u8 rawData[4];
} ScreenData;

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
    void *rawData;
} CharacterData;

typedef struct PaletteData {
    u8 pad_00[0xc];
    void *rawData;
} PaletteData;

typedef struct BgGraphicsData {
    ScreenData *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct RecordSaveData RecordSaveData;

extern RecordSaveData *data_0205fe0c;

extern void G2x_SetBlendAlpha_(vu16 *registerAddress, int firstPlanes, int secondPlanes, int firstWeight,
                               int secondWeight);
extern void *G2_GetBG2CharPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void MIi_CpuClearFast(u32 value, void *destination, u32 byteCount);
extern const u16 *func_ov039_020bcb40(RecordSaveData *save);
extern void DrawLayoutLine(PageMenu *menu, int line, const void *text, const void *suffix);
extern const u16 *func_ov027_020ba2c8(int *view, int index);
extern void *Archive_LoadFile(u32 fileId, int heapId);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                 int paletteIndex);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Scr(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *memory);

#define reg_GX_DISPCNT (*(vu32 *)0x04000000)
#define reg_G2_BG0CNT (*(vu16 *)0x04000008)
#define reg_G2_BG1CNT (*(vu16 *)0x0400000a)
#define reg_G2_BG2CNT (*(vu16 *)0x0400000c)
#define reg_G2_BG3CNT (*(vu16 *)0x0400000e)
#define reg_G2_BG1OFS (*(vu32 *)0x04000014)
#define reg_G2_BG2OFS (*(vu32 *)0x04000018)
#define reg_G2_BG3OFS (*(vu32 *)0x0400001c)
#define reg_G2_BLDCNT (*(vu16 *)0x04000050)

/* Merge new field bits into the bits kept from a display register. */
static inline int MergeRegisterBits(int kept, int bits)
{
    return kept | bits;
}

/* NitroSDK's GX/G2 register inlines. */
static inline void GX_SetVisiblePlane(int plane)
{
    reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0x1f00) | (plane << 8);
}

static inline void GX_SetVisibleWnd(int window)
{
    reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0xe000) | (window << 13);
}

static inline void G2_SetBG0Priority(int priority)
{
    reg_G2_BG0CNT = (u16)MergeRegisterBits(reg_G2_BG0CNT & ~3, priority);
}

static inline void G2_SetBG1Priority(int priority)
{
    reg_G2_BG1CNT = (u16)((reg_G2_BG1CNT & ~3) | priority);
}

static inline void G2_SetBG2Priority(int priority)
{
    reg_G2_BG2CNT = (u16)((reg_G2_BG2CNT & ~3) | priority);
}

static inline void G2_SetBG3Priority(int priority)
{
    reg_G2_BG3CNT = (u16)((reg_G2_BG3CNT & ~3) | priority);
}

static inline void G2_SetBG1Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    reg_G2_BG1CNT = (u16)((reg_G2_BG1CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                          (charBase << 2) | (bgExtPltt << 13));
}

static inline void G2_SetBG2ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    reg_G2_BG2CNT = (u16)((reg_G2_BG2CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                          (charBase << 2));
}

static inline void G2_SetBG3ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    reg_G2_BG3CNT = (u16)((reg_G2_BG3CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                          (charBase << 2));
}

/* The archive id packed from a message container's address, as InitPageMenu builds it. */
static inline u32 PackedFileId(void *container)
{
    return ((((u32)container + 0x8000) & 0xfffffc) << 7) | 0x80000000;
}

/* Set the main screen's blending, BG layers and priorities, draw the header lines, and load
 * the page background and overlay characters from the message containers' archives. */
void SetupPageMenuBackgrounds(PageMenu *menu)
{
    BgGraphicsData bg;
    BgGraphicsData overlay;
    void *file;

    G2x_SetBlendAlpha_(&reg_G2_BLDCNT, 1, 0x1e, 16, 16);
    GX_SetVisiblePlane(0x1d);
    G2_SetBG0Priority(1);
    G2_SetBG1Priority(0);
    G2_SetBG2Priority(2);
    G2_SetBG3Priority(3);
    reg_G2_BG1OFS = 0;
    reg_G2_BG2OFS = 0;
    reg_G2_BG3OFS = 0;
    GX_SetVisibleWnd(0);
    G2_SetBG1Control(0, 0, 0, 2, 0);
    G2_SetBG2ControlText(0, 0, 1, 4);
    G2_SetBG3ControlText(0, 0, 2, 6);
    MIi_CpuClearFast(0, G2_GetBG2CharPtr(), 0x20);
    MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x600);

    DrawLayoutLine(menu, 0, func_ov039_020bcb40(data_0205fe0c), NULL);
    DrawLayoutLine(menu, 5, func_ov027_020ba2c8(menu->messageView, 0), NULL);
    DrawLayoutLine(menu, 6, func_ov027_020ba2c8(menu->messageView, 1), NULL);

    file = Archive_LoadFile(PackedFileId(menu->questText), 15);
    GetBgDataFromArchive(&bg, file, 0, 0, 0);
    GX_LoadBGPltt(bg.palette->rawData, 0, 0x200);
    GX_LoadBG3Char(bg.character->rawData, 0, 0x1000);
    GX_LoadBG3Scr(bg.screen->rawData, 0, 0x600);
    NNSi_FndFreeFromDefaultHeap(file);

    file = Archive_LoadFile(PackedFileId(menu->languageText), 15);
    GetBgDataFromArchive(&overlay, file, -1, 0, -1);
    GX_LoadBG3Char(overlay.character->rawData, 0x1000, 0x400);
    NNSi_FndFreeFromDefaultHeap(file);
}
