#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ObjectClass {
    u8 pad_00[0x54];
    s32 drawParamA;
    s32 drawParamB;
    u8 pad_5c[0x14];
    fx32 scaleX;
    fx32 scaleY;
    fx32 scaleZ;
    s8 kind;
    u8 pad_7d[7];
    s32 loaded;
    u8 animState[0xd8];
    u8 blendTable[4];
} ObjectClass;

typedef struct ActorBody {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7a];
    u16 rotation;
    u8 pad_82[0x8a];
    u8 collision[4];
} ActorBody;

typedef struct FieldObject {
    u8 pad_00[0x8];
    ObjectClass *objectClass;
    void *model;
    u8 pad_10[0x28];
    u8 actorId;
    u8 slotX;
    u8 slotY;
    u8 pad_3b[5];
    VecFx32 position;
    u16 rotation;
    u16 flags;
    u8 pad_50[3];
    s8 animTrack;
} FieldObject;

extern void FieldGroup_ShufflePositions_020a0f30(ObjectClass *objectClass);
extern u32 ObjectManager_GetFirstEntryParam_0207ee14(int index);
extern u32 ObjectManager_GetSecondEntryParam_0207ee48(int index);
extern void *RetainOrInitializeSharedRecord_0202c80c(int a, int b);
extern void *func_0202c48c(u32 fileId, u32 mode);
extern void func_0202ed9c(void *animState, void *record, void *block, int count);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void selectJointAnimationBlend_0202f2cc(void *animState, int trackIndex, void *blendTable, int blendIndex);
extern void func_ov001_0208078c(void *model, int slotX, int slotY, int actorId, void *work, int kind,
                                fx32 scaleX, fx32 scaleY, fx32 scaleZ, int rotation, BOOL visible, int arg);
extern void func_020358b0(int index, int a1, int a2, int a3);
extern ActorBody *func_02036240(int actorId);
extern void Obj_SetPosition_0203569c(ActorBody *actor, const VecFx32 *position);
extern void RebindAnimTracks_020809d0(u16 *anim, int blendIndex, int frame);
extern void func_0202f4e8(u16 *anim);
extern BOOL IsObjectFlagClear_0207f7a4(FieldObject *object);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void func_020359f8(int index, int param2, int param3);
extern void func_02034050(void *collision, int a, int b);

static inline void Actor_InitRotation(ActorBody *actor, u16 rotation)
{
    if ((actor->flags & 0x20) == 0) {
        actor->rotation = rotation;
        actor->animFlags |= 0x20;
    }
}

void FieldObject_LoadAndPlace_020a07bc(FieldObject *object)
{
    ObjectClass *objectClass = object->objectClass;
    ActorBody *actor;
    u8 work[0x14];

    if (objectClass->loaded == 0) {
        void *record;
        void *block;
        objectClass->loaded = 1;
        FieldGroup_ShufflePositions_020a0f30(objectClass);
        record = RetainOrInitializeSharedRecord_0202c80c(ObjectManager_GetFirstEntryParam_0207ee14(0xcb), 3);
        block = func_0202c48c(ObjectManager_GetSecondEntryParam_0207ee48(0xcb), 3);
        func_0202ed9c(objectClass->animState, record, block, 3);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
        selectJointAnimationBlend_0202f2cc(objectClass->animState, 0, objectClass->blendTable, 0);
        selectJointAnimationBlend_0202f2cc(objectClass->animState, 2, objectClass->blendTable, 0);
    }
    func_ov001_0208078c(object->model, object->slotX, object->slotY, object->actorId, work, objectClass->kind,
                        objectClass->scaleX, objectClass->scaleY, objectClass->scaleZ, object->rotation,
                        (object->flags & 8) == 0, 1);
    func_020358b0(object->actorId, objectClass->drawParamA, objectClass->drawParamB, 3);
    actor = func_02036240(object->actorId);
    Obj_SetPosition_0203569c(actor, &object->position);
    Actor_InitRotation(actor, object->rotation);
    RebindAnimTracks_020809d0(&actor->animFlags, object->animTrack, 0);
    func_0202f4e8(&actor->animFlags);
    if (IsObjectFlagClear_0207f7a4(object)) {
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, TRUE);
        func_020359f8(object->actorId, 0, 0);
        func_02034050(actor->collision, 1, 4);
    } else {
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, FALSE);
    }
}
