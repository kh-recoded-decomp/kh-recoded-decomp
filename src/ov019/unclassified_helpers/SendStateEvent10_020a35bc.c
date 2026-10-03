#include "nitro/types.h"

typedef struct ActorEvent {
    u8 pad_00[0xc];
    u8 kind;
    u8 pad_0d[0xf];
} ActorEvent;

struct Actor;

typedef struct ActorVtable {
    u8 pad_00[0x1c];
    void (*handleEvent)(struct Actor *self, ActorEvent *event);
} ActorVtable;

typedef struct Actor {
    u8 pad_00[4];
    ActorVtable *vtable;
    u8 pad_08[0x4f - 0x08];
    u8 state : 3;
    u8 stateHigh : 5;
    u8 pad_50[0x5a - 0x50];
    u16 flags;
} Actor;

extern void func_01ff8830(void *dest, u32 value, u32 size);

void SendStateEvent10_020a35bc(Actor *self)
{
    u16 flags = self->flags;
    ActorEvent event;
    ActorVtable *vtable;
    if (flags & 0x8000) {
        return;
    }
    if ((flags & 0x100) && !(flags & 0x800)) {
        return;
    }
    if (self->state != 0) {
        return;
    }
    vtable = self->vtable;
    func_01ff8830(&event, 0, sizeof(event));
    event.kind = 10;
    vtable->handleEvent(self, &event);
}
