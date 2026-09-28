#include "nitro/types.h"

typedef struct PMSleepCallbackInfo PMSleepCallbackInfo;

typedef struct {
    s8 activeState;
    u8 pad_01[3];
    s32 unk4;
    u8 pad_08[4];
    s32 initFlag;
    void (*preCallback)(void *arg);
    s32 unk14;
    u8 pad_18[8];
    void *(*postCallback)(void);
    s32 unk24;
} SndGlobalState;

extern SndGlobalState data_0205d864;

extern void func_0200ed90(void);
extern void func_0201d2c0(void *arg);
extern void *PXI_Init_0201d2f8(void);
extern void PM_PrependPreSleepCallback_02010ac0(PMSleepCallbackInfo *info);
extern void PM_AppendPostSleepCallback_02010ad8(PMSleepCallbackInfo *info);
extern void SndCapture_Reset_0201d3f8(void);
extern void func_0201e524(void);
extern void func_0201d8c0(void);

void SndInit_0201d214(void)
{
    if (data_0205d864.initFlag != 0) {
        return;
    }
    data_0205d864.initFlag = 1;
    func_0200ed90();
    data_0205d864.preCallback = func_0201d2c0;
    data_0205d864.unk14 = 0;
    data_0205d864.postCallback = PXI_Init_0201d2f8;
    data_0205d864.unk24 = 0;
    PM_PrependPreSleepCallback_02010ac0((PMSleepCallbackInfo *)&data_0205d864.preCallback);
    PM_AppendPostSleepCallback_02010ad8((PMSleepCallbackInfo *)&data_0205d864.postCallback);
    SndCapture_Reset_0201d3f8();
    func_0201e524();
    func_0201d8c0();
    data_0205d864.activeState = -1;
    data_0205d864.unk4 = 1;
}
