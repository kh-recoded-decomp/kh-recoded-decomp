#include "nitro/types.h"

typedef struct PMSleepCallbackInfo PMSleepCallbackInfo;

typedef struct PMSleepState {
    u8 pad_00[0xc];
    volatile BOOL sleepEndFlag;
    PMSleepCallbackInfo *preSleepList;
    u8 pad_14[4];
    PMSleepCallbackInfo *postSleepList;
} PMSleepState;

extern PMSleepState data_020597c0;

extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern u32 OS_DisableIrqMask(u32 mask);
extern u32 OS_SetIrqMask(u32 mask);
extern u32 func_02003f5c(void);
extern void func_020049b4(int cycles);
extern u16 GetU16Field_020049f0(void);
extern BOOL func_02012364(void);
extern void func_02004d30(void);
extern void PMi_ExecuteList_02010aac(PMSleepCallbackInfo *listp);
extern u32 PM_GetLCDPower_02010a08(void);
extern u32 PM_GetBackLight_020105c8(u32 *top, u32 *bottom);
extern u32 PM_SetBackLight_02010518(int target, int sw);
extern void PMi_WaitVBlank_02010220(void);
extern void func_02010624(void);
extern u32 func_020103bc(u16 trigger, u16 keyIntrData);
extern BOOL func_020108a0(int sw, int led, BOOL skip, BOOL isSync);
extern u32 PMi_SetLED_020104a0(int status);
extern void ForcePowerOffAndHalt_0201057c(void);

#define reg_OS_IME (*(volatile u16 *)0x04000208)
#define reg_OS_IF (*(volatile u32 *)0x04000214)
#define reg_GX_DISPCNT (*(volatile u32 *)0x04000000)
#define reg_GXS_DB_DISPCNT (*(volatile u32 *)0x04001000)

static inline BOOL OS_DisableIrq(void)
{
    u16 prep = reg_OS_IME;
    reg_OS_IME = 0;
    return (BOOL)prep;
}

static inline BOOL OS_EnableIrq(void)
{
    u16 prep = reg_OS_IME;
    reg_OS_IME = 1;
    return (BOOL)prep;
}

static inline BOOL OS_RestoreIrq(BOOL enable)
{
    u16 prep = reg_OS_IME;
    reg_OS_IME = (u16)enable;
    return (BOOL)prep;
}

static inline void GXS_DispOff(void)
{
    reg_GXS_DB_DISPCNT &= ~0x10000;
}

void PM_GoSleepMode_02010690(u32 trigger, u32 logic, u16 keyPattern)
{
    BOOL prepIrq;
    u32 prepIntrMode;
    u32 prepIntrMask;
    BOOL powerOffFlag = FALSE;
    u32 preTop;
    u32 preBottom;
    u32 preGX;
    u32 preGXS;
    u32 preLCDPower;
    u32 topRecover;
    u32 bottomRecover;

    PMi_ExecuteList_02010aac(data_020597c0.preSleepList);

    prepIrq = OS_DisableIrq();
    prepIntrMode = func_02004938();
    prepIntrMask = OS_DisableIrqMask(0x3fffff);

    {
        u32 intr = 0x40000 | (func_02003f5c() ? 8 : 0);
        OS_SetIrqMask(intr);
    }

    func_0200494c(prepIntrMode);
    OS_EnableIrq();

    if (trigger & 8) {
        u16 bootType = GetU16Field_020049f0();
        if (bootType == 2 || bootType == 3) {
            trigger &= ~8;
        }
    }

    if (trigger & 0x10) {
        if (!func_02012364()) {
            trigger &= ~0x10;
        }
    }

    preGX = reg_GX_DISPCNT;
    preGXS = reg_GXS_DB_DISPCNT;
    preLCDPower = PM_GetLCDPower_02010a08();

    while (PM_GetBackLight_020105c8(&preTop, &preBottom) != 0) {
        func_020049b4(0x51d23);
    }

    while (PM_SetBackLight_02010518(2, 0) != 0) {
        func_020049b4(0x51d23);
    }

    PMi_WaitVBlank_02010220();
    reg_GX_DISPCNT = reg_GX_DISPCNT & ~0x30000;
    GXS_DispOff();
    PMi_WaitVBlank_02010220();
    PMi_WaitVBlank_02010220();

    func_02010624();

    data_020597c0.sleepEndFlag = FALSE;
    bottomRecover = preBottom ? 0x80 : 0;
    topRecover = preTop ? 0x40 : 0;

    OS_SetIrqMask(0x40000);
    func_020103bc((u16)(trigger | topRecover | bottomRecover), (u16)(logic | keyPattern));

    while (!data_020597c0.sleepEndFlag) {
        func_02004d30();
    }

    {
        u32 intr = 0x40000 | (func_02003f5c() ? 8 : 0);
        OS_SetIrqMask(intr);
    }

    if ((trigger & 8) && (reg_OS_IF & 0x100000)) {
        powerOffFlag = TRUE;
    }

    if (!powerOffFlag) {
        if (preLCDPower == 1) {
            while (func_020108a0(1, 1, TRUE, TRUE) != TRUE) {
            }
        } else {
            while (PMi_SetLED_020104a0(1) != 0) {
                func_020049b4(0x51d23);
            }
        }

        reg_GX_DISPCNT = preGX;
        reg_GXS_DB_DISPCNT = preGXS;
    }

    func_020049b4(0x360000);

    OS_DisableIrq();
    OS_SetIrqMask(prepIntrMask);
    func_0200494c(prepIntrMode);
    OS_RestoreIrq(prepIrq);

    if (powerOffFlag) {
        ForcePowerOffAndHalt_0201057c();
    }

    PMi_ExecuteList_02010aac(data_020597c0.postSleepList);
}
