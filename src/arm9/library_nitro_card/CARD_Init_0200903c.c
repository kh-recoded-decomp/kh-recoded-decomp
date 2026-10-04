#include "nitro/types.h"

typedef struct CardCommon {
    u32 unk_000;
    u32 flag;
    u32 priority;
    u32 unk_00c;
    u32 unk_010;
    u8 pad_014[0x14];
    u8 thread[0xc0];
    u8 threadStack[0x400];
    u32 unk_4e8;
    u32 unk_4ec;
    u32 unk_4f0;
    u32 unk_4f4;
    u32 unk_4f8;
    u32 src;
    u32 dst;
    u32 len;
    u32 dma;
    u32 unk_50c;
} CardCommon;

extern CardCommon data_02056fe0;
extern u32 data_02057620;

extern u16 GetU16Field_020049f0(void);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void CARDi_InitResourceLock_020092b8(void);
extern void OS_CreateThread_02002898(void *thread, void (*func)(void *), void *arg, void *stack, u32 stackSize, u32 prio);
extern void OS_WakeupThreadDirect_02002b60(void *thread);
extern void InitDataBlockAndHandler_020092d0(void);
extern void func_02009fec(void);
extern void func_0200911c(int arg);
extern void func_0200a04c(void);
extern void func_02009398(void *arg);

void CARD_Init_0200903c(void)
{
    CardCommon *common = &data_02056fe0;

    if (common->flag == 0) {
        common->flag = 1;
        if (GetU16Field_020049f0() == 1) {
            func_01ff89a8((void *)0x02fffe00, (void *)0x02fffa80, 0x160);
        }
        common->src = 0;
        common->dst = 0;
        common->len = 0;
        common->dma = (u32)~0;
        common->unk_50c = 0;
        common->unk_010 = 0x2400;
        common->unk_00c = 0x400;
        data_02057620 = 0;
        common->priority = 4;
        CARDi_InitResourceLock_020092b8();
        common->unk_4ec = 0;
        common->unk_4f0 = 0;
        common->unk_4f8 = 0;
        common->unk_4f4 = 0;
        OS_CreateThread_02002898(common->thread, func_02009398, NULL, common->threadStack + sizeof(common->threadStack), sizeof(common->threadStack), common->priority);
        OS_WakeupThreadDirect_02002b60(common->thread);
        InitDataBlockAndHandler_020092d0();
        func_02009fec();
        if (GetU16Field_020049f0() == 1) {
            func_0200911c(1);
        }
        func_0200a04c();
    }
}


