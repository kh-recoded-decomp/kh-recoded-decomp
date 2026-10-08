#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[0x30];
    u16 renderFlags;
    u8 pad_32[0x4f - 0x32];
    u8 state : 3;
    u8 stateMid : 3;
    u8 isLead : 1;
    u8 stateHigh : 1;
    u8 pad_50[0x5a - 0x50];
    u16 flags;
} Actor;

BOOL IsLeadLink(Actor *self);

void RefreshLeadLinkState(Actor *self)
{
    BOOL locked;
    self->isLead = IsLeadLink(self) != FALSE;
    locked = FALSE;
    if ((self->flags & 0x100) && !(self->flags & 0x800)) {
        locked = TRUE;
    }
    if (locked) {
        self->renderFlags &= ~8;
    }
}
