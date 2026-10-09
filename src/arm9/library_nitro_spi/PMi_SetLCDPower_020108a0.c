#include "nitro/types.h"

typedef struct PMiWork {
    u32 pad_00;
    u32 lcdOffCount;
    u32 lcdOnCount;
    u32 pad_0c[2];
    u32 ampStatus;
} PMiWork;

extern PMiWork data_020597c0;

extern void func_020049b4(u32 cycles);
extern void PMi_WaitVBlank_02010220(void);
extern u32 func_02010468(u32 led, void *callback, void *arg);
extern u32 PMi_SetLED_020104a0(u32 led);
extern u32 PMi_SetAmp_020105a8(u32 status);

#define VBLANK_COUNT (*(vu32 *)0x02fffc3c)
#define REG_POWCNT (*(vu16 *)0x04000304)

BOOL PMi_SetLCDPower_020108a0(int sw, u32 led, BOOL skip, BOOL isSync)
{
    switch (sw) {
    case 1:
        if (!skip && VBLANK_COUNT - data_020597c0.lcdOffCount <= 7) {
            return FALSE;
        }
        if (led != 0) {
            if (isSync) {
                while (PMi_SetLED_020104a0(led) != 0) {
                    func_020049b4(0x51d23);
                }
            } else {
                while (func_02010468(led, NULL, NULL) != 0) {
                    func_020049b4(0x51d23);
                }
            }
        }
        REG_POWCNT |= 1;
        while (PMi_SetAmp_020105a8(data_020597c0.ampStatus) != 0) {
            func_020049b4(0x51d23);
        }
        break;
    case 0:
        while (PMi_SetAmp_020105a8(0) != 0) {
            func_020049b4(0x51d23);
        }
        if (VBLANK_COUNT - data_020597c0.lcdOnCount <= 2) {
            PMi_WaitVBlank_02010220();
            PMi_WaitVBlank_02010220();
        }
#ifdef KH_RECODED_EU
        REG_POWCNT &= 0xfffe;
#else
        REG_POWCNT &= ~1;
#endif
        data_020597c0.lcdOffCount = VBLANK_COUNT;
        if (led != 0) {
            if (isSync) {
                while (PMi_SetLED_020104a0(led) != 0) {
                    func_020049b4(0x51d23);
                }
            } else {
                while (func_02010468(led, NULL, NULL) != 0) {
                    func_020049b4(0x51d23);
                }
            }
        }
        break;
    }
    return TRUE;
}
