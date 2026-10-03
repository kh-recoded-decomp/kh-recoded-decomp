#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Kind7Entry {
    u8 pad_00[0x8];
    u8 *node;
    u8 pad_0C[0x24];
    u16 statusFlags;
    u8 slot;
    u8 pad_33[0x15];
    void *animation;
    u8 pad_4C[4];
    s8 state;
    u8 pad_51[3];
    u16 flags;
} Kind7Entry;

extern BOOL AdvanceAnimationTracks_0202ef24(void *animation, fx32 step);
extern u8 *func_02036240(int slot);
extern void Obj_RemoveFromQuadTree_020355f4(void *node);

int UpdateKind7EntryAnimations_020a5854(Kind7Entry *entry)
{
    if ((entry->flags & 0x20) && AdvanceAnimationTracks_0202ef24(entry->animation, 0x1000)) {
        entry->flags &= ~0x20;
    }
    if ((entry->flags & 0x10) && AdvanceAnimationTracks_0202ef24(func_02036240(entry->slot) + 4, 0x1000)) {
        entry->flags &= ~0x50;
    }
    if (!(entry->flags & 0x30)) {
        entry->state = 2;
        if (!(entry->flags & 1)) {
            Obj_RemoveFromQuadTree_020355f4(entry->node + 0x10);
        }
    }
    return 0;
}
