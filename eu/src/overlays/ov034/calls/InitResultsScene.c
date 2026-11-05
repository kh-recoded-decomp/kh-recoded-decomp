/* Defer MWCC emission until both real BSS pointer objects are known. */
#if defined(__MWERKS__)
#pragma defer_codegen on
#if !__option(defer_codegen)
#error Results scene requires deferred code generation for its paired globals
#endif
#endif
/* Preserve the separate bonus-stage and shop-cursor lifetimes with the EU compiler. */
#if defined(__MWERKS__)
#pragma opt_lifetimes off
#endif
/* EU results-scene initialization; see docs/RESULTS_SCENE.md. */
#include "nitro/types.h"
#include "src/overlays/ov001/SessionBuffers.h"

/* Legacy symbol binding: this reads the current task work pointer and allocates nothing. */
#define GetCurrentTaskWork GetRunningTaskWork

/* Session buffer records contain a pointer followed by their allocated byte size. */
#define GetSessionBufferSize SessionBuffer_GetSize
/* Legacy slot API returns a 32-bit ARM data address. */
#define GetSessionBufferAddress SessionBuffer_GetAddress

/* The arguments the results scene is started with. */
typedef struct ResultsArgs {
    u8 pad_00;
    s8 stage;
    s16 world;
    s16 area;
    u8 pad_06[2];
    s32 score;
    s32 section;
    u8 kind;
} ResultsArgs;

typedef struct ResultsParams {
    s32 earnedAmount;
    s32 bonusAmount;
    u8 pad_08[6];
    u16 bonusRate;
    u8 pad_10[0x12];
    u8 worldId;
    s8 clearRank;
    u8 unlockedRank;
    u8 maxRank;
    s8 missionGrade;
    u8 pad_27[0x51];
    s32 isBonusStage;
    u8 pad_7c[4];
    s32 shopVisited;
    u8 pad_84[0xc];
} ResultsParams;

/* One entry written by the matched LoadResultsIconCells helper. */
typedef struct IconCell {
    u16 width;
    u16 height;
    u32 texImageParam;
    u32 plttBase;
} IconCell;

/* Shared input-record layout: the initializer clears 0x1a bytes, not 0x20.
 * Keep the following fade controls outside this record. See ov034/ResultsScreen.h.
 */
typedef struct ResultsInputState {
    u16 repeatMask;
    u16 delayFrames;
    u16 intervalFrames;
    u16 repeatCounts[10];
} ResultsInputState;

/* The destination layout used by InitTileTableFrom (0x1c bytes). */
typedef struct TileTable {
    int *ids; /* The initializer allocates and copies count IDs. */
    int count;
    u16 width;
    u16 height;
    u16 rowLength; /* width * height, in u16 entries. */
    u8 pad_0e[2];
    u16 *rows; /* Allocated as count * rowLength entries. */
    u8 pad_14[4];
    u8 dirtyMask; /* Initialized to 0xff. */
    u8 pad_19[3];
} TileTable;

typedef struct ResultsWork {
    s16 stage;
    s16 world;
    s16 area;
    u16 flags;
    s32 score;
    s32 state; /* Index into the four internal screen-state handlers. */
    u8 pad_0010[0x64d8 - 0x10];
    TileTable tileTable;
    void *task;
    s32 fadeReady;
    s32 fadeActive;
    IconCell iconCells[0x85];
    u8 pad_6b3c[0x6b94 - 0x6b3c];
    ResultsInputState keyRepeat;
    u8 pad_6bae[2];
    s32 fadeMode;
    s32 syncSecondary; /* Mirror the main-screen brightness change on the sub screen. */
    s32 brightness;
    u8 pad_6bbc[0x6bc8 - 0x6bbc];
    s32 mode;
    s32 prevMode;
    s32 shopOpen;
    s32 promptEnabled;
    s32 popupTimer;
    s32 outcome;
    s32 shownBase;
    s32 shownTotal;
    u8 pad_6be8[0x6c04 - 0x6be8];
    u8 slotFlags[0x140];
    u8 pad_6d44[0x6d60 - 0x6d44];
    u16 *ownedFlags;
    u8 pad_6d64[0x6d74 - 0x6d64];
    s32 selected;
    s32 cursor;
    s32 scroll;
    s32 scrollTarget;
    u8 pad_6d84[0x6d8c - 0x6d84];
    s32 shopSection;
    s32 sessionKind;
    u8 pad_6d94[0x6d98 - 0x6d94];
} ResultsWork;

typedef struct SessionState {
    u8 pad_00[4];
    u16 defaultSeed;
    u16 mode : 3;
    u16 cleared : 1;
    u16 bonus : 1;
    u16 rest : 11;
    u8 progress;
    u8 pad_09[2];
    u8 rank;
    u32 seed;
} SessionState;

