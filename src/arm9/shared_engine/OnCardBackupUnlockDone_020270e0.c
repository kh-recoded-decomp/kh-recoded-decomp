#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    u16 resourceId;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern void *CARD_UnlockBackup_020091ac(int id);
extern void CardUnlockAfterKeyShare_020091b8(int id);
extern void IncrementBusyCounter_020254a8(void);
extern void func_02026b00(int a, void *buf, int b);
extern void DecrementBusyCounterIfPositive_02025494(void);

int OnCardBackupUnlockDone_020270e0(void)
{
    u32 buffer;

    CARD_UnlockBackup_020091ac(g_cardThreadState_0205fe00.resourceId);
    IncrementBusyCounter_020254a8();
    func_02026b00(0, &buffer, 1);
    CardUnlockAfterKeyShare_020091b8(g_cardThreadState_0205fe00.resourceId);
    DecrementBusyCounterIfPositive_02025494();
    return 0;
}
