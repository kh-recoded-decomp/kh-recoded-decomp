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

extern ResultsScreen g_resultsScreen_020c0f80;
extern u32 data_0206085c;
extern u8 *data_0205fe0c;
extern SessionFlags *data_ov001_020a0460;
extern char OverlayId27_0000001b[];
extern char OverlayId24_00000018[];

extern void SetSoundListenersEnabled_0204df9c(int enabled);
extern void DefaultStepDone_0204f5d8(void *image);
extern void FreeAllocatedBuffers_020b9a60(void *buffers);
extern void _fp_init_020be714(void *menu);
extern void PXI_Init_0202a638(void *task);
extern void func_02029f98(int processor, int overlayId);
extern u64 func_02003fd4(void);
extern u64 GetCardThreadStartTick_0202726c(void);
extern u64 func_02023d54(u64 dividend, u64 divisor);
extern u64 func_02023d60(u64 value, u64 divisor);
extern unsigned int func_0202a9d0(unsigned int range);
extern unsigned int random_next_scaled_0202aa04(unsigned int upperBound);
extern void SeedSharedRandomState_0202a984(u32 seed, u64 mix);
extern void func_ov001_020646b8(int mode);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);

void CloseResultsSession_020bae34(void)
{
    int i;
    u32 seed;
    u32 mixA;
    u32 mixB;

    SetSoundListenersEnabled_0204df9c(0);
    DefaultStepDone_0204f5d8(g_resultsScreen_020c0f80.work->overlayImage);
    FreeAllocatedBuffers_020b9a60(g_resultsScreen_020c0f80.work->tileTable);
    _fp_init_020be714(g_resultsScreen_020c0f80.work->menuState);
    if (g_resultsScreen_020c0f80.work->task != NULL) {
        PXI_Init_0202a638(g_resultsScreen_020c0f80.work->task);
    }
    func_02029f98(0, (int)OverlayId27_0000001b);
    func_02029f98(0, (int)OverlayId24_00000018);
    if (g_resultsScreen_020c0f80.work->savedSlot != -1) {
        if (g_resultsScreen_020c0f80.work->syncPlayTime == 1) {
            data_0206085c = *g_resultsScreen_020c0f80.params;
        }
        for (i = 0; i < func_02023d60(*(u32 *)(data_0205fe0c + 0x28c8)
                + func_02023d54((func_02003fd4() - GetCardThreadStartTick_0202726c()) * 64, 0x1ff6210), 100); i++) {
            func_0202a9d0(1000);
            random_next_scaled_0202aa04(1000);
        }
        seed = random_next_scaled_0202aa04(0xffffffff);
        mixA = random_next_scaled_0202aa04(0xffffffff);
        mixB = random_next_scaled_0202aa04(0xffffffff);
        SeedSharedRandomState_0202a984(seed, (u64)mixA * mixB);
        func_ov001_020646b8(10);
        data_ov001_020a0460->resultsDone = 1;
        WriteSessionPackedBits_0206459c(0x1e19, 1, 0);
    }
    g_resultsScreen_020c0f80.work = NULL;
}
