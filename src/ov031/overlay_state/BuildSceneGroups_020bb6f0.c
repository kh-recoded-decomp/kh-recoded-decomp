#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 min;
    VecFx32 max;
} Box;

typedef struct {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box box;
} ShapeBlock;

typedef struct {
    u8 data[0xd0];
} CollisionPolygon;

typedef struct {
    void *func;
    u32 arg;
} Callback;

typedef struct {
    s32 mode;
    s32 type;
} CollisionInfo;

typedef struct {
    u8 pad_00[0xd];
    u8 enabled;
    u8 pad_0e[0x16];
    ShapeBlock block;
    CollisionInfo info;
    Callback onEnter;
    Callback onStay;
    Callback onLeave;
} GroupObject;

typedef struct {
    u8 hidden;
    u8 slot;
    u8 objectCount;
    u8 locked;
    u8 limit;
    u8 counter;
    u8 pad_06[0x2];
    VecFx32 position;
    CollisionPolygon *polygons;
    GroupObject *objects;
    s32 mode;
} ObjectGroup;

typedef struct {
    fx32 x;
    fx32 z;
} PointXZ;

typedef struct {
    u8 slot;
    u8 pad_01[0x3];
    PointXZ corners[4];
} SceneArea;

typedef struct {
    u8 slot;
    u8 limit;
    u8 pad_02[0x2];
    fx32 x;
    fx32 z;
    s32 mode;
} GroupDesc;

typedef struct {
    u8 pad_00[0x28];
    GroupDesc *groupDescs;
    u8 pad_2c[0xc];
    u8 extraGroupCount;
    u8 pad_39[0x3];
} ActiveRecord;

