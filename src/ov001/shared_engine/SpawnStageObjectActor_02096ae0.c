#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SpawnParams {
    u16 walkerKind;
    u16 ownerSlot;
    u16 spawnArg;
    u16 attachActorId;
    u16 attach : 1;
    u16 align : 1;
    u16 attachDefault : 1;
    u16 unused : 13;
    u16 pad_0a;
    const char *nodeName;
} SpawnParams;

typedef struct SpawnRequest {
    u8 pad_00[0xa];
    u16 row;
    s16 actorId;
} SpawnRequest;

typedef struct SpawnedActor {
    u8 pad_000[0x270];
    u16 spawnArg;
    u8 pad_272[0x280 - 0x272];
    u16 walkerKind;
    u8 pad_282[0x2c0 - 0x282];
    VecFx32 position;
} SpawnedActor;

extern char data_ov001_020a02f4[];
extern void WarpWalkerTo_02090f0c(SpawnedActor *walker, const VecFx32 *position);
extern void AttachActorToStageNode_020911b4(SpawnedActor *actor, int stageActorId, const char *nodeName, int align);
extern int InitStageSpawnRequest_020982ac(SpawnRequest *request, int type, int arg);
extern u16 FindStageObjectByOwner_020995c4(u16 slot, u32 owner);
extern int ReleaseStageSlot_0209c008(int index);
extern SpawnedActor *GetStageActor_0209c040(int id);
extern SpawnRequest *GetStageController_0209c120(void);
extern u16 GetStageRowIndex_0209c228(void);

int SpawnStageObjectActor_02096ae0(int assignRow, SpawnParams *params, VecFx32 *position)
{
    u16 object = FindStageObjectByOwner_020995c4(params->ownerSlot, 1);
    int slot;
    SpawnRequest *request;
    SpawnedActor *actor;

    if (object == 0) {
        return 0;
    }
    slot = ReleaseStageSlot_0209c008(4);
    request = GetStageController_0209c120();
    InitStageSpawnRequest_020982ac(request, (s16)object, params->spawnArg);
    actor = GetStageActor_0209c040(request->actorId);
    if (actor == NULL) {
        return 0;
    }
    actor->spawnArg = params->spawnArg;
    if (assignRow) {
        request->row = GetStageRowIndex_0209c228();
    }
    if (position != NULL) {
        actor->position = *position;
    }
    if (params->attach && params->attachActorId != 0) {
        AttachActorToStageNode_020911b4(actor, params->attachActorId, params->nodeName, params->align);
    }
    if (params->attach && params->attachDefault) {
        AttachActorToStageNode_020911b4(actor, 0, data_ov001_020a02f4, 0);
    }
    if (params->walkerKind != 0) {
        actor->walkerKind = params->walkerKind;
    }
    WarpWalkerTo_02090f0c(actor, &actor->position);
    return slot;
}
