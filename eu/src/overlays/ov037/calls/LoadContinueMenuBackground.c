#include "src/overlays/ov037/ContinueMenu.h"

/* The tile ids are copied by value before the table borrows them. */
typedef struct ContinueMenuTileIdList {
    s32 ids[2];
} ContinueMenuTileIdList;

typedef struct NNSG2dPaletteData {
    u32 format;
    BOOL isExtended;
    u32 size;
    void *data;
} NNSG2dPaletteData;

typedef struct NNSG2dCharacterData {
    u8 reserved00[0x10];
    u32 size;
    void *data;
} NNSG2dCharacterData;

typedef struct BgGraphicsData {
    void *screen;
    NNSG2dCharacterData *character;
    NNSG2dPaletteData *palette;
} BgGraphicsData;

extern char sOv037_CntCntPbgZ_020bb704[];
extern char sOv037_CntCntBguiZ_020bb714[];

extern void *func_0202c4a0(const char *path, u32 flags);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                 int paletteIndex);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *memory);
extern void InitTileTableFrom(ContinueMenuTileTable *table, const ContinueMenuTileConfig *source);
extern void InitBackgroundContainer(void *list, const ContinueMenuListConfig *config);
extern void func_ov027_020b7e44(void *list, const char *path);
extern void RefreshMenuListLayout(void);

/* Load the continue screen's BG3 graphics, then build its tile table and menu list. */
void LoadContinueMenuBackground(void)
{
    ContinueMenuTileConfig tiles = gContinueMenuTileConfig;
    ContinueMenuListConfig listConfig = gContinueMenuListConfig;
    ContinueMenuTileIdList ids = *(const ContinueMenuTileIdList *)gContinueMenuTileIds;
    ContinueMenuGraphicsState *context = gContinueScreenContext;
    BgGraphicsData bg;
    void *archive;
    u8 *list = context->list;

    archive = func_0202c4a0(sOv037_CntCntPbgZ_020bb704, 0xe);
    GetBgDataFromArchive(&bg, archive, -1, 0, 0);
    GX_LoadBGPltt(bg.palette->data, 0, bg.palette->size);
    GX_LoadBG3Char(bg.character->data, 0, bg.character->size);
    NNSi_FndFreeFromDefaultHeap(archive);
    tiles.ids = ids.ids;
    InitTileTableFrom(&gContinueScreenContext->tileTable, &tiles);
    InitBackgroundContainer(list, &listConfig);
    func_ov027_020b7e44(list, sOv037_CntCntBguiZ_020bb714);
    RefreshMenuListLayout();
}
