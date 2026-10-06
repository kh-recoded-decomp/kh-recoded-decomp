#include "nitro/types.h"

extern int CreateObjectSlot_020bdec4(void *manager, int animation, int resource, int x, int y, int mode,
                                     int priority, int palette, int enabled);

int func_ov034_020bdea8(void *manager, int animation, int resource, int x, int y) {
    return CreateObjectSlot_020bdec4(manager, animation, resource, x, y, 0, 0, -1, 0);
}
