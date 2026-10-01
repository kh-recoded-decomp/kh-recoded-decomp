#include "nitro/types.h"

typedef struct SlotLayoutFlags {
    u8 unk0 : 2;
    u8 highlight : 1;
    u8 locked : 1;
    u8 unk4 : 4;
} SlotLayoutFlags;

typedef struct SlotLayout {
    int state;
    u8 pad4[0x114];
    int highlightValue;
    u8 pad11C[0x24];
    SlotLayoutFlags flags;
} SlotLayout;

extern SlotLayout *data_ov001_020a04cc;
extern int func_ov001_02063f90(void);

BOOL SetSlotLayoutHighlight_0207d45c(int enable) {
    SlotLayout *layout = data_ov001_020a04cc;
    u8 on;

    if (layout != NULL && (layout->state == 1 || layout->state == 3)) {
        on = enable != 0;
        if (layout->flags.highlight != on) {
            layout->flags.highlight = on;
            if (!layout->flags.locked) {
                if (on) {
                    layout->highlightValue = func_ov001_02063f90();
                } else {
                    layout->highlightValue = 0;
                }
            }
        }
        return TRUE;
    }
    return FALSE;
}
