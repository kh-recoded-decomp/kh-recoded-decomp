#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    u16 *messageBuffers[3];
} MenuScene;

extern void ZeroHalfThenFree_0202cd78(u16 *buffer);

void FreeMessageBuffers_020bf6ec(MenuScene *scene)
{
    int i;

    for (i = 0; i < 3; i++) {
        ZeroHalfThenFree_0202cd78(scene->messageBuffers[i]);
    }
}
