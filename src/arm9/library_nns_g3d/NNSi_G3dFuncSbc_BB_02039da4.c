#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/gx.h"

typedef struct { fx32 _00, _01, _02, _10, _11, _12, _20, _21, _22, _30, _31, _32; } MtxFx43;
typedef struct {
    fx32 _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33;
} MtxFx44;

typedef struct NNSG3dRS {
    const u8 *c;
    u32 pad04;
    u32 flag;
} NNSG3dRS;

typedef struct NNSG3dGlb {
    char pad00[0x4c];
    MtxFx43 cameraMtx;
    char pad7c[0xd4 - 0x7c];
    u32 flag;
} NNSG3dGlb;

#define reg_G3X_GXFIFO (*(vu32 *)0x04000400)

#define NNS_G3D_SBCFLG_001 0x20
#define NNS_G3D_SBCFLG_010 0x40
#define NNS_G3D_SBCFLG_011 0x60
#define NNS_G3D_RSFLAG_OPT_NOGECMD      0x100
#define NNS_G3D_RSFLAG_OPT_SKIP_SBCDRAW 0x200
#define NNS_G3D_GLB_FLAG_FLUSH_WVP 1
#define NNS_G3D_GLB_FLAG_FLUSH_VP  2

extern u32 data_020560a0[];
extern u32 data_020560a4[];
extern u32 data_020560ac[];
extern VecFx32 data_020560d0;
extern VecFx32 data_020560dc;
extern NNSG3dGlb data_0205a924;

extern void NNSi_G3dGeBufferCommand1(u32 op, u32 param);
extern void GXi_FlushCommandList(void);
extern int G3X_GetClipMtx(MtxFx44 *m);
extern const MtxFx43 *GetOrInitResource749c(void);
extern const MtxFx43 *GetOrInitResource74cc(void);
extern const MtxFx43 *G3d_GetInverseCameraMtx(void);
extern void MTX_Copy43To44_(const MtxFx43 *pSrc, MtxFx44 *pDst);
extern void MTX_Concat44(const MtxFx44 *a, const MtxFx44 *b, MtxFx44 *ab);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void MIi_CpuSend32(const void *src, volatile void *dest, u32 size);

void NNSi_G3dFuncSbc_BB_02039da4(NNSG3dRS *rs, u32 opt)
{
    u32 cmdLen = 2;
    VecFx32 *trans = &data_020560d0;
    VecFx32 *scale = &data_020560dc;
    MtxFx44 m;

    if (rs->flag & NNS_G3D_RSFLAG_OPT_SKIP_SBCDRAW) {
        if (opt == NNS_G3D_SBCFLG_010 || opt == NNS_G3D_SBCFLG_011) {
            ++cmdLen;
        }
        if (opt == NNS_G3D_SBCFLG_001 || opt == NNS_G3D_SBCFLG_011) {
            ++cmdLen;
        }
        rs->c += cmdLen;
        return;
    }

    if (opt == NNS_G3D_SBCFLG_010 || opt == NNS_G3D_SBCFLG_011) {
        ++cmdLen;
        if (!(rs->flag & NNS_G3D_RSFLAG_OPT_NOGECMD)) {
            u32 idxMtxSrc;

            if (opt == NNS_G3D_SBCFLG_010) {
                idxMtxSrc = *(rs->c + 2);
            } else {
                idxMtxSrc = *(rs->c + 3);
            }
            NNSi_G3dGeBufferCommand1(G3OP_MTX_RESTORE, idxMtxSrc);
        }
    }

    if (!(rs->flag & NNS_G3D_RSFLAG_OPT_NOGECMD)) {
        GXi_FlushCommandList();

        reg_G3X_GXFIFO = 0x00151110;
        reg_G3X_GXFIFO = 0;
        reg_G3X_GXFIFO = 0;

        while (G3X_GetClipMtx(&m)) {
        }

        if (data_0205a924.flag & NNS_G3D_GLB_FLAG_FLUSH_WVP) {
            const MtxFx43 *cam = GetOrInitResource749c();
            MtxFx44 tmp;

            MTX_Copy43To44_(cam, &tmp);
            MTX_Concat44(&m, &tmp, &m);
        } else if (data_0205a924.flag & NNS_G3D_GLB_FLAG_FLUSH_VP) {
            const MtxFx43 *cam = &data_0205a924.cameraMtx;
            MtxFx44 tmp;

            MTX_Copy43To44_(cam, &tmp);
            MTX_Concat44(&m, &tmp, &m);
        }

        trans->x = m._30;
        trans->y = m._31;
        trans->z = m._32;

        scale->x = VEC_Mag((VecFx32 *)&m._00);
        scale->y = VEC_Mag((VecFx32 *)&m._10);
        scale->z = VEC_Mag((VecFx32 *)&m._20);

        if (data_0205a924.flag & NNS_G3D_GLB_FLAG_FLUSH_WVP) {
            reg_G3X_GXFIFO = 0x00171012;
            MIi_CpuSend32(data_020560a4, &reg_G3X_GXFIFO, 2 * sizeof(u32));
            MIi_CpuSend32(GetOrInitResource74cc(), &reg_G3X_GXFIFO, 12 * sizeof(u32));
            reg_G3X_GXFIFO = 0x00001b19;
            MIi_CpuSend32(data_020560ac, &reg_G3X_GXFIFO, sizeof(MtxFx43) + sizeof(VecFx32));
        } else if (data_0205a924.flag & NNS_G3D_GLB_FLAG_FLUSH_VP) {
            reg_G3X_GXFIFO = 0x00171012;
            MIi_CpuSend32(data_020560a4, &reg_G3X_GXFIFO, 2 * sizeof(u32));
            MIi_CpuSend32(G3d_GetInverseCameraMtx(), &reg_G3X_GXFIFO, 12 * sizeof(u32));
            reg_G3X_GXFIFO = 0x00001b19;
            MIi_CpuSend32(data_020560ac, &reg_G3X_GXFIFO, sizeof(MtxFx43) + sizeof(VecFx32));
        } else {
            MIi_CpuSend32(data_020560a0, &reg_G3X_GXFIFO, 18 * sizeof(u32));
        }
    }

    if (opt == NNS_G3D_SBCFLG_001 || opt == NNS_G3D_SBCFLG_011) {
        ++cmdLen;
        if (!(rs->flag & NNS_G3D_RSFLAG_OPT_NOGECMD)) {
            NNSi_G3dGeBufferCommand1(G3OP_MTX_STORE, *(rs->c + 2));
        }
    }

    rs->c += cmdLen;
}
