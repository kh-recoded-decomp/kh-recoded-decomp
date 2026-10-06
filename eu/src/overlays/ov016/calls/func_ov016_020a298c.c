#include "nitro/types.h"

typedef struct ObjectState {
    u8 pad_000[0x68];
    void (*callback)(struct ObjectState *self);
    u8 pad_06c[0x54];
    u32 flags;
} ObjectState;

extern void StackFieldObjectChain(void);
extern void GrantFieldObjectReward(ObjectState *obj);
extern void AddSessionCounter(u32 param1, u32 param2);
extern void func_ov016_020a2688(ObjectState *obj, u32 param2);

void func_ov016_020a298c(ObjectState *obj, BOOL doReset)
{
    StackFieldObjectChain();
    if ((obj->flags & 0x80) != 0) {
        obj->callback(obj);
    }
    if (doReset != 0) {
        GrantFieldObjectReward(obj);
        AddSessionCounter(0x1c, 1);
    }
    func_ov016_020a2688(obj, 0);
}
