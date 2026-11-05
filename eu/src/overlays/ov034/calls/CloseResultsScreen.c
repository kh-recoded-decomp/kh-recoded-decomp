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

extern ResultsScreen data_ov034_020c0fa0;
extern u8 data_ov024_020b74a0[];

extern u32 func_ov001_02063620(void);
extern void func_ov001_020648c8(u32 value);
extern void *CreateTaskObject(void *descriptor, void *userData);
extern void RerollBoardSlotsWrapper(ResultsParams *params);
extern void ApplyResultsPartyBonus(ResultsParams *params);
extern void CommitResultsRewards(void);
extern void StoreToGlobalPtr4Field28(int value);

int CloseResultsScreen(void)
{
    if (data_ov034_020c0fa0.work->flags & 1) {
        if (func_ov001_02063620() != 0) {
            return 0;
        }
        data_ov034_020c0fa0.work->flags &= ~1;
        if (data_ov034_020c0fa0.work->nextScene != -1) {
            func_ov001_020648c8(data_ov034_020c0fa0.work->nextScene);
        } else {
            if (data_ov034_020c0fa0.params->needsSave != 0) {
                data_ov034_020c0fa0.work->saveTask = CreateTaskObject(data_ov024_020b74a0, (void *)0x7b);
                RerollBoardSlotsWrapper(data_ov034_020c0fa0.params);
                ApplyResultsPartyBonus(data_ov034_020c0fa0.params);
                data_ov034_020c0fa0.params->needsSave = 0;
            }
            CommitResultsRewards();
        }
        StoreToGlobalPtr4Field28(1);
    }
    return 0;
}
