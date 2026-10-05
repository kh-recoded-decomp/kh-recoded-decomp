#include "nitro/types.h"

#pragma explicit_zero_data on

extern void PlaceActorAtStageAnchor_02097d84(void);
extern void PostUpdateActorController_02097fe0(void);
extern void ProbeActorGround_02097f38(void);
extern void RegisterActorSlotInEntity_02097d64(void);
extern void SweepActorMove_02097dc8(void);
extern void UpdateActorController_02097fa0(void);

void *data_ov001_020a030c[13] = {
    (void *)0x00000002,
    (void *)0x00000001,
    (void *)0x00000200,
    (void *)0x00000008,
    (void *)RegisterActorSlotInEntity_02097d64,
    (void *)PlaceActorAtStageAnchor_02097d84,
    (void *)UpdateActorController_02097fa0,
    (void *)PostUpdateActorController_02097fe0,
    (void *)SweepActorMove_02097dc8,
    NULL,
    NULL,
    (void *)ProbeActorGround_02097f38,
    NULL,
};
