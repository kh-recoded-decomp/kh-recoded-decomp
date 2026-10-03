#include "nitro/types.h"

extern void G2_GetBG1ScrPtr_02006e34(void);
extern void G2_GetBG2ScrPtr_02006e88(void);
extern void G2_GetBG3ScrPtr_02006f80(void);
extern void UpdateHudNoticeMessage_020705a4(void);
extern void UpdateSceneSlideOut_020708f4(void);
extern void _fp_init_020708f0(void);
extern void func_ov001_02070870(void);

void (*data_ov001_0209eccc[4])(void) = {
    UpdateHudNoticeMessage_020705a4,
    func_ov001_02070870,
    _fp_init_020708f0,
    UpdateSceneSlideOut_020708f4,
};

void (*data_ov001_0209ecc0[3])(void) = {
    G2_GetBG1ScrPtr_02006e34,
    G2_GetBG2ScrPtr_02006e88,
    G2_GetBG3ScrPtr_02006f80,
};
