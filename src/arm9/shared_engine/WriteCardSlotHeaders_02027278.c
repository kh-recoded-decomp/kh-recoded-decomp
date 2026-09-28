#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    u16 resourceId;
    u8 pad_04[4];
    void *buffer;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern void IncrementBusyCounter_020254a8(void);
extern void *CARD_UnlockBackup_020091ac(int id);
extern int func_02026b00(int a, void *buf, int b);
extern void func_01ff8830(void *dst, int value, u32 size);
extern int func_02026b28(int offset, void *buffer, u32 length);
extern void CardUnlockAfterKeyShare_020091b8(int id);
extern void OS_WaitVBlankIntr_020049d0(void);
extern void DecrementBusyCounterIfPositive_02025494(void);

int WriteCardSlotHeaders_02027278(int slot)
{
    int scratch;

    IncrementBusyCounter_020254a8();
    CARD_UnlockBackup_020091ac(g_cardThreadState_0205fe00.resourceId);
    if (func_02026b00(0, &scratch, 1) == 0) {
        func_01ff8830(g_cardThreadState_0205fe00.buffer, 0, 0x3c18);
        slot *= 2;
        if (func_02026b28(slot * 0x3c18 + 0x20, g_cardThreadState_0205fe00.buffer, 0x20) == 0) {
            CardUnlockAfterKeyShare_020091b8(g_cardThreadState_0205fe00.resourceId);
            OS_WaitVBlankIntr_020049d0();
            CARD_UnlockBackup_020091ac(g_cardThreadState_0205fe00.resourceId);
            if (func_02026b28((slot + 1) * 0x3c18 + 0x20, g_cardThreadState_0205fe00.buffer, 0x20) == 0) {
                CardUnlockAfterKeyShare_020091b8(g_cardThreadState_0205fe00.resourceId);
                DecrementBusyCounterIfPositive_02025494();
                return 1;
            }
        }
    }
    CardUnlockAfterKeyShare_020091b8(g_cardThreadState_0205fe00.resourceId);
    DecrementBusyCounterIfPositive_02025494();
    return 0;
}
