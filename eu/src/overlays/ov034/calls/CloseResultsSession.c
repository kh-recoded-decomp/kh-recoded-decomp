#include "nitro/types.h"
#include "src/overlays/ov001/SessionBuffers.h"

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

extern ResultsScreen gResultsScreenPointersPrefix;
extern u32 gSceneHandoffSharedHeader;
extern u8 *gSaveIoStateDataTail;
extern SessionFlags *gFieldSessionWork;
extern char OVERLAY_27_ID[];
extern char OVERLAY_24_ID[];

extern void SetSoundListenersEnabled(int enabled);
extern void FSi_DefaultStepDoneB(void *image);
extern void FreeAllocatedBuffers(void *buffers);
extern void ResultsSessionCleanupNoOp(void *menu);
extern void DestroyTaskObjectWrapper(void *task);
extern void UnloadOverlayAfterGeometryTransfer(int processor, int overlayId);
extern u64 OS_GetTick(void);
extern u64 GetCardThreadStartTick(void);
extern u64 _ll_udiv(u64 dividend, u64 divisor);
extern u64 _ull_mod(u64 value, u64 divisor);
extern unsigned int NextSharedRandom16Scaled(unsigned int range);
extern unsigned int random_next_scaled(unsigned int upperBound);
extern void SeedSharedRandomState(u32 seed, u64 mix);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

void CloseResultsSession(void)
{
    int i;
    u32 seed;
    u32 mixA;
    u32 mixB;

    SetSoundListenersEnabled(0);
    FSi_DefaultStepDoneB(gResultsScreenPointersPrefix.work->overlayImage);
    FreeAllocatedBuffers(gResultsScreenPointersPrefix.work->tileTable);
    ResultsSessionCleanupNoOp(gResultsScreenPointersPrefix.work->menuState);
    if (gResultsScreenPointersPrefix.work->task != NULL) {
        DestroyTaskObjectWrapper(gResultsScreenPointersPrefix.work->task);
    }
    UnloadOverlayAfterGeometryTransfer(0, (int)OVERLAY_27_ID);
    UnloadOverlayAfterGeometryTransfer(0, (int)OVERLAY_24_ID);
    if (gResultsScreenPointersPrefix.work->savedSlot != -1) {
        if (gResultsScreenPointersPrefix.work->syncPlayTime == 1) {
            gSceneHandoffSharedHeader = *gResultsScreenPointersPrefix.params;
        }
        for (i = 0; i < _ull_mod(*(u32 *)(gSaveIoStateDataTail + 0x28c8)
                + _ll_udiv((OS_GetTick() - GetCardThreadStartTick()) * 64, 0x1ff6210), 100); i++) {
            NextSharedRandom16Scaled(1000);
            random_next_scaled(1000);
        }
        seed = random_next_scaled(0xffffffff);
        mixA = random_next_scaled(0xffffffff);
        mixB = random_next_scaled(0xffffffff);
        SeedSharedRandomState(seed, (u64)mixA * mixB);
        SessionBuffer_Free(10);
        gFieldSessionWork->resultsDone = 1;
        WriteSessionPackedBits(0x1e19, 1, 0);
    }
    gResultsScreenPointersPrefix.work = NULL;
}
