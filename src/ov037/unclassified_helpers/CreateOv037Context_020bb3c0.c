#include "nitro/types.h"

typedef struct Ov037Context {
    s16 state;
    u8 pad_02[0x1ce];
    s32 enabled;
    u8 pad_1d4[0x54];
    u64 startTick;
    u8 pad_230[0x04];
} Ov037Context;

extern Ov037Context *g_ov037Context_020bb764;
extern char OverlayId27_0000001b[];
extern void func_02029f78(int target, int overlayId);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern void func_ov037_020bae2c(void);
extern void func_ov037_020bb314(void);
extern void func_ov037_020baebc(void);
extern void func_ov037_020bb0c8(void);
extern void func_ov037_020bafbc(void);
extern void ResetCameraProjectionOverrides_020bb088(void);
extern u64 OS_GetTick_02003fd4(void);

void CreateOv037Context_020bb3c0(void)
{
    if (g_ov037Context_020bb764 != NULL) {
        return;
    }
    func_02029f78(0, (int)OverlayId27_0000001b);
    g_ov037Context_020bb764 = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(Ov037Context));
    func_01ff8830(g_ov037Context_020bb764, 0, sizeof(Ov037Context));
    g_ov037Context_020bb764->state = 0;
    g_ov037Context_020bb764->enabled = 1;
    func_ov037_020bae2c();
    func_ov037_020bb314();
    func_ov037_020baebc();
    func_ov037_020bb0c8();
    func_ov037_020bafbc();
    ResetCameraProjectionOverrides_020bb088();
    g_ov037Context_020bb764->startTick = OS_GetTick_02003fd4();
}
