#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GridManager {
    u8 pad_00[0x59];
    u8 listId;
} GridManager;

typedef struct GridActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7a];
    u16 animFrame;
    u8 pad_82[0x8a];
    u8 collision[4];
} GridActor;

typedef struct GridObject {
    u8 pad_00[4];
    GridManager *manager;
    void *node;
    u8 pad_0C[0x24];
    u16 statusFlags;
    u8 slot;
    u8 group;
    u8 pad_34[4];
    VecFx32 position;
    u8 pad_44[3];
    s8 idleAnim;
    u8 pad_48;
    s8 cellsX;
    s8 cellsY;
    s8 cellsZ;
} GridObject;

typedef struct ShapeBuffer {
    u8 data[20];
} ShapeBuffer;

extern void func_ov001_0208078c(void *node, int listId, int group, int slot, ShapeBuffer *shape, int kind, fx32 sizeX,
                                fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int mask);
extern void func_020358b0(int slot, u16 *counter, int arg, int mode);
extern GridActor *func_02036240(int slot);
extern void Obj_SetPosition_0203569c(void *entity, const VecFx32 *position);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *anim);
extern BOOL IsNodeFlagBitClear_020872b8(GridObject *object);
extern void func_020359f8(int slot, int a, int b);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void func_02034050(void *collision, int layer, int mask);
extern void func_ov001_0207f050(int mask);
extern void func_020369c8(int slot, GridObject *object, int offset);

void RestoreGridObjectRecord_020a2640(GridObject *object, int phase, u16 *counter, int arg)
{
    ShapeBuffer shape;
    GridActor *actor;

    if (phase != 2) {
        return;
    }
    func_ov001_0208078c(object->node, object->manager->listId, object->group, object->slot, &shape, 3,
                        object->cellsX * 0x1800, object->cellsY * 0x1800, object->cellsZ * 0x1800, 0, TRUE, 0);
    func_020358b0(object->slot, counter, arg, 4);
    (*counter)++;
    actor = func_02036240(object->slot);
    Obj_SetPosition_0203569c(actor, &object->position);
    if (!(actor->flags & 0x20)) {
        actor->animFrame = 0;
        actor->animFlags |= 0x20;
    }
    RebindAnimTracks_020809d0(&actor->animFlags, object->idleAnim, 0);
    func_0202f4e8(&actor->animFlags);
    if (IsNodeFlagBitClear_020872b8(object)) {
        func_020359f8(object->slot, 0, 0);
    }
    ActorSlot_SetFlag8ByIndex_02036120(object->slot, IsNodeFlagBitClear_020872b8(object));
    func_02034050(actor->collision, 1, 4);
    func_02034050(actor->collision, 3, 0xe);
    func_ov001_0207f050(0xe);
    func_020369c8(object->slot, object, 0x1c);
    object->statusFlags |= 4;
}
