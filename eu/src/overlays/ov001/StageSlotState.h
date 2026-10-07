#ifndef KH_RECODED_EU_STAGE_SLOT_STATE_H
#define KH_RECODED_EU_STAGE_SLOT_STATE_H

#include "nitro/types.h"

typedef struct StageSlotState {
    u8 pad_00[2];
    u16 state;
    u8 pad_04[5];
    u8 active : 1;
    u8 pending : 1;
    u8 lockMask : 2;
    u8 flag4 : 1;
    u8 released : 1;
    u8 flag6 : 1;
    u8 flag7 : 1;
} StageSlotState;

typedef struct StageSlotManager {
    u8 pad_00000[0x18de6];
    u16 slotCount;
} StageSlotManager;

extern StageSlotManager *data_ov001_020a0528;
#define gStageSlotManager data_ov001_020a0528

#endif
