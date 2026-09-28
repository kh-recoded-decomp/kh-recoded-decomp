#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u16 unk_02;
    u32 rawValue;
} ScriptOperand;

typedef struct RoamPath {
    VecFx32 *points;
    s8 pointCount;
    s8 pathId;
    u8 pad_06[0x2];
} RoamPath;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, ScriptOperand *operand);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void *func_ov001_0207f028(int groupIndex);
extern void CreateRoamingObject_02084a0c(void *group, u16 kind, u16 saveBitOffset, u8 saveBitCount,
                                         s8 pathCount, RoamPath *paths);

int ScriptCmd_CreateRoamingObject_02080430(void *vm, ScriptOperand *operands)
{
    u16 saveBitOffset;
    u8 saveBitCount;
    s8 pathCount;
    s8 pointCount;
    s8 pathIndex;
    RoamPath *paths;
    int groupIndex;
    int kind;
    u32 saveBits;
    s8 pointIndex;

    groupIndex = ScriptVm_ReadOperandInt_02025de4(vm, &operands[0]);
    kind = ScriptVm_ReadOperandInt_02025de4(vm, &operands[1]);
    saveBits = operands[2].rawValue;
    saveBitOffset = saveBits;
    saveBitCount = (u16)(saveBits >> 16);
    operands += 3;
    pathCount = ScriptVm_ReadOperandInt_02025de4(vm, operands++);
    paths = NNSi_FndAllocFromDefaultHeap_0202a178(pathCount * sizeof(RoamPath));
    for (pathIndex = 0; pathIndex < pathCount; pathIndex++) {
        paths[pathIndex].pathId = ScriptVm_ReadOperandInt_02025de4(vm, operands++);
        pointCount = ScriptVm_ReadOperandInt_02025de4(vm, operands++);
        paths[pathIndex].pointCount = pointCount;
        paths[pathIndex].points = NNSi_FndAllocFromDefaultHeap_0202a178(pointCount * sizeof(VecFx32));
        for (pointIndex = 0; pointIndex < pointCount; pointIndex++) {
            paths[pathIndex].points[pointIndex].x = ScriptVm_ReadOperandFx32_02025df8(vm, operands++);
            paths[pathIndex].points[pointIndex].y = ScriptVm_ReadOperandFx32_02025df8(vm, operands++);
            paths[pathIndex].points[pointIndex].z = ScriptVm_ReadOperandFx32_02025df8(vm, operands++);
        }
    }
    CreateRoamingObject_02084a0c(func_ov001_0207f028(groupIndex), kind, saveBitOffset, saveBitCount,
                                 pathCount, paths);
    return 1;
}
