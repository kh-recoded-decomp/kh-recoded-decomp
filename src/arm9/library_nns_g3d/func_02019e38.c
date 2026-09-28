/* Initializes G3X, shared geometry context, and empty-FIFO interrupt condition.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nns/g3d/calls/func_020163cc.c.
 * Original routine: func_020163cc. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
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

#define offsetof(type, member) ((u32)&(((type *)0)->member))



typedef vu32 REGType32v;
typedef enum {
    GX_FIFOINTR_COND_DISABLE      = 0,
    GX_FIFOINTR_COND_UNDERHALF    = 1,
    GX_FIFOINTR_COND_EMPTY        = 2
} GXFifoIntrCond;
void G3X_Init(void);
extern void G3X_SetFifoIntrCond(GXFifoIntrCond cond);
static inline void G3X_SetFifoIntrCond (GXFifoIntrCond cond)
{
    (*( REGType32v *) (0x04000000 + 0x600)) = (((*( REGType32v *) (0x04000000 + 0x600)) & ~0xc0000000 ) |
                      (cond << 30 ));
}
void func_020190b0(void);

/* InitializeGeometryEngine_02019e38 -- NitroSystem util.c: NNS_G3dInit. */
void InitializeGeometryEngine_02019e38 (void)
{
    G3X_Init();

    func_020190b0();

    G3X_SetFifoIntrCond(GX_FIFOINTR_COND_EMPTY);
}
