#include "nitro/types.h"

extern int CreateObjectSlot_020b6794(void *manager, int animation, int resource, int x, int y, int mode,
                                     int priority, int palette, int enabled);

int CreateDefaultObjectSlot_020b6778(void *manager, int animation, int resource, int x, int y) {
    return CreateObjectSlot_020b6794(manager, animation, resource, x, y, 0, 0, -1, 0);
}
