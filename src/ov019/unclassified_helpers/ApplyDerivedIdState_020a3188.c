#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[0x32];
    u8 idByte;
} Actor;

extern u32 func_02036164(u8 id);
extern void func_ov001_02087258(Actor *self, u32 value);

void
ApplyDerivedIdState_020a3188(Actor *self)
{
    u32 value = func_02036164(self->idByte);
    func_ov001_02087258(self, value);
}
