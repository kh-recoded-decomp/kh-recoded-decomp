#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ResultsParams {
    int money;
    int basePoints;
    u8 pad_08[4];
    u16 bonusCount;
    u16 multiplierTenths;
    u8 pad_10[0x14];
    u8 currentChapter;
    u8 finalChapter;
    s8 stageKind;
    u8 pad_27[0x51];
    int shopMode;
    int needsSave;
    u8 pad_80[0xc];
    int hasBonusItem;
} ResultsParams;

typedef struct ResultsText {
    u8 messages[0x18];
    u8 font[0xc];
    u8 text[0x50];
} ResultsText;

typedef struct ResultsWork {
    u8 pad_0000[0x10];
    u8 tagTracker[0x4c];
    u8 objects[0x649c];
    int isActive;
    u8 pad_64fc[4];
    u8 iconLayer[0x63c];
    ResultsText ui;
    int needsRedraw;
    u8 pad_6bb4[8];
    int rankValues[3];
    u32 mode;
    u8 pad_6bcc[4];
    int hideBackPrompt;
    int pendingJingle;
    int messageId;
    int nextScene;
    int shownMoney;
    int targetMoney;
    int moneyStep;
    int shownPoints;
    int targetPoints;
    int pointsStep;
    int frame;
    int blinkTimer;
    u8 pad_6c00[4];
    u8 counters[7][0x28];
    u8 pad_6d1c[0x28];
    int badgeEntry;
    int rowEntries[6];
    u16 *ownedFlags;
    int itemCount;
    int itemBase;
    u8 pad_6d6c[8];
    int selectedItem;
    int cursorRow;
    int scrollTop;
    int scrollBarSize;
    int rankIndex;
    int dialogOpen;
    u8 pad_6d8c[8];
    int bonusJinglePlayed;
} ResultsWork;

typedef struct ResultsScreen {
    ResultsParams *params;
    ResultsWork *work;
} ResultsScreen;

typedef struct ShopEntry {
    u8 pad_00[2];
    u8 iconPalette;
    u8 iconFrame;
    int price;
    s8 category;
    u8 pad_09[3];
} ShopEntry;

typedef struct ItemInfo {
    u8 pad_00[0x10];
    int iconId;
    u8 pad_14[0x2c];
    const u16 *name;
    const u16 *description;
} ItemInfo;

typedef struct ScreenPoint {
    fx32 x;
    fx32 y;
} ScreenPoint;

typedef struct G3dGlobalState {
    u32 unk_00;
    u32 unk_04;
    MtxFx44 projectionMtx;
    u32 unk_48;
    MtxFx43 cameraMtx;
    u8 pad_7C[0x58];
    u32 flags;
    u8 pad_D8[0x140];
    VecFx32 camPos;
    VecFx32 camUp;
    VecFx32 camTarget;
} G3dGlobalState;

extern ResultsScreen g_resultsScreen_020c0f80;
extern ShopEntry data_ov034_020bed4c[];
extern const u16 data_ov034_020c0f00[];
extern const u16 data_ov034_020c0f1c[];
extern const char data_ov034_020c0f24[];
extern u16 data_02060500;
extern G3dGlobalState g_g3dGlobal_0205a924;

