#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct NNSG3dJntAnmResult {
    u32 flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
} NNSG3dJntAnmResult;

typedef struct NNSG3dScaleCacheEntry {
    VecFx32 inverseScale;
    VecFx32 scale;
} NNSG3dScaleCacheEntry;

typedef struct NNSG3dRenderState {
    u8 pad000[0xc4];
    u32 scaleCacheFlags[8];
} NNSG3dRenderState;

extern NNSG3dRenderState *data_0205ab60;
extern NNSG3dScaleCacheEntry data_0205b970[];

void NNSi_G3dGetJointScaleMaya_01ffa73c(NNSG3dJntAnmResult *result, const fx32 *values,
                                const u8 *command, u32 options)
{
    u8 commandFlags = command[3];

    if (options & 4) {
        result->flag |= 1;
        if (commandFlags & 2) {
            u32 nodeId = command[1];
            data_0205ab60->scaleCacheFlags[nodeId >> 5] |= 1 << (nodeId & 0x1f);
        }
    } else {
        result->scale.x = values[0];
        result->scale.y = values[1];
        result->scale.z = values[2];
        if (commandFlags & 2) {
            u32 nodeId = command[1];
            data_0205ab60->scaleCacheFlags[nodeId >> 5] &= ~(1 << (nodeId & 0x1f));
            data_0205b970[nodeId].inverseScale.x = values[3];
            data_0205b970[nodeId].inverseScale.y = values[4];
            data_0205b970[nodeId].inverseScale.z = values[5];
        }
    }

    if (commandFlags & 1) {
        u32 parentId = command[2];
        result->flag |= 0x20;
        if (data_0205ab60->scaleCacheFlags[parentId >> 5] & (1 << (parentId & 0x1f))) {
            result->flag |= 8;
        } else {
            result->scaleEx0 = data_0205b970[parentId].inverseScale;
        }
    }

    result->flag |= 0x10;
}
