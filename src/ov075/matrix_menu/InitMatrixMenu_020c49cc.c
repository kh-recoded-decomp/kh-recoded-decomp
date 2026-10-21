#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nnsys/g2d.h"

#define ARCHIVE_FILE(handle) ((((u32)(handle) + 0x8000) & 0xfffffc) << 7)
#define ARCHIVE_FILE_ID(handle, index) (ARCHIVE_FILE(handle) | 0x80000000 | ((index) & 0x1ff))

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_BG0CNT (*(vu16 *)0x04000008)
#define REG_BG1CNT (*(vu16 *)0x0400000a)
#define REG_BG2CNT (*(vu16 *)0x0400000c)
#define REG_BG3CNT (*(vu16 *)0x0400000e)
#define REG_DISP3DCNT (*(vu16 *)0x04000060)
#define REG_POWCNT (*(vu16 *)0x04000304)

typedef struct ResourceContainer ResourceContainer;
typedef struct LayoutObject LayoutObject;

typedef struct {
    s16 x;
    s16 y;
} Point16;

typedef union {
    Point16 pos;
    u32 packed;
} GridCell;

typedef struct {
    u16 id;
    u8 type;
    s8 linkIndex;
    s16 slotId;
    u16 groupBit;
    u8 placed;
    u8 pad_09[7];
    s16 parentIndex;
    u8 pad_12[2];
} GridItem;

typedef struct {
    u8 width;
    u8 pad_01[3];
    u16 itemCount;
} GridHeader;

typedef struct {
    u8 pad_0000[4];
    u16 unlockOrder[10];
    GridItem *links[32];
    GridHeader *header;
    GridItem *cells[0x6c0];
    GridItem *items[(0x21dc - 0x1b9c) / 4];
    GridItem *pathCells[13][16];
    u8 pathLength[12];
    u8 pad_2528[0x2be8 - 0x2528];
    u8 unlockLevel[1];
} Grid;

typedef struct {
    NNSG2dScreenData *screen;
    NNSG2dCharacterData *character;
    NNSG2dPaletteData *palette;
} BgGraphicsData;

typedef struct {
    u16 words[8];
} TextFrameParams;

typedef struct {
    u8 levels[6];
} LevelTable;

typedef struct {
    u8 x;
    u8 y;
    s8 offsetX;
    s8 offsetY;
} IconOffset;

typedef struct {
    u32 data[3];
} MenuSprite;

typedef struct {
    u8 pad_00[0xb0];
    fx32 scaleX;
    u8 pad_b4[0x104 - 0xb4];
} MenuModel;

typedef struct {
    Point16 points[16];
    u8 lastStep;
    u8 step;
    u8 frame;
    u8 done;
} PathTrail;

typedef struct {
    u8 pad_000[0x38a];
    u8 rank;
    u8 abilityLevel;
    u8 attackLevel;
    u8 magicLevel;
    u8 cellLevel;
} MatrixProgress;

typedef struct {
    u8 pad_0000[0x28d8];
    MatrixProgress progress;
    u8 unlockCount;
    u8 pad_2c68[5];
    s8 itemFlags[0x2d36 - 0x2c6d];
    u16 lastItemId;
} SaveBlock;

