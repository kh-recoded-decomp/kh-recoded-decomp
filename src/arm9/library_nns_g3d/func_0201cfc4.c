/* Builds a unit-scale texture matrix with dimension-scaled S/T translation.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nns/g3d/auto/func_02019900.c.
 * Original routine: func_02019900. External references are
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


#define FX32_ONE ((fx32) 0x0000000000001000L)         // 1.000000000000

typedef s32 fx32;
typedef s16 fx16;
typedef union {
        struct {
            fx32 _00, _01, _02, _03;
            fx32 _10, _11, _12, _13;
            fx32 _20, _21, _22, _23;
            fx32 _30, _31, _32, _33;
        };
        fx32 m[4][4];
        fx32 a[16];
    } MtxFx44;
struct NNSG3dMatAnmResult_;
typedef enum {
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_SCALEONE  = 0x00000001,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_ROTZERO   = 0x00000002,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_TRANSZERO = 0x00000004,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_SET       = 0x00000008,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_MULT      = 0x00000010,
    NNS_G3D_MATANM_RESULTFLAG_WIREFRAME        = 0x00000020}
NNSG3dMatAnmResultFlag;
typedef struct NNSG3dMatAnmResult_ {
    NNSG3dMatAnmResultFlag flag;
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
    u32 prmTexImage;
    u32 prmTexPltt;
    fx32 scaleS, scaleT;
    fx16 sinR, cosR;
    fx32 transS, transT;
    u16 origWidth, origHeight;
    fx32 magW, magH;
} NNSG3dMatAnmResult;

/* BuildTextureTranslationMatrix_0201cfc4 -- NitroSystem 3dsmax.c: texmtxCalc_flagRS_. */
void BuildTextureTranslationMatrix_0201cfc4 (MtxFx44 * m, const NNSG3dMatAnmResult * anm)
{
    m->_00 = FX32_ONE;
    m->_11 = FX32_ONE;

    m->_01 = 0;

    m->_30 = (-anm->transS * anm->origWidth) << 4;
    m->_31 = (anm->transT * anm->origHeight) << 4;

    m->_10 = 0;
}
