#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x11];
    u8 flags11;
    u8 pad_12[0xb0 - 0x12];
} PanelState;

extern PanelState *data_ov002_0206c460;
extern void CallVirtualHandlerSlot1(void *entry, int mode);

void func_ov002_020620fc(int selector) {
    switch (selector) {
    case -1:
        CallVirtualHandlerSlot1((u8 *)data_ov002_0206c460 + 0xb0, 0);
        CallVirtualHandlerSlot1((u8 *)data_ov002_0206c460 + 0xe4, 0);
        data_ov002_0206c460->flags11 = (data_ov002_0206c460->flags11 & ~0x01) | 0x01;
        data_ov002_0206c460->flags11 |= 0x02;
        return;
    case 0:
        CallVirtualHandlerSlot1((u8 *)data_ov002_0206c460 + 0xb0, 0);
        data_ov002_0206c460->flags11 = (data_ov002_0206c460->flags11 & ~0x01) | 0x01;
        return;
    case 1:
        CallVirtualHandlerSlot1((u8 *)data_ov002_0206c460 + 0xe4, 0);
        data_ov002_0206c460->flags11 |= 0x02;
        return;
    }
}