typedef struct {
    u8 pad_00000[7];
    u8 needsRedraw;
    u8 pad_00008[0x10];
    fx32 originX;
    fx32 originY;
    u8 pad_00020[8];
    Point16 cursor;
    u8 pad_0002c[8];
    fx32 scrollX;
    fx32 scrollY;
    u8 pad_0003c[0x6c - 0x3c];
    BOOL ready;
    u8 pad_00070[0x84 - 0x70];
    u8 picker[0x778 - 0x84];
    u8 effectWork[0x4ee0 - 0x778];
    u8 messageBank[0x11f44 - 0x4ee0];
    u8 textFrame[0x11fac - 0x11f44];
    void *currentMessage;
    u8 pad_11fb0[0x12db4 - 0x11fb0];
    void *archiveA;
    void *archiveB;
    NNSG2dScreenData *screen;
    void *touch;
    u8 pad_12dc4[0x12dd0 - 0x12dc4];
    Grid *grid;
    GridItem *selectedItem;
    u8 groupCounts[12];
    GridItem *groupSlots[12][20];
    ResourceContainer *layout;
    u8 pad_131a8[0x131b8 - 0x131a8];
    MenuSprite hudSprites[7];
    MenuSprite cellSprites[5][9];
    MenuSprite tabSprites[5];
    MenuModel abilityModel;
    MenuModel attackModel;
    MenuSprite modeSprite;
    MenuModel magicModel;
    MenuModel cellModel;
    MenuSprite frameSprites[4];
    MenuSprite markerSprites[5];
    void *effect;
    MenuModel bigModels[5];
    MenuSprite iconSprites[8];
    u8 pad_13e64[0x13e8c - 0x13e64];
    u8 *rank;
    u8 *magicLevel;
    u8 *cellLevel;
    u8 *attackLevel;
    u8 *abilityLevel;
    u8 pad_13ea0[0x13eb8 - 0x13ea0];
    GridCell cellOffset;
    GridCell cellTarget;
    fx32 cellHeight;
    u8 pad_13ec4[4];
    LayoutObject *objectA;
    LayoutObject *objectB;
    void *bgArchive;
    BgGraphicsData bg;
    u8 history[0x174e0 - 0x13ee0];
    void *charBuffer;
    u8 pad_174e4[0x174f4 - 0x174e4];
    s32 introState;
    u8 pad_174f8[0x17574 - 0x174f8];
    PathTrail trails[12];
    s32 trailIndex;
} MatrixMenu;

extern SaveBlock *data_0205fe0c;
extern MatrixMenu *data_ov075_020d18e0;
extern char data_ov075_020d1824[];
extern char data_ov075_020d1838[];
extern char data_ov075_020d184c[];
extern const TextFrameParams data_ov075_020d14f0;
extern const LevelTable data_ov075_020d14a0;
extern const IconOffset data_ov075_020d1454[];

extern void func_01ff8830(void *dst, int value, u32 size);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *path, u32 kind, u32 fromTop);
extern BOOL HasPendingUnlocks_020c49a8(void);
extern void SetPrimaryElementEnabled_020bc054(BOOL enabled);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern void G2x_SetBlendAlpha_02006850(vu16 *reg, int plane1, int plane2, int ev1, int ev2);
extern void *func_0202c478(u32 fileId, u32 heapId);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void func_02007250(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int alignment);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_01ff869c(const void *src, void *dst, u32 size);
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void *G2_GetBG1ScrPtr_02006e34(void);
extern void func_01ff8740(int value, void *dst, u32 size);
extern void func_01ff86fc(int value, void *dst, u32 size);
extern void func_01ff8ad8(const void *src, void *dst, u32 size);
extern void func_ov075_020cfbfc(void *picker, int recordIndex, void (*callback)(void));
extern void SetDescriptionText_020cccd8(void);
extern void OpenTextFrame_020be5b8(int position, int size, int palette, void *frame, const TextFrameParams *params);
extern void *func_ov027_020ba2a8(void *bank, int index);
extern ResourceContainer *func_ov039_020bc1bc(void);
extern Grid *AcquireMapLayout_020506dc(int index, int flags);
extern LayoutObject *FindWidgetById_020b90a4(ResourceContainer *layout, int elementId);
extern void SetLayoutElementVisible_020d0e4c(ResourceContainer *layout, int index, BOOL visible);
extern void func_ov027_020b97b8(ResourceContainer *layout, LayoutObject *object, int flag);
extern void func_0202c690(int mode);
extern void LoadTextureImageParams_020d0c18(MenuSprite *sprite, u32 fileId);
extern void InitMenuModel_020d0b74(MenuModel *model, u32 fileId, u32 trackMask);
extern int *func_01ffb2f8(MenuModel *model, int track, fx32 value);
extern GridCell GetSlotCellOffset_020c493c(int code);
extern BOOL IsMenuModeUnlocked_020c4324(int mode);
extern int CountUnlockedTiers_020c4988(void);
extern u32 PropagateMatrixNodeVisit_020c5778(MatrixMenu *menu, GridItem *node, int dir, BOOL quiet, BOOL keepSteps);
extern void DrawMatrixCellGlyph_020c7fa8(u8 *pixels, Grid *grid, GridItem *item, u32 cellIndex);
extern void InvokeForChannelOrBoth_0200110c(int channel, const char *name, void (*callback)(void), int arg);
extern void func_ov075_020c8920(void);
extern void *func_ov039_020bca00(void);
extern void SetupAllSelectionRecords_0204f85c(void);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern int GetPackedBitMask_0202d4a0(void *bitWords, int bitIndex);

