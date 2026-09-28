#include "nitro/types.h"
#include "nitro/os_types.h"

typedef void *OSMessage;

#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define REG_POWCNT_OFFSET 0x304
#define REG_POWCNT_ADDR (HW_REG_BASE + REG_POWCNT_OFFSET)
#define HW_IOREG 0x04000000
#define HW_REG_BASE HW_IOREG
#define reg_GX_POWCNT (*( REGType16v *) REG_POWCNT_ADDR)
#define REG_GX_POWCNT_LCD_MASK 0x0001

typedef enum {
    PM_LCD_POWER_OFF = 0,
    PM_LCD_POWER_ON = 1
} PMLCDPower;

PMLCDPower PM_GetLCDPower_02010a08 (void)
{
    return (reg_GX_POWCNT & REG_GX_POWCNT_LCD_MASK) ? PM_LCD_POWER_ON : PM_LCD_POWER_OFF;
}
