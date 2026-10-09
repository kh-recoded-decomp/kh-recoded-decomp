#include "nitro/types.h"

typedef struct ResultsWork {
    u8 pad_0000[0x64d8];
    u8 tileTable[0x1c];
    void *task;
    u8 pad_64f8[8];
    u8 menuState[0x694];
    u8 overlayImage[0x48];
    int savedSlot;
    u8 pad_6be0[0x1b0];
    int syncPlayTime;
} ResultsWork;

typedef struct ResultsScreen {
    u32 *params;
    ResultsWork *work;
} ResultsScreen;

typedef struct SessionFlags {
    u8 pad_0000[0x27fd];
    u8 resultsDone : 1;
    u8 rest : 7;
} SessionFlags;

extern ResultsScreen data_ov034_020c0fa0;
extern u32 data_0206085c;
extern u8 *data_0205fe0c;
extern SessionFlags *data_ov001_020a0480;
extern char OVERLAY_27_ID[];
extern char OVERLAY_24_ID[];

extern void SetSoundListenersEnabled(int enabled);
extern void FSi_DefaultStepDoneB(void *image);
extern void FreeAllocatedBuffers(void *buffers);
extern void func_ov034_020be734(void *menu);
extern void PXI_Init_0202a64c(void *task);
extern void func_02029fac(int processor, int overlayId);
extern u64 OS_GetTick(void);
extern u64 GetCardThreadStartTick(void);
extern u64 _ll_udiv(u64 dividend, u64 divisor);
extern u64 _ull_mod(u64 value, u64 divisor);
extern unsigned int func_0202a9e4(unsigned int range);
extern unsigned int random_next_scaled(unsigned int upperBound);
extern void SeedSharedRandomState(u32 seed, u64 mix);
extern void func_ov001_020646b8(int mode);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

void CloseResultsSession(void)
{
    int i;
    u32 seed;
    u32 mixA;
    u32 mixB;

    SetSoundListenersEnabled(0);
    FSi_DefaultStepDoneB(data_ov034_020c0fa0.work->overlayImage);
    FreeAllocatedBuffers(data_ov034_020c0fa0.work->tileTable);
    func_ov034_020be734(data_ov034_020c0fa0.work->menuState);
    if (data_ov034_020c0fa0.work->task != NULL) {
        PXI_Init_0202a64c(data_ov034_020c0fa0.work->task);
    }
    func_02029fac(0, (int)OVERLAY_27_ID);
    func_02029fac(0, (int)OVERLAY_24_ID);
    if (data_ov034_020c0fa0.work->savedSlot != -1) {
        if (data_ov034_020c0fa0.work->syncPlayTime == 1) {
            data_0206085c = *data_ov034_020c0fa0.params;
        }
        for (i = 0; i < _ull_mod(*(u32 *)(data_0205fe0c + 0x28c8)
                + _ll_udiv((OS_GetTick() - GetCardThreadStartTick()) * 64, 0x1ff6210), 100); i++) {
            func_0202a9e4(1000);
            random_next_scaled(1000);
        }
        seed = random_next_scaled(0xffffffff);
        mixA = random_next_scaled(0xffffffff);
        mixB = random_next_scaled(0xffffffff);
        SeedSharedRandomState(seed, (u64)mixA * mixB);
        func_ov001_020646b8(10);
        data_ov001_020a0480->resultsDone = 1;
        WriteSessionPackedBits(0x1e19, 1, 0);
    }
    data_ov034_020c0fa0.work = NULL;
}
