#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SceneMatrix {
    VecFx32 xAxis;
    VecFx32 yAxis;
    VecFx32 zAxis;
    VecFx32 translation;
} SceneMatrix;

typedef struct SceneNodeView {
    u16 flags;
    u8 reserved02[0x20 - 2];
    u32 renderFlags;
    u8 reserved24[0x78 - 0x24];
    void *model;
    u16 yaw;
    u16 pitch;
    SceneMatrix matrix;
    VecFx32 scale;
    u8 reservedbc[0x40];
    u16 colorScale;
} SceneNodeView;

typedef struct ScenePart {
    u32 flags;
    SceneNodeView node;
} ScenePart;

typedef struct FieldSceneActor {
    u8 reserved000[0x10];
    ScenePart part;
    u8 reserved114[0x27c - 0x114];
    u16 drawableId;
    u8 reserved27e[0x284 - 0x27e];
    u16 firstCollisionId;
    u16 firstAttachmentId;
    u16 attachmentMode : 2;
    u16 reservedMode2 : 2;
    u16 showMarker : 1;
    u16 reservedMode5 : 5;
    u16 positionOnly : 1;
    u16 reservedMode11 : 5;
    u8 reserved28a[0x290 - 0x28a];
    fx32 floorHeight;
    u8 reserved294[0x2b0 - 0x294];
    void *marker;
    u8 reserved2b4[0x2c0 - 0x2b4];
    VecFx32 position;
    u8 reserved2cc[0x2e5 - 0x2cc];
    u8 polygonId;
    u16 yaw;
    u8 reserved2e8[0x320 - 0x2e8];
    u8 alpha;
    u8 reserved321[0x3ac - 0x321];
    u16 ownerId;
    u16 jointId;
    u8 reserved3b0[0x3c8 - 0x3b0];
} FieldSceneActor;

typedef struct AttachedSceneMatrix {
    SceneMatrix matrix;
    u16 nodeId;
    u16 nextAttachmentId : 12;
    u16 applyCorrection : 1;
    u16 keepScale : 1;
    u16 reservedFlags14 : 2;
} AttachedSceneMatrix;

typedef struct CollisionBounds {
    fx32 values[6];
} CollisionBounds;

typedef struct SceneCollisionShape {
    void *data;
    CollisionBounds bounds;
    int kind;
} SceneCollisionShape;

typedef struct SceneCollisionObject {
    u8 reserved00[0x24];
    SceneCollisionShape shape;
    u8 reserved44[0x90 - 0x44];
    VecFx32 offset;
    u8 reserved9c[4];
    u16 nodeId;
    u16 nextCollisionId;
} SceneCollisionObject;

typedef struct SegmentShapeData {
    VecFx32 position;
    VecFx32 endpoint;
    VecFx32 axis;
    fx32 length;
} SegmentShapeData;

typedef struct StageRenderManager {
    u32 flags;
} StageRenderManager;

typedef struct SceneTreeRoot {
    void *root;
} SceneTreeRoot;

typedef struct CollisionRegistry {
    u32 reserved00;
    SceneTreeRoot *tree;
} CollisionRegistry;

#define SCENE_OFFSET_OF(type, member) ((u32)&((type *)0)->member)
#define SCENE_CHECK_OFFSET(type, member, expected, label) \
    typedef char label[SCENE_OFFSET_OF(type, member) == (expected) ? 1 : -1]

