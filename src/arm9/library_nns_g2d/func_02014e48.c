/* Resolves the extended cell-attribute array and each cell attribute pointer from resource-relative offsets.
 * Uncertainty: This identifies a shared library operation; the particular scene, asset or gameplay caller using it is not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nns/g2d/auto/func_02011ae8.c.
 * Original routine: func_02011ae8. External references are
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

#define NNS_G2D_UNPACK_OFFSET_PTR(ptr, baseOffs) (ptr) = (void *)((u32)(ptr) + (u32)baseOffs)

typedef struct NNSG2dUserExCellAttr {
    u32 * pAttr;
} NNSG2dUserExCellAttr;
typedef struct NNSG2dUserExCellAttrBank {
    u16 numCells;
    u16 numAttribute;
    NNSG2dUserExCellAttr * pCellAttrArray;
} NNSG2dUserExCellAttrBank;

/* G2D_UnpackCellAttributes_02014e48 -- NitroSystem g2d_Load.c: NNSi_G2dUnpackUserExCellAttrBank. */
void G2D_UnpackCellAttributes_02014e48 (NNSG2dUserExCellAttrBank * pCellAttrBank)
{
    u16 i;

    pCellAttrBank->pCellAttrArray
        = NNS_G2D_UNPACK_OFFSET_PTR(pCellAttrBank->pCellAttrArray,
                                    pCellAttrBank);
    for (i = 0; i < pCellAttrBank->numCells; i++) {
        pCellAttrBank->pCellAttrArray[i].pAttr
            = NNS_G2D_UNPACK_OFFSET_PTR(pCellAttrBank->pCellAttrArray[i].pAttr,
                                        pCellAttrBank);
    }
}
