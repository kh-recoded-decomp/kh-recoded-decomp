#include "nitro/types.h"

typedef struct GaugeSlot {
    u64 start;
    u64 interval;
    int active;
    int phase;
} GaugeSlot;

typedef struct CountPair {
    u16 total;
    u16 count;
    u16 pad;
} CountPair;

typedef struct GaugeCounter {
    u8 data[0x1c];
} GaugeCounter;

typedef struct HudGaugeSet {
    void *handles[9];
    u8 dirty;
    u8 pad_25[3];
    BOOL soundPlaying;
    BOOL suppressDraw;
    u8 pad_30[0x50 - 0x30];
    u32 drainEnabled : 1;
    u32 flagBits : 31;
    u64 flashTicks[3];
    GaugeSlot slots[3];
    CountPair counts[4];
    u8 pad_cc[0xd4 - 0xcc];
    GaugeCounter drainA;
    GaugeCounter fillA;
    GaugeCounter drainB;
    GaugeCounter fillB;
} HudGaugeSet;

typedef struct GaugeCommand {
    int offset;
    int size;
    int unused;
} GaugeCommand;

typedef struct {
    u8 pad_0000[0x214];
    u32 lowBits : 12;
    u32 eventLock : 1;
    u32 highBits : 19;
    u8 pad_0218[0x27b6 - 0x218];
    u8 stateLow : 4;
    u8 keepGauge : 1;
    u8 stateHigh : 3;
    u8 pad_27b7[0x27ec - 0x27b7];
    int eventMode;
} FieldGlobal;

extern HudGaugeSet *data_ov001_020a04ac;
extern FieldGlobal *data_ov001_020a0460;
extern GaugeCommand data_ov001_0209edd0[];

extern BOOL UpdateHudGaugeCounters_02073e40(GaugeCounter *fill, GaugeCounter *drain, int gaugeIndex, void *handle);
extern void RedrawHudGaugeRows_020745e0(void);
extern void RepaintPanelGaugeRows_020746e8(void);
extern BOOL AdvanceGaugeSlot_0207414c(int index, GaugeSlot *slot);
extern void GFXi_EnqueueCommand_02014090(int command, int offset, void *data, int size);
extern u64 OS_GetTick_02003fd4(void);
extern void func_ov001_020716e8(int index, int mode);
extern void func_ov001_02071770(int index, int mode);
extern BOOL func_ov001_020645c8(int bitOffset);
extern BOOL IsFieldPanelHidden_0207187c(void);
extern BOOL IsFirstEntryFlagSet_0206e584(void);
extern BOOL func_ov001_02064490(void);
extern BOOL func_ov001_02063838(void);
extern int func_02029f48(void);
extern void PlaySoundEffect_0204d924(int a, int id);
extern void StopSeqArcOrDefault_0204d960(int a, int id, int fade);

int UpdateHudGauges_02074d14(void)
{
    HudGaugeSet *set = data_ov001_020a04ac;
    int i;
    u64 now;
    BOOL keepShown;
    BOOL blocked;

    if (UpdateHudGaugeCounters_02073e40(&set->fillA, &set->drainA, 0, set->handles[0])) {
        RedrawHudGaugeRows_020745e0();
    }
    if (set->drainEnabled == 1 && UpdateHudGaugeCounters_02073e40(&set->fillB, &set->drainB, 1, set->handles[6])) {
        RepaintPanelGaugeRows_020746e8();
    }
    for (i = 0; i < 3; i++) {
        if (AdvanceGaugeSlot_0207414c(i, &set->slots[i])) {
            set->dirty |= (u8)(1 << (i + 3));
        }
        if (set->suppressDraw == 0 && (set->dirty & (1 << (i + 3)))) {
            GFXi_EnqueueCommand_02014090(7, data_ov001_0209edd0[i].offset, set->handles[i], data_ov001_0209edd0[i].size);
        }
        if (set->flashTicks[i] != 0) {
            now = OS_GetTick_02003fd4();
            if (set->flashTicks[i] + 0x1991b < now) {
                set->flashTicks[i] = 0;
                if (set->counts[i].count != 0) {
                    func_ov001_020716e8(i, 0);
                    if (i == 0 && set->slots[0].active) {
                        func_ov001_02071770(i, 2);
                    } else {
                        func_ov001_02071770(i, 0);
                    }
                } else {
                    if (i == 0 && (func_ov001_020645c8(0x3525) || data_ov001_020a0460->keepGauge)) {
                        keepShown = TRUE;
                    } else {
                        keepShown = FALSE;
                    }
                    if (!keepShown) {
                        func_ov001_020716e8(i, 2);
                    }
                    func_ov001_02071770(i, 2);
                }
            }
        }
    }
    if (set->suppressDraw == 0 && (set->dirty & 2)) {
        GFXi_EnqueueCommand_02014090(7, 0x1c00, set->handles[6], 0xe0);
    }
    if (set->suppressDraw == 0) {
        set->dirty = 0;
    }
    if (set->soundPlaying) {
        if (IsFieldPanelHidden_0207187c() && !IsFirstEntryFlagSet_0206e584() && !func_ov001_02064490()) {
            blocked = FALSE;
            if (data_ov001_020a0460->eventLock && data_ov001_020a0460->eventMode == 5) {
                blocked = TRUE;
            }
            if (!blocked && !func_ov001_02063838() && func_02029f48() != -16 && func_02029f48() != 16) {
                goto done;
            }
        }
        StopSeqArcOrDefault_0204d960(0, 0xe, 5);
        set->soundPlaying = FALSE;
    } else if (set->slots[0].active && IsFieldPanelHidden_0207187c() && !IsFirstEntryFlagSet_0206e584() && !func_ov001_02064490()) {
        blocked = FALSE;
        if (data_ov001_020a0460->eventLock && data_ov001_020a0460->eventMode == 5) {
            blocked = TRUE;
        }
        if (!blocked && !func_ov001_02063838() && func_02029f48() != -16 && func_02029f48() != 16) {
            PlaySoundEffect_0204d924(0, 0xe);
            set->soundPlaying = TRUE;
        }
    }
done:
    return 0;
}
