#include "nitro/types.h"

extern void func_020049b4(u32 cycles);
extern int PM_GetLCDPower_02010a08(void);
extern int PM_SetBackLight_02010518(int target, int sw);
extern int func_020109e4(int sw);
extern u32 data_02055c44;

/* prepares the LCD before a forced power-off */
void PMi_PrepareForcePowerOff_02010b24(void)
{
    u32 saved;
    int result;

    func_020049b4(0x360000);
    saved = data_02055c44;
    data_02055c44 = 0xe;
    result = PM_GetLCDPower_02010a08();
    if (result != 1) {
        result = PM_SetBackLight_02010518(2, 0);
        while (result != 0) {
            func_020049b4(0x51d23);
            result = PM_SetBackLight_02010518(2, 0);
        }
        result = func_020109e4(1);
        while (result == 0) {
            func_020049b4(5);
            result = func_020109e4(1);
        }
    }
    data_02055c44 = saved;
}
