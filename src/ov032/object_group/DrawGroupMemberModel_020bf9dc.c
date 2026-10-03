#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct SceneNode {
    u16 flags;
    u8 pad_02[0x7a];
    u16 angleY;
    u16 angleX;
    MtxFx33 rotation;
    VecFx32 translation;
    VecFx32 scale;
} SceneNode;

typedef struct NodeTable {
    u8 pad_00[0x60];
    SceneNode *nodes[1];
} NodeTable;

typedef struct ObjectRecord {
    u8 pad_00[0x8];
    u32 unk_08_lo : 5;
    u32 nodeIndex : 8;
    u32 unk_08_hi : 19;
    u8 pad_0C[0x28];
    MtxFx33 rotation;
    VecFx32 origin;
} ObjectRecord;

typedef struct LinkedActor {
    u8 pad_00[0x80];
    u16 angleY;
    u8 pad_82[0x32];
    VecFx32 scale;
} LinkedActor;

typedef struct DisplayObject {
    u8 pad_00[0x4];
    NodeTable *nodeTable;
    u8 pad_08[0x2a];
    u8 actorId;
    u8 pad_33[0x5];
    VecFx32 cameraTarget;
    u8 pad_44[0x3];
    s8 animBlend;
    u8 pad_48[0x28];
    u16 unk_70_lo : 7;
    u16 direction : 2;
    u16 unk_70_hi : 7;
    u8 pad_72[0x5];
    u8 kind;
    u8 pad_78[0x5c];
    u32 angle;
} DisplayObject;

typedef struct GeometryCommandCache {
    u8 pad_00[0xd4];
    u32 flags;
} GeometryCommandCache;

extern void func_ov032_020bbc60(DisplayObject *object);
extern ObjectRecord *func_ov032_020bbc78(DisplayObject *object);
extern void RebindAnimTracks_020809d0(SceneNode *node, int blendIndex, int frame);
extern LinkedActor *func_02036240(u32 actorId);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_Concat33_01ff9270(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *ab);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_0204a5e4(VecFx32 *vec, fx32 scale);
extern void SceneNode_Draw_01ffb12c(SceneNode *node);
extern int FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern void func_020192ec(const VecFx32 *target);
extern void func_01ff87c4(const MtxFx33 *src, MtxFx43 *dst);
extern void func_0201931c(const VecFx32 *scale);
extern void func_02019188(void);

extern const s16 data_0205356c[];
extern const VecFx32 data_ov032_020bffb0;
extern MtxFx43 data_0205a9b8;
extern GeometryCommandCache data_0205a924;

void DrawGroupMemberModel_020bf9dc(DisplayObject *object, const VecFx32 *position)
{
    ObjectRecord *record;
    SceneNode *node;
    MtxFx33 rotation;
    VecFx32 actorScale;
    VecFx32 forward;
    VecFx32 scaleCopy;
    VecFx32 offset;
    VecFx32 scale;
    int index;

    func_ov032_020bbc60(object);
    record = func_ov032_020bbc78(object);
    node = object->nodeTable->nodes[record->nodeIndex];
    rotation = record->rotation;
    RebindAnimTracks_020809d0(node, object->animBlend, 0);
    if (object->kind == 6) {
        node->angleY = ((object->direction + 2) & 3) << 14;
        node->flags |= 0x20;
    } else if (object->kind == 11) {
        LinkedActor *actor = func_02036240(object->actorId);
        u16 angle = object->angle;
        actorScale = actor->scale;
        node->angleY = actor->angleY;
        node->flags |= 0x20;
        MTX_RotY33_01ff923c(&node->rotation, data_0205356c[angle >> 4], data_0205356c[(0x400 - (angle >> 4)) & 0xfff]);
        MTX_Concat33_01ff9270(&node->rotation, &rotation, &rotation);
        if (actorScale.x != 0x1000 || actorScale.y != 0x1000 || actorScale.z != 0x1000) {
            func_0204a5e4(&actorScale, 0x10cd);
        }
        node->scale = actorScale;
    }
    node->rotation = rotation;
    node->flags &= ~0x20;
    VEC_Subtract_01ff9e3c(position, &record->origin, &offset);
    node->translation = offset;
    SceneNode_Draw_01ffb12c(node);
    forward = data_ov032_020bffb0;
    MTX_MultVec33_01ff9404(&forward, &record->rotation, &forward);
    index = FixedPointAtan2_020062bc(forward.x, forward.z) >> 4;
    MTX_RotY33_01ff923c(&rotation, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
    func_020192ec(&object->cameraTarget);
    func_01ff87c4(&rotation, &data_0205a9b8);
    data_0205a924.flags &= ~0xa4;
    scale.x = 0x1800;
    scale.y = 0x1800;
    scale.z = 0x1800;
    scaleCopy = scale;
    func_0201931c(&scaleCopy);
    func_02019188();
}