static inline void SetBlendAlpha(int plane1, int plane2, int ev1, int ev2)
{
    G2x_SetBlendAlpha_02006850((vu16 *)0x04000050, plane1, plane2, ev1, ev2);
}

static inline void SetVisiblePlane(int plane)
{
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (plane << 8);
}

static inline void SetBG1Control(int screenSize, int colorMode, int screenBase, int charBase, int extPltt)
{
    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) | (extPltt << 13));
}

static inline void SetBG2Control(int screenSize, int colorMode, int screenBase, int charBase, int extPltt)
{
    REG_BG2CNT = (u16)((REG_BG2CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) | (extPltt << 13));
}

static inline void SetBG3Control(int screenSize, int colorMode, int screenBase, int charBase, int extPltt)
{
    REG_BG3CNT = (u16)((REG_BG3CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) | (extPltt << 13));
}

static inline void SetBG0Priority(int priority)
{
    REG_BG0CNT = (u16)((REG_BG0CNT & ~3) | priority);
}

static inline void SetBG1Priority(int priority)
{
    REG_BG1CNT = (u16)((REG_BG1CNT & ~3) | priority);
}

static inline void SetBG2Priority(int priority)
{
    REG_BG2CNT = (u16)((REG_BG2CNT & ~3) | priority);
}

static inline void SetBG3Priority(int priority)
{
    REG_BG3CNT = (u16)((REG_BG3CNT & ~3) | priority);
}

typedef struct {
    u16 cells[32];
} ScreenRow;

