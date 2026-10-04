#include "nitro/types.h"

typedef struct {
    u32 words[0x3760 / 4];
} SaveData;

typedef struct {
    u8 pad_00[0x28c4];
    u32 saveStamp;
} SaveFields;

typedef struct {
    s32 status : 8;
    u32 statusHigh : 24;
    u8 pad_04[0xcc];
    SaveFields saveData;
    u8 pad_2998[0x3830 - 0x2998];
} SaveSlot;

typedef struct {
    u8 slotIndex;
    u8 pad_01[9];
    u8 readFailed;
    u8 pad_0B[0x15];
    u32 latestStamp;
    u8 pad_24[0x54];
    SaveSlot slots[2];
    SaveData savedGame;
} SaveSelectScreen;

extern SaveData *data_0205fe0c;
extern int PollCardThreadResult_02027060(void);
extern void StartCardWriteFromSlot_02027034(u8 slot);
extern void BuildSlotSummary_020c4b84(SaveSelectScreen *screen, SaveSlot *slot);
extern void HandleSlotReadResult_020c4cb8(SaveSlot *slot, int result);
extern void CountValidSlots_020c4260(SaveSelectScreen *screen);
extern void func_01ff8ad8(const void *src, void *dst, u32 len);
extern int func_ov039_020bc914(void);
extern int *AcquireMapLayout_020506dc(BOOL reload, BOOL discard);
extern void RebuildRecordCounters_02028e6c(void);
extern void *GetOverlaySelectionRecord(u32 selectionIndex);
extern void ComputePlayerStats_02050b30(SaveData *state, void *out, BOOL recompute, int scaleParam);
extern void func_ov073_020c1eb4(SaveData *saveData, void *options);
extern void func_02050a44(void);
extern void LoadSlotIntoGame_020c58c4(SaveSlot *slot);

BOOL PollSaveSlotReads_020c4d08(SaveSelectScreen *screen)
{
    int result = PollCardThreadResult_02027060();
    SaveSlot *slot;
    int firstValid;
    int secondValid;
    s32 first;
    s32 latest;
    u32 stamp;

    if (result == 1) {
        return FALSE;
    }
    if ((u16)result != 3) {
        slot = &screen->slots[screen->slotIndex];
        if (result == 0) {
            BuildSlotSummary_020c4b84(screen, slot);
        } else {
            HandleSlotReadResult_020c4cb8(slot, result);
        }
        screen->slotIndex++;
        if (screen->slotIndex < 2) {
            StartCardWriteFromSlot_02027034(screen->slotIndex);
            return PollSaveSlotReads_020c4d08(screen);
        }
        firstValid = screen->slots[0].status >= 2 ? 1 : 0;
        secondValid = screen->slots[1].status >= 2 ? 1 : 0;
        switch ((u16)(firstValid | (secondValid << 1))) {
        case 0:
        case 1:
            screen->latestStamp = screen->slots[0].saveData.saveStamp;
            break;
        case 2:
            screen->latestStamp = screen->slots[1].saveData.saveStamp;
            break;
        case 3:
            first = screen->slots[0].saveData.saveStamp;
            latest = screen->slots[1].saveData.saveStamp;
            if ((first & 0x0fffffff) >= (latest & 0x0fffffff)) {
                latest = first;
            }
            screen->latestStamp = latest;
            break;
        }
        CountValidSlots_020c4260(screen);
        func_01ff8ad8(&screen->savedGame, data_0205fe0c, sizeof(SaveData));
        if (func_ov039_020bc914() != 3) {
            AcquireMapLayout_020506dc(TRUE, FALSE);
            RebuildRecordCounters_02028e6c();
            ComputePlayerStats_02050b30(data_0205fe0c, GetOverlaySelectionRecord(0), TRUE, 1);
            func_ov073_020c1eb4(data_0205fe0c, NULL);
            func_02050a44();
        }
        if (func_ov039_020bc914() != 3) {
            stamp = ((SaveFields *)data_0205fe0c)->saveStamp;
        } else {
            stamp = screen->latestStamp;
        }
        screen->slotIndex = (stamp & 0x30000000) >> 28;
        screen->latestStamp &= 0x0fffffff;
        LoadSlotIntoGame_020c58c4(&screen->slots[screen->slotIndex]);
        return TRUE;
    }
    screen->readFailed = 1;
    return TRUE;
}
