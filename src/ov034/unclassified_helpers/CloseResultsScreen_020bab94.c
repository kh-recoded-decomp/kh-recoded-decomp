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

extern ResultsScreen g_resultsScreen_020c0f80;
extern u8 data_ov024_020b7480[];

extern u32 func_ov001_02063620(void);
extern void func_ov001_020648c8(u32 value);
extern void *func_0202a448(void *descriptor, void *userData);
extern void PXI_Init_020b72dc(ResultsParams *params);
extern void func_ov034_020be258(ResultsParams *params);
extern void func_ov034_020bd0a0(void);
extern void StoreToGlobalPtr4Field28_0202a778(int value);

int CloseResultsScreen_020bab94(void)
{
    if (g_resultsScreen_020c0f80.work->flags & 1) {
        if (func_ov001_02063620() != 0) {
            return 0;
        }
        g_resultsScreen_020c0f80.work->flags &= ~1;
        if (g_resultsScreen_020c0f80.work->nextScene != -1) {
            func_ov001_020648c8(g_resultsScreen_020c0f80.work->nextScene);
        } else {
            if (g_resultsScreen_020c0f80.params->needsSave != 0) {
                g_resultsScreen_020c0f80.work->saveTask = func_0202a448(data_ov024_020b7480, (void *)0x7b);
                PXI_Init_020b72dc(g_resultsScreen_020c0f80.params);
                func_ov034_020be258(g_resultsScreen_020c0f80.params);
                g_resultsScreen_020c0f80.params->needsSave = 0;
            }
            func_ov034_020bd0a0();
        }
        StoreToGlobalPtr4Field28_0202a778(1);
    }
    return 0;
}
