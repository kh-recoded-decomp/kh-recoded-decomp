#ifndef EU_GROUP_SPAWN_PARAMS_H
#define EU_GROUP_SPAWN_PARAMS_H

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupSpawnParams {
    u32 flags;
    s32 unknown04;
    u8 unknown08[4];
    fx32 unknown0c;
    u8 unknown10[4];
    fx32 speedScale;
    fx32 maxDistance;
    s32 duration;
    s32 unknown20;
    s32 startHidden;
    u8 unknown28[8];
    s32 unknown30;
    u8 unknown34[0xc];
    VecFx32 position;
    s32 unknown4c;
    fx32 unknown50;
    fx32 unknown54;
    s16 linkA;
    s16 linkB;
    s8 unitCount;
    u8 unknown5d[3];
} GroupSpawnParams;

typedef struct GroupUnit GroupUnit;
typedef struct UnitGroup UnitGroup;
struct UnitGroup {
    u8 unknown00[0x2c];
    BOOL (*advance)(UnitGroup *, GroupUnit *, fx32);
};

typedef char GroupSpawnParamsIs96Bytes[sizeof(GroupSpawnParams) == 0x60 ? 1 : -1];
#define GROUP_PARAM_CHECK(field, offset, name) \
    typedef char name[(u32)&((GroupSpawnParams *)0)->field == (offset) ? 1 : -1]
GROUP_PARAM_CHECK(speedScale, 0x14, GroupSpeedScaleOffset);
GROUP_PARAM_CHECK(maxDistance, 0x18, GroupMaxDistanceOffset);
GROUP_PARAM_CHECK(duration, 0x1c, GroupDurationOffset);
GROUP_PARAM_CHECK(startHidden, 0x24, GroupStartHiddenOffset);
GROUP_PARAM_CHECK(position, 0x40, GroupPositionOffset);
GROUP_PARAM_CHECK(unitCount, 0x5c, GroupUnitCountOffset);
#undef GROUP_PARAM_CHECK
typedef char GroupAdvanceOffset[(u32)&((UnitGroup *)0)->advance == 0x2c ? 1 : -1];

extern void ResetMotionState(GroupSpawnParams *params);
extern void SetupOwnerAndEntries(UnitGroup *group, u32 modelFile, u32 animationFile,
                                GroupSpawnParams *params, int descriptorCount, int slotCount);

#endif
