#include "nitro/types.h"

typedef struct {
    u32 initialized;
    u32 hasMainExArena;
} OSiArenaInfo;

extern OSiArenaInfo data_02056dc4;
extern u32 func_02002ed8(void);

void *OS_GetInitArenaLo_02003784(int arenaId)
{
    switch (arenaId) {
    case 0:
        return (void *)0x020d9c20;
    case 2:
        if (data_02056dc4.hasMainExArena == 0) {
            return NULL;
        }
        if ((func_02002ed8() & 0xf) == 1) {
            return NULL;
        }
        return (void *)0x023e0000;
    case 3:
        return (void *)0x01fffec0;
    case 4:
        return (void *)0x027e0280;
    case 5:
        return (void *)0x02fff000;
    case 6:
        return (void *)0x037f8000;
    }
    return NULL;
}