extern void func_ov024_020b72dc(ResultsParams *params);
extern void func_ov034_020be258(ResultsParams *params);
extern void func_ov024_020b72e4(ResultsParams *params, int flag);
extern void func_ov001_020648c8(u32 value);
extern void func_ov034_020bce50(void);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, void *record);
extern const u16 *func_ov027_020ba2a8(void *messages, int index);
extern const u16 *func_ov027_020ba2e0(void *messages, int index, u16 *buffer, int size, ...);
extern void func_02001768(void *text, int x, int y, int color, int unk4, int unk5, const u16 *str, int flags);
extern void Text_UploadTileBuffer_02001520(void *text);
extern void func_0200160c(void *text, int x, int y, int color, int flags, const u16 *str, void *font, int maxWidth);
extern void DrawTextAnchored_020015a0(void *text, int x, int y, int color, int flags, const u16 *str);
extern void CallVirtualHandlerSlot1_02001574(void *text, int arg);
extern void *func_ov027_020b90a4(void *objects, int id);
extern void func_ov027_020b9580(void *objects, void *object, int visible);
extern void func_ov027_020b96e4(void *objects, void *object);
extern void func_ov027_020b91c8(void *objects, void *object, ScreenPoint *pos, int mode);
extern void func_ov027_020b9360(void *objects, void *object, ScreenPoint *pos, int mode);
extern void *func_ov027_020b91a8(void *objects, void *object);
extern void func_ov027_020b91b0(void *objects, void *dst, void *src);
extern void func_ov027_020b95e4(void *objects, void *object);
extern void func_ov027_020b96a0(void *objects, void *object, int mode);
extern void func_ov034_020bcf30(void *objects, int id, int unk2, int value, int digits, void *counter);
extern int func_0202b788(void);
extern void PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_ov034_020bb234(int slot, int value);
extern void SetEntryRotation_0204f308(void *table, int entryIndex, int angle);
extern void SlotTable_SetEntryPair_0204f35c(void *table, int entryIndex, int scaleX, int scaleY);
extern void func_0204f378(void *table, int entryIndex, int value);
extern void MTX_OrthoW_02005f10(fx32 top, fx32 bottom, fx32 left, fx32 right, fx32 near, fx32 far, fx32 scaleW, MtxFx44 *mtx);
extern void func_01ff9b70(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target, MtxFx43 *mtx);
extern ItemInfo *func_ov034_020be418(int itemIndex);
extern int func_ov034_020be4f8(int itemIndex);
extern int func_ov034_020bdb70(int itemIndex);
extern void func_ov034_020bd010(void *text, int x, int y, int color, int flags, ItemInfo *info, int palette, int frame);
extern void OS_SNPrintf_0202e080(char *buffer, u32 size, const char *format, ...);
extern void func_ov034_020be718(void *layer, u32 attr0, u32 attr1, int attr2);

#define PARAMS (g_resultsScreen_020c0f80.params)
#define WORK (g_resultsScreen_020c0f80.work)
#define MESSAGE(id) func_ov027_020ba2a8(WORK->ui.messages, id)
#define OBJECT(id) func_ov027_020b90a4(WORK->objects, id)
#define SHOW_OBJECT(id) func_ov027_020b9580(WORK->objects, OBJECT(id), 1)

static inline void SetOrthoProjection(fx32 top, fx32 bottom, fx32 left, fx32 right, fx32 near, fx32 far, fx32 scaleW)
{
    MTX_OrthoW_02005f10(top, bottom, left, right, near, far, scaleW, &g_g3dGlobal_0205a924.projectionMtx);
    g_g3dGlobal_0205a924.flags &= ~0x50;
}

static inline void SetCameraLookAt(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target)
{
    g_g3dGlobal_0205a924.camPos = *camPos;
    g_g3dGlobal_0205a924.camUp = *camUp;
    g_g3dGlobal_0205a924.camTarget = *target;
    func_01ff9b70(camPos, camUp, target, &g_g3dGlobal_0205a924.cameraMtx);
    g_g3dGlobal_0205a924.flags &= ~0xe8;
}

static inline void DrawRowIcon(s16 iconId, s16 x, s16 y)
{
    func_ov034_020be718(WORK->iconLayer, ((u16)iconId << 16) | 0x7fff, ((u16)x << 16) | (u16)y, 0x3fe);
}

