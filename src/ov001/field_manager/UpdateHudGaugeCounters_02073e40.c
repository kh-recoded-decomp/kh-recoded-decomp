#include "nitro/types.h"

typedef struct GaugeTrack {
    u16 unk_00;
    u16 value;
    u16 target;
    u16 hold;
    s64 interval;
    u64 lastTick;
    BOOL active;
} GaugeTrack;

typedef struct GaugeLayout {
    u8 pad_00[4];
    int rowSize;
    u8 pad_08[0x14];
} GaugeLayout;

typedef struct MenuState {
    u8 pad_000[0x4c];
    int rowScale;
    u8 pad_050[0x7c - 0x50];
    int sideActive;
    int sideOpen;
    u8 pad_084[0xb6 - 0x84];
    u16 menuMode;
    u8 pad_0b8[0xc6 - 0xb8];
    u16 rowCount;
} MenuState;

typedef struct SessionFlags {
    u8 pad_0000[0x27b6];
    u8 lowBits : 4;
    u8 tutorialSeen : 1;
    u8 highBits : 3;
} SessionFlags;

extern MenuState *data_ov001_020a04ac;
extern SessionFlags *data_ov001_020a0460;
extern GaugeLayout data_ov001_0209edf4[];
extern u64 OS_GetTick_02003fd4(void);
extern void RebuildGaugeFillRows_02073b38(s32 filledUnits);
extern void DrawGaugeFill_020739d0(s32 pageRows, s32 startRow);
extern void SetMenuGaugeActive_0207512c(int index, BOOL enable);
extern BOOL func_ov001_020645c8(u32 value);
extern void func_ov001_020716e8(int index, int mode);
extern void func_ov001_02071770(int index, int mode);

BOOL UpdateHudGaugeCounters_02073e40(GaugeTrack *fill, GaugeTrack *drain, int kind, void *handle)
{
    u64 now;
    BOOL keepOpen;
    MenuState *menu;
    int steps;
    int target;
    int total;
    int base;
    BOOL redraw;
    int end;
    BOOL changed;
    GaugeLayout *layout;
    int current;
    BOOL result;
    int last;
    int rowSize;
    int prev;
    int pageRows;
    int startRow;
    int pages;

    menu = data_ov001_020a04ac;
    now = OS_GetTick_02003fd4();
    result = FALSE;
    redraw = FALSE;
    layout = &data_ov001_0209edf4[kind];
    if (fill->active) {
        steps = (now - fill->lastTick) / fill->interval;
        prev = fill->value;
        rowSize = layout->rowSize;
        if ((prev - 1) / rowSize + 1 != (prev + steps - 1) / rowSize + 1) {
            result = TRUE;
        }
        fill->value += (u16)steps;
        fill->lastTick += (s64)steps * fill->interval;
        if (fill->value >= fill->target) {
            fill->value = fill->target;
            fill->active = FALSE;
        }
        if (1 == kind && !drain->active && result) {
            total = 0x30 * menu->rowCount / (menu->rowScale * 200);
            pages = total / 0x30;
            pageRows = fill->value > pages * 0x30 ? total - pages * 0x30 : 0x30;
            RebuildGaugeFillRows_02073b38(fill->value + 1);
            startRow = 0;
            redraw = TRUE;
        }
        fill->lastTick = now;
        result = TRUE;
    }
    if (drain->active) {
        if (fill->value >= drain->value + drain->hold || (fill->value >= drain->value && drain->hold == 0)) {
            drain->hold = 0;
            keepOpen = FALSE;
            drain->active = FALSE;
            if (0 == menu->menuMode) {
                SetMenuGaugeActive_0207512c(0, FALSE);
                if (func_ov001_020645c8(0x3525) || data_ov001_020a0460->tutorialSeen) {
                    keepOpen = TRUE;
                }
                if (!keepOpen) {
                    func_ov001_020716e8(0, 2);
                }
                func_ov001_02071770(0, 2);
            } else if (menu->sideActive) {
                func_ov001_02071770(0, 2);
                if (menu->sideOpen == 0) {
                    keepOpen = TRUE;
                }
                func_ov001_020716e8(0, keepOpen);
            } else {
                func_ov001_02071770(0, 0);
                func_ov001_020716e8(0, keepOpen);
            }
        }
        if (drain->value == drain->target && drain->hold) {
            drain->hold--;
        }
        now -= drain->lastTick;
        steps = now / drain->interval;
        prev = drain->value;
        if (prev - steps > drain->target) {
            drain->value = prev - (u16)steps;
            drain->lastTick += (s64)steps * drain->interval;
        } else {
            drain->value = drain->target;
        }
        current = drain->value;
        changed = FALSE;
        rowSize = layout->rowSize;
        if ((prev - 1) / rowSize + 1 != (current - 1) / rowSize + 1) {
            changed = TRUE;
        }
        if (1 == kind && changed && current) {
            target = drain->target;
            last = target - 1;
            if (0 == target) {
                last = 0;
            }
            base = last / rowSize * rowSize;
            end = base + rowSize;
            startRow = (base <= current && current < end) ? (target - 1) % rowSize + 1 : 0;
            RebuildGaugeFillRows_02073b38(current);
            pageRows = 0x30;
            redraw = TRUE;
        }
        result = TRUE;
    }
    if (redraw) {
        DrawGaugeFill_020739d0(pageRows, startRow);
    }
    return result;
}
