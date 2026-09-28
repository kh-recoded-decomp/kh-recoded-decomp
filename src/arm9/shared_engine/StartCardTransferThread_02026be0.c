#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x2c0];
    void *src;
    u32 length;
    void *dst;
    u32 result;
} CardThreadBlock;

typedef struct {
    u8 pad_00[4];
    CardThreadBlock *thread;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_02002898(CardThreadBlock *thread, void (*entry)(CardThreadBlock *), CardThreadBlock *arg,
                          void *stack, u32 stackSize, u32 priority);
extern void OS_WakeupThreadDirect_02002b60(char *thread);
extern void func_02026b58(CardThreadBlock *arg);

void StartCardTransferThread_02026be0(void *src, void *dst, u32 length)
{
    g_cardThreadState_0205fe00.thread = NNSi_FndAllocFromDefaultHeap_0202a178(0x2d0);
    g_cardThreadState_0205fe00.thread->src = src;
    g_cardThreadState_0205fe00.thread->length = length;
    g_cardThreadState_0205fe00.thread->dst = dst;
    func_02002898(g_cardThreadState_0205fe00.thread, func_02026b58, g_cardThreadState_0205fe00.thread,
                  &g_cardThreadState_0205fe00.thread->src, 0x200, 0x11);
    OS_WakeupThreadDirect_02002b60((char *)g_cardThreadState_0205fe00.thread);
}
