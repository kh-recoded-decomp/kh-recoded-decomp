#include "nitro/types.h"

struct TexMtxState;
typedef void (*TexMtxBuilder)(u32 *matrix, const struct TexMtxState *state);

extern void BuildTextureTransformB_(u32 *matrix, const struct TexMtxState *state);
extern void BuildTextureTransformE_(u32 *matrix, const struct TexMtxState *state);
extern void BuildTextureTransformG_(u32 *matrix, const struct TexMtxState *state);
extern void BuildTextureTranslationMatrix_(u32 *matrix, const struct TexMtxState *state);
extern void BuildTextureTransformC_(u32 *matrix, const struct TexMtxState *state);
extern void BuildTextureTransformF_(u32 *matrix, const struct TexMtxState *state);
extern void BuildTextureScaleMatrix_(u32 *matrix, const struct TexMtxState *state);
extern void func_01ffae58(int *matrix);

/* Indexed by the scale-one, rotation-zero and translation-zero flags. */
#pragma define_section textureBuilders ".text" ".text" ".text" RX
__declspec(textureBuilders) const TexMtxBuilder gTexMtxAltBuilders[8] = {
    BuildTextureTransformB_,
    BuildTextureTransformE_,
    BuildTextureTransformG_,
    BuildTextureTranslationMatrix_,
    BuildTextureTransformC_,
    BuildTextureTransformF_,
    BuildTextureScaleMatrix_,
    (TexMtxBuilder)func_01ffae58,
};
