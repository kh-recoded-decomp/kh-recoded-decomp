#include "nitro/types.h"

typedef struct StateDef
{
    u8 pad_00[0x8];
    u16 flags;
} StateDef;

typedef struct StateObject
{
    u8 pad_00[0xC];
    StateDef *def;
    u8 pad_10[0x4];
    int (*update)(struct StateObject *object);
    u8 pad_18[0x20];
    u8 actorIndex;
    u8 pad_39[0x15];
    u16 flags;
    u8 pad_50[0x8];
    int timer;
} StateObject;

extern int func_ov001_020850ac(StateObject *object);
extern void func_02036120(int actorIndex, BOOL enable);

void func_ov001_02084f38(StateObject *object)
{
    object->timer = 0;
    object->update = func_ov001_020850ac;
    object->flags &= ~0x20;
    if (object->def->flags & 1)
        func_02036120(object->actorIndex, FALSE);
}
