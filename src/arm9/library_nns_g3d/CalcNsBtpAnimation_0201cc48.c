#include "nitro/types.h"

typedef struct NNSG3dMatAnmResult NNSG3dMatAnmResult;
typedef struct NNSG3dResTex NNSG3dResTex;
typedef struct NNSG3dResName NNSG3dResName;

typedef struct {
    u8 pad_00[4];
    u16 numFrame;
} NNSG3dResTexPatAnm;

typedef struct {
    u16 idxFrame;
    u8 idTex;
    u8 idPltt;
} NNSG3dResTexPatAnmFV;

typedef struct {
    s32 frame;
    u8 pad_04[4];
    const NNSG3dResTexPatAnm *resAnm;
    u8 pad_0c[8];
    const NNSG3dResTex *resTex;
} NNSG3dAnmObj;

extern const NNSG3dResTexPatAnmFV *FindTexturePatternFrameEntry_0201ad5c(const NNSG3dResTexPatAnm *pPatAnm, u32 idx, u32 frame);
extern const NNSG3dResName *GetTexturePatternTextureName_0201ad0c(const NNSG3dResTexPatAnm *pPatAnm, u8 texIdx);
extern const NNSG3dResName *GetTexturePatternPaletteName_0201ad34(const NNSG3dResTexPatAnm *pPatAnm, u8 plttIdx);
extern void SetTextureAnimationResult_0201cb0c(const NNSG3dResTex *pTex, const NNSG3dResName *pTexName, NNSG3dMatAnmResult *pResult);
extern void SetPaletteAnimationResult_0201cbe4(const NNSG3dResTex *pTex, const NNSG3dResName *pPlttName, NNSG3dMatAnmResult *pResult);

void CalcNsBtpAnimation_0201cc48(NNSG3dMatAnmResult *pResult, const NNSG3dAnmObj *pAnmObj, u32 dataIdx, u32 unused)
{
    const NNSG3dResTexPatAnm *pPatAnm = pAnmObj->resAnm;
    s32 frame = pAnmObj->frame;
    const NNSG3dResTexPatAnmFV *pFV;

    if (frame >= (s32)(pPatAnm->numFrame << 12)) {
        frame = (pPatAnm->numFrame << 12) - 1;
    } else if (frame < 0) {
        frame = 0;
    }

    pFV = FindTexturePatternFrameEntry_0201ad5c(pPatAnm, (u16)dataIdx, (u16)(frame >> 12));

    SetTextureAnimationResult_0201cb0c(pAnmObj->resTex,
                                        GetTexturePatternTextureName_0201ad0c(pPatAnm, pFV->idTex),
                                        pResult);

    if (pFV->idPltt != 0xff) {
        SetPaletteAnimationResult_0201cbe4(pAnmObj->resTex,
                                            GetTexturePatternPaletteName_0201ad34(pPatAnm, pFV->idPltt),
                                            pResult);
    }
}
