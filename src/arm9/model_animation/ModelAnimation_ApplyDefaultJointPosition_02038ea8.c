/* Restores a model joint's default position when using its stored model pose.
 * Reads the current model node from the render command; copies its three translation values or marks zero translation.
 * Inputs use 20.12 fixed-point values where applicable; output is the sampled joint pose.
 * Uncertainty: Shared model-animation code. Callers have not yet established which characters, enemies, or scenery use this copy.
 * Adapted from khdays-decomp/src/calls/func_02026a44.c (CC0-1.0),
 * revision ab832f38b943c15f461228968a89002e1a99c03e. See THIRD_PARTY.md.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed short fx16;
typedef signed long fx32;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

typedef struct MtxFx33 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
} MtxFx33;

typedef struct NNSG3dJntAnmResult {
    u32 flags;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx33 rotation;
    VecFx32 position;
} NNSG3dJntAnmResult;

typedef struct NNSG3dResDictTreeNode {
    u8 referenceBit, leftChild, rightChild, entryIndex;
} NNSG3dResDictTreeNode;

typedef struct NNSG3dResDict {
    u8 revision;
    u8 entryCount;
    u16 dictionarySize;
    u16 reserved;
    u16 entriesOffset;
    NNSG3dResDictTreeNode node[1];
} NNSG3dResDict;

typedef struct NNSG3dResDictEntryHeader {
    u16 entrySize;
    u16 namesOffset;
    u8 entryData[4];
} NNSG3dResDictEntryHeader;

typedef struct NNSG3dResNodeInfo {
    NNSG3dResDict dictionary;
} NNSG3dResNodeInfo;

typedef struct NNSG3dResDictNodeData {
    u32 offset;
} NNSG3dResDictNodeData;

typedef struct NNSG3dResNodeData {
    u16 flags;
    fx16 _00;
} NNSG3dResNodeData;

typedef struct NNSG3dRS {
    const u8 *renderCommand;
    u8 padding_004_to_0d4[0xd0];
    const NNSG3dResNodeInfo *modelJointInfo;
} NNSG3dRS;

extern NNSG3dRS *g_modelRenderState;

static inline void *NNS_G3dGetResDataByIdx(const NNSG3dResDict *dictionary, u32 entryIndex)
{
    NNSG3dResDictEntryHeader *entryHeader;

    if (dictionary != 0 && entryIndex < dictionary->entryCount) {
        entryHeader = (NNSG3dResDictEntryHeader *)((u8 *)dictionary + dictionary->entriesOffset);
        return (void *)(&entryHeader->entryData[0] + entryHeader->entrySize * entryIndex);
    } else {
        return 0;
    }
}

static inline const NNSG3dResNodeData *NNS_G3dGetNodeDataByIdx(const NNSG3dResNodeInfo *modelJointInfo, u32 entryIndex)
{
    NNSG3dResDictNodeData *entryData;

    if (modelJointInfo) {
        entryData = (NNSG3dResDictNodeData *)NNS_G3dGetResDataByIdx(&modelJointInfo->dictionary, entryIndex);
        if (entryData) {
            return (const NNSG3dResNodeData *)((const u8 *)modelJointInfo + entryData->offset);
        }
    }
    return 0;
}

void ModelAnimation_ApplyDefaultJointPosition_02038ea8(NNSG3dJntAnmResult *jointPose)
{
    u32 jointIndex;
    const NNSG3dResNodeData *jointData;

    jointIndex = *(g_modelRenderState->renderCommand + 1);
    jointData = NNS_G3dGetNodeDataByIdx(g_modelRenderState->modelJointInfo, jointIndex);

    if (jointData->flags & 1) {
        jointPose->flags |= 4;
    } else {
        const fx32 *defaultPosition = (const fx32 *)((const u8 *)jointData + sizeof(NNSG3dResNodeData));

        jointPose->position.x = *(defaultPosition + 0);
        jointPose->position.y = *(defaultPosition + 1);
        jointPose->position.z = *(defaultPosition + 2);
    }
}
