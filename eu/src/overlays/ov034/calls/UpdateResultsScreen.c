#pragma optimization_level 2
#include "src/overlays/ov034/ResultsScreen.h"

extern u8 data_ov024_020b74a0[];
extern void *func_0202a45c(void *descriptor, void *arg);
extern int FS_UnloadOverlayImage_0204f5f0(void *keyRepeat);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void FlushDirtyTileTableRows(void *tileTable);

static inline int AbsoluteValue(int value)
{
    return value < 0 ? -value : value;
}

#define WORK (data_ov034_020c0fa0.work)

int UpdateResultsScreen(void)
{
    int nextState;

    if (WORK->task == NULL) WORK->task = func_0202a45c(data_ov024_020b74a0, (void *)0x7b);
    FS_UnloadOverlayImage_0204f5f0(&WORK->keyRepeat);

    if (WORK->targetValueA != WORK->currentValueA) {
        WORK->currentValueA += WORK->stepValueA;
        if (WORK->stepValueA == 0 ||
            AbsoluteValue(WORK->stepValueA) > AbsoluteValue(WORK->targetValueA - WORK->currentValueA)) {
            WORK->currentValueA = WORK->targetValueA;
        }
        PlaySoundEffect(0, 0x11);
    }
    if (WORK->targetValueB != WORK->currentValueB) {
        WORK->currentValueB += WORK->stepValueB;
        if (WORK->stepValueB == 0 ||
            AbsoluteValue(WORK->stepValueB) > AbsoluteValue(WORK->targetValueB - WORK->currentValueB)) {
            WORK->currentValueB = WORK->targetValueB;
        }
        PlaySoundEffect(0, 0x11);
    }

    if (WORK->fadeReady == 0 ||
        !((WORK->fadeMode == 0 && WORK->brightness > -16) ||
          (WORK->fadeMode == 2 && WORK->brightness < 16))) {
        do {
            WORK->flags &= ~0x8000;
            nextState = (int)gResultsScreenHandlers[WORK->state]();
            if (nextState >= 0) WORK->state = nextState;
        } while (WORK->flags & 0x8000);
    }
    WORK->fadeActive = 1;
    FlushDirtyTileTableRows(WORK->tileTable);
    return 0;
}
