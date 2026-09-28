/* Graphics: the 2D and 3D engines and the VRAM banks, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NITRO_GX_H
#define NITRO_GX_H

#include "nitro/types.h"

struct G3MatrixRegisters;
struct GXAffineReg;
struct GXOamAttr;

#define GX_DMA_NOT_USE          ((u32) ~0)

#define G3OP_MTX_MODE           0x10

#define G3OP_TEXPLTT_BASE       0x2b

typedef enum { GX_SHADING_TOON = 0, GX_SHADING_HIGHLIGHT = 1 } GXShading;

typedef enum { GX_FIFOINTR_COND_DISABLE = 0, GX_FIFOINTR_COND_UNDERHALF = 1, GX_FIFOINTR_COND_EMPTY = 2 } GXFifoIntrCond;

typedef enum { GX_POLYGONMODE_MODULATE = 0 } GXPolygonMode;

typedef enum { GX_CULL_ALL = 0, GX_CULL_FRONT = 0x40, GX_CULL_BACK = 0x80, GX_CULL_NONE = 0xc0 } GXCull;

typedef enum { GX_TEXGEN_NONE = 0 } GXTexGen;

typedef enum { GX_TEXSIZE_S8 = 0 } GXTexSizeS;

typedef enum { GX_TEXSIZE_T8 = 0 } GXTexSizeT;

typedef enum { GX_TEXREPEAT_NONE = 0 } GXTexRepeat;

typedef enum { GX_TEXFLIP_NONE = 0 } GXTexFlip;

typedef enum { GX_TEXPLTTCOLOR0_USE = 0 } GXTexPlttColor0;

#define GX_LIGHTMASK_NONE 0

#define GX_POLYGON_ATTR_MISC_NONE 0

#define G2_BLENDTYPE_FADEIN  0x0080

#define G2_BLENDTYPE_FADEOUT 0x00c0

typedef enum {
	GX_VRAM_A = 0x1,
	GX_VRAM_B = 0x2,
	GX_VRAM_C = 0x4,
	GX_VRAM_D = 0x8,
	GX_VRAM_E = 0x10,
	GX_VRAM_F = 0x20,
	GX_VRAM_G = 0x40,
	GX_VRAM_H = 0x80,
	GX_VRAM_I = 0x100,
	GX_VRAM_ALL = 0x1ff
} GXVRam;

typedef enum {
	GX_VRAM_LCDC_NONE = 0x0000,
	GX_VRAM_LCDC_A = GX_VRAM_A,
	GX_VRAM_LCDC_B = GX_VRAM_B,
	GX_VRAM_LCDC_C = GX_VRAM_C,
	GX_VRAM_LCDC_D = GX_VRAM_D,
	GX_VRAM_LCDC_E = GX_VRAM_E,
	GX_VRAM_LCDC_F = GX_VRAM_F,
	GX_VRAM_LCDC_G = GX_VRAM_G,
	GX_VRAM_LCDC_H = GX_VRAM_H,
	GX_VRAM_LCDC_I = GX_VRAM_I,

	GX_VRAM_LCDC_ALL = GX_VRAM_ALL
} GXVRamLCDC;

typedef enum {
	GX_VRAM_BG_NONE        = 0x0000,
	GX_VRAM_BG_16_F        = GX_VRAM_F,
	GX_VRAM_BG_16_G        = GX_VRAM_G,
	GX_VRAM_BG_32_FG       = GX_VRAM_F | GX_VRAM_G,
	GX_VRAM_BG_64_E        = GX_VRAM_E,
	GX_VRAM_BG_80_EF       = GX_VRAM_E | GX_VRAM_F,
	GX_VRAM_BG_96_EFG      = GX_VRAM_E | GX_VRAM_F | GX_VRAM_G,
	GX_VRAM_BG_128_A       = GX_VRAM_A,
	GX_VRAM_BG_128_B       = GX_VRAM_B,
	GX_VRAM_BG_128_C       = GX_VRAM_C,
	GX_VRAM_BG_128_D       = GX_VRAM_D,
	GX_VRAM_BG_256_AB      = GX_VRAM_A | GX_VRAM_B,
	GX_VRAM_BG_256_BC      = GX_VRAM_B | GX_VRAM_C,
	GX_VRAM_BG_256_CD      = GX_VRAM_C | GX_VRAM_D,
	GX_VRAM_BG_384_ABC     = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C,
	GX_VRAM_BG_384_BCD     = GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,
	GX_VRAM_BG_512_ABCD    = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,
	GX_VRAM_BG_80_EG       = GX_VRAM_E | GX_VRAM_G,
	GX_VRAM_BG_256_AC      = GX_VRAM_A | GX_VRAM_C,
	GX_VRAM_BG_256_AD      = GX_VRAM_A | GX_VRAM_D,
	GX_VRAM_BG_256_BD      = GX_VRAM_B | GX_VRAM_D,
	GX_VRAM_BG_384_ABD     = GX_VRAM_A | GX_VRAM_B | GX_VRAM_D,
	GX_VRAM_BG_384_ACD     = GX_VRAM_A | GX_VRAM_C | GX_VRAM_D
} GXVRamBG;

typedef enum {
	GX_VRAM_OBJ_NONE      = 0x0000,
	GX_VRAM_OBJ_16_F      = GX_VRAM_F,
	GX_VRAM_OBJ_16_G      = GX_VRAM_G,
	GX_VRAM_OBJ_32_FG     = GX_VRAM_F | GX_VRAM_G,
	GX_VRAM_OBJ_64_E      = GX_VRAM_E,
	GX_VRAM_OBJ_80_EF     = GX_VRAM_E | GX_VRAM_F,
	GX_VRAM_OBJ_80_EG     = GX_VRAM_E | GX_VRAM_G,
	GX_VRAM_OBJ_96_EFG    = GX_VRAM_E | GX_VRAM_F | GX_VRAM_G,
	GX_VRAM_OBJ_128_A     = GX_VRAM_A,
	GX_VRAM_OBJ_128_B     = GX_VRAM_B,
	GX_VRAM_OBJ_256_AB    = GX_VRAM_A | GX_VRAM_B
} GXVRamOBJ;

typedef enum {
	GX_VRAM_ARM7_NONE      = 0x0000,
	GX_VRAM_ARM7_128_C     = GX_VRAM_C,
	GX_VRAM_ARM7_128_D     = GX_VRAM_D,
	GX_VRAM_ARM7_256_CD    = GX_VRAM_C | GX_VRAM_D
} GXVRamARM7;

typedef enum {
	GX_VRAM_TEX_NONE         = 0x0000,
	GX_VRAM_TEX_0_A          = GX_VRAM_A,
	GX_VRAM_TEX_0_B          = GX_VRAM_B,
	GX_VRAM_TEX_0_C          = GX_VRAM_C,
	GX_VRAM_TEX_0_D          = GX_VRAM_D,
	GX_VRAM_TEX_01_AB        = GX_VRAM_A | GX_VRAM_B,
	GX_VRAM_TEX_01_BC        = GX_VRAM_B | GX_VRAM_C,
	GX_VRAM_TEX_01_CD        = GX_VRAM_C | GX_VRAM_D,
	GX_VRAM_TEX_012_ABC      = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C,
	GX_VRAM_TEX_012_BCD      = GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,
	GX_VRAM_TEX_0123_ABCD    = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,
	GX_VRAM_TEX_01_AC        = GX_VRAM_A | GX_VRAM_C,
	GX_VRAM_TEX_01_AD        = GX_VRAM_A | GX_VRAM_D,
	GX_VRAM_TEX_01_BD        = GX_VRAM_B | GX_VRAM_D,
	GX_VRAM_TEX_012_ABD      = GX_VRAM_A | GX_VRAM_B | GX_VRAM_D,
	GX_VRAM_TEX_012_ACD      = GX_VRAM_A | GX_VRAM_C | GX_VRAM_D
} GXVRamTex;

typedef enum {
	GX_VRAM_CLEARIMAGE_NONE      = 0x0000,
	GX_VRAM_CLEARIMAGE_256_AB    = GX_VRAM_A | GX_VRAM_B,
	GX_VRAM_CLEARIMAGE_256_CD    = GX_VRAM_C | GX_VRAM_D,
	GX_VRAM_CLEARDEPTH_128_A     = GX_VRAM_A,
	GX_VRAM_CLEARDEPTH_128_B     = GX_VRAM_B,
	GX_VRAM_CLEARDEPTH_128_C     = GX_VRAM_C,
	GX_VRAM_CLEARDEPTH_128_D     = GX_VRAM_D
} GXVRamClearImage;

typedef enum {
	GX_VRAM_TEXPLTT_NONE          = 0x0000,
	GX_VRAM_TEXPLTT_0_F           = GX_VRAM_F,
	GX_VRAM_TEXPLTT_0_G           = GX_VRAM_G,
	GX_VRAM_TEXPLTT_01_FG         = GX_VRAM_F | GX_VRAM_G,
	GX_VRAM_TEXPLTT_0123_E        = GX_VRAM_E,
	GX_VRAM_TEXPLTT_01234_EF      = GX_VRAM_E | GX_VRAM_F,
	GX_VRAM_TEXPLTT_012345_EFG    = GX_VRAM_E | GX_VRAM_F | GX_VRAM_G
} GXVRamTexPltt;

typedef enum {
	GX_VRAM_BGEXTPLTT_NONE       = 0x0000,
	GX_VRAM_BGEXTPLTT_01_F       = GX_VRAM_F,
	GX_VRAM_BGEXTPLTT_23_G       = GX_VRAM_G,
	GX_VRAM_BGEXTPLTT_0123_E     = GX_VRAM_E,
	GX_VRAM_BGEXTPLTT_0123_FG    = GX_VRAM_F | GX_VRAM_G
} GXVRamBGExtPltt;

typedef enum {
	GX_VRAM_OBJEXTPLTT_NONE    = 0,
	GX_VRAM_OBJEXTPLTT_0_F     = GX_VRAM_F,
	GX_VRAM_OBJEXTPLTT_0_G     = GX_VRAM_G
} GXVRamOBJExtPltt;

#define GX_VRAM_OBJEXTPLTT_8_F    GX_VRAM_OBJEXTPLTT_0_F

#define GX_VRAM_OBJEXTPLTT_8_G    GX_VRAM_OBJEXTPLTT_0_G

typedef enum {
	GX_VRAM_SUB_BG_NONE     = 0x0000,
	GX_VRAM_SUB_BG_128_C    = GX_VRAM_C,
	GX_VRAM_SUB_BG_32_H     = GX_VRAM_H,
	GX_VRAM_SUB_BG_48_HI    = GX_VRAM_H | GX_VRAM_I
} GXVRamSubBG;

typedef enum {
	GX_VRAM_SUB_OBJ_NONE     = 0x0000,
	GX_VRAM_SUB_OBJ_128_D    = GX_VRAM_D,
	GX_VRAM_SUB_OBJ_16_I     = GX_VRAM_I
} GXVRamSubOBJ;

typedef enum {
	GX_VRAM_SUB_BGEXTPLTT_NONE = 0x0000,
	GX_VRAM_SUB_BGEXTPLTT_0123_H = GX_VRAM_H
} GXVRamSubBGExtPltt;

#define GX_VRAM_SUB_BGEXTPLTT_32_H GX_VRAM_SUB_BGEXTPLTT_0123_H

typedef enum {
	GX_VRAM_SUB_OBJEXTPLTT_NONE = 0x0000,
	GX_VRAM_SUB_OBJEXTPLTT_0_I = GX_VRAM_I
} GXVRamSubOBJExtPltt;

#define GX_VRAM_SUB_OBJEXTPLTT_16_I GX_VRAM_SUB_OBJEXTPLTT_0_I

typedef enum {
	GX_VRAMCNT_A_DISABLE           = 0,
	GX_VRAMCNT_A_LCDC_0x06800000   = (0 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_A_BG_0x06000000     = (1 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_A_BG_0x06020000     = (1 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_A_BG_0x06040000     = (1 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_A_BG_0x06060000     = (1 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_A_OBJ_0x06400000    = (2 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_A_OBJ_0x06420000    = (2 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_A_TEX_0             = (3 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_A_TEX_1             = (3 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_A_TEX_2             = (3 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_A_TEX_3             = (3 << 0) | (3 << 3) | (1 << 7)
} GX_VRAMCNT_A;

typedef enum {
	GX_VRAMCNT_B_DISABLE           = 0,
	GX_VRAMCNT_B_LCDC_0x06820000   = (0 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_B_BG_0x06000000     = (1 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_B_BG_0x06020000     = (1 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_B_BG_0x06040000     = (1 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_B_BG_0x06060000     = (1 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_B_OBJ_0x06400000    = (2 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_B_OBJ_0x06420000    = (2 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_B_TEX_0             = (3 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_B_TEX_1             = (3 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_B_TEX_2             = (3 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_B_TEX_3             = (3 << 0) | (3 << 3) | (1 << 7)
} GX_VRAMCNT_B;

typedef enum {
	GX_VRAMCNT_C_DISABLE           = 0,
	GX_VRAMCNT_C_LCDC_0x06840000   = (0 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_C_BG_0x06000000     = (1 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_C_BG_0x06020000     = (1 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_C_BG_0x06040000     = (1 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_C_BG_0x06060000     = (1 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_C_ARM7_0x06000000   = (2 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_C_ARM7_0x06020000   = (2 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_C_TEX_0             = (3 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_C_TEX_1             = (3 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_C_TEX_2             = (3 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_C_TEX_3             = (3 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_C_SUBBG_0x06200000  = (4 << 0) | (1 << 7)
} GX_VRAMCNT_C;

typedef enum {
	GX_VRAMCNT_D_DISABLE           = 0,
	GX_VRAMCNT_D_LCDC_0x06860000   = (0 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_D_BG_0x06000000     = (1 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_D_BG_0x06020000     = (1 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_D_BG_0x06040000     = (1 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_D_BG_0x06060000     = (1 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_D_ARM7_0x06000000   = (2 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_D_ARM7_0x06020000   = (2 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_D_TEX_0             = (3 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_D_TEX_1             = (3 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_D_TEX_2             = (3 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_D_TEX_3             = (3 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_D_SUBOBJ_0x06600000 = (4 << 0) | (1 << 7)
} GX_VRAMCNT_D;

typedef enum {
	GX_VRAMCNT_E_DISABLE           = 0,
	GX_VRAMCNT_E_LCDC_0x06880000   = (0 << 0) | (1 << 7),
	GX_VRAMCNT_E_BG_0x06000000     = (1 << 0) | (1 << 7),
	GX_VRAMCNT_E_OBJ_0x06400000    = (2 << 0) | (1 << 7),
	GX_VRAMCNT_E_TEXPLTT_0123      = (3 << 0) | (1 << 7),
	GX_VRAMCNT_E_BGEXTPLTT_0123    = (4 << 0) | (1 << 7)
}
GX_VRAMCNT_E;

typedef enum {
	GX_VRAMCNT_F_DISABLE           = 0,
	GX_VRAMCNT_F_LCDC_0x06890000   = (0 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_F_BG_0x06000000     = (1 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_F_BG_0x06004000     = (1 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_F_BG_0x06010000     = (1 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_F_BG_0x06014000     = (1 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_F_OBJ_0x06400000    = (2 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_F_OBJ_0x06404000    = (2 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_F_OBJ_0x06410000    = (2 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_F_OBJ_0x06414000    = (2 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_F_TEXPLTT_0         = (3 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_F_TEXPLTT_1         = (3 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_F_TEXPLTT_4         = (3 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_F_TEXPLTT_5         = (3 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_F_BGEXTPLTT_01      = (4 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_F_BGEXTPLTT_23      = (4 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_F_OBJEXTPLTT        = (5 << 0) | (0 << 3) | (1 << 7)
} GX_VRAMCNT_F;

typedef enum {
	GX_VRAMCNT_G_DISABLE           = 0,
	GX_VRAMCNT_G_LCDC_0x06894000   = (0 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_G_BG_0x06000000     = (1 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_G_BG_0x06004000     = (1 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_G_BG_0x06010000     = (1 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_G_BG_0x06014000     = (1 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_G_OBJ_0x06400000    = (2 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_G_OBJ_0x06404000    = (2 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_G_OBJ_0x06410000    = (2 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_G_OBJ_0x06414000    = (2 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_G_TEXPLTT_0         = (3 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_G_TEXPLTT_1         = (3 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_G_TEXPLTT_4         = (3 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_G_TEXPLTT_5         = (3 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_G_BGEXTPLTT_01      = (4 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_G_BGEXTPLTT_23      = (4 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_G_OBJEXTPLTT        = (5 << 0) | (0 << 3) | (1 << 7)
} GX_VRAMCNT_G;

typedef enum {
	GX_VRAMCNT_H_DISABLE           = 0,
	GX_VRAMCNT_H_LCDC_0x06898000   = (0 << 0) | (1 << 7),
	GX_VRAMCNT_H_SUBBG_0x06200000  = (1 << 0) | (1 << 7),
	GX_VRAMCNT_H_SUBBGEXTPLTT_0123 = (2 << 0) | (1 << 7)
} GX_VRAMCNT_H;

typedef enum {
	GX_VRAMCNT_I_DISABLE           = 0,
	GX_VRAMCNT_I_LCDC_0x068A0000   = (0 << 0) | (1 << 7),
	GX_VRAMCNT_I_SUBBG_0x06208000  = (1 << 0) | (1 << 7),
	GX_VRAMCNT_I_SUBOBJ_0x06600000 = (2 << 0) | (1 << 7),
	GX_VRAMCNT_I_SUBOBJEXTPLTT     = (3 << 0) | (1 << 7)
} GX_VRAMCNT_I;

#define GX_StateCheck_VRAMCnt() ((void)0)

typedef struct {
    u16 lcdc;
    u16 bg;
    u16 obj;
    u16 arm7;
    u16 tex;
    u16 texPltt;
    u16 clrImg;
    u16 bgExtPltt;
    u16 objExtPltt;
    u16 sub_bg;
    u16 sub_obj;
    u16 sub_bgExtPltt;
    u16 sub_objExtPltt;
} GX_VRAMCnt_;

typedef struct {
    GX_VRAMCnt_ vramCnt;
} GX_State;

typedef struct GXAffineReg {
    unsigned int paPb;
    unsigned int pcPd;
    int x;
    int y;
} GXAffineReg;

#define GX_CPU_FASTER32_SIZE 0x30

#define GX_RegionCheck_OBJ(a, b)

#define GX_RegionCheck_SubOBJ(a, b)

#define GX_RegionCheck_Tex(t, a, b)

typedef enum {
    GX_DISPMODE_GRAPHICS = 0x01,
    GX_DISPMODE_VRAM_A = 0x02,
    GX_DISPMODE_VRAM_B = 0x06,
    GX_DISPMODE_VRAM_C = 0x0a,
    GX_DISPMODE_VRAM_D = 0x0e,
    GX_DISPMODE_MMEM = 0x03
} GXDispMode;

#define GX_DISPMODE_OFF ((GXDispMode)0x00)

typedef enum {
    GX_BGMODE_0 = 0,
    GX_BGMODE_1 = 1,
    GX_BGMODE_2 = 2,
    GX_BGMODE_3 = 3,
    GX_BGMODE_4 = 4,
    GX_BGMODE_5 = 5,
    GX_BGMODE_6 = 6
} GXBGMode;

typedef enum {
    GX_BG0_AS_2D = 0,
    GX_BG0_AS_3D = 1
} GXBG0As;

typedef u16 GXScrFmtText;

typedef u16 GXRgb;

typedef u16 GXBGPltt16[16];

typedef u16 GXBGPltt256[256];

#define GX_COLOR_R(rgb) ((rgb) & 0x1f)

#define GX_COLOR_G(rgb) (((rgb) >> 5) & 0x1f)

#define GX_COLOR_B(rgb) (((rgb) >> 10) & 0x1f)

#define GX_RGB(r, g, b) \
    (((r) & 0x1f) | (((g) & 0x1f) << 5) | (((b) & 0x1f) << 10))

typedef struct G3MatrixRegisters {
    u32 mode, reserved04, push, store, restore, identity;
} G3MatrixRegisters;

#define GX_OAM_ATTR01_Y_SHIFT 0

#define GX_OAM_ATTR01_Y_MASK 0x000000ff

#define GX_OAM_ATTR01_RSENABLE_SHIFT 8

#define GX_OAM_ATTR01_RSENABLE_MASK 0x00000300

#define GX_OAM_ATTR01_SHAPE_SHIFT 14

#define GX_OAM_ATTR01_SHAPE_MASK 0x0000c000

#define GX_OAM_ATTR01_X_SHIFT 16

#define GX_OAM_ATTR01_X_MASK 0x01ff0000

#define GX_OAM_ATTR01_RS_SHIFT 25

#define GX_OAM_ATTR01_RS_MASK 0x3e000000

#define GX_OAM_ATTR01_FLIP_MASK 0x30000000

#define GX_OAM_ATTR01_SIZE_SHIFT 30

#define GX_OAM_ATTR01_SIZE_MASK 0xc0000000

typedef enum GXOamEffect {
    GX_OAM_EFFECT_NONE = 0,
    GX_OAM_EFFECT_AFFINE = 0x100,
    GX_OAM_EFFECT_NODISPLAY = 0x200,
    GX_OAM_EFFECT_AFFINE_DOUBLE = 0x300
} GXOamEffect;

typedef enum GXOamShape {
    GX_OAM_SHAPE_8x8 = 0
} GXOamShape;

typedef struct GXOamAttr {
    union {
        u32 attr01;
        struct {
            u16 attr0;
            u16 attr1;
        };
    };
    u16 attr2;
    u16 _3;
} GXOamAttr;

#define GX_LCD_SIZE_X 256

#define GX_LCD_SIZE_Y 192

typedef enum {
    GX_TEXFMT_NONE       = 0,
    GX_TEXFMT_A3I5       = 1,
    GX_TEXFMT_PLTT4      = 2,
    GX_TEXFMT_PLTT16     = 3,
    GX_TEXFMT_PLTT256    = 4,
    GX_TEXFMT_COMP4x4    = 5,
    GX_TEXFMT_A5I3       = 6,
    GX_TEXFMT_DIRECT     = 7
} GXTexFmt;

typedef enum {
    GX_OBJVRAMMODE_CHAR_2D      = (0 << 4 ) | (0 << 20 ),
    GX_OBJVRAMMODE_CHAR_1D_32K  = (1 << 4 ) | (0 << 20 ),
    GX_OBJVRAMMODE_CHAR_1D_64K  = (1 << 4 ) | (1 << 20 ),
    GX_OBJVRAMMODE_CHAR_1D_128K = (1 << 4 ) | (2 << 20 ),
    GX_OBJVRAMMODE_CHAR_1D_256K = (1 << 4 ) | (3 << 20 )
} GXOBJVRamModeChar;

typedef union {
    u32 data32[8];
    u16 data16[16];
    u8 data8[32];
} GXCharFmt16;

typedef union {
    u32 data32[16];
    u16 data16[32];
    u8 data8[64];
} GXCharFmt256;

typedef u8 GXScrFmtAffine;

typedef enum {
    GX_BG_SCRSIZE_256x16PLTT_128x128 = 0,
    GX_BG_SCRSIZE_256x16PLTT_256x256 = 1,
    GX_BG_SCRSIZE_256x16PLTT_512x512 = 2,
    GX_BG_SCRSIZE_256x16PLTT_1024x1024 = 3
} GXBGScrSize256x16Pltt;

typedef enum {
    GX_BG_AREAOVER_XLU = 0,
    GX_BG_AREAOVER_REPEAT = 1
} GXBGAreaOver;

typedef enum {
    GX_BG_CHARBASE_0x00000 = 0,
    GX_BG_CHARBASE_0x04000 = 1,
    GX_BG_CHARBASE_0x08000 = 2,
    GX_BG_CHARBASE_0x0c000 = 3,
    GX_BG_CHARBASE_0x10000 = 4,
    GX_BG_CHARBASE_0x14000 = 5,
    GX_BG_CHARBASE_0x18000 = 6,
    GX_BG_CHARBASE_0x1c000 = 7,
    GX_BG_CHARBASE_0x20000 = 8,
    GX_BG_CHARBASE_0x24000 = 9,
    GX_BG_CHARBASE_0x28000 = 10,
    GX_BG_CHARBASE_0x2c000 = 11,
    GX_BG_CHARBASE_0x30000 = 12,
    GX_BG_CHARBASE_0x34000 = 13,
    GX_BG_CHARBASE_0x38000 = 14,
    GX_BG_CHARBASE_0x3c000 = 15
} GXBGCharBase;

typedef enum {
    GX_BG_SCRBASE_0x0000 = 0,
    GX_BG_SCRBASE_0x0800 = 1,
    GX_BG_SCRBASE_0x1000 = 2,
    GX_BG_SCRBASE_0x1800 = 3,
    GX_BG_SCRBASE_0x2000 = 4,
    GX_BG_SCRBASE_0x2800 = 5,
    GX_BG_SCRBASE_0x3000 = 6,
    GX_BG_SCRBASE_0x3800 = 7,
    GX_BG_SCRBASE_0x4000 = 8,
    GX_BG_SCRBASE_0x4800 = 9,
    GX_BG_SCRBASE_0x5000 = 10,
    GX_BG_SCRBASE_0x5800 = 11,
    GX_BG_SCRBASE_0x6000 = 12,
    GX_BG_SCRBASE_0x6800 = 13,
    GX_BG_SCRBASE_0x7000 = 14,
    GX_BG_SCRBASE_0x7800 = 15,
    GX_BG_SCRBASE_0x8000 = 16,
    GX_BG_SCRBASE_0x8800 = 17,
    GX_BG_SCRBASE_0x9000 = 18,
    GX_BG_SCRBASE_0x9800 = 19,
    GX_BG_SCRBASE_0xa000 = 20,
    GX_BG_SCRBASE_0xa800 = 21,
    GX_BG_SCRBASE_0xb000 = 22,
    GX_BG_SCRBASE_0xb800 = 23,
    GX_BG_SCRBASE_0xc000 = 24,
    GX_BG_SCRBASE_0xc800 = 25,
    GX_BG_SCRBASE_0xd000 = 26,
    GX_BG_SCRBASE_0xd800 = 27,
    GX_BG_SCRBASE_0xe000 = 28,
    GX_BG_SCRBASE_0xe800 = 29,
    GX_BG_SCRBASE_0xf000 = 30,
    GX_BG_SCRBASE_0xf800 = 31
} GXBGScrBase;

typedef enum {
    GX_BG_SCRSIZE_AFFINE_128x128      = 0,
    GX_BG_SCRSIZE_AFFINE_256x256      = 1,
    GX_BG_SCRSIZE_AFFINE_512x512      = 2,
    GX_BG_SCRSIZE_AFFINE_1024x1024    = 3
} GXBGScrSizeAffine;

typedef enum {
    GX_BG_COLORMODE_16 = 0,
    GX_BG_COLORMODE_256 = 1
} GXBGColorMode;

typedef enum {
    GX_BG_SCRSIZE_TEXT_256x256 = 0,
    GX_BG_SCRSIZE_TEXT_512x256 = 1,
    GX_BG_SCRSIZE_TEXT_256x512 = 2,
    GX_BG_SCRSIZE_TEXT_512x512 = 3
} GXBGScrSizeText;

typedef enum {
    GX_BG_EXTMODE_256x16PLTT = (0 << 2 ) | (0 << 7 ),
    GX_BG_EXTMODE_256BITMAP  = (0 << 2 ) | (1 << 7 ),
    GX_BG_EXTMODE_DCBITMAP   = (1 << 2 ) | (1 << 7 )
} GXBGExtMode;

typedef enum {
    GX_BG_EXTPLTT_01 = 0,
    GX_BG_EXTPLTT_23 = 1
} GXBGExtPltt;

typedef enum {
    GX_MTXMODE_PROJECTION      = 0,
    GX_MTXMODE_POSITION        = 1,
    GX_MTXMODE_POSITION_VECTOR = 2,
    GX_MTXMODE_TEXTURE         = 3
} GXMtxMode;

#define G3OP_MTX_STORE   0x13

#define G3OP_MTX_RESTORE 0x14

#define G3OP_MTX_MULT_4x4 0x18

#define G3OP_MTX_MULT_3x3 0x1a

#define G3OP_MTX_SCALE    0x1b

#define G3OP_TEXCOORD     0x22

#define GX_FX16ST(x) ((short)((x) >> 8))

#define GX_ST(s, t) ((u32)((u16)GX_FX16ST(s) | ((u16)GX_FX16ST(t) << 16)))

#define GX_PACK_TEXCOORD_PARAM(s, t) (GX_ST((s), (t)))

#define G3OP_MTX_LOAD_4x4 0x16

#define G3OP_MTX_MULT_4x3 0x19

#define G3OP_MTX_TRANS    0x1c

#define G3D_NORMALIZE_ROT_MTX

#endif
