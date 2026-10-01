#include "nitro/types.h"

typedef struct Actor {
    u8 pad_0000[0x928];
    u64 stateFlags;
} Actor;

extern void ProbeLinkedMeshEntries_020cb8cc(Actor *actor);
extern int FSi_CloseFileCommand_020cb90c(Actor *actor);

void Actor_ProbeLinkIfFlagClear_020cb898(Actor *actor)
{
    if ((actor->stateFlags & 0x800) == 0) {
        ProbeLinkedMeshEntries_020cb8cc(actor);
        FSi_CloseFileCommand_020cb90c(actor);
    }
}
