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
    u8 pad_48;
    s8 stackCount;
} PanelStack;

typedef struct {
    u32 flags;
    u16 drawFlags;
    u8 pad_06[0x7a];
    u16 unk_80;
    u8 pad_82[0x8a];
    u8 collision[4];
} Actor;

extern void func_ov001_0208078c(void *model, u8 modelKind, u8 paletteId, u8 actorId, void *out, int mode, int x, int y, int z, int a, int b, int c);
extern void func_020358b0(int index, u16 *counter, int arg, int count);
extern Actor *func_02036240(u32 id);
extern void func_ov001_020809d0(void *target, int value, int extra);
extern void func_0202f4e8(void *target);
extern void Obj_SetPosition_0203569c(Actor *actor, const s32 *position);
extern void func_020359f8(int index, int a, int b);
extern void func_02034050(void *target, int a, int b);
extern int func_ov001_020872b8(PanelStack *obj);
extern void func_ov001_0207f050(u32 bit);

void LoadPanelStackPhase_020a349c(PanelStack *obj, int phase, u16 *counter, int arg)
{
    u8 buffer[20];
    Actor *actor;

    if (phase == 2) {
        func_ov001_0208078c(obj->model, obj->def->modelKind, obj->paletteId, obj->actorId, buffer, 3, 0x1800, obj->stackCount * 0x1800, 0x1800, 0, 1, 0);
        func_020358b0(obj->actorId, counter, arg, 4);
        (*counter)++;
        actor = func_02036240(obj->actorId);
        Obj_SetPosition_0203569c(actor, obj->position);
        if (!(actor->flags & 0x20)) {
            actor->unk_80 = 0;
            actor->drawFlags |= 0x20;
        }
        func_ov001_020809d0(&actor->drawFlags, obj->animIndex, 0);
        func_0202f4e8(&actor->drawFlags);
        if (func_ov001_020872b8(obj)) {
            func_020359f8(obj->actorId, 0, 0);
        }
        func_02034050(actor->collision, 1, 4);
        func_02034050(actor->collision, 3, 0xc);
        func_ov001_0207f050(0xc);
        obj->renderFlags |= 4;
    }
}
