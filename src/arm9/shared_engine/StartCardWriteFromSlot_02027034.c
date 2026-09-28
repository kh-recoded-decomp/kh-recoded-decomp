#include "nitro/types.h"

typedef struct {
    u8 blockCounter;
    u8 slot;
    u8 pad_02[6];
    void *buffer;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern void IncrementBusyCounter_020254a8(void);
extern void StartCardTransferThread_02026be0(void *src, void *dst, u32 length);

void StartCardWriteFromSlot_02027034(u8 slot)
{
    IncrementBusyCounter_020254a8();
    g_cardThreadState_0205fe00.blockCounter = 0;
    g_cardThreadState_0205fe00.slot = slot;
    StartCardTransferThread_02026be0(
        (void *)((g_cardThreadState_0205fe00.slot << 1) * 0x3c18 + 0x20),
        g_cardThreadState_0205fe00.buffer, 0x3c18);
}
