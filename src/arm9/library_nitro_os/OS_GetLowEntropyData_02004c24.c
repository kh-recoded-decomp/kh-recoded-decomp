#include "nitro/types.h"
#include "nitro/os.h"

#define NVRAM_CONFIG_SIZE   0x74
#define SYSTEM_WORK         ((const OSSystemWork *)0x02fffc00)
#define BUTTON_XY_BUF       (*(vu16 *)0x02ffffa8)
#define reg_GX_VCOUNT       (*(vu16 *)0x04000006)
#define reg_G3X_GXSTAT      (*(vu32 *)0x04000600)
#define reg_PAD_KEYINPUT    (*(vu16 *)0x04000130)

extern volatile u64 data_02056e9c;
#define OSi_TickCounter data_02056e9c

extern u16 OS_GetTickLo(void);

static inline u16 GX_GetVCount(void)
{
    return reg_GX_VCOUNT;
}

void OS_GetLowEntropyData_02004c24(u32 buffer[OS_LOW_ENTROPY_DATA_SIZE / sizeof(u32)])
{
    const OSSystemWork *work = SYSTEM_WORK;
    const u8 *macAddress = (u8 *)((u32)(work->nvramUserInfo) + ((NVRAM_CONFIG_SIZE + 3) & ~0x00000003));

    buffer[0] = (u32)((GX_GetVCount() << 16) | OS_GetTickLo());
    buffer[1] = (u32)(*(u16 *)(macAddress + 4) << 16) ^ (u32)(OSi_TickCounter);
    buffer[2] = (u32)(OSi_TickCounter >> 32) ^ *(u32 *)macAddress ^ work->vblankCount;
    buffer[2] ^= reg_G3X_GXSTAT;
    buffer[3] = *(u32 *)(&work->real_time_clock[0]);
    buffer[4] = *(u32 *)(&work->real_time_clock[4]);
    buffer[5] = (((u32)work->mic_sampling_data) << 16) ^ work->mic_last_address;
    buffer[6] = (u32)((*(u16 *)(&work->touch_panel[0]) << 16) | *(u16 *)(&work->touch_panel[2]));
    buffer[7] = (u32)((work->wm_rssi_pool << 16) | (reg_PAD_KEYINPUT | BUTTON_XY_BUF));
}
