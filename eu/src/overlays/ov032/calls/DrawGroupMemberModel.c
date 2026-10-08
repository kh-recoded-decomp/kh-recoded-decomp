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
    u8 pad_00[0x54];
    u32 flags;
} GeometryCommandCache;

extern void func_ov032_020bbc80(DisplayObject *object);
extern ObjectRecord *func_ov032_020bbc98(DisplayObject *object);
extern void RebindAnimTracks(SceneNode *node, int blendIndex, int frame);
extern LinkedActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_Concat33(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *ab);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void SceneNode_Draw(SceneNode *node);
extern int FX_Atan2Idx(fx32 y, fx32 x);
extern void NNS_G3dGlbSetBaseTrans(const VecFx32 *target);
extern void MI_Copy36B(const MtxFx33 *src, MtxFx43 *dst);
extern void NNS_G3dGlbSetBaseScale(const VecFx32 *scale);
extern void NNS_G3dGlbFlushP(void);

extern const s16 data_02053580[];
extern const VecFx32 data_ov032_020bffd0;
extern MtxFx43 NNS_G3dGlb_prmBaseRot;
extern GeometryCommandCache NNS_G3dGlb_prmMatColor0;

void DrawGroupMemberModel(DisplayObject *object, const VecFx32 *position)
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

    func_ov032_020bbc80(object);
    record = func_ov032_020bbc98(object);
    node = object->nodeTable->nodes[record->nodeIndex];
    rotation = record->rotation;
    RebindAnimTracks(node, object->animBlend, 0);
    if (object->kind == 6) {
        node->angleY = ((object->direction + 2) & 3) << 14;
        node->flags |= 0x20;
    } else if (object->kind == 11) {
        LinkedActor *actor = ActorRegistry_GetEntityByIndex(object->actorId);
        u16 angle = object->angle;
        actorScale = actor->scale;
        node->angleY = actor->angleY;
        node->flags |= 0x20;
        MTX_RotY33_(&node->rotation, data_02053580[angle >> 4], data_02053580[(0x400 - (angle >> 4)) & 0xfff]);
        MTX_Concat33(&node->rotation, &rotation, &rotation);
        if (actorScale.x != 0x1000 || actorScale.y != 0x1000 || actorScale.z != 0x1000) {
            ScaleVecFx32InPlace(&actorScale, 0x10cd);
        }
        node->scale = actorScale;
    }
    node->rotation = rotation;
    node->flags &= ~0x20;
    VEC_Subtract(position, &record->origin, &offset);
    node->translation = offset;
    SceneNode_Draw(node);
    forward = data_ov032_020bffd0;
    MTX_MultVec33(&forward, &record->rotation, &forward);
    index = FX_Atan2Idx(forward.x, forward.z) >> 4;
    MTX_RotY33_(&rotation, data_02053580[index], data_02053580[(0x400 - index) & 0xfff]);
    NNS_G3dGlbSetBaseTrans(&object->cameraTarget);
    MI_Copy36B(&rotation, &NNS_G3dGlb_prmBaseRot);
    NNS_G3dGlb_prmMatColor0.flags &= ~0xa4;
    scale.x = 0x1800;
    scale.y = 0x1800;
    scale.z = 0x1800;
    scaleCopy = scale;
    NNS_G3dGlbSetBaseScale(&scaleCopy);
    NNS_G3dGlbFlushP();
}
