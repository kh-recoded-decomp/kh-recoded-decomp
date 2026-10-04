#include "nitro/types.h"

typedef struct QuantityPicker {
    u8 mode;
    u8 dirty;
    u8 pad2[2];
    u8 quantity;
    u8 maxQuantity;
    u8 swapped;
} QuantityPicker;

extern u16 data_02060500;
extern void PlaySoundEffect_0204d924(int channel, int id);
extern void ArrangeWidgetPair_020c0b38(QuantityPicker *picker);

void StepPickerBack_020c15f0(QuantityPicker *picker)
{
    if (picker->mode == 2) {
        if ((data_02060500 & 0x20) == 0) {
            goto done;
        }
        picker->swapped ^= 1;
        ArrangeWidgetPair_020c0b38(picker);
    } else {
        if (picker->mode != 1 || picker->quantity <= 1) {
            goto done;
        }
        if (picker->quantity > 10) {
            picker->quantity -= 10;
        } else {
            picker->quantity = 1;
        }
    }
    PlaySoundEffect_0204d924(0, 0);
done:
    picker->dirty = 1;
}
