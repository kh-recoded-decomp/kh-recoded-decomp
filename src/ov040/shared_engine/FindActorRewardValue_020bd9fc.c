#include "nitro/types.h"

typedef struct NameTriple {
    int values[3];
} NameTriple;

typedef struct ActorQuery {
    int actorId;
    NameTriple *names;
    int scale;
    u16 mode;
    u16 mask;
    int flags;
    u8 results[0x4c];
} ActorQuery;

typedef struct ActorSlots {
    u8 pad_00[0x80];
    u8 recordIds[3];
} ActorSlots;

typedef struct QueryActor {
    u8 pad_00[4];
    ActorSlots *slots;
} QueryActor;

typedef struct ActorRecord {
    u8 pad_00[0xc];
    u8 kind;
    u8 value;
} ActorRecord;

extern NameTriple data_ov040_020be1a4;
extern int func_02036230(void);
extern QueryActor *func_020351b8(int handle, ActorQuery *query);
extern ActorRecord *GetActorRecord_020364f4(QueryActor *actor, int index);

int FindActorRewardValue_020bd9fc(int actorId)
{
    NameTriple names = data_ov040_020be1a4;
    ActorQuery query;
    int i;
    QueryActor *actor;

    query.actorId = actorId;
    query.names = &names;
    query.scale = 0x1000;
    i = 1;
    query.mode = 1;
    query.mask = 0xf;
    query.flags = 0;
    actor = func_020351b8(func_02036230(), &query);
    if (actor != NULL && actor->slots != NULL) {
        for (; i < 3; i++) {
            ActorRecord *record = GetActorRecord_020364f4(actor, actor->slots->recordIds[i]);
            if (record != NULL && record->kind == 8) {
                return record->value;
            }
        }
    }
    return -1;
}

