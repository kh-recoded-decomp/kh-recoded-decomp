#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct { fx32 _00, _01, _10, _11; } AffineMtx22;

#define reg_GX_DISPCNT      (*(vu32 *)0x04000000)
#define reg_G2_BG0CNT       (*(vu16 *)0x04000008)
#define reg_G2_BG1CNT       (*(vu16 *)0x0400000a)
#define reg_G2_BG2CNT       (*(vu16 *)0x0400000c)
#define reg_G2_BG3CNT       (*(vu16 *)0x0400000e)
#define reg_G2_BG0OFS       (*(vu32 *)0x04000010)
#define reg_G2_BG1OFS       (*(vu32 *)0x04000014)
#define reg_G2_BG2OFS       (*(vu32 *)0x04000018)
#define reg_G2_BG3OFS       (*(vu32 *)0x0400001c)
#define reg_G2_BG2PA        (*(vu16 *)0x04000020)
#define reg_G2_BG3PA        (*(vu16 *)0x04000030)
#define reg_G2_BLDCNT       (*(vu16 *)0x04000050)
#define reg_GXS_DB_DISPCNT  (*(vu32 *)0x04001000)
#define reg_G2S_DB_BG0CNT   (*(vu16 *)0x04001008)
#define reg_G2S_DB_BG1CNT   (*(vu16 *)0x0400100a)
#define reg_G2S_DB_BG2CNT   (*(vu16 *)0x0400100c)
#define reg_G2S_DB_BG3CNT   (*(vu16 *)0x0400100e)
#define reg_G2S_DB_BG0OFS   (*(vu32 *)0x04001010)
#define reg_G2S_DB_BG1OFS   (*(vu32 *)0x04001014)
#define reg_G2S_DB_BG2OFS   (*(vu32 *)0x04001018)
#define reg_G2S_DB_BG3OFS   (*(vu32 *)0x0400101c)
#define reg_G2S_DB_BG2PA    (*(vu16 *)0x04001020)
#define reg_G2S_DB_BG3PA    (*(vu16 *)0x04001030)
#define reg_G2S_DB_BLDCNT   (*(vu16 *)0x04001050)

extern void apply_pending_display_vram_mode_02006680(void);
extern u32 func_02008ecc(void);
extern u32 func_02008ee0(void);
extern u32 func_02008e5c(void);
extern u32 GX_ResetBankForBGExtPltt_02008e84(void);
extern u32 func_02008e70(void);
extern u32 GX_ResetBankForOBJExtPltt_02008ea8(void);
extern u32 func_02008f08(void);
extern u32 func_02008f1c(void);
extern u32 GX_ResetBankForSubBGExtPltt_02008f30(void);
extern u32 GX_ResetBankForSubOBJExtPltt_02008f58(void);
extern void GX_SetBankForLCDC_02008a74(int banks);
extern u32 func_02008ef4(void);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);
extern void MTX_Identity22_02005930(AffineMtx22 *mtx);
extern void G2x_SetBGyAffine_020067b0(vu16 *reg, const AffineMtx22 *mtx, int centerX, int centerY, int x, int y);
extern void G3X_SetClearColor_02006c08(int rgb, int alpha, int depth, int polygonID, int fog);

static inline void GXS_DispOn(void)
{
    reg_GXS_DB_DISPCNT |= 0x10000;
}

static inline void GX_SetVisiblePlane(int plane)
{
    reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0x1f00) | (plane << 8);
}

static inline void GXS_SetVisiblePlane(int plane)
{
    reg_GXS_DB_DISPCNT = (reg_GXS_DB_DISPCNT & ~0x1f00) | (plane << 8);
}

static inline void GX_SetVisibleWnd(int window)
{
    reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0xe000) | (window << 13);
}

static inline void GXS_SetVisibleWnd(int window)
{
    reg_GXS_DB_DISPCNT = (reg_GXS_DB_DISPCNT & ~0xe000) | (window << 13);
}

#define BG_OFFSET(h, v) ((u32)((((h) << 0) & 0x1ff) | (((v) << 16) & 0x1ff0000)))
#define BG_PRIORITY(reg, p) ((reg) = (u16)(((reg) & ~3) | ((p) << 0)))

void ResetDisplayHardware_02029bfc(void)
{
    AffineMtx22 identity;

    apply_pending_display_vram_mode_02006680();
    GXS_DispOn();
    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);

    func_02008ecc();
    func_02008ee0();
    func_02008e5c();
    GX_ResetBankForBGExtPltt_02008e84();
    func_02008e70();
    GX_ResetBankForOBJExtPltt_02008ea8();
    func_02008f08();
    func_02008f1c();
    GX_ResetBankForSubBGExtPltt_02008f30();
    GX_ResetBankForSubOBJExtPltt_02008f58();

    GX_SetBankForLCDC_02008a74(0x1ff);
    MIi_CpuClearFast_01ff8740(0, (void *)0x06800000, 0xa4000);
    func_02008ef4();

    MIi_CpuClearFast_01ff8740(0, (void *)0x05000000, 0x400);
    MIi_CpuClearFast_01ff8740(0, (void *)0x05000400, 0x400);
    MIi_CpuClearFast_01ff8740(0xc0, (void *)0x07000000, 0x400);
    MIi_CpuClearFast_01ff8740(0xc0, (void *)0x07000400, 0x400);

    reg_G2_BG0OFS = BG_OFFSET(0, 0);
    reg_G2_BG1OFS = BG_OFFSET(0, 0);
    reg_G2_BG2OFS = BG_OFFSET(0, 0);
    reg_G2_BG3OFS = BG_OFFSET(0, 0);
    reg_G2S_DB_BG0OFS = BG_OFFSET(0, 0);
    reg_G2S_DB_BG1OFS = BG_OFFSET(0, 0);
    reg_G2S_DB_BG2OFS = BG_OFFSET(0, 0);
    reg_G2S_DB_BG3OFS = BG_OFFSET(0, 0);

    MTX_Identity22_02005930(&identity);
    G2x_SetBGyAffine_020067b0(&reg_G2_BG2PA, &identity, 0, 0, 0, 0);
    G2x_SetBGyAffine_020067b0(&reg_G2_BG3PA, &identity, 0, 0, 0, 0);
    G2x_SetBGyAffine_020067b0(&reg_G2S_DB_BG2PA, &identity, 0, 0, 0, 0);
    G2x_SetBGyAffine_020067b0(&reg_G2S_DB_BG3PA, &identity, 0, 0, 0, 0);

    BG_PRIORITY(reg_G2_BG0CNT, 0);
    BG_PRIORITY(reg_G2_BG1CNT, 1);
    BG_PRIORITY(reg_G2_BG2CNT, 2);
    BG_PRIORITY(reg_G2_BG3CNT, 3);
    BG_PRIORITY(reg_G2S_DB_BG0CNT, 0);
    BG_PRIORITY(reg_G2S_DB_BG1CNT, 1);
    BG_PRIORITY(reg_G2S_DB_BG2CNT, 2);
    BG_PRIORITY(reg_G2S_DB_BG3CNT, 3);

    GX_SetVisibleWnd(0);
    GXS_SetVisibleWnd(0);
    reg_G2_BLDCNT = 0;
    reg_G2S_DB_BLDCNT = 0;
    G3X_SetClearColor_02006c08(0, 0, 0x7fff, 0, 0);
}
