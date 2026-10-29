#include "src/overlays/ov001/HudGaugeTable.h"

typedef void (*GaugeCellFn)(void *layer, int cell, int mode);

typedef struct HudGaugeSlot {
    u16 maxValue;
    u16 value;
    u16 width;
} HudGaugeSlot;

typedef struct GaugeTween {
    u16 count;
    u16 drawn;
    u16 target;
    u16 span;
    u8 pad_08[8];
    u64 stamp;
    BOOL active;
} GaugeTween;

typedef struct HudMenuEntry {
    u8 pad_00[0x10];
    BOOL highlighted;
    u8 pad_14[4];
} HudMenuEntry;

typedef struct HudGaugeSet {
    void *layers[3];
    void *cellLayers[3];
    u8 pad_18[0xc];
    u8 dirtyMask;
    u8 pad_25[0xb];
    BOOL resetPending;
    BOOL empty[3];
    u16 shownCells;
    u8 pad_42[0x12];
    u64 changeTicks[3];
    HudMenuEntry entries[3];
    HudGaugeSlot slots[3];
    u8 pad_c6[0xe];
    GaugeTween previousTween;
    GaugeTween tween;
} HudGaugeSet;

extern HudGaugeSet *data_ov001_020a04cc;

extern BOOL RedrawGaugeCells(void *target, u16 value, u16 scale, HudGaugeSlot *counts, GaugeCellFn draw, BOOL rebuild);
extern void RefreshMenuGaugeState(HudGaugeSet *set, int index, BOOL force);
extern void StartGaugeTween(GaugeTween *dst, GaugeTween *src, u16 value, GaugeCellFn draw, void *layer, int notify,
                                int setupIndex);
extern void UploadPaletteSlotBlock(int index, int mode);
extern void UploadScreenSlotBlock(int index, int mode);
extern u64 OS_GetTick(void);
extern int _s32_div_f(int numerator, int denominator);
extern void DrawShortLayoutRow(void *layer, int cell, int mode);
extern void DrawShortLayoutRow_02073824(void *layer, int cell, int mode);
extern void BlitFourPixelLabelPattern(void *layer, int cell, int mode);

void SetHudGaugeValue(int index, u16 value, int notifyIndex, BOOL animate, BOOL rebuild, BOOL force)
{
    HudGaugeSet *set = data_ov001_020a04cc;
    u16 shown;
    u16 cells;
    BOOL changed = TRUE;

    if (!force && animate && value == set->slots[index].value) {
        return;
    }
    if (index == 0) {
        if (animate) {
            shown = set->tween.drawn;
            cells = _s32_div_f(value * gHudGaugeTable.layouts[index].cellCount, set->slots[index].maxValue);

            /* Keep a nonempty gauge visible when its scaled width rounds to zero. */
            if (cells == 0 && value != 0) {
                cells = 1;
            }
            if (shown == cells && set->slots[index].value > value) {
                UploadPaletteSlotBlock(index, 1);
                UploadScreenSlotBlock(index, 1);
                set->changeTicks[index] = OS_GetTick();
                set->slots[index].value = value;
                RefreshMenuGaugeState(set, index, FALSE);
                return;
            }
            set->slots[index].value = value;
            StartGaugeTween(&set->tween, &set->previousTween, cells, DrawShortLayoutRow, set->layers[0], 1, 0);
            set->shownCells = cells;
        } else {
            int count;

            changed = RedrawGaugeCells(set->layers[index], value, gHudGaugeTable.layouts[index].cellCount,
                                       &set->slots[index], DrawShortLayoutRow_02073824, rebuild);
            count = _s32_div_f(value * gHudGaugeTable.layouts[index].cellCount, set->slots[index].maxValue);
            if (value != 0 && count == 0) {
                set->tween.target = 1;
            } else {
                set->tween.target = count;
            }
            set->tween.drawn = set->tween.target;
            set->shownCells = set->tween.drawn;
        }
        RefreshMenuGaugeState(set, index, rebuild);
    } else {
        changed = RedrawGaugeCells(set->layers[index], value, gHudGaugeTable.layouts[index].cellCount,
                                   &set->slots[index], BlitFourPixelLabelPattern, rebuild);
        RefreshMenuGaugeState(set, index, rebuild);
    }

    if (changed && notifyIndex >= 0) {
        set->dirtyMask |= (u8)(1 << (index + 3));
    }
}
