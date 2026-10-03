#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject FieldObject;

typedef struct FieldObjectClass {
    u8 pad_00[4];
    BOOL (*canSpawn)(FieldObject *object);
    void (*onSpawn)(FieldObject *object);
    void (*onAllSpawned)(FieldObject *object);
    u8 pad_10[0x4c];
    void *modelData;
    void *animData;
    u8 pad_64[2];
    s16 animIndex;
    u8 pad_68[0x16];
    u8 flags;
    u8 spawnTarget;
    u8 spawnCount;
} FieldObjectClass;

typedef struct SpawnAnim {
    u16 flags;
    u8 pad_02[0x7a];
    u16 angle;
    u8 pad_7e[0x26];
    VecFx32 position;
} SpawnAnim;

typedef struct SpawnWork {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0a[0x82];
    void *model;
    u16 angle;
    u8 pad_92[0x26];
    VecFx32 position;
    u8 pad_c4[0xfc];
    s32 linkedValue;
} SpawnWork;

struct FieldObject {
    u8 pad_00[8];
    FieldObjectClass *objectClass;
    SpawnWork *work;
    SpawnAnim *anim;
    u8 pad_14[0x28];
    s16 probeRadius;
    u8 pad_3e[0x10];
    u16 stateFlags;
    u8 pad_50[4];
    s32 linkedValue;
};

extern void func_02036a90(SpawnWork *work, void *callback);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_0202ed9c(void *anim, void *model, void *data, int mode);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void SetObjectProbeSphere_020361b8(SpawnWork *work, BOOL enable, fx32 radius);
extern void Model_SetAllPolygonIds_0201a8c0(void *model, int polygonId);
extern void func_ov001_0207f2bc(void);

BOOL FieldObject_TrySpawn_0207f508(FieldObject *object)
{
    BOOL ready;
    FieldObjectClass *objectClass;
    SpawnAnim *anim;

    objectClass = object->objectClass;

    if (objectClass->flags & 1) {
        ready = TRUE;
        if (objectClass->canSpawn != NULL && (ready = objectClass->canSpawn(object)) != FALSE) {
            objectClass->flags |= 2;
        }
        if (ready != FALSE) {
            objectClass->flags &= ~1;
        } else {
            return FALSE;
        }
    }
    if (!(objectClass->flags & 1) && !(object->stateFlags & 4)) {
        if (objectClass->onSpawn != NULL) {
            objectClass->onSpawn(object);
            objectClass->spawnCount++;
            func_02036a90(object->work, func_ov001_0207f2bc);
            if (objectClass->animIndex >= 0) {
                object->anim = NNSi_FndAllocFromDefaultHeap_0202a178(0x104);
                func_0202ed9c(object->anim, object->objectClass->modelData, object->objectClass->animData, 3);
                RebindAnimTracks_020809d0(object->anim, 0, 0);
                object->anim->position = object->work->position;
                anim = object->anim;
                anim->angle = object->work->angle;
                anim->flags |= 0x20;
            }
            if (objectClass->spawnCount == objectClass->spawnTarget && objectClass->onAllSpawned != NULL) {
                objectClass->onAllSpawned(object);
            }
            if ((object->stateFlags & 8) && (object->work->flags & 4)) {
                SetObjectProbeSphere_020361b8(object->work, TRUE, object->probeRadius);
                if (object->stateFlags & 0x80) {
                    Model_SetAllPolygonIds_0201a8c0(object->work->model, 0x3f);
                }
            }
            if (object->work != NULL) {
                object->work->linkedValue = object->linkedValue;
            }
        }
        object->stateFlags |= 4;
    }
    return TRUE;
}
