typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

typedef void (*MIDmaCallback)(void *);
#define GX_DMA_NOT_USE      ((u32) ~0)
#define GX_CPU_FASTER32_SIZE 0x30
#define HW_OBJ_VRAM         0x06400000
#define HW_DB_OBJ_VRAM      0x06600000
#define HW_LCDC_VRAM_E      0x06880000
#define HW_LCDC_VRAM_F      0x06890000
#define HW_LCDC_VRAM_G      0x06894000
typedef enum {
    GX_VRAM_BGEXTPLTT_NONE    = 0x0000,
    GX_VRAM_BGEXTPLTT_01_F    = 0x0020,
    GX_VRAM_BGEXTPLTT_23_G    = 0x0040,
    GX_VRAM_BGEXTPLTT_0123_E  = 0x0010,
    GX_VRAM_BGEXTPLTT_0123_FG = 0x0060
} GXVRamBGExtPltt;
typedef enum {
    GX_VRAM_OBJEXTPLTT_NONE = 0x0000,
    GX_VRAM_OBJEXTPLTT_0_F  = 0x0020,
    GX_VRAM_OBJEXTPLTT_0_G  = 0x0040
} GXVRamOBJExtPltt;
typedef int GXVRamTex;

extern u32 data_020422b8;
#define GXi_DmaId data_020422b8
extern void MI_DmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);
extern void MI_DmaCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size, MIDmaCallback callback, void *arg);
extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);
#define MI_CpuCopy32 MIi_CpuCopy32

extern GXVRamBGExtPltt GX_DisableBankForBGExtPltt(void);
#define GX_ResetBankForBGExtPltt GX_DisableBankForBGExtPltt
extern GXVRamOBJExtPltt GX_DisableBankForOBJExtPltt(void);
#define GX_ResetBankForOBJExtPltt GX_DisableBankForOBJExtPltt

static inline void *G2_GetOBJCharPtr(void) { return (void *)HW_OBJ_VRAM; }
static inline void *G2S_GetOBJCharPtr(void) { return (void *)HW_DB_OBJ_VRAM; }
#define GX_RegionCheck_OBJ(a, b)
#define GX_RegionCheck_SubOBJ(a, b)
#define GX_RegionCheck_Tex(t, a, b)

static inline void GXi_DmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size)
{
    if (dmaNo != GX_DMA_NOT_USE && size > GX_CPU_FASTER32_SIZE) {
        MI_DmaCopy32(dmaNo, src, dest, size);
    } else {
        MI_CpuCopy32(src, dest, size);
    }
}

static inline void GXi_DmaCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size,
                                      MIDmaCallback callback, void *arg)
{
    if (dmaNo != GX_DMA_NOT_USE) {
        MI_DmaCopy32Async(dmaNo, src, dest, size, callback, arg);
    } else {
        MI_CpuCopy32(src, dest, size);
    }
}

extern struct {
    u32 sSubBGExtPltt;
    u32 sOBJExtPlttLCDCBlk;
    GXVRamOBJExtPltt sOBJExtPltt;
    u32 sBGExtPlttLCDCOffset;
    u32 sBGExtPlttLCDCBlk;
    GXVRamBGExtPltt sBGExtPltt;
    u32 sSubOBJExtPltt;
} data_02056f0c;
#define sOBJExtPlttLCDCBlk data_02056f0c.sOBJExtPlttLCDCBlk
#define sOBJExtPltt data_02056f0c.sOBJExtPltt
#define sBGExtPlttLCDCOffset data_02056f0c.sBGExtPlttLCDCOffset
#define sBGExtPlttLCDCBlk data_02056f0c.sBGExtPlttLCDCBlk
#define sBGExtPltt data_02056f0c.sBGExtPltt

void GX_BeginLoadBGExtPltt_02007c50 (void)
{

	sBGExtPltt = GX_ResetBankForBGExtPltt();

	switch (sBGExtPltt) {
	case GX_VRAM_BGEXTPLTT_0123_E:
		sBGExtPlttLCDCBlk = HW_LCDC_VRAM_E;
		sBGExtPlttLCDCOffset = 0;
		break;
	case GX_VRAM_BGEXTPLTT_23_G:
		sBGExtPlttLCDCBlk = HW_LCDC_VRAM_G;
		sBGExtPlttLCDCOffset = 0x4000;
		break;
	case GX_VRAM_BGEXTPLTT_0123_FG:
	case GX_VRAM_BGEXTPLTT_01_F:
		sBGExtPlttLCDCBlk = HW_LCDC_VRAM_F;
		sBGExtPlttLCDCOffset = 0;
		break;
	case GX_VRAM_BGEXTPLTT_NONE:
		break;
	default:
		break;
	}
}
