#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags10;
    u8 pad_11[0x7c - 0x11];
} PanelState;

extern PanelState *data_ov002_0206c460;
extern void CallVirtualHandlerSlot1(void *entry, int mode);

void func_ov002_0206203c(int selector) {
    switch (selector) {
    case -1:
        CallVirtualHandlerSlot1((u8 *)data_ov002_0206c460 + 0x48, 0);
        CallVirtualHandlerSlot1((u8 *)data_ov002_0206c460 + 0x7c, 0);
        data_ov002_0206c460->flags10 |= 0x80;
        data_ov002_0206c460->flags10 |= 0x40;
        return;
    case 0:
        CallVirtualHandlerSlot1((u8 *)data_ov002_0206c460 + 0x48, 0);
        data_ov002_0206c460->flags10 |= 0x40;
        return;
    case 1:
        CallVirtualHandlerSlot1((u8 *)data_ov002_0206c460 + 0x7c, 0);
        data_ov002_0206c460->flags10 |= 0x80;
        return;
    }
}
