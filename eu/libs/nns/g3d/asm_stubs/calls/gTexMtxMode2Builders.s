/* NNS G3D: the texture-matrix builders NNSi_G3dSendTexMtxMode2 dispatches to, indexed by the
 * material's scale/rotation/translation flags. The table sits in .text. */
    .syntax unified
    .text
    .align 2
    .global gTexMtxMode2Builders
    .type gTexMtxMode2Builders, %object
gTexMtxMode2Builders:
    .word texmtxCalc_flag_
    .word NNSi_G3dCalcTexMtxRot
    .word BuildTextureTransformVariantH
    .word BuildTextureTranslationMatrixITCM
    .word BuildTextureTransformVariantD
    .word NNSi_G3dCalcTexMtxRotTransZero
    .word BuildTextureVerticalScaleMatrix
    .word func_01ffacdc
    .size gTexMtxMode2Builders, . - gTexMtxMode2Builders
