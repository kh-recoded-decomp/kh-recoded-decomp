#include "nitro/types.h"
#include "nitro/fx_types.h"

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

extern u32 data_020560e8[];
extern u32 data_020560ec[];
extern MtxFx43 data_020560f4;
extern VecFx32 data_02056118;
extern VecFx32 data_02056124;
extern NNSG3dGlb data_0205a924;

extern void QueueOrSendGeometryCommandPair_01ffcedc(u32 command, u32 argument);
extern void func_01ff80e4(void);
extern int G3X_GetClipMtx_02006b90(MtxFx44 *m);
extern const MtxFx43 *func_02019658(void);
extern const MtxFx43 *func_0201968c(void);
extern const MtxFx43 *GetCachedInverseViewMatrix_02019378(void);
extern void func_01ff94a8(const MtxFx43 *src, MtxFx44 *dst);
extern void MTX_Concat44_02005a08(const MtxFx44 *a, const MtxFx44 *b, MtxFx44 *ab);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb);
extern void func_01ff8728(const void *src, volatile void *dest, u32 size);

void NNSi_G3dFuncSbc_RollBB_02039fec(NNSG3dRS *rs, u32 opt)
{
    u32 cmdLen = 2;
    VecFx32 *trans = &data_02056118;
    VecFx32 *scale = &data_02056124;
    MtxFx43 *mtx = &data_020560f4;
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
            QueueOrSendGeometryCommandPair_01ffcedc(0x14, idxMtxSrc);
        }
    }

    if (!(rs->flag & NNS_G3D_RSFLAG_OPT_NOGECMD)) {
        func_01ff80e4();

        reg_G3X_GXFIFO = 0x00151110;
        reg_G3X_GXFIFO = 0;
        reg_G3X_GXFIFO = 0;

        while (G3X_GetClipMtx_02006b90(&m)) {
        }

        if (data_0205a924.flag & NNS_G3D_GLB_FLAG_FLUSH_WVP) {
            const MtxFx43 *cam = func_02019658();
            MtxFx44 tmp;

            func_01ff94a8(cam, &tmp);
            MTX_Concat44_02005a08(&m, &tmp, &m);
        } else if (data_0205a924.flag & NNS_G3D_GLB_FLAG_FLUSH_VP) {
            const MtxFx43 *cam = &data_0205a924.cameraMtx;
            MtxFx44 tmp;

            func_01ff94a8(cam, &tmp);
            MTX_Concat44_02005a08(&m, &tmp, &m);
        }

        trans->x = m._30;
        trans->y = m._31;
        trans->z = m._32;

        scale->x = VEC_Mag_01ff9f28((VecFx32 *)&m._00);
        scale->y = VEC_Mag_01ff9f28((VecFx32 *)&m._10);
        scale->z = VEC_Mag_01ff9f28((VecFx32 *)&m._20);

        mtx->_12 = m._12;
        mtx->_10 = m._10;
        mtx->_11 = m._11;
        mtx->_00 = m._11;
        mtx->_01 = -m._10;
        mtx->_02 = 0;

        func_01ff9f88((VecFx32 *)&mtx->_00, (VecFx32 *)&mtx->_00);
        func_01ff9f88((VecFx32 *)&mtx->_10, (VecFx32 *)&mtx->_10);
        VEC_CrossProduct_01ff9ea8((VecFx32 *)&mtx->_00, (VecFx32 *)&mtx->_10, (VecFx32 *)&mtx->_20);

        if (data_0205a924.flag & NNS_G3D_GLB_FLAG_FLUSH_WVP) {
            reg_G3X_GXFIFO = 0x00171012;
            func_01ff8728(data_020560ec, &reg_G3X_GXFIFO, 2 * sizeof(u32));
            func_01ff8728(func_0201968c(), &reg_G3X_GXFIFO, 12 * sizeof(u32));
            reg_G3X_GXFIFO = 0x00001b19;
            func_01ff8728(&data_020560f4, &reg_G3X_GXFIFO, sizeof(MtxFx43) + sizeof(VecFx32));
        } else if (data_0205a924.flag & NNS_G3D_GLB_FLAG_FLUSH_VP) {
            reg_G3X_GXFIFO = 0x00171012;
            func_01ff8728(data_020560ec, &reg_G3X_GXFIFO, 2 * sizeof(u32));
            func_01ff8728(GetCachedInverseViewMatrix_02019378(), &reg_G3X_GXFIFO, 12 * sizeof(u32));
            reg_G3X_GXFIFO = 0x00001b19;
            func_01ff8728(&data_020560f4, &reg_G3X_GXFIFO, sizeof(MtxFx43) + sizeof(VecFx32));
        } else {
            func_01ff8728(data_020560e8, &reg_G3X_GXFIFO, 18 * sizeof(u32));
        }
    }

    if (opt == NNS_G3D_SBCFLG_001 || opt == NNS_G3D_SBCFLG_011) {
        ++cmdLen;
        if (!(rs->flag & NNS_G3D_RSFLAG_OPT_NOGECMD)) {
            QueueOrSendGeometryCommandPair_01ffcedc(0x13, *(rs->c + 2));
        }
    }

    rs->c += cmdLen;
}