typedef struct {
    u8 pad_00[0x44];
    s32 recordIndex;
    u8 pad_48[0x8];
    ActiveRecord *records;
    u8 pad_54[0x2];
    u8 activeGroupCount;
    u8 pad_57[0x3];
    u8 areaCount;
    u8 pad_5b[0x5];
    SceneArea *areas;
    ObjectGroup *groups;
    s32 maxDepth[9];
    s32 minDepth[9];
    u8 pad_b0[0x1bc];
    u8 collisionOwner[4];
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern VecFx32 data_02053438;
extern void *func_02036230(void);
extern void func_01ff8710(const void *src, void *dst, int size);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern BOOL InitCollisionObject_02033c7c(GroupObject *object, u16 groupMask, void *owner);
extern void InitPolygonShape_0203af1c(CollisionShape *shape, CollisionPolygon *polygon, u8 vertexCount, const VecFx32 *points);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetShapePosition_0203afa0(CollisionShape *shape, const VecFx32 *position);
extern void IsSupportedOwnerState_020bb574(void);
extern void func_ov031_020bb598(void);
extern void MarkLinkedTargetFlag_020bb5b8(void);

typedef VecFx32 Quad[4];

static inline int FindArea(int start, u8 slot)
{
    int areaCount = g_activeState_020bc800->areaCount;
    SceneArea *areas = g_activeState_020bc800->areas;

    for (; start < areaCount; start++) {
        if (slot == areas[start].slot) {
            return start;
        }
    }
    return -1;
}

void BuildSceneGroups_020bb6f0(void)
{
    Quad *buffers[9];
    s32 counts[9];
    ShapeBlock block;
    CollisionInfo info;
    VecFx32 base;
    VecFx32 corner;
    VecFx32 position;
    VecFx32 sum;
    VecFx32 moved;
    VecFx32 offset;
    int i;
    ActiveRecord *record;
    int write;
    s32 maxDepth;
    SceneArea *area;
    GroupDesc *desc;
    SceneArea *areas;
    int areaCount;
    int count;
    int objectCount;
    int n;
    int j;
    int v;
    int areaIndex;
    s32 minDepth;
    GroupObject *object;
    CollisionPolygon *polygons;
    GroupObject *objects;

    func_02036230();
    record = &g_activeState_020bc800->records[g_activeState_020bc800->recordIndex];
    write = 1;
    for (i = 1; i < g_activeState_020bc800->activeGroupCount; i++) {
        if (g_activeState_020bc800->groups[i].hidden == 0) {
            if (i != write) {
                for (j = 0; j < g_activeState_020bc800->groups[i].objectCount; j++) {
                    func_01ff8710(&g_activeState_020bc800->groups[i].objects[j], &g_activeState_020bc800->groups[write].objects[j], sizeof(GroupObject));
                    func_01ff8710(&g_activeState_020bc800->groups[i].polygons[j], &g_activeState_020bc800->groups[write].polygons[j], sizeof(CollisionPolygon));
                    g_activeState_020bc800->groups[write].objects[j].block.shape.data = (VecFx32 *)&g_activeState_020bc800->groups[write].polygons[j];
                }
                polygons = g_activeState_020bc800->groups[write].polygons;
                objects = g_activeState_020bc800->groups[write].objects;
                func_01ff8710(&g_activeState_020bc800->groups[i], &g_activeState_020bc800->groups[write], sizeof(ObjectGroup));
                g_activeState_020bc800->groups[write].polygons = polygons;
                g_activeState_020bc800->groups[write].objects = objects;
            }
            g_activeState_020bc800->groups[write].locked = 1;
            write++;
        }
    }
    g_activeState_020bc800->activeGroupCount = write + record->extraGroupCount;

    for (i = 0; i < 9; i++) {
        count = 0;
        n = 0;
        areaCount = g_activeState_020bc800->areaCount;
        areas = g_activeState_020bc800->areas;
        for (; n < areaCount; n++) {
            if ((u8)(i + 2) == areas[n].slot) {
                count++;
            }
        }
        counts[i] = count;
        if (count == 0) {
            buffers[i] = NULL;
            continue;
        }
        buffers[i] = NNSi_FndAllocFromDefaultHeapEx_0202a19c(count * sizeof(Quad), -4);
        maxDepth = 0;
        minDepth = 0;
        areaIndex = 0;
        for (j = 0; j < counts[i]; j++, areaIndex++) {
            areaIndex = FindArea(areaIndex, i + 2);
            if (areaIndex != -1) {
                area = &g_activeState_020bc800->areas[areaIndex];
                for (v = 0; v < 4; v++) {
                    corner.x = area->corners[v].x;
                    corner.y = 0;
                    corner.z = area->corners[v].z;
                    buffers[i][j][v] = corner;
                    buffers[i][j][v].y += 0x266;
                    if (maxDepth < buffers[i][j][v].z) {
                        maxDepth = buffers[i][j][v].z;
                    } else if (minDepth > buffers[i][j][v].z) {
                        minDepth = buffers[i][j][v].z;
                    }
                }
            }
        }
        g_activeState_020bc800->maxDepth[i] = maxDepth;
        g_activeState_020bc800->minDepth[i] = minDepth;
    }

    info.mode = 0;
    info.type = 0xb;
    i = write;
    if (i < g_activeState_020bc800->activeGroupCount) {
        offset = data_02053438;
        do {
            desc = &record->groupDescs[i - write];
            g_activeState_020bc800->groups[i].hidden = 0;
            g_activeState_020bc800->groups[i].slot = desc->slot;
            position.x = desc->x;
            position.y = 0;
            position.z = desc->z;
            g_activeState_020bc800->groups[i].position = position;
            base = g_activeState_020bc800->groups[i].position;
            g_activeState_020bc800->groups[i].position.y += 0x266;
            g_activeState_020bc800->groups[i].mode = desc->mode;
            g_activeState_020bc800->groups[i].limit = desc->limit;
            g_activeState_020bc800->groups[i].counter = 0;
            g_activeState_020bc800->groups[i].locked = 0;
            objectCount = counts[desc->slot - 2];
            g_activeState_020bc800->groups[i].objectCount = objectCount;
            if (objectCount != 0) {
                for (j = 0; j < objectCount; j++) {
                    Callback onEnter;
                    Callback onStay;
                    Callback onLeave;

                    onEnter.func = IsSupportedOwnerState_020bb574;
                    onEnter.arg = 0;
                    onStay.func = func_ov031_020bb598;
                    onStay.arg = 0;
                    onLeave.func = MarkLinkedTargetFlag_020bb5b8;
                    onLeave.arg = 0;
                    object = &g_activeState_020bc800->groups[i].objects[j];
                    InitCollisionObject_02033c7c(object, 0, g_activeState_020bc800->collisionOwner);
                    InitPolygonShape_0203af1c(&block.shape, &g_activeState_020bc800->groups[i].polygons[j], 4, buffers[desc->slot - 2][j]);
                    block.delta = offset;
                    OffsetBoxByDelta_0203ac70(&block.shape.bounds, &block.box, &block.delta);
                    object->block = block;
                    VEC_Add_01ff9e0c(object->block.shape.data, &base, &sum);
                    moved = sum;
                    SetShapePosition_0203afa0(&object->block.shape, &moved);
                    OffsetBoxByDelta_0203ac70(&object->block.shape.bounds, &object->block.box, &object->block.delta);
                    object->enabled = 1;
                    object->info = info;
                    object->onEnter = onEnter;
                    object->onStay = onStay;
                    object->onLeave = onLeave;
                }
            }
            i++;
        } while (i < g_activeState_020bc800->activeGroupCount);
    }

    for (i = 0; i < 9; i++) {
        if (buffers[i] != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(buffers[i]);
        }
    }
}