typedef char SceneMatrixIs48Bytes[sizeof(SceneMatrix) == 0x30 ? 1 : -1];
typedef char SceneNodeDrawViewIs256Bytes[sizeof(SceneNodeView) == 0x100 ? 1 : -1];
typedef char ScenePartDrawViewIs260Bytes[sizeof(ScenePart) == 0x104 ? 1 : -1];
/* GetStageActor indexes 64 records with a native 0x3c8-byte stride. */
typedef char FieldSceneActorIs968Bytes[sizeof(FieldSceneActor) == 0x3c8 ? 1 : -1];
typedef char AttachedMatrixViewIs52Bytes[sizeof(AttachedSceneMatrix) == 0x34 ? 1 : -1];
/* The stage manager creates 64 entries of each size for these two pools. */
typedef char CollisionPoolEntryIs164Bytes[sizeof(SceneCollisionObject) == 0xa4 ? 1 : -1];
typedef char SegmentShapeIs40Bytes[sizeof(SegmentShapeData) == 0x28 ? 1 : -1];
SCENE_CHECK_OFFSET(FieldSceneActor, part, 0x10, ActorPartOffset);
SCENE_CHECK_OFFSET(SceneNodeView, scale, 0xb0, NodeScaleOffset);
SCENE_CHECK_OFFSET(SceneNodeView, colorScale, 0xfc, NodeColorScaleOffset);
SCENE_CHECK_OFFSET(FieldSceneActor, part.node.matrix, 0x94, ActorMatrixOffset);
SCENE_CHECK_OFFSET(FieldSceneActor, firstCollisionId, 0x284, ActorFirstCollisionOffset);
SCENE_CHECK_OFFSET(FieldSceneActor, firstAttachmentId, 0x286, ActorFirstAttachmentOffset);
SCENE_CHECK_OFFSET(FieldSceneActor, floorHeight, 0x290, ActorFloorOffset);
SCENE_CHECK_OFFSET(FieldSceneActor, position, 0x2c0, ActorPositionOffset);
SCENE_CHECK_OFFSET(FieldSceneActor, polygonId, 0x2e5, ActorPolygonIdOffset);
SCENE_CHECK_OFFSET(FieldSceneActor, yaw, 0x2e6, ActorYawOffset);
SCENE_CHECK_OFFSET(FieldSceneActor, alpha, 0x320, ActorAlphaOffset);
SCENE_CHECK_OFFSET(FieldSceneActor, ownerId, 0x3ac, ActorOwnerIdOffset);
SCENE_CHECK_OFFSET(FieldSceneActor, jointId, 0x3ae, ActorJointIdOffset);
SCENE_CHECK_OFFSET(AttachedSceneMatrix, nodeId, 0x30, AttachedNodeIdOffset);
SCENE_CHECK_OFFSET(SceneCollisionObject, shape, 0x24, CollisionShapeOffset);
SCENE_CHECK_OFFSET(SceneCollisionObject, shape.kind, 0x40, CollisionKindOffset);
SCENE_CHECK_OFFSET(SceneCollisionObject, nodeId, 0xa0, CollisionNodeIdOffset);
SCENE_CHECK_OFFSET(SceneCollisionObject, nextCollisionId, 0xa2, CollisionNextIdOffset);
#undef SCENE_CHECK_OFFSET
#undef SCENE_OFFSET_OF

extern const s16 gSinFx12Table[4096];
extern const VecFx32 gZeroVecFx32;
extern void (*const gCollisionBoundsDispatch[])(SceneCollisionShape *shape, CollisionBounds *bounds);
extern StageRenderManager *GetStageManager(void);
extern FieldSceneActor *GetStageActor(int id);
extern void MTX_RotY33_(void *matrix, fx32 sine, fx32 cosine);
extern void GetNodeMatrix(FieldSceneActor *actor, u32 nodeId, SceneMatrix *matrix);
extern void GetNodePosition(FieldSceneActor *actor, u32 nodeId, VecFx32 *position);
extern void Obj_SetPosition(ScenePart *part, const VecFx32 *position);
extern fx32 FX_Div(fx32 first, fx32 second);
extern fx32 FX_Mul(fx32 first, fx32 second);
extern void MTX_ScaleApply43(const SceneMatrix *source, SceneMatrix *out, fx32 x, fx32 y, fx32 z);
extern BOOL func_ov001_02063a24(void);
extern int func_ov001_02063a38(void);
extern void DrawProximityMarker(FieldSceneActor *actor);
extern void NNS_G3dGlbPolygonAttr(int lights, int polygonMode, int cull, int polygonId, int alpha, int misc);
extern void NNS_G3dMdlSetMdlAlphaAll(void *model, int alpha);
extern void NNS_G3dMdlSetMdlPolygonIDAll(void *model, int id);
extern void SceneNode_DrawImmediate(SceneNodeView *node);
extern AttachedSceneMatrix *GetAttachedObject(FieldSceneActor *actor);
extern BOOL RestoreNodeMatrixWithRotationCorrection(SceneNodeView *node, SceneMatrix *matrix, u32 nodeId, BOOL correct);
extern fx32 VEC_NormalizeLength(const VecFx32 *source, VecFx32 *out);
extern AttachedSceneMatrix *GetObjectAttachment(AttachedSceneMatrix *attached);
extern CollisionRegistry *GetActorRegistry(void);
extern SceneCollisionObject *GetFirstLinkedActor(FieldSceneActor *actor);
extern SceneCollisionObject *GetNextLinkedActor(SceneCollisionObject *object);
extern void SetCollisionObjectPosition(SceneCollisionObject *object, const VecFx32 *position);
extern void MI_Copy36B(const void *source, void *out);
extern void UpdateSegmentEndpoint(SegmentShapeData *shape);
extern void VEC_Add(const VecFx32 *first, const VecFx32 *second, VecFx32 *out);
extern void UpdateBoxAxisAlignedFlag(void *shape);
extern void QuadTree_ReinsertNodeIfFlagSet(void *tree, SceneCollisionObject *object);

