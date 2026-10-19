#ifndef KH_RECODED_RESULTS_SCREEN_TYPES_H
#define KH_RECODED_RESULTS_SCREEN_TYPES_H

#include "nitro/types.h"

typedef struct ResultsInputState {
    u16 repeatMask;
    u16 delayFrames;
    u16 intervalFrames;
    u16 repeatCounts[10];
} ResultsInputState;

typedef struct ResultsUpdateWork {
    u8 pad_0000[6];
    u16 flags;
    u8 pad_0008[4];
    int state;
    u8 pad_0010[0x64c8];
    u8 tileTable[0x1c];
    void *task;
    int fadeReady;
    int fadeActive;
    u8 pad_6500[0x694];
    ResultsInputState keyRepeat;
    u8 pad_6bae[2];
    int fadeMode;
    int syncSecondary;
    int brightness;
    u8 pad_6bbc[0x24];
    int currentValueA;
    int targetValueA;
    int stepValueA;
    int currentValueB;
    int targetValueB;
    int stepValueB;
} ResultsUpdateWork;

typedef struct ResultsUpdateScreen {
    void *params;
    ResultsUpdateWork *work;
} ResultsUpdateScreen;

/* State callbacks return 0xffffffff when no state change is requested. */
typedef u32 (*ResultsStateHandler)(void);

#endif
