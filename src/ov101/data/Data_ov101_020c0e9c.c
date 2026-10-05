#include "nitro/types.h"

#pragma explicit_zero_data on

extern void NextItemPage_020bee80(void);
extern void PrevItemPage_020bef1c(void);
extern void SelectItemAfterScrollDown_020bee00(void);
extern void SelectItemAfterScrollUp_020bed80(void);
extern void UpdateStateFrame_020bed04(void);
extern void func_ov101_020beb20(void);
extern void func_ov101_020beca0(void);
extern void func_ov101_020befac(void);
extern void func_ov101_020befd4(void);

void *data_ov101_020c0e9c[17] = {
    (void *)func_ov101_020beb20,
    (void *)func_ov101_020beca0,
    (void *)UpdateStateFrame_020bed04,
    (void *)0x00000009,
    (void *)0x0000CFD8,
    (void *)SelectItemAfterScrollUp_020bed80,
    (void *)SelectItemAfterScrollDown_020bee00,
    (void *)PrevItemPage_020bef1c,
    (void *)NextItemPage_020bee80,
    (void *)NextItemPage_020bee80,
    (void *)func_ov101_020befac,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)func_ov101_020befd4,
};
