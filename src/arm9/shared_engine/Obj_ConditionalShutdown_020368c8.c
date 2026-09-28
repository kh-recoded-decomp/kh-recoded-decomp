#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0A[6];
    u32 sub;
} Container;

extern void func_02036874(Container *obj, u16 arg);
extern void func_020359b0(Container *obj);
extern void func_02035c48(Container *obj);
extern void Obj_ShutdownBase_02035554(void *entity);

void Obj_ConditionalShutdown_020368c8(Container *obj, u16 arg) {
    if (obj->flags & 0x80) {
        func_02036874(obj, arg);
    }
    if (obj->flags & 0x40) {
        return;
    }
    if ((obj->flags & 4) == 0) {
        return;
    }
    func_020359b0(obj);
    if (obj->flags & 2) {
        func_02035c48(obj);
    }
    Obj_ShutdownBase_02035554((u8 *)obj + 0x10);
    obj->flags = 0;
}
