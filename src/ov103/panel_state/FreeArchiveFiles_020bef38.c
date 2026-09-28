#include "nitro/types.h"

typedef struct MenuScene {
    u8 pad_00[0x10];
    u16 *archiveFiles[2];
} MenuScene;

extern void ZeroHalfThenFree_0202cd78(u16 *buffer);

void FreeArchiveFiles_020bef38(MenuScene *scene)
{
    int i;

    for (i = 0; i < 2; i++) {
        ZeroHalfThenFree_0202cd78(scene->archiveFiles[i]);
    }
}