/* Draw the actor, then synchronize its attached matrices and collision shapes. */
void UpdateSceneObjectAttachments(FieldSceneActor *actor, int mode)
{
    VecFx32 center;
    VecFx32 basis[3];
    SceneMatrix jointMatrix;
    FieldSceneActor *owner;
    ScenePart *part;
    AttachedSceneMatrix *attached;
    CollisionRegistry *registry;
    SceneCollisionObject *collision;
    BOOL skipRootCollision;
    StageRenderManager *manager = GetStageManager();
    u32 temporaryFlags = 0;
    fx32 floorHeight;
    fx32 heightChange;
    fx32 scale;
    int fieldMode;

    if (actor == NULL || actor->drawableId == 0) {
        return;
    }
    part = &actor->part;
    if (actor->ownerId != 0) {
        owner = GetStageActor((s16)actor->ownerId);
        if (owner != NULL) {
            if (actor->attachmentMode == 2) {
                u32 ownerFlags = part->flags;
                u16 ownerYaw = owner->yaw;
                if (!(ownerFlags & 0x20)) {
                    part->node.yaw = ownerYaw;
                    part->node.flags |= 0x20;
                }
                MTX_RotY33_(&part->node.matrix,
                    gSinFx12Table[part->node.yaw >> 4],
                    gSinFx12Table[(1024 - (part->node.yaw >> 4)) & 4095]);
                Obj_SetPosition(part, &gZeroVecFx32);
            } else {
                if (!actor->positionOnly) {
                    GetNodeMatrix(owner, actor->jointId, &part->node.matrix);
                } else {
                    u32 ownerFlags = part->flags;
                    u16 ownerYaw = owner->yaw;
                    if (!(ownerFlags & 0x20)) {
                        part->node.yaw = ownerYaw;
                        part->node.flags |= 0x20;
                    }
                    MTX_RotY33_(&part->node.matrix,
                        gSinFx12Table[part->node.yaw >> 4],
                        gSinFx12Table[(1024 - (part->node.yaw >> 4)) & 4095]);
                    GetNodePosition(owner, actor->jointId, &part->node.matrix.translation);
                }
                Obj_SetPosition(part, &part->node.matrix.translation);
            }
            part->node.flags &= 0xffdf;
            actor->position = part->node.matrix.translation;
        }
    } else if (!(manager->flags & 1)) {
        part->node.flags &= 0xffdf;
    }
    if (mode == 0 && actor->attachmentMode == 1) {
        ScenePart *floorPart = &actor->part;
        floorHeight = actor->floorHeight;
        if (floorHeight < 0x333) {
            floorHeight = 0x333;
        }
        heightChange = floorPart->node.matrix.translation.y - floorHeight;
        if (heightChange < 0) {
            heightChange = -heightChange;
        }
        floorPart->node.matrix.translation.y = floorHeight;
        Obj_SetPosition(floorPart, &floorPart->node.matrix.translation);
        if (heightChange > 0x4000) {
            heightChange = 0x4000;
        }
        scale = FX_Div(heightChange, 0x4000);
        scale = FX32_ONE - scale;
        scale = FX_Mul(0x99a, scale) + 0x666;
        MTX_ScaleApply43(&floorPart->node.matrix, &floorPart->node.matrix,
                         scale, FX32_ONE, scale);
    }
    if (mode == 0 && actor->showMarker) {
        fieldMode = func_ov001_02063a24() ? func_ov001_02063a38() : 0;
        if (fieldMode != 4 && actor->marker != NULL &&
            actor->attachmentMode == 0 && mode == 0) {
            DrawProximityMarker(actor);
        }
    }
    if (mode != 0 || !actor->showMarker) {
        temporaryFlags |= 4;
    }
    part->node.renderFlags |= temporaryFlags;
    NNS_G3dGlbPolygonAttr(0, 0, 0, 0, actor->alpha, 0);
    NNS_G3dMdlSetMdlAlphaAll(part->node.model, actor->alpha);
    if (actor->polygonId != 0) {
        NNS_G3dMdlSetMdlPolygonIDAll(actor->part.node.model, actor->polygonId);
    }
    SceneNode_DrawImmediate(&part->node);

    {
        ScenePart *parentPart = &actor->part;
        for (attached = GetAttachedObject(actor); attached != NULL;
             attached = GetObjectAttachment(attached)) {
            attached->matrix = parentPart->node.matrix;
            if (attached->nodeId != 0xffff &&
                RestoreNodeMatrixWithRotationCorrection(&parentPart->node,
                    &attached->matrix, attached->nodeId, attached->applyCorrection)) {
                if (!attached->keepScale) {
                    VEC_NormalizeLength(&attached->matrix.xAxis, &attached->matrix.xAxis);
                    VEC_NormalizeLength(&attached->matrix.yAxis, &attached->matrix.yAxis);
                    VEC_NormalizeLength(&attached->matrix.zAxis, &attached->matrix.zAxis);
                }
            }
        }
    }

    registry = GetActorRegistry();
    if (registry != NULL) {
        collision = GetFirstLinkedActor(actor);
        skipRootCollision = TRUE;
        for (; collision != NULL;
             collision = GetNextLinkedActor(collision)) {
            if (!skipRootCollision) {
                GetNodeMatrix(actor, collision->nodeId, &jointMatrix);
                switch (collision->shape.kind) {
                case 0:
                default:
                    SetCollisionObjectPosition(collision, &jointMatrix.translation);
                    QuadTree_ReinsertNodeIfFlagSet(registry->tree->root, collision);
                    break;
                case 3:
                    SetCollisionObjectPosition(collision, &jointMatrix.translation);
                    MI_Copy36B(&jointMatrix, basis);
                    VEC_NormalizeLength(&basis[1], &basis[1]);
                    ((SegmentShapeData *)collision->shape.data)->axis.x = basis[1].x;
                    ((SegmentShapeData *)collision->shape.data)->axis.y = basis[1].y;
                    ((SegmentShapeData *)collision->shape.data)->axis.z = basis[1].z;
                    UpdateSegmentEndpoint(collision->shape.data);
                    gCollisionBoundsDispatch[collision->shape.kind](&collision->shape, &collision->shape.bounds);
                    QuadTree_ReinsertNodeIfFlagSet(registry->tree->root, collision);
                    break;
                case 1:
                    /* The box path also snapshots the original matrix basis. */
                    MI_Copy36B(&jointMatrix, basis);
                    center = jointMatrix.translation;
                    VEC_Add(&center, &collision->offset, &center);
                    center.z = 0;
                    *(VecFx32 *)collision->shape.data = center;
                    UpdateBoxAxisAlignedFlag(collision->shape.data);
                    gCollisionBoundsDispatch[collision->shape.kind](&collision->shape, &collision->shape.bounds);
                    QuadTree_ReinsertNodeIfFlagSet(registry->tree->root, collision);
                    break;
                }
            }
            skipRootCollision = FALSE;
        }
    }
    part->node.renderFlags &= ~temporaryFlags;
}
