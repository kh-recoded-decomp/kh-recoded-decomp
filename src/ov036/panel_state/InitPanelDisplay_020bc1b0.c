#include "nitro/types.h"

typedef u32 (*TexVramAllocFunc)(u32 size, BOOL is4x4, u32 opt);
typedef int (*TexVramFreeFunc)(u32 key);

typedef struct PanelVramWork {
    void *texManagerWork;
    void *scene;
    void *plttManagerWork;
} PanelVramWork;

extern PanelVramWork data_ov036_020c3920;
extern TexVramAllocFunc data_02055c4c;
extern TexVramFreeFunc data_02055c50;
extern void GX_SetBankForTex_02008820(int tex);
extern void GX_BeginLoadOBJExtPltt_02008998(int bank);
extern int func_020144e8(int value);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void InitRangeManagerConfig_020144f0(u32 size, u32 base, void *work, u32 workSize, int installCallbacks);
extern int func_02014850(int value);
extern void InitRangeManagerConfig_02014858(u32 size, void *work, u32 workSize, int installCallbacks);
extern void G2x_SetBlendAlpha_02006850(vu16 *reg, int plane1, int plane2, int ev1, int ev2);
extern void G3X_SetClearColor_02006c08(u32 color, u32 alpha, u32 depth, u32 polygonId, BOOL fog);
extern void func_02007250(const void *src, u32 offset, u32 size);

#define REG_DISP3DCNT (*(vu16 *)0x04000060)
#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_DB_DISPCNT (*(vu32 *)0x04001000)
#define REG_DB_BG0CNT (*(vu16 *)0x04001008)

void InitPanelDisplay_020bc1b0(void)
{
    u16 backdropColor = 0;
    u32 workSize;
    u32 key0;
    u32 key1;
    u32 key2;

    REG_DISP3DCNT = (u16)(REG_DISP3DCNT & ~0x3002);
    REG_DISP3DCNT &= (u16)~0x3004;
    REG_DISP3DCNT = (u16)((REG_DISP3DCNT & ~0x3000) | 0x8);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1f00;
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1100;
    GX_SetBankForTex_02008820(7);
    GX_BeginLoadOBJExtPltt_02008998(0x60);
    workSize = func_020144e8(0x60);
    data_ov036_020c3920.texManagerWork = NNSi_FndAllocFromDefaultHeap_0202a178(workSize);
    InitRangeManagerConfig_020144f0(0x60000, 0, data_ov036_020c3920.texManagerWork, workSize, TRUE);
    key0 = data_02055c4c(0x20000, FALSE, 0);
    key1 = data_02055c4c(0x20000, FALSE, 0);
    key2 = data_02055c4c(0x20000, FALSE, 0);
    data_02055c50(key0);
    data_02055c50(key1);
    data_02055c50(key2);
    workSize = func_02014850(0x20);
    data_ov036_020c3920.plttManagerWork = NNSi_FndAllocFromDefaultHeap_0202a178(workSize);
    InitRangeManagerConfig_02014858(0x8000, data_ov036_020c3920.plttManagerWork, workSize, TRUE);
    REG_DB_BG0CNT = (u16)((REG_DB_BG0CNT & 0x43) | 0x210);
    G2x_SetBlendAlpha_02006850((vu16 *)0x04000050, 1, 0x22, 0, 0x10);
    G3X_SetClearColor_02006c08(0, 0, 0x7fff, 0x3f, FALSE);
    func_02007250(&backdropColor, 0, sizeof(backdropColor));
}
