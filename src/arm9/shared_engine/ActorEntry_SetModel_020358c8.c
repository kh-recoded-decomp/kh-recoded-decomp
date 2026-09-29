#include "nitro/types.h"

typedef struct ActorEntry {
    u8 pad_00[8];
    u16 flags;
    u8 modelExtra;
    u8 registryTag;
    u8 pad_0C[4];
    u8 object[4];
} ActorEntry;

typedef struct ActorRegistry {
    u8 pad_000[0xc2c];
    u8 currentTag;
} ActorRegistry;

extern void ActorEntry_Init_020357d8(int slot, ActorEntry *entry, u16 group, const u8 *attributes, const void *shape, BOOL flag20, s8 priority);
extern BOOL Obj_SetModel_020353d0(void *object, s32 resource, s32 source, u32 extra);
extern ActorRegistry *g_actorRegistry_0206083c;

BOOL ActorEntry_SetModel_020358c8(ActorEntry *entry, s32 resource, s32 source, u32 extra)
{
    if ((entry->flags & 1) == 0) {
        ActorEntry_Init_020357d8(0xffff, entry, 0, NULL, NULL, TRUE, 0x20);
    }
    if (Obj_SetModel_020353d0(entry->object, resource, source, extra)) {
        entry->registryTag = g_actorRegistry_0206083c->currentTag;
        entry->flags |= 4;
        entry->modelExtra = extra;
        return TRUE;
    }
    return FALSE;
}
