#include "nitro/types.h"

typedef struct ResultsParams {
    u8 pad_00[0x7c];
    int needsSave;
} ResultsParams;

typedef struct ResultsWork {
    u8 pad_0000[6];
    u16 flags;
    u8 pad_0008[0x64ec];
    void *saveTask;
    u8 pad_64f8[0x6e4];
    int nextScene;
} ResultsWork;

typedef struct ResultsScreen {
    ResultsParams *params;
    ResultsWork *work;
} ResultsScreen;

extern ResultsScreen gResultsScreenPointersPrefix;
extern u8 gBoardScreenTaskDescriptor[];

extern u32 func_ov001_02063620(void);
extern void func_ov001_020648c8(u32 value);
extern void *CreateTaskObject(void *descriptor, void *userData);
extern void RerollBoardSlotsWrapper(ResultsParams *params);
extern void ApplyResultsPartyBonus(ResultsParams *params);
extern void CommitResultsRewards(void);
extern void StoreToGlobalPtr4Field28(int value);

int CloseResultsScreen(void)
{
    if (gResultsScreenPointersPrefix.work->flags & 1) {
        if (func_ov001_02063620() != 0) {
            return 0;
        }
        gResultsScreenPointersPrefix.work->flags &= ~1;
        if (gResultsScreenPointersPrefix.work->nextScene != -1) {
            func_ov001_020648c8(gResultsScreenPointersPrefix.work->nextScene);
        } else {
            if (gResultsScreenPointersPrefix.params->needsSave != 0) {
                gResultsScreenPointersPrefix.work->saveTask = CreateTaskObject(gBoardScreenTaskDescriptor, (void *)0x7b);
                RerollBoardSlotsWrapper(gResultsScreenPointersPrefix.params);
                ApplyResultsPartyBonus(gResultsScreenPointersPrefix.params);
                gResultsScreenPointersPrefix.params->needsSave = 0;
            }
            CommitResultsRewards();
        }
        StoreToGlobalPtr4Field28(1);
    }
    return 0;
}
