#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct NNSG3dResJntAnm {
    u8 anmHeader[4];
    u16 frameCount;
    u16 jointCount;
    u32 flags;
    u32 compactRotationOffset;
    u32 fullRotationOffset;
} NNSG3dResJntAnm;

typedef struct NNSG3dJntAnmResult {
    u32 flags;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx33 rotation;
    VecFx32 position;
} NNSG3dJntAnmResult;

extern void ModelAnimation_BlendJointTranslation_02039280(fx32 *translationComponent, fx32 animationFrame,
                                                          const u32 *trackDescriptor,
                                                          const NNSG3dResJntAnm *jointAnimation);
extern void ModelAnimation_BlendJointRotation_02039728(MtxFx33 *rotation, fx32 animationFrame,
                                                       const u32 *trackDescriptor,
                                                       const NNSG3dResJntAnm *jointAnimation);
extern void ModelAnimation_BlendJointScale_020395a8(fx32 *scaleAndInverse, fx32 animationFrame,
                                                    const u32 *trackDescriptor,
                                                    const NNSG3dResJntAnm *jointAnimation);
extern BOOL DecodeCompressedRotationITCM_01ffd56c(MtxFx33 *rotation, const void *compactRotations,
                                                  const void *fullRotations, u32 rotationIndex);
extern void ModelAnimation_ApplyDefaultJointPosition_02038ea8(NNSG3dJntAnmResult *result);
extern void NNSi_G3dGetMdlRot_02038fd0(NNSG3dJntAnmResult *result);
extern void ModelAnimation_ApplyDefaultJointScale_02038f3c(NNSG3dJntAnmResult *result);

static inline void CrossRows(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb)
{
    axb->x = (a->y * b->z - a->z * b->y) >> 12;
    axb->y = (a->z * b->x - a->x * b->z) >> 12;
    axb->z = (a->x * b->y - a->y * b->x) >> 12;
}

void ModelAnimation_GetJointSRTResult_02039a54(const NNSG3dResJntAnm *jointAnimation, u32 *srtTag, u32 tag,
                                               fx32 animationFrame, NNSG3dJntAnmResult *result, fx32 *scaleAndInverse)
{
    u32 *trackData;

    result->flags = 0;
    trackData = srtTag + 1;

    if (!(tag & 0x6)) {
        if (!(tag & 0x8)) {
            ModelAnimation_BlendJointTranslation_02039280(&result->position.x, animationFrame, trackData, jointAnimation);
            trackData += 2;
        } else {
            result->position.x = (fx32)*trackData;
            trackData += 1;
        }
        if (!(tag & 0x10)) {
            ModelAnimation_BlendJointTranslation_02039280(&result->position.y, animationFrame, trackData, jointAnimation);
            trackData += 2;
        } else {
            result->position.y = (fx32)*trackData;
            trackData += 1;
        }
        if (!(tag & 0x20)) {
            ModelAnimation_BlendJointTranslation_02039280(&result->position.z, animationFrame, trackData, jointAnimation);
            trackData += 2;
        } else {
            result->position.z = (fx32)*trackData;
            trackData += 1;
        }
    } else {
        if (tag & 0x2) {
            result->flags |= 4;
        } else {
            ModelAnimation_ApplyDefaultJointPosition_02038ea8(result);
        }
    }

    if (!(tag & 0xc0)) {
        if (!(tag & 0x100)) {
            ModelAnimation_BlendJointRotation_02039728(&result->rotation, animationFrame, trackData, jointAnimation);
            trackData += 2;
        } else {
            if (DecodeCompressedRotationITCM_01ffd56c(&result->rotation,
                                                     (const u8 *)jointAnimation + jointAnimation->compactRotationOffset,
                                                     (const u8 *)jointAnimation + jointAnimation->fullRotationOffset,
                                                     *trackData)) {
                CrossRows((const VecFx32 *)&result->rotation._00, (const VecFx32 *)&result->rotation._10,
                          (VecFx32 *)&result->rotation._20);
            }
            trackData += 1;
        }
    } else {
        if (tag & 0x40) {
            result->flags |= 2;
        } else {
            NNSi_G3dGetMdlRot_02038fd0(result);
        }
    }

    if (!(tag & 0x600)) {
        if (!(tag & 0x800)) {
            fx32 xPair[2];

            ModelAnimation_BlendJointScale_020395a8(xPair, animationFrame, trackData, jointAnimation);
            scaleAndInverse[0] = xPair[0];
            scaleAndInverse[3] = xPair[1];
        } else {
            scaleAndInverse[0] = trackData[0];
            scaleAndInverse[3] = trackData[1];
        }
        trackData += 2;

        if (!(tag & 0x1000)) {
            fx32 yPair[2];

            ModelAnimation_BlendJointScale_020395a8(yPair, animationFrame, trackData, jointAnimation);
            scaleAndInverse[1] = yPair[0];
            scaleAndInverse[4] = yPair[1];
        } else {
            scaleAndInverse[1] = trackData[0];
            scaleAndInverse[4] = trackData[1];
        }
        trackData += 2;

        if (!(tag & 0x2000)) {
            fx32 zPair[2];

            ModelAnimation_BlendJointScale_020395a8(zPair, animationFrame, trackData, jointAnimation);
            scaleAndInverse[2] = zPair[0];
            scaleAndInverse[5] = zPair[1];
        } else {
            scaleAndInverse[2] = trackData[0];
            scaleAndInverse[5] = trackData[1];
        }
        trackData += 2;
    } else {
        if (tag & 0x200) {
            result->flags |= 1;
        } else {
            ModelAnimation_ApplyDefaultJointScale_02038f3c(result);
        }
    }
}