/* Unused extra parameters double as scratch locals. */
BOOL InitMatrixMenu_020c49cc(MatrixMenu *menu, void *archiveA, u16 line, u16 *src, u16 *dst)
{
    MatrixProgress *progress = &data_0205fe0c->progress;
    BOOL pending;
    BgGraphicsData screenData;
    TextFrameParams frameParams;
    LevelTable levels;
    u16 blocksX;
    u16 blocksY;
    u16 row;
    u16 col;
    void *archive;
    ResourceContainer *layout;
    void *archiveB;
    u16 i;
    GridItem **items;
    s8 *itemFlags;
    GridItem **cells;
    GridItem *item;
    int count;
    int index;
    int width;
    int group;
    int step;
    int length;
    u32 maxLevel;
    PathTrail *trail;
    fx32 height;
    const IconOffset *offset;
    int iconIndex;
    GridItem *first;
    BOOL unlocked;
    GridItem *node;
    u32 cellIndex;
    GridCell cell;
    void *history;

    func_01ff8830(menu, 0, sizeof(MatrixMenu));
    data_ov075_020d18e0 = menu;
    REG_POWCNT = REG_POWCNT & ~0x8000;
    REG_DISP3DCNT = (u16)((REG_DISP3DCNT & ~0x3002) | 2);
    menu->archiveA = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov075_020d1824, 0xe, 0);
    menu->archiveB = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov075_020d1838, 0xe, 0);
    menu->rank = &progress->rank;
    menu->magicLevel = &progress->magicLevel;
    menu->cellLevel = &progress->cellLevel;
    menu->attackLevel = &progress->attackLevel;
    menu->abilityLevel = &progress->abilityLevel;

    pending = HasPendingUnlocks_020c49a8();
    if (pending) {
        menu->introState = 0;
        SetPrimaryElementEnabled_020bc054(FALSE);
        SetSecondaryElementEnabled_020bc084(FALSE);
    } else {
        menu->introState = -1;
    }

    SetBlendAlpha(1, 0x1e, 0x10, 0x10);
    SetVisiblePlane(0x1f);
    SetBG1Control(0, 1, 0, 5, 0);
    SetBG2Control(0, 0, 1, 7, 0);
    SetBG3Control(1, 0, 2, 1, 0);
    SetBG0Priority(2);
    SetBG1Priority(1);
    SetBG2Priority(0);
    SetBG3Priority(3);

    menu->bgArchive = func_0202c478(ARCHIVE_FILE_ID(menu->archiveA, 1), 0xf);
    GetBgDataFromArchive_0202b554(&menu->bg, menu->bgArchive, 0, 0, -1);
    archive = func_0202c478(ARCHIVE_FILE_ID(menu->archiveA, 0), 0xf);
    GetBgDataFromArchive_0202b554(&screenData, archive, 0, 0, 0);
    func_02007250(screenData.palette->pRawData, 0, screenData.palette->szByte);
    GX_LoadBG3Char_02007b70(screenData.character->pRawData, 0, screenData.character->szByte);
    menu->screen = screenData.screen;
    menu->screen = NNSi_FndAllocFromDefaultHeapEx_0202a19c(((screenData.screen->szByte >> 1) - 2) * 2 + 0x10, 0x10);
    func_01ff869c(screenData.screen, menu->screen, 0xc);
    menu->charBuffer = NNSi_FndAllocFromDefaultHeap_0202a178(menu->bg.character->szByte);
    func_01ff878c(screenData.character->pRawData, menu->charBuffer, menu->bg.character->szByte);

    src = (u16 *)screenData.screen;
    blocksX = screenData.screen->screenWidth >> 8;
    blocksY = screenData.screen->screenHeight >> 8;
    src += 6;
    for (row = 0; row < blocksY; row++) {
        for (col = 0; col < blocksX; col++) {
            dst = (u16 *)menu->screen->rawData + (col + row * blocksX * 32) * 32;
            for (line = 32; line != 0; line--) {
                *(ScreenRow *)dst = *(ScreenRow *)src;
                src += 32;
                dst += blocksX * 32;
            }
        }
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
    func_01ff8740(0, G2_GetBG1ScrPtr_02006e34(), 0x600);

    func_ov075_020cfbfc(menu->picker, 0, SetDescriptionText_020cccd8);
    frameParams = data_ov075_020d14f0;
    OpenTextFrame_020be5b8(0x160000, 0x20020, 2, menu->textFrame, &frameParams);
    menu->currentMessage = func_ov027_020ba2a8(menu->messageBank, 0x58);

    layout = func_ov039_020bc1bc();
    archiveA = menu->archiveA;
    archiveB = menu->archiveB;
    menu->originX = 0x78000;
    menu->originY = 0x60000;
    menu->layout = layout;
    menu->grid = AcquireMapLayout_020506dc(1, 0);
    func_01ff8ad8(menu->grid->pathLength, menu->groupCounts, sizeof(menu->groupCounts));
    menu->objectB = FindWidgetById_020b90a4(layout, 0x29);
    menu->objectA = FindWidgetById_020b90a4(layout, 0x27);
    SetLayoutElementVisible_020d0e4c(layout, 0, FALSE);
    func_ov027_020b97b8(layout, FindWidgetById_020b90a4(layout, 6), 1);
    func_ov027_020b97b8(layout, FindWidgetById_020b90a4(layout, 0x29), 1);

    func_0202c690(0);
    LoadTextureImageParams_020d0c18(&menu->hudSprites[0], ARCHIVE_FILE_ID(archiveA, 2));
    LoadTextureImageParams_020d0c18(&menu->hudSprites[1], ARCHIVE_FILE_ID(archiveA, 3));
    LoadTextureImageParams_020d0c18(&menu->hudSprites[2], ARCHIVE_FILE_ID(archiveA, 6));
    LoadTextureImageParams_020d0c18(&menu->hudSprites[3], ARCHIVE_FILE_ID(archiveA, 5));
    LoadTextureImageParams_020d0c18(&menu->hudSprites[4], ARCHIVE_FILE_ID(archiveA, 4));
    LoadTextureImageParams_020d0c18(&menu->hudSprites[5], ARCHIVE_FILE_ID(archiveA, 7));
    LoadTextureImageParams_020d0c18(&menu->hudSprites[6], ARCHIVE_FILE_ID(archiveA, 8));
    for (i = 0; i < 5; i++) {
        LoadTextureImageParams_020d0c18(&menu->cellSprites[i][8], ARCHIVE_FILE_ID(archiveA, i + 0x15));
    }
    for (i = 0; i < 4; i++) {
        LoadTextureImageParams_020d0c18(&menu->cellSprites[i][0], ARCHIVE_FILE_ID(archiveA, i + 0x1a));
        LoadTextureImageParams_020d0c18(&menu->cellSprites[i][1], ARCHIVE_FILE_ID(archiveA, i + 0x1f));
        LoadTextureImageParams_020d0c18(&menu->cellSprites[i][2], ARCHIVE_FILE_ID(archiveA, i + 0x24));
        LoadTextureImageParams_020d0c18(&menu->cellSprites[i][3], ARCHIVE_FILE_ID(archiveA, i + 0x29));
        LoadTextureImageParams_020d0c18(&menu->cellSprites[i][4], ARCHIVE_FILE_ID(archiveA, i + 0x2e));
        LoadTextureImageParams_020d0c18(&menu->cellSprites[i][5], ARCHIVE_FILE_ID(archiveA, i + 0x32));
        LoadTextureImageParams_020d0c18(&menu->cellSprites[i][6], ARCHIVE_FILE_ID(archiveA, i + 0x36));
        LoadTextureImageParams_020d0c18(&menu->cellSprites[i][7], ARCHIVE_FILE_ID(archiveA, i + 0x3a));
    }
    LoadTextureImageParams_020d0c18(&menu->cellSprites[4][0], ARCHIVE_FILE_ID(archiveA, 0x1e));
    LoadTextureImageParams_020d0c18(&menu->cellSprites[4][2], ARCHIVE_FILE_ID(archiveA, 0x23));
    LoadTextureImageParams_020d0c18(&menu->cellSprites[4][4], ARCHIVE_FILE_ID(archiveA, 0x28));
    LoadTextureImageParams_020d0c18(&menu->cellSprites[4][6], ARCHIVE_FILE_ID(archiveA, 0x2d));
    menu->cellSprites[4][1] = menu->cellSprites[4][0];
    menu->cellSprites[4][3] = menu->cellSprites[4][2];
    menu->cellSprites[4][5] = menu->cellSprites[4][4];
    menu->cellSprites[4][7] = menu->cellSprites[4][6];
    LoadTextureImageParams_020d0c18(&menu->tabSprites[0], ARCHIVE_FILE_ID(archiveA, 9));
    LoadTextureImageParams_020d0c18(&menu->tabSprites[1], ARCHIVE_FILE_ID(archiveA, 0xa));
    LoadTextureImageParams_020d0c18(&menu->tabSprites[2], ARCHIVE_FILE_ID(archiveA, 0xb));
    LoadTextureImageParams_020d0c18(&menu->tabSprites[3], ARCHIVE_FILE_ID(archiveA, 0xc));
    LoadTextureImageParams_020d0c18(&menu->tabSprites[4], ARCHIVE_FILE_ID(archiveA, 0x10));
    LoadTextureImageParams_020d0c18(&menu->frameSprites[0], ARCHIVE_FILE_ID(archiveB, 0));
    LoadTextureImageParams_020d0c18(&menu->frameSprites[1], ARCHIVE_FILE_ID(archiveB, 1));
    LoadTextureImageParams_020d0c18(&menu->frameSprites[2], ARCHIVE_FILE_ID(archiveB, 3));
    LoadTextureImageParams_020d0c18(&menu->frameSprites[3], ARCHIVE_FILE_ID(archiveB, 2));
    InitMenuModel_020d0b74(&menu->abilityModel, ARCHIVE_FILE_ID(archiveB, 4), 5);
    InitMenuModel_020d0b74(&menu->attackModel, ARCHIVE_FILE_ID(archiveB, 5), 0xc);
    LoadTextureImageParams_020d0c18(&menu->modeSprite, ARCHIVE_FILE_ID(archiveA, 0xe));
    InitMenuModel_020d0b74(&menu->magicModel, ARCHIVE_FILE_ID(archiveB, 6), 5);
    InitMenuModel_020d0b74(&menu->cellModel, ARCHIVE_FILE_ID(archiveB, 7), 0xc);
    InitMenuModel_020d0b74(&menu->bigModels[0], ARCHIVE_FILE_ID(archiveA, 0x3e), 0x14);
    InitMenuModel_020d0b74(&menu->bigModels[1], ARCHIVE_FILE_ID(archiveA, 0x41), 0x15);
    InitMenuModel_020d0b74(&menu->bigModels[2], ARCHIVE_FILE_ID(archiveA, 0x40), 0x15);
    InitMenuModel_020d0b74(&menu->bigModels[3], ARCHIVE_FILE_ID(archiveA, 0x3f), 0x15);
    InitMenuModel_020d0b74(&menu->bigModels[4], ARCHIVE_FILE_ID(archiveA, 0x42), 0x15);
    LoadTextureImageParams_020d0c18(&menu->markerSprites[0], ARCHIVE_FILE_ID(archiveA, 0x11));
    LoadTextureImageParams_020d0c18(&menu->markerSprites[1], ARCHIVE_FILE_ID(archiveA, 0x14));
    LoadTextureImageParams_020d0c18(&menu->markerSprites[2], ARCHIVE_FILE_ID(archiveA, 0x13));
    LoadTextureImageParams_020d0c18(&menu->markerSprites[3], ARCHIVE_FILE_ID(archiveA, 0x12));
    LoadTextureImageParams_020d0c18(&menu->markerSprites[4], ARCHIVE_FILE_ID(archiveA, 0xf));
    LoadTextureImageParams_020d0c18(&menu->iconSprites[0], ARCHIVE_FILE_ID(archiveA, 0x43));
    LoadTextureImageParams_020d0c18(&menu->iconSprites[1], ARCHIVE_FILE_ID(archiveA, 0x44));
    LoadTextureImageParams_020d0c18(&menu->iconSprites[2], ARCHIVE_FILE_ID(archiveA, 0x45));
    LoadTextureImageParams_020d0c18(&menu->iconSprites[3], ARCHIVE_FILE_ID(archiveA, 0x46));
    LoadTextureImageParams_020d0c18(&menu->iconSprites[4], ARCHIVE_FILE_ID(archiveA, 0x47));
    LoadTextureImageParams_020d0c18(&menu->iconSprites[5], ARCHIVE_FILE_ID(archiveA, 0x48));
    LoadTextureImageParams_020d0c18(&menu->iconSprites[6], ARCHIVE_FILE_ID(archiveA, 0x49));
    LoadTextureImageParams_020d0c18(&menu->iconSprites[7], ARCHIVE_FILE_ID(archiveA, 0x4a));
    func_0202c690(1);

    menu->effect = menu->effectWork;
    menu->abilityModel.scaleX += 0x20;
    menu->attackModel.scaleX -= 0x20;
    func_01ffb2f8(&menu->abilityModel, 0, *menu->abilityLevel << 12);
    func_01ffb2f8(&menu->attackModel, 3, *menu->attackLevel << 12);
    func_01ffb2f8(&menu->magicModel, 0, *menu->magicLevel << 12);
    levels = data_ov075_020d14a0;
    cell = GetSlotCellOffset_020c493c(*menu->cellLevel);
    menu->cellOffset = cell;
    menu->cellTarget = cell;
    height = levels.levels[*menu->cellLevel & 7] << 12;
    menu->cellHeight = height;
    func_01ffb2f8(&menu->cellModel, 3, height);
    func_01ffb2f8(&menu->abilityModel, 2, IsMenuModeUnlocked_020c4324(5) << 12);
    func_01ffb2f8(&menu->attackModel, 2, IsMenuModeUnlocked_020c4324(4) << 12);
    func_01ffb2f8(&menu->magicModel, 2, IsMenuModeUnlocked_020c4324(2) << 12);
    func_01ffb2f8(&menu->cellModel, 2, IsMenuModeUnlocked_020c4324(3) << 12);

    itemFlags = data_0205fe0c->itemFlags;
    items = menu->grid->items;
    count = menu->grid->header->itemCount;
    history = menu->history;
    maxLevel = CountUnlockedTiers_020c4988();
    if (maxLevel < data_0205fe0c->unlockCount) {
        maxLevel = data_0205fe0c->unlockCount;
    }
    for (; count != 0; count--, items++) {
        item = *items;
        if (item->type <= 2) {
            if (*itemFlags >= 0) {
                PropagateMatrixNodeVisit_020c5778(menu, item, 4, 1, 0);
            }
            if (item->type == 1) {
                GridItem **slot = menu->groupSlots[item->groupBit];

                while (*slot != NULL) {
                    slot++;
                }
                *slot = item;
            }
            itemFlags++;
        }
    }

    cells = menu->grid->cells;
    for (cellIndex = 0; cellIndex < 0x6c0; cellIndex++, cells++) {
        node = *cells;
        if (node != NULL && node->type != 0 && menu->grid->unlockLevel[node->id] <= maxLevel) {
            DrawMatrixCellGlyph_020c7fa8(history, menu->grid, node, cellIndex);
            if (node->slotId >= 0 && node->type == 1) {
                menu->groupCounts[node->groupBit]--;
            }
        }
    }

    func_01ff86fc(-1, menu->trails, sizeof(menu->trails));
    width = menu->grid->header->width;
    for (group = 0; group < 12; group++) {
        trail = &menu->trails[group];
        cells = menu->grid->pathCells[group];
        length = menu->grid->pathLength[group];
        for (step = 0; step < length; step++) {
            trail->points[step].x = **(u16 **)cells % width;
            trail->points[step].y = **(u16 **)cells / width;
            cells++;
        }
        trail->step = 0;
        trail->frame = 0;
        trail->lastStep = length * 8 - 1;
        trail->done = 0;
    }
    menu->trailIndex = -1;

    InvokeForChannelOrBoth_0200110c(1, data_ov075_020d184c, func_ov075_020c8920, 0);
    menu->touch = func_ov039_020bca00();
    SetupAllSelectionRecords_0204f85c();
    menu->needsRedraw = 2;

    if (data_0205fe0c->lastItemId == 0xffff) {
        menu->selectedItem = menu->grid->cells[menu->grid->unlockOrder[0]];
        if (!IsGlobalPackedBitSet_02027304(0xf5d)) {
            menu->selectedItem = menu->grid->cells[menu->selectedItem->parentIndex];
        }
    } else {
        item = menu->grid->cells[data_0205fe0c->lastItemId];
        if (item->linkIndex >= 0 && item < menu->grid->links[0]) {
            unlocked = GetPackedBitMask_0202d4a0((u8 *)data_0205fe0c + 0x2c5c, item->linkIndex) != 0;
            if (!unlocked) {
                item = menu->grid->links[item->linkIndex];
            }
        }
        menu->selectedItem = item;
    }

    menu->cursor.x = *(u16 *)menu->selectedItem % menu->grid->header->width;
    menu->cursor.y = *(u16 *)menu->selectedItem / menu->grid->header->width;
    iconIndex = menu->selectedItem->type;
    if (iconIndex < 3 || iconIndex >= 14) {
        iconIndex = 0;
    } else {
        iconIndex -= 2;
    }
    offset = &data_ov075_020d1454[iconIndex];
    menu->scrollX = (menu->cursor.x << 16) + (offset->x << 11) - (offset->offsetX << 12);
    menu->scrollY = (menu->cursor.y << 16) + (offset->y << 11) - (offset->offsetY << 12) - 0x8000;

    first = menu->grid->cells[menu->grid->unlockOrder[0]];
    if (pending) {
        count = CountUnlockedTiers_020c4988();
    } else {
        count = data_0205fe0c->unlockCount;
    }
    first->placed = 0;
    for (index = 0; index <= count; index++) {
        PropagateMatrixNodeVisit_020c5778(menu, menu->grid->cells[menu->grid->unlockOrder[index]], 4, 1, 0);
    }
    menu->ready = TRUE;
    return TRUE;
}
