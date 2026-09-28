#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    s32 unk_10;
    u32 pxiChannel;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern void func_0204df9c(int flag);
extern void func_ov031_020ba51c(void);
extern void PXI_Init_0202a638(u32 channel);
extern void func_ov001_020667b4(void);
extern void func_ov001_0206a714(void);
extern void ArmObject_0206c6f4(void);
extern void func_ov001_02063c54(void);

/* Tears down the active overlay state. */
void ShutdownActiveState_020ba5d0(void)
{
    func_0204df9c(0);
    func_ov031_020ba51c();
    PXI_Init_0202a638(g_activeState_020bc800->pxiChannel);
    func_ov001_020667b4();
    if (g_activeState_020bc800->unk_10 != -1) {
        func_ov001_0206a714();
        g_activeState_020bc800->unk_10 = -1;
    }
    ArmObject_0206c6f4();
    func_ov001_02063c54();
    g_activeState_020bc800 = 0;
}
