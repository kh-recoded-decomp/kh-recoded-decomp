#pragma optimization_level 4
#pragma opt_lifetimes on
#pragma opt_common_subs on
#pragma opt_propagation on
#include "src/overlays/ov021/GroupSpawnParams.h"

typedef struct BossBattleObject {
    u8 unknown00[0x84];
    UnitGroup *group;
    u32 archive;
} BossBattleObject;

#define GROUP_CHECK_OFFSET(type, field, offset, name) \
    typedef char name[(u32)&((type *)0)->field == (offset) ? 1 : -1]
GROUP_CHECK_OFFSET(BossBattleObject, group, 0x84, BossBattleGroupOffset);
GROUP_CHECK_OFFSET(BossBattleObject, archive, 0x88, BossBattleArchiveOffset);
#undef GROUP_CHECK_OFFSET

extern BOOL AdvanceGroupUnitPhase(UnitGroup *, GroupUnit *, fx32);

#define ARCHIVE_FILE(archive, index) \
    ((((archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((index) & 0x1ff))

void SetupBossBattleGroup(void *unused, BossBattleObject *object)
{
    GroupSpawnParams params;

    ResetMotionState(&params);
    params.flags = 2;
    params.unknown04 = 0;
    params.duration = 0x7fffffff;
    params.unknown20 = 0x1000;
    params.startHidden = 0x1000;
    params.unknown50 = 0x1800;
    params.unknown54 = 0x1800;
    params.linkA = -1;
    params.linkB = -1;
    params.unknown4c = 2;
    params.position.y = 0;
    params.position.x = 0x100;
    params.position.z = 0x100;
    params.unknown30 = 1;
    params.unitCount = 5;
    SetupOwnerAndEntries(object->group, ARCHIVE_FILE(object->archive, 0),
                        ARCHIVE_FILE(object->archive, 1), &params, 1, 5);
    object->group->advance = AdvanceGroupUnitPhase;
}

#undef ARCHIVE_FILE
