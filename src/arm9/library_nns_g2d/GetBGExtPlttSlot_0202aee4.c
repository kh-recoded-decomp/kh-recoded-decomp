#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nnsys/g2d.h"

typedef void *OSMessage;

#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define HW_IOREG 0x04000000
#define HW_REG_BASE HW_IOREG
#define REG_BG0CNT_OFFSET 0x008
#define REG_BG1CNT_OFFSET 0x00a
#define REG_G2_BG0CNT_BGPLTTSLOT_MASK 0x2000
#define REG_DB_BG0CNT_OFFSET 0x1008
#define REG_DB_BG1CNT_OFFSET 0x100a

extern const u16 data_0205556c[8];

NNSG2dBGExtPlttSlot GetBGExtPlttSlot_0202aee4 (NNSG2dBGSelect bg)
{
    u32 addr;
    NNSG2dBGExtPlttSlot slot = (NNSG2dBGExtPlttSlot)bg;

    addr = data_0205556c[bg];

    if (addr != 0) {
        addr += HW_REG_BASE;

        if ((*(u16 *)addr & REG_G2_BG0CNT_BGPLTTSLOT_MASK) != 0) {
            slot += 2;
        }
    }

    return slot;
}
