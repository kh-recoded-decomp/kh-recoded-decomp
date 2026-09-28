#include "nitro/types.h"

typedef struct {
    u8 blockCounter;
    u8 slot;
    u16 resourceId;
    u8 pad_04[4];
    void *buffer;
    u8 pad_0c[8];
    int threadResult;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern void *PXI_Init_02026c94(void);
extern int func_02009128(void);
extern void CardUnlockAfterKeyShare_020091b8(int resource);
extern void DecrementBusyCounterIfPositive_02025494(void);
extern void EmitCommandVariantA_02026c6c(int offset, void *buffer, int length);

int PollCardThreadState_020271f8(void)
{
    int combinedIndex;

    if (PXI_Init_02026c94() != 0) {
        g_cardThreadState_0205fe00.threadResult = func_02009128();
        if (g_cardThreadState_0205fe00.threadResult != 0) {
            CardUnlockAfterKeyShare_020091b8(g_cardThreadState_0205fe00.resourceId);
            DecrementBusyCounterIfPositive_02025494();
            return 3;
        }
        g_cardThreadState_0205fe00.blockCounter = g_cardThreadState_0205fe00.blockCounter + 1;
        if (g_cardThreadState_0205fe00.blockCounter >= 2) {
            CardUnlockAfterKeyShare_020091b8(g_cardThreadState_0205fe00.resourceId);
            DecrementBusyCounterIfPositive_02025494();
            return 0;
        }
        combinedIndex = g_cardThreadState_0205fe00.blockCounter + g_cardThreadState_0205fe00.slot * 2;
        EmitCommandVariantA_02026c6c(combinedIndex * 0x3c18 + 0x20, g_cardThreadState_0205fe00.buffer, 0x3c18);
    }
    return 1;
}
