#include "nitro/types.h"

struct TexMtxState;
typedef void (*TexMtxBuilder)(u32 *matrix, const struct TexMtxState *state);

extern void texmtxCalc_flag_(u32 *matrix, const struct TexMtxState *state);
extern void NNSi_G3dCalcTexMtxRot(u32 *matrix, const struct TexMtxState *state);
extern void BuildTextureTransformVariantH(u32 *matrix, const struct TexMtxState *state);
extern void BuildTextureTranslationMatrixITCM(u32 *matrix, const struct TexMtxState *state);
extern void BuildTextureTransformVariantD(u32 *matrix, const struct TexMtxState *state);
extern void NNSi_G3dCalcTexMtxRotTransZero(u32 *matrix, const struct TexMtxState *state);
extern void BuildTextureVerticalScaleMatrix(u32 *matrix, const struct TexMtxState *state);
extern void func_01ffacdc(int *matrix);

/* Indexed by the scale-one, rotation-zero and translation-zero flags. */
#pragma define_section textureBuilders ".text" ".text" ".text" RX
__declspec(textureBuilders) const TexMtxBuilder gTexMtxMode2Builders[8] = {
    texmtxCalc_flag_,
    NNSi_G3dCalcTexMtxRot,
    BuildTextureTransformVariantH,
    BuildTextureTranslationMatrixITCM,
    BuildTextureTransformVariantD,
    NNSi_G3dCalcTexMtxRotTransZero,
    BuildTextureVerticalScaleMatrix,
    (TexMtxBuilder)func_01ffacdc,
};
