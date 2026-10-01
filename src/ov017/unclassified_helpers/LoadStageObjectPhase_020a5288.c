#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x59];
    u8 modelKind;
} ObjectDef;

typedef struct {
    u8 pad_00[4];
    ObjectDef *def;
    void *model;
    u8 pad_0c[0x24];
    u16 renderFlags;
    u8 actorId;
    u8 paletteId;
    u8 pad_34[4];
    s32 position[3];
    u8 pad_44[3];
    s8 animIndex;
    void *resource;
    u8 pad_4c[4];
    s8 state;
    s8 scaleSteps;
    u8 pad_52[2];
    u16 flags;
} StageObject;

typedef struct {
    u32 flags;
    u16 drawFlags;
    u8 pad_06[0x7a];
    u16 unk_80;
    u8 pad_82[0x8a];
    u8 collision[4];
} Actor;

extern int func_ov017_020a5248(StageObject *obj);
extern void *func_ov017_020a51c8(StageObject *obj);
extern void func_ov001_0208078c(void *model, u8 modelKind, u8 paletteId, u8 actorId, void *out, int mode, int x, int y, int z, int a, int b, int c);
extern void func_020358b0(int index, u16 *counter, int arg, int count);
extern Actor *func_02036240(u32 id);
extern void func_ov001_020809d0(void *target, int value, int extra);
extern void func_0202f4e8(void *target);
extern void Obj_SetPosition_0203569c(Actor *actor, const s32 *position);
extern void func_020359f8(int index, int a, int b);
extern void func_020369c8(u32 id, StageObject *obj, int value);
extern void func_02034050(void *target, int a, int b);
extern int func_ov017_020a5dd0(StageObject *obj);
extern int func_ov001_020872b8(StageObject *obj);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void func_ov001_0207f050(u32 bit);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_0202ed9c(void *object, u16 *counter, int arg, int count);
extern void func_0202f4d8(void *object);

static inline BOOL IsState1Or2(StageObject *obj)
{
    return obj->state == 2 || obj->state == 1;
}

void LoadStageObjectPhase_020a5288(StageObject *obj, int phase, u16 *counter, int arg)
{
    u8 buffer[20];
    Actor *actor;
    BOOL enable;
    BOOL canEnable;

    if (phase == func_ov017_020a5248(obj)) {
        if (obj->flags & 1) {
            if (func_ov017_020a51c8(obj) == NULL) {
                return;
            }
            func_ov001_0208078c(obj->model, obj->def->modelKind, obj->paletteId, obj->actorId, buffer, 3, 0x1800, obj->scaleSteps * 0x1800, 0x1800, 0, 1, 0);
        } else {
            func_ov001_0208078c(obj->model, obj->def->modelKind, obj->paletteId, obj->actorId, buffer, -1, 0, 0, 0, 0, 1, 0);
        }
        func_020358b0(obj->actorId, counter, arg, 4);
        (*counter)++;
        actor = func_02036240(obj->actorId);
        func_ov001_020809d0(&actor->drawFlags, obj->animIndex, 0);
        func_0202f4e8(&actor->drawFlags);
        Obj_SetPosition_0203569c(actor, obj->position);
        if (!(actor->flags & 0x20)) {
            actor->unk_80 = 0;
            actor->drawFlags |= 0x20;
        }
        enable = FALSE;
        func_020359f8(obj->actorId, 0, 0);
        func_020369c8(obj->actorId, obj, 0x1b);
        func_02034050(actor->collision, 1, 4);
        canEnable = FALSE;
        if (!func_ov017_020a5dd0(obj) && !IsState1Or2(obj)) {
            canEnable = TRUE;
        }
        if (canEnable && func_ov001_020872b8(obj)) {
            enable = TRUE;
        }
        ActorSlot_SetFlag8ByIndex_02036120(obj->actorId, enable);
        obj->flags |= 0x40;
        func_02034050(actor->collision, 3, 0xe);
        func_ov001_0207f050(0xe);
        obj->renderFlags |= 4;
    } else if (phase == 8) {
        if (!IsState1Or2(obj)) {
            obj->resource = NNSi_FndAllocFromDefaultHeap_0202a178(0x104);
            func_0202ed9c(obj->resource, counter, arg, 4);
            func_ov001_020809d0(obj->resource, 0, 0);
            func_0202f4d8(obj->resource);
            (*counter)++;
        }
    }
}
