#include "nitro/types.h"

typedef struct {
    u32 slot0;
    u8 pad_04[0x378];
    u32 slot_37c;
} EngineState;

extern u16 g_engineMode_02fffc40;
extern EngineState g_engineState_02fffc20;

extern void RunResetCallbackAndIdle_02004cf0(void);
extern u32 func_020023a0(void);
extern void func_02009150(u16 value);
extern u32 OS_SetIrqMask(u32 mask);
extern u32 OS_ResetRequestIrqMask(u32 mask);
extern void ResetFourChannels_020052dc(void);
extern void OSi_SendToPxi_0200205c(int data);
extern int func_02003d10(void);
extern void func_01ff8310(void);

void func_02004a60(u32 newSlot0)
{
    if (g_engineMode_02fffc40 == 2) {
        RunResetCallbackAndIdle_02004cf0();
    }

    func_02009150((u16)func_020023a0());

    OS_SetIrqMask(0x40000);
    OS_ResetRequestIrqMask(0xfffbffff);
    ResetFourChannels_020052dc();

    g_engineState_02fffc20.slot0 = newSlot0;
    OSi_SendToPxi_0200205c(0x10);
    g_engineState_02fffc20.slot_37c = func_02003d10();

    func_01ff8310();
}