typedef struct SessionFlags {
    u8 pad_0000[0x214];
    u32 flagsLow : 4;
    u32 replay : 1;
    u32 flagsHigh : 27;
    u8 pad_0218[0x27fd - 0x218];
    u8 resultsSeen : 1;
    u8 pad_27fd_1 : 7;
} SessionFlags;

typedef struct SaveData {
    u8 pad_0000[0x2888];
    u16 ownedFlags[1];
} SaveData;

typedef struct StageInfo {
    s8 group;
    u8 pad_01[0x27];
} StageInfo;

typedef struct TileIds {
    int ids[4];
} TileIds;

typedef struct TileTableSource {
    int *ids;
    int count;
    u16 width;
    u16 height;
    int reserved_0c; /* Not read by InitTileTableFrom; the native caller zeroes it. */
} TileTableSource;

/* ROM layout contracts for the objects allocated or copied by this initializer. */
typedef char TileTableSizeCheck[sizeof(TileTable) == 0x1c ? 1 : -1];
typedef char ResultsWorkSizeCheck[sizeof(ResultsWork) == 0x6d98 ? 1 : -1];
typedef char ResultsInputStateSizeCheck[sizeof(ResultsInputState) == 0x1a ? 1 : -1];
typedef char ResultsTaskOffsetCheck[(u32)&((ResultsWork *)0)->task == 0x64f4 ? 1 : -1];
typedef char ResultsFadeReadyOffsetCheck[(u32)&((ResultsWork *)0)->fadeReady == 0x64f8 ? 1 : -1];
typedef char ResultsFadeActiveOffsetCheck[(u32)&((ResultsWork *)0)->fadeActive == 0x64fc ? 1 : -1];
typedef char ResultsKeyRepeatOffsetCheck[(u32)&((ResultsWork *)0)->keyRepeat == 0x6b94 ? 1 : -1];
typedef char ResultsFadeModeOffsetCheck[(u32)&((ResultsWork *)0)->fadeMode == 0x6bb0 ? 1 : -1];
typedef char ResultsSyncSecondaryOffsetCheck[(u32)&((ResultsWork *)0)->syncSecondary == 0x6bb4 ? 1 : -1];
typedef char ResultsBrightnessOffsetCheck[(u32)&((ResultsWork *)0)->brightness == 0x6bb8 ? 1 : -1];
typedef char ResultsParamsSizeCheck[sizeof(ResultsParams) == 0x90 ? 1 : -1];
typedef char IconCellSizeCheck[sizeof(IconCell) == 12 ? 1 : -1];
typedef char TileIdsSizeCheck[sizeof(TileIds) == 16 ? 1 : -1];
typedef char TileTableSourceSizeCheck[sizeof(TileTableSource) == 16 ? 1 : -1];

typedef int (*ResultsStateFn)(void);

/* The scene owns two adjacent pointer slots: params at +0 and work at +4.
 * Deferred MWCC emission gives them one address base while retaining separate
 * object identities. MWCC emits them in reverse declaration order.
 */
ResultsWork *data_ov034_020c0fa4;
ResultsParams *data_ov034_020c0fa0;
extern const TileIds data_ov034_020be8cc;
extern SessionState data_0206085c;
extern SessionFlags *data_ov001_020a0480;
extern StageInfo data_ov034_020bf990[];
extern u8 data_ov034_020bea78[][3];
extern SaveData *data_0205fe0c;
extern u8 OVERLAY_27_ID[];
extern u8 OVERLAY_24_ID[];

extern void *GetCurrentTaskWork(void);
extern void MI_CpuFill8(void *dst, u32 value, u32 size);
extern void MIi_CpuClear32(u32 value, void *dst, u32 size);
extern void SetupResultsDisplay(void);
extern void LoadOverlayAfterGeometryTransfer(int bank, int value);
extern void InitTileTableFrom(void *table, const TileTableSource *source);
extern int InitKeyRepeatState(s16 *record, s16 *limits);
extern void QueueSoundCommandForArc(u32 archive);
extern u32 GetSessionCounter(int index);
extern u32 NextSharedRandom16Scaled(u32 range);
extern u32 random_next_scaled(u32 range);
extern void SetupStageParams(ResultsParams *params, int worldId, int stage);
extern void BuildUniqueItemPriceList(u16 *items, int count);
extern void SetupResultsShopList(void);
extern void LoadResultsIconCells(IconCell *cells);
extern void SetResultsMode(u32 mode);
extern int SetSelectionIfChanged(int selection);
extern int QueueSoundKind4(int track, int fade);
extern int CloseResultsScreen(void);
extern int UpdateResultsScreen(void);

