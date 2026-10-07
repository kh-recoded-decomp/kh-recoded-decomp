#include "nitro/types.h"

typedef struct GaugeSlot {
    u16 maximum;
    u16 current;
    u16 target;
} GaugeSlot;

typedef struct GaugeMenu {
    u8 pad_000[0xb4];
    GaugeSlot slots[3];
} GaugeMenu;

extern GaugeMenu *data_ov001_020a04cc;

u16 GetGaugeSlotMaximum(int index)
{
    if (data_ov001_020a04cc == NULL) {
        return 0;
    }
    return data_ov001_020a04cc->slots[index].maximum;
}
