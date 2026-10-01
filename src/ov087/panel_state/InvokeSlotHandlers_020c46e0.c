#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} HandlerSlot;

typedef struct {
    u8 pad_000[0x9f8];
    HandlerSlot slots[3];
} PanelScene;

extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);

void InvokeSlotHandlers_020c46e0(PanelScene *scene)
{
    int slotIndex;

    for (slotIndex = 0; slotIndex < 3; slotIndex++) {
        CallVirtualHandlerSlot1_02001574(&scene->slots[slotIndex], 0);
    }
}
