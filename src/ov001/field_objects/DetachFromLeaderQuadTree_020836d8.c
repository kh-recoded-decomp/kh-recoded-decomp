#include "nitro/types.h"

typedef struct FieldState {
    u8 pad_000[0x20a];
    s16 leaderId;
} FieldState;

typedef struct ActorBody {
    u8 pad_000[0x11c];
    u8 quadNode[4];
} ActorBody;

typedef struct FieldActor {
    u8 pad_00[0xc];
    ActorBody *body;
    u8 pad_10[0x6e];
    s8 actorId;
} FieldActor;

typedef struct ActorCollision {
    int *quadTree;
} ActorCollision;

typedef struct ActorRecord {
    u8 pad_00[4];
    ActorCollision *collision;
} ActorRecord;

extern FieldState *data_ov001_020a0460;

extern ActorRecord *func_02036230(int actorId);
extern void QuadTree_RemoveObject_02033c60(int *tree, void *node);

BOOL DetachFromLeaderQuadTree_020836d8(FieldActor *actor)
{
    ActorRecord *record;

    if (actor->actorId == data_ov001_020a0460->leaderId) {
        return TRUE;
    }
    record = func_02036230(data_ov001_020a0460->leaderId);
    if (record != NULL && record->collision != NULL) {
        QuadTree_RemoveObject_02033c60(record->collision->quadTree, actor->body->quadNode);
    }
    return FALSE;
}
