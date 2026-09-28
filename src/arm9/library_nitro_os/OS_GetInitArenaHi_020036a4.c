#include "nitro/types.h"

typedef struct {
    u32 initialized;
    u32 hasMainExArena;
} OSiArenaInfo;

extern OSiArenaInfo data_02056dc4;
extern unsigned char data_027e0000[];
extern void SDK_SYS_STACKSIZE_00000000(void);
extern void SDK_IRQ_STACKSIZE_00000800(void);
extern u32 func_02002ed8(void);

#define OSi_SYS_STACKSIZE ((s32)SDK_SYS_STACKSIZE_00000000)
#define OSi_IRQ_STACKSIZE ((s32)SDK_IRQ_STACKSIZE_00000800)
#define HW_DTCM ((u32)data_027e0000)
#define OSi_DTCM_ARENA_LO_DEFAULT 0x027e0280

void *OS_GetInitArenaHi_020036a4(int arenaId)
{
    switch (arenaId) {
    case 0:
        return (void *)0x023e0000;
    case 2:
        if (data_02056dc4.hasMainExArena == 0) {
            return NULL;
        }
        if ((func_02002ed8() & 0xf) == 1) {
            return NULL;
        }
        return (void *)0x02700000;
    case 3:
        return (void *)0x02000000;
    case 4: {
        u32 irqStackLo;
        u32 sysStackLo;

        irqStackLo = HW_DTCM + 0x3f80 - OSi_IRQ_STACKSIZE;

        if (OSi_SYS_STACKSIZE == 0) {
            sysStackLo = HW_DTCM;
            if (sysStackLo < OSi_DTCM_ARENA_LO_DEFAULT) {
                sysStackLo = OSi_DTCM_ARENA_LO_DEFAULT;
            }
        } else if (OSi_SYS_STACKSIZE < 0) {
            sysStackLo = OSi_DTCM_ARENA_LO_DEFAULT - OSi_SYS_STACKSIZE;
        } else {
            sysStackLo = irqStackLo - OSi_SYS_STACKSIZE;
        }
        return (void *)sysStackLo;
    }
    case 5:
        return (void *)0x02fff680;
    case 6:
        return (void *)0x037f8000;
    }
    return NULL;
}
