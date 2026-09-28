/* Resets five frame-texture VRAM regions, sets active flags from slot count, and resets head/tail bounds.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nns/gfd/calls/func_02010f08.c.
 * Original routine: func_02010f08. External references are
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


#define NNS_GFD_NUM_TEX_VRAM_REGION 5

typedef void (*NNSGfdFrmTexVramDebugDumpCallBack)(int index, u32 startAddr, u32 endAddr, u32 blockMax, BOOL bActive, void * pUserContext);
typedef struct NNSGfdFrmTexRegionState {
    u32 head;
    u32 tail;
    BOOL bActive;
    const BOOL bHalfSize;
    const u16 index;
    const u16 pad16_;
    const u32 baseAddress;
} NNSGfdFrmTexRegionState;
typedef struct NNSGfdFrmTexVramMnager {
    u16 numSlot;
} NNSGfdFrmTexVramMnager;
extern NNSGfdFrmTexVramMnager data_0205a8c0;
extern NNSGfdFrmTexRegionState data_02055c78[5 ];
static inline void ResetRegionNormal_ (NNSGfdFrmTexRegionState * pRegion)
{
    pRegion->head = 0x0;
    pRegion->tail = 0x20000 ;
}
static inline void ResetRegionHalf_ (NNSGfdFrmTexRegionState * pRegion)
{
    pRegion->head = 0x0;
    pRegion->tail = 0x20000 / 2;
}

/* NNS_GfdResetFrmTexVramState_0201391c -- NitroSystem gfd_FrameTexVramMan.c: NNS_GfdResetFrmTexVramState. */
void NNS_GfdResetFrmTexVramState_0201391c (void)
{
    int i;
    u16 numSlot = data_0205a8c0.numSlot;

    const numRegion = (numSlot > 1) ? numSlot + 1 : numSlot + 0;


    for (i = 0; i < NNS_GFD_NUM_TEX_VRAM_REGION; i++) {
        if ( i < numRegion ) {
            data_02055c78[i].bActive = TRUE;
        } else {
            data_02055c78[i].bActive = FALSE;
        }

        if ( data_02055c78[i].bHalfSize ) {
            ResetRegionHalf_(&data_02055c78[i]);
        } else {
            ResetRegionNormal_(&data_02055c78[i]);
        }
    }
}
