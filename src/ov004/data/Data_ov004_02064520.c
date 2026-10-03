#include "nitro/types.h"

extern void PXI_Init_020622e4(void);
extern void UpdateScrollTextFadeOut_02062530(void);
extern void func_ov004_020622f0(void);
extern void func_ov004_0206252c(void);

void (*data_ov004_02064520[4])(void) = {
    PXI_Init_020622e4,
    func_ov004_020622f0,
    UpdateScrollTextFadeOut_02062530,
    func_ov004_0206252c,
};
