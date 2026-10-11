#include "nitro/types.h"

typedef struct HudGaugeSlot {
    u16 maxValue;
    u16 value;
    u16 width;
} HudGaugeSlot;

typedef struct HudGaugeSet {
    void *layers[3];
    void *cellLayers[3];
    u8 pad_18[0x18];
    BOOL resetPending;
    u8 pad_34[0x80];
    HudGaugeSlot slots[3];
} HudGaugeSet;

typedef struct HudGaugeLayout {
    u32 unk_00;
    u32 tileSize;
    u32 cellCount;
} HudGaugeLayout;

extern HudGaugeSet *data_ov001_020a04ac;

typedef struct HudGaugeTable {
    u32 header;
    HudGaugeLayout layouts[3];
} HudGaugeTable;

extern HudGaugeTable data_ov001_0209edcc;

extern void DrawShortLabel_0207384c(void *layer, int cell, int mode);
extern void func_ov001_02073870(void *layer, int cell, int mode);
extern void SetGaugeValues_02074688(int value, int maxValue);
extern void RefreshMenuGaugeState_02073a3c(HudGaugeSet *set, int index, int mode);
extern void func_01ff878c(void *src, void *dst, u32 size);
extern void func_ov001_020747fc(int index, u32 value, int notifyIndex, BOOL animate, int redrawMode, BOOL force);

void SetHudGaugeRange_020749c0(int index, u16 maxValue, int value, int width, int notifyIndex, BOOL force)
{
    HudGaugeSet *set = data_ov001_020a04ac;
    HudGaugeSlot *slot = &set->slots[index];
    int cells;
    int extra;
    int i;

    if (value >= 0) {
        if (value > maxValue) {
            value = maxValue;
        }
    } else {
        value = set->slots[index].value;
        if ((u32)value > (u32)maxValue) {
            value = maxValue;
        }
    }
    if (index == 0) {
        if (!set->resetPending) {
            if (!force && slot->maxValue == maxValue && slot->width == width) {
                return;
            }
        } else {
            set->resetPending = FALSE;
        }
    } else if (!force && slot->maxValue == maxValue && slot->width == width) {
        return;
    }
    if (index == 0) {
        extra = (width - 60) * 80 / 340;
        cells = maxValue * (extra + 30) / width;
        if (cells == 0) {
            cells = 1;
        }
        for (i = 0; i < cells; i++) {
            DrawShortLabel_0207384c(set->cellLayers[0], i, 1);
        }
        for (; i < extra + 30; i++) {
            DrawShortLabel_0207384c(set->cellLayers[0], i, 5);
        }
        DrawShortLabel_0207384c(set->cellLayers[0], i, 2);
        DrawShortLabel_0207384c(set->cellLayers[0], i + 1, 3);
        data_ov001_0209edcc.layouts[0].cellCount = cells;
        SetGaugeValues_02074688(value, maxValue);
    }
    set->slots[index].maxValue = maxValue;
    set->slots[index].value = value;
    set->slots[index].width = width;
    if (index != 0) {
        cells = maxValue * 22 / width;
        for (i = 0; i < cells; i++) {
            func_ov001_02073870(set->cellLayers[index], i, 1);
        }
        for (; i < 22; i++) {
            func_ov001_02073870(set->cellLayers[index], i, 3);
        }
        func_01ff878c(set->cellLayers[index], set->layers[index], data_ov001_0209edcc.layouts[index].tileSize);
        data_ov001_0209edcc.layouts[index].cellCount = cells;
        func_ov001_020747fc(index, set->slots[index].value, notifyIndex, FALSE, 1, 1);
    } else {
        RefreshMenuGaugeState_02073a3c(set, index, 1);
    }
}
