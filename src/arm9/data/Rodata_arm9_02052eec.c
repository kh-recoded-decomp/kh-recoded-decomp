#include "nitro/types.h"

extern void AllocatorAllocForFrmHeap_02013674(void);
extern void AllocatorFreeForSDKHeap_020136e0(void);
extern void AllocatorFreeForSDKHeap_020136fc(void);
extern void AllocatorFreeForUnitHeap_02013688(void);
extern void GXS_LoadBG0Char_02007940(void);
extern void GXS_LoadBG0Scr_020075c0(void);
extern void GXS_LoadBG1Char_02007a20(void);
extern void GXS_LoadBG1Scr_020076a0(void);
extern void GXS_LoadBG2Char_02007b00(void);
extern void GXS_LoadBG2Scr_02007780(void);
extern void GXS_LoadBG3Char_02007be0(void);
extern void GXS_LoadBG3Scr_02007860(void);
extern void GXS_LoadBGPltt_020072b4(void);
extern void GXS_LoadOAM_0200742c(void);
extern void GXS_LoadOBJPltt_0200736c(void);
extern void GX_LoadBG0Char_020078d0(void);
extern void GX_LoadBG0Scr_02007550(void);
extern void GX_LoadBG1Char_020079b0(void);
extern void GX_LoadBG1Scr_02007630(void);
extern void GX_LoadBG2Char_02007a90(void);
extern void GX_LoadBG2Scr_02007710(void);
extern void GX_LoadBG3Char_02007b70(void);
extern void GX_LoadBG3Scr_020077f0(void);
extern void GX_LoadOBJPltt_02007310(void);
extern void func_02007250(void);
extern void func_020073c8(void);
extern void func_02007488(void);
extern void func_020074ec(void);
extern void func_02013ddc(void);
extern void func_02013e08(void);
extern void func_02013e34(void);
extern void func_02013e60(void);
extern void func_02013e8c(void);
extern void func_02013eb8(void);

void (*const data_02052efc[36])(void) = {
    func_02013ddc,
    func_02013e08,
    NULL,
    NULL,
    GX_LoadBG0Char_020078d0,
    GX_LoadBG1Char_020079b0,
    GX_LoadBG2Char_02007a90,
    GX_LoadBG3Char_02007b70,
    GX_LoadBG0Scr_02007550,
    GX_LoadBG1Scr_02007630,
    GX_LoadBG2Scr_02007710,
    GX_LoadBG3Scr_020077f0,
    NULL,
    NULL,
    GX_LoadOBJPltt_02007310,
    func_02007250,
    func_02013e34,
    func_02013e60,
    func_020073c8,
    func_02007488,
    GXS_LoadBG0Char_02007940,
    GXS_LoadBG1Char_02007a20,
    GXS_LoadBG2Char_02007b00,
    GXS_LoadBG3Char_02007be0,
    GXS_LoadBG0Scr_020075c0,
    GXS_LoadBG1Scr_020076a0,
    GXS_LoadBG2Scr_02007780,
    GXS_LoadBG3Scr_02007860,
    NULL,
    NULL,
    GXS_LoadOBJPltt_0200736c,
    GXS_LoadBGPltt_020072b4,
    func_02013e8c,
    func_02013eb8,
    GXS_LoadOAM_0200742c,
    func_020074ec,
};

void (*const data_02052eec[4])(void) = {
    AllocatorAllocForFrmHeap_02013674,
    AllocatorFreeForUnitHeap_02013688,
    AllocatorFreeForSDKHeap_020136e0,
    AllocatorFreeForSDKHeap_020136fc,
};
