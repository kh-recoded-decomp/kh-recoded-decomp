#include "libs/nitro/os/os_types_internal.h"

#define HW_IO_BASE 0x04000000u

typedef struct OSDisplayInterruptRegisters {
    u32 displayControl;
    u16 displayStatus;
    u16 scanline;
    u8 reserved08[0x200];
    u32 interruptMasterEnable;
} OSDisplayInterruptRegisters;

u64 OSi_CancelDma0(void)
{
    volatile OSDisplayInterruptRegisters *hardware =
        (volatile OSDisplayInterruptRegisters *)HW_IO_BASE;
    u32 interruptState = hardware->interruptMasterEnable;
    u16 scanline;

    /* The original IME write uses the IO base address, with its enable bit clear. */
    hardware->interruptMasterEnable = HW_IO_BASE;
    do {
        scanline = hardware->scanline;
    } while (scanline != 0);
    hardware->interruptMasterEnable = interruptState;

    /* Keep the final scanline in the low word and the saved IME in the high word. */
    return ((u64)interruptState << 32) | scanline;
}