static inline void InitResultsTiles(ResultsWork *work, TileIds *tileIds, TileTableSource *source)
{
    *tileIds = data_ov034_020be8cc;
    source->count = 4;
    source->width = 0x20;
    source->height = 0x20;
    source->reserved_0c = 0;
    source->ids = tileIds->ids;
    InitTileTableFrom(&work->tileTable, source);
}

/* Prepare result state and stage-specific shop entries, then select the next scene step. */
ResultsStateFn InitResultsScene(ResultsArgs *args)
{
    TileIds tileIds;
    TileTableSource source;
    u16 items[22];
    ResultsParams *params;
    int stageIndex;
    int worldCount;
    int stageCount;
    int itemCount;
    int itemSlot;
    int itemIndex;

    /* Legacy symbol name: this returns the current task's work pointer. */
    data_ov034_020c0fa4 = GetCurrentTaskWork();
    MI_CpuFill8(data_ov034_020c0fa4, 0, sizeof(ResultsWork));
    MIi_CpuClear32(-1, data_ov034_020c0fa4->slotFlags, sizeof(data_ov034_020c0fa4->slotFlags));
    data_ov034_020c0fa4->stage = args->stage;
    data_ov034_020c0fa4->world = args->world;
    data_ov034_020c0fa4->area = args->area;
    data_ov034_020c0fa4->score = args->score;
    data_ov034_020c0fa4->shopSection = args->section;
    data_ov034_020c0fa4->sessionKind = args->kind;
    data_ov034_020c0fa4->prevMode = -1;
    data_ov034_020c0fa4->flags = 3;
    SetupResultsDisplay();
    LoadOverlayAfterGeometryTransfer(0, (int)OVERLAY_27_ID);
    LoadOverlayAfterGeometryTransfer(0, (int)OVERLAY_24_ID);
    InitResultsTiles(data_ov034_020c0fa4, &tileIds, &source);
    InitKeyRepeatState((s16 *)&data_ov034_020c0fa4->keyRepeat, NULL);
    QueueSoundCommandForArc(3 + 0x198);
    data_ov034_020c0fa4->state = 0;

    if (data_ov034_020c0fa0 == NULL) {
        if (GetSessionBufferSize(10) == 0) {
            data_ov034_020c0fa0 = AllocSessionBuffer(10, sizeof(ResultsParams));
            MI_CpuFill8(data_ov034_020c0fa0, 0, sizeof(ResultsParams));
            data_ov034_020c0fa4->mode = 0;
            if (args->kind == 1) {
                /* This encounter number is independent of the later shop-table cursor. */
                int bonusStage;
                data_ov034_020c0fa4->shopSection = 0x1a;
                data_ov034_020c0fa0->worldId = data_ov034_020c0fa4->shopSection;
                if (data_0206085c.progress % 10 == 0) {
                    bonusStage = data_0206085c.progress / 10 * 2;
                    data_0206085c.seed = NextSharedRandom16Scaled(0xffff) + random_next_scaled(-1);
                } else {
                    bonusStage = data_0206085c.progress / 10 * 2 + 1;
                    if (data_0206085c.mode == 0) {
                        data_0206085c.seed = data_0206085c.defaultSeed;
                    }
                }
                SetupStageParams(data_ov034_020c0fa0, data_ov034_020c0fa0->worldId, bonusStage);
                if (data_0206085c.mode == 0) {
                    /* The ROM stores bit 3, reloads the halfword, then clears bit 4.
                     * Preserve that two-step memory update when rebuilding EU.
                     */
                    data_0206085c.cleared = 0;
                    ((volatile SessionState *)&data_0206085c)->bonus = 0;
                }
            } else {
                data_ov034_020c0fa0->worldId = data_ov034_020c0fa4->shopSection;
                if (data_ov001_020a0480->replay) {
                    data_ov034_020c0fa0->earnedAmount = GetSessionCounter(1);
                } else {
                    data_0206085c.rank = 1;
                    data_0206085c.seed = NextSharedRandom16Scaled(0x10000 - 1) + random_next_scaled(-1);
                }
                data_ov034_020c0fa0->unlockedRank = data_0206085c.rank;
                SetupStageParams(data_ov034_020c0fa0, data_ov034_020c0fa0->worldId,
                                 data_ov034_020c0fa0->unlockedRank);
            }
            data_ov034_020c0fa4->shownBase = data_ov034_020c0fa0->earnedAmount;
            data_ov034_020c0fa4->shownTotal = data_ov034_020c0fa4->shownBase;

            worldCount = 0;
            stageIndex = 0;
            while (worldCount != data_ov034_020c0fa0->worldId) {
                if (data_ov034_020bf990[stageIndex].group == -1) {
                    worldCount++;
                }
                stageIndex++;
            }
            stageCount = data_ov034_020c0fa0->maxRank;
            if (args->kind == 1) {
                stageCount = 0x14;
            }
            const int firstStage = stageIndex;
            items[0] = 0x3f;
            items[1] = 0x3e;
            items[2] = 0x63;
            itemCount = 3;
            for (; stageIndex < firstStage + stageCount; stageIndex++) {
                for (itemSlot = 0; itemSlot < 3; itemSlot++) {
                    for (itemIndex = 0; itemIndex < itemCount; itemIndex++) {
                        if (items[itemIndex] == data_ov034_020bea78[data_ov034_020bf990[stageIndex].group][itemSlot]) {
                            break;
                        }
                    }
                    if (itemIndex == itemCount) {
                        items[itemCount++] = data_ov034_020bea78[data_ov034_020bf990[stageIndex].group][itemSlot];
                    }
                }
            }
            BuildUniqueItemPriceList(items, itemCount);
        } else {
            data_ov034_020c0fa0 = (ResultsParams *)GetSessionBufferAddress(10);
            data_ov034_020c0fa4->mode = 2;
            data_ov034_020c0fa0->earnedAmount = GetSessionCounter(1);
            data_ov034_020c0fa4->shownBase = data_ov034_020c0fa0->earnedAmount;
            data_ov034_020c0fa4->shownTotal = data_ov034_020c0fa4->shownBase;
            data_ov034_020c0fa4->shopSection = data_ov034_020c0fa0->worldId;
            params = data_ov034_020c0fa0;
            if (params->missionGrade >= 0) {
                if (params->clearRank >= 0 && params->missionGrade < 0xf && params->missionGrade != 0xb) {
                    params->isBonusStage = 1;
                }
                params = data_ov034_020c0fa0;
                if (params->isBonusStage) {
                    params->earnedAmount += params->bonusAmount * params->bonusRate / 10;
                    if (data_ov034_020c0fa0->earnedAmount > 9999999) {
                        data_ov034_020c0fa0->earnedAmount = 9999999;
                    }
                }
            }
        }
    }
    data_ov034_020c0fa4->selected = 0;
    data_ov034_020c0fa4->cursor = 0;
    data_ov034_020c0fa4->scroll = 0;
    data_ov034_020c0fa4->scrollTarget = 0;
    data_ov034_020c0fa4->outcome = -1;
    data_ov034_020c0fa4->fadeActive = 0;
    data_ov034_020c0fa4->ownedFlags = &data_0205fe0c->ownedFlags[data_ov034_020c0fa0->worldId];
    data_ov034_020c0fa4->shopOpen = 0;
    data_ov034_020c0fa4->syncSecondary = 1;
    data_ov034_020c0fa4->promptEnabled = 1;
    data_ov034_020c0fa4->popupTimer = 0;
    data_ov034_020c0fa0->shopVisited = 0;
    SetupResultsShopList();
    LoadResultsIconCells(data_ov034_020c0fa4->iconCells);
    if (args->kind == 1 && data_ov034_020c0fa4->mode == 2) {
        data_0206085c.bonus = 1;
    }
    if (args->kind == 1 && data_0206085c.progress % 10 != 0) {
        data_ov034_020c0fa4->syncSecondary = 0;
        if (data_0206085c.mode == 0) {
            if (data_ov034_020c0fa4->mode == 2) {
                if (data_ov034_020c0fa0->isBonusStage) {
                    data_0206085c.cleared = 1;
                }
                data_ov034_020c0fa4->outcome = 1;
            }
            return CloseResultsScreen;
        }
        SetResultsMode(3);
        if (data_0206085c.mode == 2) {
            data_ov034_020c0fa4->shopOpen = 1;
        }
        return UpdateResultsScreen;
    }
    if (data_ov034_020c0fa0->missionGrade < 0) {
        if (data_ov034_020c0fa4->mode == 2) {
            if (data_ov034_020c0fa0->unlockedRank == data_ov034_020c0fa0->maxRank) {
                SetResultsMode(3);
                data_ov034_020c0fa4->shopOpen = 1;
                return UpdateResultsScreen;
            }
            data_ov034_020c0fa0->unlockedRank++;
            data_0206085c.rank = data_ov034_020c0fa0->unlockedRank;
            data_0206085c.seed = NextSharedRandom16Scaled(0xffff) + random_next_scaled(0xffff - 0x10000);
            SetupStageParams(data_ov034_020c0fa0, data_ov034_020c0fa0->worldId,
                             data_ov034_020c0fa0->unlockedRank);
        }
        return CloseResultsScreen;
    }
    if (data_ov034_020c0fa4->mode == 0) {
        data_ov001_020a0480->resultsSeen = 1;
        SetSelectionIfChanged(0x16);
    } else if (data_ov034_020c0fa4->mode == 2) {
        QueueSoundKind4(0x16, 0x1e);
    }
    return UpdateResultsScreen;
}
