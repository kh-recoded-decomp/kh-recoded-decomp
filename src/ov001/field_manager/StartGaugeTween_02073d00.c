#include "nitro/types.h"

typedef void (*GaugeCellFn)(int handle, int cell, int mode);

typedef struct GaugeRecord {
    u16 count;
    u16 drawn;
    u16 target;
    u16 span;
    u8 pad_08[8];
    u64 stamp;
    int active;
} GaugeRecord;

typedef struct GaugeSetup {
    int unk00;
    int rowWidth;
    u8 pad_08[0x14];
} GaugeSetup;

extern GaugeSetup data_ov001_0209edf4[];
extern void ArmCountdown_02073cdc(GaugeRecord *record, int value, int kind);
extern void func_ov001_020716e8(int screen, int mode);
extern void UploadScreenSlotBlock_02071770(int screen, int mode);

static inline int CellColumn(int value, int width)
{
    if (value == 0) {
        return 0;
    }
    return (value - 1) % width + 1;
}

void StartGaugeTween_02073d00(GaugeRecord *dst, GaugeRecord *src, u16 value, GaugeCellFn draw, int handle,
                              int notify, int setupIndex)
{
    GaugeSetup *setup = &data_ov001_0209edf4[setupIndex];
    int drawn = dst->drawn;
    int last;
    int width;
    int end;
    int start;
    int sameRow;

    if (value >= (unsigned int)drawn) {
        ArmCountdown_02073cdc(dst, drawn, value);
        if (setupIndex != 1) {
            return;
        }
        if (src->active == 0) {
            return;
        }
        width = setup->rowWidth;
        end = width * ((src->drawn - 1) / width) + 1;
        start = src->target;
        if (start <= end) {
            start = end;
        }
        dst->drawn = start;
        return;
    }

    sameRow = 1;
    if (setupIndex == 1 && src->active != 0) {
        if ((src->drawn - 1) / 48 > src->target / 48) {
            sameRow = 0;
        }
    }
    ArmCountdown_02073cdc(src, drawn, value);

    end = dst->drawn;
    if (end == 0) {
        last = 0;
        end = 0;
    } else {
        last = end - 1;
        end = last % setup->rowWidth + 1;
    }

    if (sameRow != 0) {
        if (value == 0) {
            start = 0;
        } else {
            width = setup->rowWidth;
            if ((int)value / width < last / width) {
                start = 0;
            } else {
                start = CellColumn(value, width);
            }
        }
        while (start < end) {
            draw(handle, start, 1);
            start = start + 1;
        }
    }

    if (src->count < dst->drawn) {
        src->count = dst->drawn;
    }
    if (src->drawn < dst->drawn) {
        src->drawn = src->count;
    }
    if (dst->drawn > value) {
        dst->active = 0;
        dst->drawn = value;
    } else {
        dst->target = value;
    }

    if (notify != 0) {
        func_ov001_020716e8(0, 1);
        UploadScreenSlotBlock_02071770(0, 1);
    }
}
