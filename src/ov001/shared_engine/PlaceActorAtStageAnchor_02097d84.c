#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageController {
    u8 pad_00[0xa];
    u16 eventId;
} StageController;

typedef struct StageActor {
    u8 pad_000[0x1d2];
    u16 controllerId;
    u8 pad_1d4[0x28c - 0x1d4];
    u16 lowBits : 11;
    u16 anchorId : 3;
    u16 highBits : 2;
} StageActor;

extern StageController *GetStageController_0209c120(u32 id);
extern u8 *GetStageEventRecord_0209c0ec(u32 id);
extern void GetStageEntryAnchor_02099058(u32 id, VecFx32 *outPosition);
extern void func_ov001_02097c78(u8 *record, StageActor *actor, VecFx32 *position);

void PlaceActorAtStageAnchor_02097d84(StageActor *actor, int unused, VecFx32 *position)
{
    StageController *controller = GetStageController_0209c120(actor->controllerId);
    u8 *record = NULL;

    if (controller != NULL && controller->eventId != 0) {
        record = GetStageEventRecord_0209c0ec(controller->eventId);
    }
    GetStageEntryAnchor_02099058(actor->anchorId, position);
    if (record != NULL) {
        func_ov001_02097c78(record, actor, position);
    }
}
