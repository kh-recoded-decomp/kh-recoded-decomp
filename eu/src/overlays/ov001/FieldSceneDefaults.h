#ifndef RECODED_FIELD_SCENE_DEFAULTS_H
#define RECODED_FIELD_SCENE_DEFAULTS_H

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SceneSpawn {
    s16 roomId;
    s16 spawnX;
    u8 spawnY;
    u8 pad_05;
} SceneSpawn;

typedef struct SceneSpawnTable {
    SceneSpawn entries[8];
} SceneSpawnTable;

typedef struct IdList5 {
    u32 ids[5];
} IdList5;

typedef struct MtxFx33 {
    fx32 m[9];
} MtxFx33;

extern const SceneSpawnTable gSceneSlotSpawns;
extern const IdList5 gTimedSceneRecordIds;
extern const VecFx32 gDefaultSceneBaseTranslation;
extern const VecFx32 gDefaultSceneBaseScale;
extern const MtxFx33 gDefaultSceneBaseRotation;

#endif
