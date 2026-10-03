#include "nitro/types.h"

extern void G2S_GetBG0ScrPtr_02006e14(void);
extern void G2S_GetBG1ScrPtr_02006e68(void);
extern void G2S_GetBG2ScrPtr_02006f0c(void);
extern void G2S_GetBG3ScrPtr_02007004(void);
extern void G2_GetBG0ScrPtr_02006de0(void);
extern void G2_GetBG1ScrPtr_02006e34(void);
extern void G2_GetBG2ScrPtr_02006e88(void);
extern void G2_GetBG3ScrPtr_02006f80(void);
extern void GXS_LoadBG0Char_02007940(void);
extern void GXS_LoadBG0Scr_020075c0(void);
extern void GXS_LoadBG1Char_02007a20(void);
extern void GXS_LoadBG1Scr_020076a0(void);
extern void GXS_LoadBG2Char_02007b00(void);
extern void GXS_LoadBG2Scr_02007780(void);
extern void GXS_LoadBG3Char_02007be0(void);
extern void GXS_LoadBG3Scr_02007860(void);
extern void GXS_LoadBGPltt_020072b4(void);
extern void GX_LoadBG0Char_020078d0(void);
extern void GX_LoadBG0Scr_02007550(void);
extern void GX_LoadBG1Char_020079b0(void);
extern void GX_LoadBG1Scr_02007630(void);
extern void GX_LoadBG2Char_02007a90(void);
extern void GX_LoadBG2Scr_02007710(void);
extern void GX_LoadBG3Char_02007b70(void);
extern void GX_LoadBG3Scr_020077f0(void);
extern void SetEngineBBG2Control(void);
extern void SetEngineBBG3Control(void);
extern void func_02007250(void);
extern void func_0202acf0(void);
extern void func_0202ad24(void);
extern void func_0202ad58(void);
extern void func_0202ad84(void);
extern void func_0202adb0(void);

void (*const data_02055774[44])(void) = {
    GX_LoadBG0Char_020078d0,
    func_02007250,
    func_0202adb0,
    NULL,
    G2_GetBG1ScrPtr_02006e34,
    GX_LoadBG1Scr_02007630,
    GX_LoadBG1Char_020079b0,
    func_02007250,
    NULL,
    func_0202ad84,
    G2_GetBG2ScrPtr_02006e88,
    GX_LoadBG2Scr_02007710,
    GX_LoadBG2Char_02007a90,
    func_02007250,
    NULL,
    func_0202ad58,
    G2_GetBG3ScrPtr_02006f80,
    GX_LoadBG3Scr_020077f0,
    GX_LoadBG3Char_02007b70,
    func_02007250,
    func_0202ad24,
    NULL,
    G2S_GetBG0ScrPtr_02006e14,
    GXS_LoadBG0Scr_020075c0,
    GXS_LoadBG0Char_02007940,
    GXS_LoadBGPltt_020072b4,
    func_0202acf0,
    NULL,
    G2S_GetBG1ScrPtr_02006e68,
    GXS_LoadBG1Scr_020076a0,
    GXS_LoadBG1Char_02007a20,
    GXS_LoadBGPltt_020072b4,
    NULL,
    SetEngineBBG2Control,
    G2S_GetBG2ScrPtr_02006f0c,
    GXS_LoadBG2Scr_02007780,
    GXS_LoadBG2Char_02007b00,
    GXS_LoadBGPltt_020072b4,
    NULL,
    SetEngineBBG3Control,
    G2S_GetBG3ScrPtr_02007004,
    GXS_LoadBG3Scr_02007860,
    GXS_LoadBG3Char_02007be0,
    GXS_LoadBGPltt_020072b4,
};

void (*const data_0205576c[2])(void) = {
    G2_GetBG0ScrPtr_02006de0,
    GX_LoadBG0Scr_02007550,
};
