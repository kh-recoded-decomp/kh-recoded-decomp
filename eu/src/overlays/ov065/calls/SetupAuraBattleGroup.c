#include "src/overlays/ov021/GroupSpawnParams.h"

typedef struct AuraBattleObject {
    u8 unknown00[8];
    u32 id;
    u8 unknown0c[0x84 - 0xc];
    UnitGroup *group;
    u32 archive;
} AuraBattleObject;

typedef char AuraBattleIdOffset[(u32)&((AuraBattleObject *)0)->id == 8 ? 1 : -1];
typedef char AuraBattleGroupOffset[(u32)&((AuraBattleObject *)0)->group == 0x84 ? 1 : -1];
typedef char AuraBattleArchiveOffset[(u32)&((AuraBattleObject *)0)->archive == 0x88 ? 1 : -1];

extern BOOL UpdateStoppingEffect(UnitGroup *, GroupUnit *, fx32);

#define ARCHIVE_FILE(archive, index) \
    ((((archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((index) & 0x1ff))

void SetupAuraBattleGroup(void *unused, AuraBattleObject *object)
{
    GroupSpawnParams params;

    ResetMotionState(&params);
    params.flags = 0x40;
    params.unknown04 = 0;
    params.unknown0c = 0x1800;
    params.speedScale = 0x99a;
    params.maxDistance = 0x14000;
    params.unknown20 = 0x1000;
    params.unknown54 = 0x1000;
    params.duration = 0x14000;
    params.unknown50 = 0x2400;
    params.unknown4c = 2;
    params.linkA = object->id;
    params.linkB = 1;
    params.position.y = 0;
    params.position.x = 0x100;
    params.position.z = 0x100;
    params.unknown30 = 0;
    params.unitCount = 5;
    SetupOwnerAndEntries(object->group, ARCHIVE_FILE(object->archive, 2),
                        ARCHIVE_FILE(object->archive, 3), &params, 1, 5);
    object->group->advance = UpdateStoppingEffect;
}

#undef ARCHIVE_FILE
