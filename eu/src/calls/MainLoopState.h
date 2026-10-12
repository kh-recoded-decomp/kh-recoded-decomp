#ifndef MAIN_LOOP_STATE_H
#define MAIN_LOOP_STATE_H

#include "nitro/types.h"

typedef struct DisplayPowerState {
    u8 displaysOff;
    u8 reserved01[3];
    void *resourceTable;
    u8 reserved08[0x800];
} DisplayPowerState;

extern DisplayPowerState gMainDisplayState;
extern BOOL gPanelActive;
extern BOOL gPreviousPanelActive;

#endif
