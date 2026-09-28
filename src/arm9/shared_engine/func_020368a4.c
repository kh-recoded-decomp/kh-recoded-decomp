#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0A[6];
    u32 sub;
} Container;

extern void Obj_ConditionalShutdown_020368c8(Container *obj, int arg);
extern u8 *g_recordTablePtr_0206083c;

void func_020368a4(int index) {
    Container **slots = (Container **)(g_recordTablePtr_0206083c + 0x20);
    Obj_ConditionalShutdown_020368c8(slots[index], index);
}
