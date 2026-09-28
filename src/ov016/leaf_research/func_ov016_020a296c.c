#include "nitro/types.h"

typedef struct ObjectState {
    u8 pad_000[0x68];
    void (*callback)(struct ObjectState *self);
    u8 pad_06c[0x54];
    u32 flags;
} ObjectState;

extern void func_ov016_020a4ccc(void);
extern void func_ov016_020a28d0(ObjectState *obj);
extern void func_ov001_02063a80(u32 param1, u32 param2);
extern void func_ov016_020a2668(ObjectState *obj, u32 param2);

void func_ov016_020a296c(ObjectState *obj, BOOL doReset)
{
    func_ov016_020a4ccc();
    if ((obj->flags & 0x80) != 0) {
        obj->callback(obj);
    }
    if (doReset != 0) {
        func_ov016_020a28d0(obj);
        func_ov001_02063a80(0x1c, 1);
    }
    func_ov016_020a2668(obj, 0);
}