void RefreshResultsScreen_020bb578(void)
{
    int rowCount;
    ItemInfo *info;
    char priceText[0x14];
    ShopEntry *entry;
    s16 iconId;
    VecFx32 camUp;
    s16 titleBuffer[0x40];
    int row;

    if (PARAMS->needsSave) {
        func_ov024_020b72dc(PARAMS);
        func_ov034_020be258(PARAMS);
        func_ov024_020b72e4(PARAMS, 0);
        PARAMS->needsSave = 0;
    }
    if (WORK->isActive == 0) {
        return;
    }
    if (WORK->nextScene != -1 && WORK->targetMoney == WORK->shownMoney && WORK->targetPoints == WORK->shownPoints) {
        func_ov001_020648c8(WORK->nextScene);
        WORK->needsRedraw = 0;
    }
    if (WORK->frame < 100 && WORK->frame >= 0) {
        WORK->frame++;
    }

    if (WORK->messageId > 0) {
        if (WORK->frame == 1 || WORK->frame < 0) {
            func_ov034_020bce50();
            TagTracker_InvokeCallback_020b8210(WORK->tagTracker, FindActiveRecordById_020b8184(WORK->tagTracker, 0));
            TagTracker_InvokeCallback_020b8210(WORK->tagTracker, FindActiveRecordById_020b8184(WORK->tagTracker, 5));
            func_02001768(WORK->ui.text, 0x70, 0x38, 0xf2, 0xf6, 0xfa, MESSAGE(WORK->messageId + 0x35), 0);
            Text_UploadTileBuffer_02001520(WORK->ui.text);
            WORK->needsRedraw = 1;
            SHOW_OBJECT(0xe4);
        }
    } else if (WORK->mode <= 1) {
        if (1 == WORK->frame || WORK->frame < 0) {
            void *rankObject;
            func_ov034_020bce50();
            int count;
            TagTracker_InvokeCallback_020b8210(WORK->tagTracker, FindActiveRecordById_020b8184(WORK->tagTracker, 0));
            TagTracker_InvokeCallback_020b8210(WORK->tagTracker, FindActiveRecordById_020b8184(WORK->tagTracker, 2));
            if (PARAMS->stageKind == 0x16 && PARAMS->bonusCount == 1) {
                func_0200160c(WORK->ui.text, 0x70, 0x3c, 0xf2, 0x10, MESSAGE(0x3e), WORK->ui.font, 0xd8);
            } else if (PARAMS->stageKind == 0x18 && PARAMS->bonusCount == 1) {
                func_0200160c(WORK->ui.text, 0x70, 0x3c, 0xf2, 0x10, MESSAGE(0x3f), WORK->ui.font, 0xd8);
            } else if (PARAMS->stageKind == 0x19 && PARAMS->bonusCount == 1) {
                func_0200160c(WORK->ui.text, 0x70, 0x3c, 0xf2, 0x10, MESSAGE(0x40), WORK->ui.font, 0xd8);
            } else if (PARAMS->stageKind == 0x1d && PARAMS->bonusCount == 1) {
                func_0200160c(WORK->ui.text, 0x70, 0x3c, 0xf2, 0x10, MESSAGE(0x41), WORK->ui.font, 0xd8);
            } else if (0x1e == PARAMS->stageKind && PARAMS->bonusCount == 1) {
                func_0200160c(WORK->ui.text, 0x70, 0x3c, 0xf2, 0x10, MESSAGE(0x42), WORK->ui.font, 0xd8);
            } else {
                count = PARAMS->bonusCount;
                if (count) {
                    if ((u8)(s8)(PARAMS->stageKind - 3) <= 4 && func_0202b788() != 0) {
                        count--;
                    }
                    func_0200160c(WORK->ui.text, 0x70, 0x3c, 0xf2, 0x10, func_ov027_020ba2e0(WORK->ui.messages, 3 + PARAMS->stageKind, titleBuffer, 0x40, count), WORK->ui.font, 0xd8);
                } else {
                    func_0200160c(WORK->ui.text, 0x70, 0x3c, 0xf2, 0x10, MESSAGE(3 + PARAMS->stageKind), WORK->ui.font, 0xd8);
                }
            }
            if (WORK->mode == 0) {
                rankObject = OBJECT(0x12 + WORK->rankIndex);
            } else {
                rankObject = OBJECT(0x19);
            }
            func_ov027_020b96e4(WORK->objects, rankObject);
            SHOW_OBJECT(10);
            SHOW_OBJECT(0);
            func_ov034_020bcf30(WORK->objects, 1, 1, WORK->shownMoney, 0xd, WORK->counters[0]);
            SHOW_OBJECT(2);
            func_0200160c(WORK->ui.text, 0xdc, 2, 0xfa, 0x20, MESSAGE(0), WORK->ui.font, 0x50);
            SHOW_OBJECT(0xb);
            SHOW_OBJECT(0xd);
            SHOW_OBJECT(0xe);
            func_ov034_020bcf30(WORK->objects, 0x11, 1, PARAMS->multiplierTenths / 10, 0xd, WORK->counters[3]);
            SHOW_OBJECT(0x10);
            func_ov034_020bcf30(WORK->objects, 0xf, 1, PARAMS->multiplierTenths % 10, 0xd, WORK->counters[2]);
            SHOW_OBJECT(0x12);
            SHOW_OBJECT(0x13);
            SHOW_OBJECT(0x14);
            SHOW_OBJECT(0x1b);
            func_ov034_020bcf30(WORK->objects, 0x1a, 1, WORK->rankValues[0], 0xd, WORK->counters[4]);
            SHOW_OBJECT(0x1d);
            func_ov034_020bcf30(WORK->objects, 0x1c, 1, WORK->rankValues[1], 0xd, WORK->counters[5]);
            SHOW_OBJECT(0x1f);
            func_ov034_020bcf30(WORK->objects, 0x1e, 1, WORK->rankValues[2], 0xd, WORK->counters[6]);
            SHOW_OBJECT(0x15);
            SHOW_OBJECT(0x16);
            SHOW_OBJECT(0x17);
            func_ov034_020bcf30(WORK->objects, 0x18, 1, WORK->rankValues[WORK->rankIndex] * PARAMS->money / 100, 0xd, WORK->counters[1]);
            SHOW_OBJECT(0x19);
            if (PARAMS->hasBonusItem) {
                SHOW_OBJECT(0x20);
                if (WORK->bonusJinglePlayed == 0) {
                    PlaySoundEffect_0204d924(0x19b, 0);
                    WORK->bonusJinglePlayed = 1;
                }
            }
            Text_UploadTileBuffer_02001520(WORK->ui.text);
            WORK->needsRedraw = 1;
        }
        if (PARAMS->hasBonusItem) {
            ScreenPoint bonusPos;
            void *bonus = OBJECT(0x20);
            fx32 startX = ((fx32 *)bonus)[9];

            bonusPos.x = startX + WORK->blinkTimer * ((((fx32 *)bonus)[11] - startX) / 120);
            bonusPos.y = 0x64000;
            func_ov027_020b91c8(WORK->objects, bonus, &bonusPos, 0);
            WORK->blinkTimer = (WORK->blinkTimer + 1) % 120;
            func_ov027_020b9580(WORK->objects, OBJECT(0x20), WORK->blinkTimer % 30 < 15);
            func_ov034_020bb234(2, 0x7f);
        }
        func_ov034_020bb234(1, 0x6c);
        func_ov034_020bcf30(WORK->objects, 1, 1, WORK->shownMoney, 0xd, WORK->counters[0]);
        func_ov034_020bcf30(WORK->objects, 0x18, 1, PARAMS->money * WORK->rankValues[WORK->rankIndex] / 100, 0xd, WORK->counters[1]);
    } else if (2 == WORK->mode) {
        if (WORK->frame > 0 && WORK->frame < 100 && (data_02060500 & 2)) {
            WORK->frame = -1;
        }
        if (WORK->frame == 1 || WORK->frame < 0) {
            func_ov034_020bce50();
            TagTracker_InvokeCallback_020b8210(WORK->tagTracker, FindActiveRecordById_020b8184(WORK->tagTracker, 0));
        }
        if (WORK->frame == 2 || WORK->frame < 0) {
            WORK->needsRedraw = 1;
        }
        if (WORK->frame == 30 || WORK->frame < 0) {
            TagTracker_InvokeCallback_020b8210(WORK->tagTracker, FindActiveRecordById_020b8184(WORK->tagTracker, 3));
            SHOW_OBJECT(0);
            func_ov034_020bcf30(WORK->objects, 1, 1, WORK->shownMoney, 0xd, WORK->counters[0]);
        }
        if (40 == WORK->frame || WORK->frame < 0) {
            SHOW_OBJECT(0x68);
            SHOW_OBJECT(0x69);
            func_ov034_020bcf30(WORK->objects, 0x6a, 1, PARAMS->basePoints, 0xd, WORK->counters[1]);
        }
        if (50 == WORK->frame || WORK->frame < 0) {
            SHOW_OBJECT(0x6b);
            SHOW_OBJECT(0x6c);
            func_ov034_020bcf30(WORK->objects, 0x6f, 1, PARAMS->multiplierTenths / 10, 0xd, WORK->counters[3]);
            SHOW_OBJECT(0x6e);
            func_ov034_020bcf30(WORK->objects, 0x6d, 1, PARAMS->multiplierTenths % 10, 0xd, WORK->counters[2]);
        }
        if (60 == WORK->frame || WORK->frame < 0) {
            TagTracker_InvokeCallback_020b8210(WORK->tagTracker, FindActiveRecordById_020b8184(WORK->tagTracker, 4));
            SHOW_OBJECT(0x71);
            SHOW_OBJECT(0x72);
            SHOW_OBJECT(0xe6);
            func_ov034_020bcf30(WORK->objects, 0x73, 1, WORK->shownPoints, 0xd, WORK->counters[4]);
        }
        if (WORK->frame == 70 || WORK->frame < 0) {
            if (PARAMS->shopMode) {
                SHOW_OBJECT(0x65);
                SHOW_OBJECT(0x77);
                if (WORK->pendingJingle) {
                    PlaySoundEffect_0204d924(0, 0x3f);
                    WORK->pendingJingle = 0;
                }
            } else {
                SHOW_OBJECT(0x66);
                SHOW_OBJECT(0x78);
                if (WORK->pendingJingle) {
                    PlaySoundEffect_0204d924(0, 0x40);
                    WORK->pendingJingle = 0;
                }
            }
        }
        if (WORK->frame == 70 && PARAMS->shopMode) {
            WORK->targetPoints = PARAMS->basePoints * PARAMS->multiplierTenths / 10;
            WORK->pointsStep = (WORK->targetPoints - WORK->shownPoints) / 10;
            WORK->targetMoney = PARAMS->money;
            WORK->moneyStep = (WORK->targetMoney - WORK->shownMoney) / 10;
        }
        if (PARAMS->shopMode) {
            if (WORK->frame >= 70 && WORK->frame <= 80) {
                func_ov034_020bcf30(WORK->objects, 1, 1, WORK->shownMoney, 0xd, WORK->counters[0]);
                func_ov034_020bcf30(WORK->objects, 0x73, 1, WORK->shownPoints, 0xd, WORK->counters[4]);
            }
        } else if (WORK->frame >= 70 && WORK->frame <= 80) {
            SetEntryRotation_0204f308(WORK->objects, WORK->badgeEntry, (u16)((80 - WORK->frame) * 0x2000));
            SlotTable_SetEntryPair_0204f35c(WORK->objects, WORK->badgeEntry, FX32_ONE + (80 - WORK->frame) * 0x200, FX32_ONE + (80 - WORK->frame) * 0x200);
            func_0204f378(WORK->objects, WORK->badgeEntry, 1);
        }
        if (WORK->frame == 90 || WORK->frame < 0) {
            ScreenPoint rankPos;

            if (PARAMS->currentChapter == PARAMS->finalChapter) {
                func_ov027_020b9360(WORK->objects, OBJECT(0x75), &rankPos, 0);
                func_ov027_020b96e4(WORK->objects, OBJECT(0x75));
                WORK->rankIndex = 1;
            } else {
                ResultsWork *work = *(ResultsWork *volatile *)&WORK;

                func_ov027_020b9360(WORK->objects, func_ov027_020b90a4(work->objects, 0x74 + work->rankIndex), &rankPos, 0);
                func_ov027_020b96e4(WORK->objects, OBJECT(0x74 + WORK->rankIndex));
                SHOW_OBJECT(0x74);
                func_0200160c(WORK->ui.text, 0x70, 0x9a, 0xf2, 0x10, MESSAGE(1), WORK->ui.font, 0x98);
            }
            func_ov027_020b91c8(WORK->objects, OBJECT(100), &rankPos, 0);
            SHOW_OBJECT(100);
            SHOW_OBJECT(0x75);
            func_0200160c(WORK->ui.text, 0x70, 0xaa, 0xf2, 0x10, MESSAGE(2), WORK->ui.font, 0x98);
            Text_UploadTileBuffer_02001520(WORK->ui.text);
            SHOW_OBJECT(2);
            func_0200160c(WORK->ui.text, 0xdc, 2, 0xfa, 0x20, MESSAGE(0), WORK->ui.font, 0x50);
            if (PARAMS->shopMode) {
                WORK->shownMoney = WORK->targetMoney = PARAMS->money;
                WORK->shownPoints = WORK->targetPoints = PARAMS->basePoints * PARAMS->multiplierTenths / 10;
                WORK->moneyStep = WORK->pointsStep = 0;
                func_ov034_020bcf30(WORK->objects, 1, 1, WORK->shownMoney, 0xd, WORK->counters[0]);
                func_ov034_020bcf30(WORK->objects, 0x73, 1, WORK->shownPoints, 0xd, WORK->counters[4]);
            } else {
                SetEntryRotation_0204f308(WORK->objects, WORK->badgeEntry, 0);
                SlotTable_SetEntryPair_0204f35c(WORK->objects, WORK->badgeEntry, FX32_ONE, FX32_ONE);
                func_0204f378(WORK->objects, WORK->badgeEntry, 1);
            }
        }
    } else if (WORK->mode == 3) {
        void *thumb;

        rowCount = WORK->itemCount <= 6 ? WORK->itemCount : 6;
        if (1 == WORK->frame) {
            func_ov034_020bce50();
            TagTracker_InvokeCallback_020b8210(WORK->tagTracker, FindActiveRecordById_020b8184(WORK->tagTracker, 1));
            func_ov027_020b96e4(WORK->objects, OBJECT(0xd5 + WORK->cursorRow));
            SHOW_OBJECT(200);
            SHOW_OBJECT(0xc9);
            SHOW_OBJECT(0);
            if (WORK->hideBackPrompt == 0) {
                SHOW_OBJECT(2);
            }
            if (WORK->itemCount > 6) {
                s32 scale;

                scale = 65 / WORK->itemCount;
                WORK->scrollBarSize = 9 <= (2 >= scale ? 2 : scale) ? 9 : (2 >= scale ? 2 : scale);
                SHOW_OBJECT(0xca);
                SHOW_OBJECT(0xcb);
                for (row = 0; row < WORK->scrollBarSize - 2; row++) {
                    SHOW_OBJECT(row + 0xcc);
                }
                thumb = func_ov027_020b91a8(WORK->objects, OBJECT(row + 0xcc));
                func_ov027_020b91b0(WORK->objects, OBJECT(0xd4), thumb);
                SHOW_OBJECT(0xd4);
            } else {
                WORK->scrollBarSize = 0;
            }
            for (row = 0; row < rowCount; row++) {
                SHOW_OBJECT(row + 0xd5);
                func_ov027_020b95e4(WORK->objects, OBJECT(row + 0xd5));
                func_ov027_020b96a0(WORK->objects, OBJECT(row + 0xd5), 1);
            }
        } else if (WORK->frame == 2) {
            WORK->needsRedraw = 1;
        }
        if (WORK->scrollBarSize > 0) {
            ScreenPoint offset = {0, 0};

            offset.y = (WORK->scrollTop * ((10 - WORK->scrollBarSize) * 8) / (WORK->itemCount - 6)) << 12;
            for (row = 0; row < 10; ++row) {
                func_ov027_020b91c8(WORK->objects, OBJECT(row + 0xcb), &offset, 5);
            }
        }
        CallVirtualHandlerSlot1_02001574(WORK->ui.text, 0);
        s32 state;
        {
            SetOrthoProjection(0xc0000, 0, 0, 0x100000, 0, 0x400000, 0x200000);
            VecFx32 camTarget;
            VecFx32 camPos;
            camPos.y = 0;
            camPos.x = 0;
            camPos.z = 0x400000;
            camUp.z = 0;
            camUp.x = 0;
            camUp.y = FX32_ONE;
            camTarget.z = 0;
            camTarget.y = 0;
            camTarget.x = 0;

            SetCameraLookAt(&camPos, &camUp, &camTarget);
        }
        for (row = 0; row < rowCount; ++row) {
            entry = &data_ov034_020bed4c[WORK->scrollTop + (WORK->itemBase + row)];
            info = func_ov034_020be418(row + WORK->scrollTop);
            iconId = (s16)info->iconId;
            func_0204f378(WORK->objects, *(s32 *)&WORK->rowEntries[row], 0);
            if (func_ov034_020be4f8(row + WORK->scrollTop) != 0) {
                func_0200160c(WORK->ui.text, 0x1c, row * 16 + 0x33, 0xf2, 0, info->name, WORK->ui.font, 0x68);
                func_ov027_020b96a0(WORK->objects, OBJECT(0xd5 + row), 2);
                DrawTextAnchored_020015a0(WORK->ui.text, 0xaa, row * 16 + 0x33, 0xfa, 0x10, MESSAGE(0x29));
                if (row == WORK->cursorRow) {
                    func_0200160c(WORK->ui.text, 0x14, 0xa8, 0xf2, 0, info->description, WORK->ui.font, 0xc4);
                }
                iconId = 0x85 - (func_ov034_020be4f8(row + WORK->scrollTop) == 2 ? 2 : 3);
            } else if (1 == entry->category && WORK->scrollTop + row < 16 && (*WORK->ownedFlags & (1 << (WORK->scrollTop + row)))) {
                func_0200160c(WORK->ui.text, 0x1c, row * 16 + 0x33, 0xf4, 0, info->name, WORK->ui.font, 0x68);
                func_ov027_020b96a0(WORK->objects, OBJECT(0xd5 + row), 0);
                func_0204f378(WORK->objects, WORK->rowEntries[row], 1);
                if (row == WORK->cursorRow) {
                    func_0200160c(WORK->ui.text, 0x14, 0xa8, 0xf2, 0, info->description, WORK->ui.font, 0xc4);
                }
            } else if (func_ov034_020bdb70(row + WORK->scrollTop) == 0) {
                DrawTextAnchored_020015a0(WORK->ui.text, 0x1c, row * 16 + 0x33, 0xf4, 0, data_ov034_020c0f00);
                func_ov027_020b96a0(WORK->objects, OBJECT(row + 0xd5), 0);
                DrawTextAnchored_020015a0(WORK->ui.text, 0xb1, 16 * row + 0x33, 0xf4, 0x20, data_ov034_020c0f1c);
                if (row == WORK->cursorRow) {
                    DrawTextAnchored_020015a0(WORK->ui.text, 0x14, 0xa8, 0xf2, 0, data_ov034_020c0f00);
                }
                DrawTextAnchored_020015a0(WORK->ui.text, 0xb6, row * 16 + 0x33, 0xf8, 0, MESSAGE(0x39));
                iconId = 0x81;
            } else {
                OS_SNPrintf_0202e080(priceText, 10, data_ov034_020c0f24, entry->price);
                if (PARAMS->money >= entry->price) {
                    func_ov034_020bd010(WORK->ui.text, 0x1c, 16 * row + 0x33, 0xf2, 0, info, entry->iconPalette, entry->iconFrame);
                    state = 1 == entry->category ? 1 : 2;
                    func_ov027_020b96a0(WORK->objects, OBJECT(row + 0xd5), (u16)state);
                    func_0200160c(WORK->ui.text, 0xb1, row * 16 + 0x33, 0xf2, 0x20, (const u16 *)priceText, WORK->ui.font, 0x68);
                } else {
                    func_ov034_020bd010(WORK->ui.text, 0x1c, 16 * row + 0x33, 0xf4, 0, info, entry->iconPalette, entry->iconFrame);
                    func_ov027_020b96a0(WORK->objects, OBJECT(row + 0xd5), 0);
                    func_0200160c(WORK->ui.text, 0xb1, row * 16 + 0x33, 0xf4, 0x20, (const u16 *)priceText, WORK->ui.font, 0x68);
                }
                DrawTextAnchored_020015a0(WORK->ui.text, 0xb6, row * 16 + 0x33, 0xf8, 0, MESSAGE(0x39));
                if (row == WORK->cursorRow) {
                    func_0200160c(WORK->ui.text, 0x14, 0xa8, 0xf2, 0, info->description, WORK->ui.font, 0xc4);
                }
            }
            if (iconId >= 0) {
                DrawRowIcon(iconId, 0x18, row * 16 + 0x30);
            }
        }
        if (WORK->hideBackPrompt == 0) {
            func_0200160c(WORK->ui.text, 0xdc, 2, 0xfa, 0x20, MESSAGE(0x3d), WORK->ui.font, 0x50);
        }
        Text_UploadTileBuffer_02001520(WORK->ui.text);
        func_ov034_020bcf30(WORK->objects, 1, 1, WORK->shownMoney, 0xd, WORK->counters[0]);
        func_ov027_020b9580(WORK->objects, OBJECT(0xdb), WORK->scrollTop > 0);
        func_ov027_020b9580(WORK->objects, OBJECT(0xdc), WORK->itemCount - WORK->scrollTop > 6);
    } else if (WORK->mode == 4) {
        if (WORK->frame == 1) {
            ScreenPoint dialogPos;

            func_ov034_020bce50();
            TagTracker_InvokeCallback_020b8210(WORK->tagTracker, FindActiveRecordById_020b8184(WORK->tagTracker, 0));
            TagTracker_InvokeCallback_020b8210(WORK->tagTracker, FindActiveRecordById_020b8184(WORK->tagTracker, 5));
            SHOW_OBJECT(0xdf);
            SHOW_OBJECT(0xe0);
            SHOW_OBJECT(0xe1);
            SHOW_OBJECT(0xe2);
            SHOW_OBJECT(0);
            info = func_ov034_020be418(WORK->selectedItem);
            if (func_ov034_020be4f8(WORK->selectedItem) == 0) {
                entry = &data_ov034_020bed4c[WORK->itemBase + WORK->selectedItem];
                func_ov034_020bd010(WORK->ui.text, 0x70, 0x42, 0xf2, 0x10, info, entry->iconPalette, entry->iconFrame);
            } else {
                func_ov034_020bd010(WORK->ui.text, 0x70, 0x42, 0xf2, 0x10, info, 0, 0);
            }
            func_0200160c(WORK->ui.text, 0x46, 0x6a, 0xf2, 0x10, MESSAGE(0x23), WORK->ui.font, 0x38);
            func_0200160c(WORK->ui.text, 0x9d, 0x6a, 0xf2, 0x10, MESSAGE(0x24), WORK->ui.font, 0x38);
            Text_UploadTileBuffer_02001520(WORK->ui.text);
            WORK->dialogOpen = 1;
            func_ov027_020b96e4(WORK->objects, OBJECT(0xe1));
            func_ov027_020b9360(WORK->objects, OBJECT(0xe1), &dialogPos, 0);
            func_ov027_020b91c8(WORK->objects, OBJECT(0xe2), &dialogPos, 0);
            WORK->needsRedraw = 1;
        }
        func_ov034_020bcf30(WORK->objects, 1, 1, WORK->shownMoney, 0xd, WORK->counters[0]);
    } else if (WORK->mode == 5) {
        if (WORK->frame == 1) {
            func_ov034_020bce50();
            TagTracker_InvokeCallback_020b8210(WORK->tagTracker, FindActiveRecordById_020b8184(WORK->tagTracker, 0));
            ScreenPoint promptPos;
            TagTracker_InvokeCallback_020b8210(WORK->tagTracker, FindActiveRecordById_020b8184(WORK->tagTracker, 5));
            SHOW_OBJECT(0xe0);
            SHOW_OBJECT(0xe1);
            SHOW_OBJECT(0xe2);
            SHOW_OBJECT(0);
            func_ov034_020bcf30(WORK->objects, 1, 1, WORK->shownMoney, 0xd, WORK->counters[0]);
            func_0200160c(WORK->ui.text, 0x70, 0x42, 0xf2, 0x10, MESSAGE(0x3a), WORK->ui.font, 200);
            func_0200160c(WORK->ui.text, 0x46, 0x6a, 0xf2, 0x10, MESSAGE(0x3b), WORK->ui.font, 0x38);
            func_0200160c(WORK->ui.text, 0x9d, 0x6a, 0xf2, 0x10, MESSAGE(0x3c), WORK->ui.font, 0x38);
            Text_UploadTileBuffer_02001520(WORK->ui.text);
            WORK->dialogOpen = 1;
            func_ov027_020b96e4(WORK->objects, OBJECT(0xe1));
            func_ov027_020b9360(WORK->objects, OBJECT(0xe1), &promptPos, 0);
            func_ov027_020b91c8(WORK->objects, OBJECT(0xe2), &promptPos, 0);
            WORK->needsRedraw = 1;
        }
    }
    if (WORK->frame < 0) {
        WORK->frame = 100;
    }
}
