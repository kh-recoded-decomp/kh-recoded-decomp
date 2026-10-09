#include "nitro/types.h"

typedef union {
    u32 raw;
    struct {
        s16 x;
        s16 y;
    };
} Point16;

typedef struct {
    u8 width;
    u8 height;
    s8 offsetX;
    s8 offsetY;
} DialArea;

typedef struct {
    u8 pad_00[4];
    Point16 pos;
    u16 flags;
    u16 keys;
} TouchState;

typedef struct {
    s16 x;
    s16 y;
    u8 minRadius;
    u8 maxRadius;
    u8 type;
    u8 pad_07;
    s32 useMenuKeys : 4;
    s32 dpadMode : 4;
    s32 pad_bits : 24;
    u16 angleStep;
    u16 count;
} DialConfig;

typedef struct {
    u8 pad_00000[0x12dc0];
    TouchState *touch;
    u8 pad_12dc4[0x13e7e - 0x12dc4];
    s8 pageStep;
    u8 pad_13e7f[0x13e88 - 0x13e7f];
    int dragging;
    u8 pad_13e8c[0x13eac - 0x13e8c];
    u16 dragAngle;
    u8 pad_13eae[0x13eb6 - 0x13eae];
    u16 menuKeys;
} DialMenu;

extern DialArea data_ov075_020d1454[];
extern u16 data_02060500;
extern u16 FixedPointAtan2_020062bc(int y, int x);
extern int FX_Sqrt_01ff9cfc(int value);
extern void PlaySoundEffect_0204d924(int bank, int id);

#define AbsS16(v) ((u16)(((s16)(v) ^ (s16)((s16)(v) >> 15)) - (s16)((s16)(v) >> 15)))

static inline BOOL IsOutsideArea(Point16 pos, DialArea *area)
{
    BOOL outside = TRUE;
    if (AbsS16(pos.x - 0x80) < (area->width >> 1) + area->offsetX && AbsS16(pos.y - 0x60) < (area->height >> 1) + area->offsetY) {
        outside = FALSE;
    }
    return outside;
}

/* D-pad jumps straight to one of four values */
static inline void HandleDpad(u8 *value, int *changed, u8 current)
{
    if ((data_02060500 & 0x40) && current != 2) {
        *value = 2;
        *changed = 1;
    } else if ((data_02060500 & 0x80) && current != 0) {
        *value = 0;
        *changed = 1;
    } else if ((data_02060500 & 0x20) && current != 1) {
        *value = 1;
        *changed = 1;
    } else if ((data_02060500 & 0x10) && current != 3) {
        *value = 3;
        *changed = 1;
    }
}

int UpdateDialInput_020cbf3c(DialMenu *menu, DialConfig *config, int *changed, u8 *value)
{
    int result;
    TouchState *touch;
    u8 mode;
    u8 current;
    u16 angle;
    int dx;
    int dy;
    BOOL forward;
    BOOL outside;
    u16 step;
    int type;
    int index;
    DialArea *area;
    int dist;
    u16 inRange;
    u16 diff;
    u16 count;

    result = 0;
    touch = menu->touch;
    mode = touch->flags & 3;
    current = *value;
    if (mode != 0) {
        type = config->type;
        if (type < 3 || type >= 14) {
            index = 0;
        } else {
            index = type - 2;
        }
        area = &data_ov075_020d1454[index];
        outside = IsOutsideArea(touch->pos, area);
        dx = touch->pos.x - 0x80 - config->x;
        dy = touch->pos.y - 0x60 - config->y;
        angle = FixedPointAtan2_020062bc(dx << 12, dy << 12);
        dist = FX_Sqrt_01ff9cfc((dx * dx + dy * dy) << 12) >> 12;
        inRange = (config->minRadius <= dist && dist < config->maxRadius) ? 1 : 0;

        if (mode == 1) {
            if (inRange) {
                menu->dragging = 1;
                menu->dragAngle = angle;
            } else if (outside) {
                result = 1;
            }
        } else if (menu->dragging != 0 && mode == 3) {
            if (inRange) {
                if (menu->dragAngle > angle) {
                    diff = menu->dragAngle - angle;
                    forward = FALSE;
                } else {
                    diff = angle - menu->dragAngle;
                    forward = TRUE;
                }
                if (diff >= 0x8000) {
                    diff = ~diff + 1;
                    forward ^= 1;
                }
                step = config->angleStep;
                count = diff / step;
                if (count != 0) {
                    if (forward) {
                        menu->dragAngle += (u16)(count * step);
                        if (*value < count) {
                            *value = config->dpadMode ? config->count - count + 1 : 0;
                        } else {
                            *value = *value - (u8)count;
                        }
                        *changed = 1;
                    } else {
                        u16 total;
                        menu->dragAngle -= (u16)(count * step);
                        total = config->count;
                        if (*value > total - count) {
                            if (config->dpadMode) {
                                total = 0;
                            }
                            *value = total;
                        } else {
                            *value = *value + (u8)count;
                        }
                        *changed = 1;
                    }
                }
            } else {
                menu->dragging = 0;
            }
        }
    } else {
        if (config->dpadMode) {
            HandleDpad(value, changed, current);
            menu->dragging = 0;
        } else {
            u16 keys = config->useMenuKeys ? menu->menuKeys : touch->keys;
            if (keys & 0xa0) {
                if (current != 0) {
                    if (current <= menu->pageStep) {
                        *value = 0;
                    } else {
                        *value -= (u8)menu->pageStep;
                    }
                    *changed = 1;
                }
            } else if (keys & 0x50) {
                u16 total = config->count;
                if (current < total) {
                    if (current >= total - menu->pageStep) {
                        *value = total;
                    } else {
                        *value += (u8)menu->pageStep;
                    }
                    *changed = 1;
                }
            }
            menu->dragging = 0;
        }
    }
    if (*changed && current != *value) {
        PlaySoundEffect_0204d924(1, 10);
    }
    return result;
}


