#include "nitro/types.h"

extern int SetSlotEventHandler_0201144c(int slot, void (*callback)(void *), void *arg);

int ClearSlotEventHandler_02011ea4(void *record)
{
    u16 *handlerActive;
    u16 slot;

    if (record == NULL) {
        return 6;
    }
    handlerActive = (u16 *)((u8 *)record + 0x80e);
    if (*handlerActive == 0) {
        return 3;
    }
    slot = *(u16 *)((u8 *)record + 0x816);
    SetSlotEventHandler_0201144c(slot, 0, 0);
    *handlerActive = 0;
    *(u16 *)((u8 *)record + 0x81c) = 0;
    return 0;
}
