#include "nitro/types.h"

typedef struct {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct {
    s32 mode;
    s32 duration;
    s32 from;
    s32 to;
    u32 startTickLow;
    u32 startTickHigh;
    TweenFlags flags;
} Tween;

typedef struct {
    s32 status : 8;
    u32 statusHigh : 24;
    u8 pad_04[0xcc];
    u8 saveData[0x3760];
} SaveSlot;

typedef struct {
    u32 words[0x3760 / 4];
} SaveData;

typedef struct {
    u8 slotIndex;
    u8 pad_01;
    u8 needsRedraw;
    u8 cursorShown;
    s32 step : 8;
    u32 stepHigh : 24;
    u8 pad_08[2];
    u8 errorState;
    u8 pad_0B[5];
    BOOL cardRequestPending;
    u8 pad_14[4];
    BOOL busyHeld;
    u8 pad_1C[0x18];
    Tween fade;
    u8 pad_50[4];
    void *panel;
    u8 pad_58[0x14];
    void *cursorElement;
    u8 pad_70[8];
    SaveSlot slots[2];
    SaveData backup;
    u8 pad_A838[0xe8];
    BOOL unlockFlagA;
    BOOL unlockFlagB;
} SaveSelectScreen;

extern SaveData *data_0205fe0c;

extern int func_020271e8(int slotIndex);
extern int PollCardThreadState_020271f8(void);
extern int WriteCardSlotHeaders_02027278(int slotIndex);
extern void DecrementBusyCounterIfPositive_02025494(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void *func_ov027_020b90a4(void *panel, int elementId);
extern void func_ov027_020b9580(void *panel, void *element, BOOL visible);
extern void func_ov080_020c4b84(SaveSelectScreen *screen, SaveSlot *slot);
extern void func_ov080_020c4cb8(SaveSlot *slot, int mode);
extern void func_ov080_020c4260(SaveSelectScreen *screen);
extern void func_ov080_020c5584(SaveSelectScreen *screen, int value);
extern void func_ov073_020c1eb4(void *saveData, void *options);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern void SetPrimaryElementEnabled_020bc054(BOOL enabled);
extern void func_ov039_020bc03c(int value);
extern void func_ov039_020bc018(int value);
extern u32 func_ov039_020bc0d4(void);
extern int GetFieldCa4a_020bc9e0(void);
extern void func_ov039_020bc7e0(int value);
extern void func_ov039_020bbf78(int mode, int arg, int enable);
extern void SampleTweenValue_0205258c(Tween *tween, s32 *value);
extern void func_02052514(Tween *tween, int mode, int from, int to, int duration);
extern void func_0205255c(Tween *tween);
extern void SetBrightnessAndSyncMain_02029e7c(s32 brightness);
extern void SetSecondaryBrightness_02029ed0(s32 brightness);
extern void func_02007250(const void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt_020072b4(const void *src, u32 offset, u32 size);
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void SetGlobalPackedBit_02027320(int bit);
extern void ClearGlobalPackedBit_02027334(int bit);
extern void RebuildRecordCounters_02028e6c(void);
extern void *GetOverlaySelectionRecord(u32 selectionIndex);
extern void ComputePlayerStats_02050b30(void *saveData, void *record, int rebuild, int flags);
extern void func_0204f8dc(void);
extern void func_0204f98c(void);
extern void SyncSelectionRecordFromSlotEntry_0204fabc(void);
extern void func_0204fba0(void);
extern void func_0205053c(void);

void UpdateSaveSelectScreen_020c4740(SaveSelectScreen *screen)
{
    s32 brightness;
    u16 backdropColor;
    int value;
    BOOL idle;

    if (screen->errorState == 0) {
        switch (screen->step) {
        case 3:
            if (screen->cardRequestPending) {
                screen->cardRequestPending = FALSE;
                if (func_020271e8(screen->slotIndex) != 0) {
                    break;
                }
                goto fail;
            }
            switch (PollCardThreadState_020271f8()) {
            case 0:
                PlaySoundEffect_0204d924(0, 0xb);
                screen->step = 4;
                func_ov027_020b9580(screen->panel, func_ov027_020b90a4(screen->panel, 8), FALSE);
                screen->needsRedraw = 1;
                func_ov080_020c4b84(screen, &screen->slots[screen->slotIndex]);
                func_ov080_020c4260(screen);
                SetSecondaryElementEnabled_020bc084(TRUE);
                screen->busyHeld = TRUE;
                screen->backup = *data_0205fe0c;
                break;
            case 1:
                break;
            default:
                goto fail;
            }
            break;
        fail:
            screen->errorState = 2;
            screen->needsRedraw = 1;
            DecrementBusyCounterIfPositive_02025494();
            break;
        case 5:
            if (screen->cardRequestPending) {
                screen->cardRequestPending = FALSE;
                if (WriteCardSlotHeaders_02027278(screen->slotIndex) == 0) {
                    screen->errorState = 2;
                }
                if (screen->errorState == 2) {
                    screen->needsRedraw = 1;
                    DecrementBusyCounterIfPositive_02025494();
                }
            }
            SampleTweenValue_0205258c(&screen->fade, NULL);
            if (screen->fade.flags.finished) {
                PlaySoundEffect_0204d924(0, 0xb);
                screen->step = 6;
                func_ov027_020b9580(screen->panel, func_ov027_020b90a4(screen->panel, 8), FALSE);
                screen->needsRedraw = 1;
                func_ov080_020c4cb8(&screen->slots[screen->slotIndex], 2);
                func_ov073_020c1eb4(NULL, NULL);
                func_ov080_020c4260(screen);
                SetSecondaryElementEnabled_020bc084(TRUE);
                screen->busyHeld = TRUE;
                if (screen->slots[0].status < 3 && screen->slots[1].status < 3) {
                    screen->unlockFlagA = FALSE;
                    screen->unlockFlagB = FALSE;
                }
            }
            break;
        case 7:
            SampleTweenValue_0205258c(&screen->fade, &brightness);
            SetBrightnessAndSyncMain_02029e7c(brightness);
            SetSecondaryBrightness_02029ed0(brightness);
            if (screen->fade.flags.finished) {
                func_02052514(&screen->fade, 0, 0, 0x10, 0x10a);
                func_0205255c(&screen->fade);
                screen->step = 8;
            }
            break;
        case 8:
            SampleTweenValue_0205258c(&screen->fade, NULL);
            if (screen->fade.flags.finished) {
                backdropColor = 0x7fff;
                *(vu32 *)0x04000000 &= ~0x1f00;
                *(vu32 *)0x04001000 &= ~0x1f00;
                func_02007250(&backdropColor, 0, 2);
                GXS_LoadBGPltt_020072b4(&backdropColor, 0, 2);
                func_ov039_020bbf78(-1, 0x42b, 1);
                func_ov039_020bc7e0(1);
                screen->step++;
                func_01ff878c(screen->slots[screen->slotIndex].saveData, data_0205fe0c, sizeof(SaveData));
                SetGlobalPackedBit_02027320(0x1a05);
                if (screen->unlockFlagA) {
                    SetGlobalPackedBit_02027320(0x1150);
                } else {
                    ClearGlobalPackedBit_02027334(0x1150);
                }
                if (screen->unlockFlagB) {
                    SetGlobalPackedBit_02027320(0x1151);
                } else {
                    ClearGlobalPackedBit_02027334(0x1151);
                }
                RebuildRecordCounters_02028e6c();
                ComputePlayerStats_02050b30(data_0205fe0c, GetOverlaySelectionRecord(0), 1, 0);
                func_0204f8dc();
                func_0204f98c();
                SyncSelectionRecordFromSlotEntry_0204fabc();
                func_0204fba0();
                func_0205053c();
                *(u16 *)((u8 *)data_0205fe0c + 0x2d36) = 0xffff;
                return;
            }
            break;
        case 4:
        case 6:
            if (screen->busyHeld) {
                screen->busyHeld = FALSE;
                DecrementBusyCounterIfPositive_02025494();
            }
            break;
        }
    }

    if (screen->errorState > 0x80) {
        func_ov027_020b9580(screen->panel, func_ov027_020b90a4(screen->panel, 8), FALSE);
    }

    idle = func_ov039_020bc0d4() == 0;
    if (idle) {
        value = 0;
        if (!screen->cursorShown) {
            func_ov027_020b9580(screen->panel, screen->cursorElement, FALSE);
            screen->cursorShown = TRUE;
        }
    } else {
        value = GetFieldCa4a_020bc9e0();
        if (screen->cursorShown) {
            if (screen->step < 3) {
                func_ov027_020b9580(screen->panel, screen->cursorElement, TRUE);
            }
            screen->cursorShown = FALSE;
        }
    }
    func_ov080_020c5584(screen, value);

    if (screen->errorState != 0) {
        screen->errorState |= 0x80;
        func_ov039_020bc018(0);
        SetPrimaryElementEnabled_020bc054(FALSE);
        SetSecondaryElementEnabled_020bc084(FALSE);
        func_ov039_020bc03c(0);
        func_ov027_020b9580(screen->panel, screen->cursorElement, FALSE);
    }
}
