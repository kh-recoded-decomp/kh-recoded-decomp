#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    void *messageData;
    u8 pad_10[0x23a9c - 0x10];
    void *mainFontFile;
    u8 pad_23aa0[0x23aa8 - 0x23aa0];
    void *subFontFile;
    u8 pad_23aac[0x23ac4 - 0x23aac];
    u32 unk_23ac4_0 : 1;
    u32 loading : 1;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals g_scrollText_020645a0;
extern char data_ov004_02064544[];
extern char data_ov004_02064550[];
extern char data_ov004_02064564[];

extern void SetBrightnessAndSyncMain_02029e7c(int value);
extern void SetSecondaryBrightness_02029ed0(int value);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void *func_0202c364(const char *path, u32 mode);
extern void InitTitleDisplay_02063218(void);
extern void func_ov004_0206366c(void);
extern int func_0202c438(void);
extern void func_ov004_02063598(void);
extern void InitScrollTextLayers_02063a28(void);
extern void func_ov004_02063aec(void);
extern u32 func_0202a794(u32 argument0);
extern void G2x_SetBlendBrightness_0200686c(u32 regAddr, int plane, int brightness);
extern void func_ov004_02062034(void);
extern void func_ov004_020629d0(void);

void *LoadScrollTextResources_02061598(void)
{
    SetBrightnessAndSyncMain_02029e7c(-16);
    SetSecondaryBrightness_02029ed0(-16);
    g_scrollText_020645a0.work->messageData = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov004_02064544, 0xe, FALSE);
    g_scrollText_020645a0.work->mainFontFile = func_0202c364(data_ov004_02064550, 0xe);
    g_scrollText_020645a0.work->subFontFile = func_0202c364(data_ov004_02064564, 0xe);
    InitTitleDisplay_02063218();
    func_ov004_0206366c();
    func_0202c438();
    func_ov004_02063598();
    InitScrollTextLayers_02063a28();
    func_ov004_02063aec();
    func_0202a794(0);
    G2x_SetBlendBrightness_0200686c(0x04000050, 4, -16);
    G2x_SetBlendBrightness_0200686c(0x04001050, 4, -16);
    SetBrightnessAndSyncMain_02029e7c(0);
    SetSecondaryBrightness_02029ed0(0);
    func_ov004_02062034();
    g_scrollText_020645a0.work->loading = 0;
    return func_ov004_020629d0;
}
