#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x2cc];
    u32 result;
} CardThreadBlock;

typedef struct {
    u8 pad_00[4];
    CardThreadBlock *thread;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern BOOL OS_IsThreadTerminated(int *thread);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

u32 PollCardTransferThread_02026c3c(void)
{
    u32 result = 0xffffffff;

    if (g_cardThreadState_0205fe00.thread != 0 &&
        OS_IsThreadTerminated((int *)g_cardThreadState_0205fe00.thread) != 0) {
        result = g_cardThreadState_0205fe00.thread->result;
        NNSi_FndFreeFromDefaultHeap_0202a1c4(g_cardThreadState_0205fe00.thread);
        g_cardThreadState_0205fe00.thread = 0;
    }
    return result;
}
