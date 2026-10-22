/* NNS G3D: the texture-matrix builders SendTexMtxAltBuilders dispatches to, indexed by the
 * material's scale/rotation/translation flags. The table sits in .text. */
    .syntax unified
    .text
    .align 2
    .global gTexMtxAltBuilders
    .type gTexMtxAltBuilders, %object
gTexMtxAltBuilders:
    .word BuildTextureTransformB_
    .word BuildTextureTransformE_
    .word BuildTextureTransformG_
    .word BuildTextureTranslationMatrix_
    .word BuildTextureTransformC_
    .word BuildTextureTransformF_
    .word BuildTextureScaleMatrix_
    .word func_01ffae58
    .size gTexMtxAltBuilders, . - gTexMtxAltBuilders
