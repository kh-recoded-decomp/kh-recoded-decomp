#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Box {
    VecFx32 min;
    VecFx32 max;
} Box;

typedef struct CollisionShape {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct CollisionInfo {
    s32 mode;
    s32 type;
} CollisionInfo;

typedef struct GroupObject {
    u8 pad_00[0xd];
    u8 enabled;
    u8 pad_0e[0x16];
    CollisionShape shape;
    u8 pad_44[0x24];
    CollisionInfo info;
    u8 pad_70[0x18];
} GroupObject;

typedef struct CollisionPolygon {
    u8 data[0xd0];
} CollisionPolygon;

typedef struct ObjectGroup {
    u8 hidden;
    u8 slot;
    u8 objectCount;
    u8 locked;
    u8 limit;
    u8 counter;
    u8 pad_06[2];
    VecFx32 position;
    CollisionPolygon *polygons;
    GroupObject *objects;
    s32 mode;
} ObjectGroup;

typedef struct PointXZ {
    fx32 x;
    fx32 z;
} PointXZ;

typedef struct SceneArea {
    u8 slot;
    u8 pad_01[3];
    PointXZ corners[4];
} SceneArea;

typedef struct GroupDesc {
    u8 slot;
    u8 limit;
    u8 pad_02[2];
    fx32 x;
    fx32 z;
    s32 mode;
} GroupDesc;

typedef struct ActorSpawn {
    u8 kind;
    u8 variant;
    s8 offsetX;
    s8 offsetY;
    VecFx32 position;
    u32 param;
} ActorSpawn;

typedef struct RecordItem {
    u32 handle;
    u16 group;
    u16 channel;
} RecordItem;

typedef struct PanelSpawn {
    VecFx32 position;
    s32 param;
    s32 itemId;
} PanelSpawn;

/* The part of a scene record stored as is in the record file. */
typedef struct SceneRecordHeader {
    u8 pad_00[8];
    VecFx32 origin;
    u8 pad_14[0x14];
} SceneRecordHeader;

typedef struct SceneRecord {
    SceneRecordHeader header;
    GroupDesc *groupDescs;
    ActorSpawn *spawns;
    RecordItem *items;
    PanelSpawn *panelSpawns;
    u8 groupDescCount;
    u8 spawnCount;
    u8 itemCount;
    u8 panelCount;
} SceneRecord;

typedef struct LinkState {
    u8 pad_000[0x194];
    u8 kind;
    u8 pad_195[3];
} LinkState;

typedef struct SceneState {
    u8 pad_00[0x40];
    s32 field_40;
    s32 recordIndex;
    u8 pad_48[4];
    u32 *stepCodes;
    SceneRecord *records;
    u8 stepCount;
    u8 recordCount;
    u8 activeGroupCount;
    u8 groupCount;
    u8 field_58;
    u8 filledStepCount;
    u8 areaCount;
    u8 field_5b;
    u16 nearestEvent;
    u8 pad_5e[2];
    SceneArea *areas;
    ObjectGroup *groups;
    u8 pad_68[0xb0 - 0x68];
    s32 field_b0;
    s32 field_b4;
    fx32 field_b8;
    u32 frameCount;
    s32 field_c0;
    u8 pad_c4[8];
    s32 field_cc;
    u8 pad_d0[4];
    LinkState links[2];
} SceneState;

extern SceneState *gOv031SceneWorkStorage;

extern void FreeSceneRecords(void);
extern void ResetCameraDefault(void);
extern int GetCtxModeByte(void);
extern u8 *GetSessionResourceArchive(void);
extern int findSharedResourceByName(void *table, const char *name);
extern void *LoadFileAllocFromHeapTail(u32 fileId, u32 flags);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *memory);
extern void MIi_CpuCopy32(const void *src, void *dst, u32 size);
extern void Obj_InitLinkState(LinkState *link);
extern BOOL InitCollisionObject(GroupObject *object, u16 groupMask, void *owner);
extern void InitPolygonShape(CollisionShape *shape, CollisionPolygon *polygon, u8 vertexCount, const VecFx32 *points);

/* The key of the file at `index` of a resource archive. */
#define ARCHIVE_FILE_KEY(archive, index) (((index) & 0x1ff) | ((((u32)(archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000))

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 v;

    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

static inline CollisionShape MakePolygonShape(CollisionPolygon *polygon, u8 vertexCount, const VecFx32 *points)
{
    CollisionShape shape;

    InitPolygonShape(&shape, polygon, vertexCount, points);
    return shape;
}

static inline CollisionInfo MakeCollisionInfo(s32 mode, s32 type)
{
    CollisionInfo info;

    info.mode = mode;
    info.type = type;
    return info;
}

static inline GroupObject *Group_GetObjects(ObjectGroup *group)
{
    return group->objects;
}

/* Loads the scene's areas and records from the two named files of the shared archive: the step
 * codes, then for every record its group descriptions, actor spawns, items and panel spawns. Sets
 * up the floor group and enough groups for the busiest record, and resets the playback state. */
/*
 * Loads a scene: frees the previous records, reads the area file (the trigger areas) and the record
 * file (step codes, then per record its group descriptions, actor spawns, items and panel spawns)
 * into heap copies, sizes the object groups for the largest record (three groups per description
 * plus the floor), builds group 0 as a 20 x 200 floor quad and clears the scene cursors. Finally
 * counts the steps whose record has anything to place.
 */
void LoadSceneData(const char *areaFile, const char *recordFile)
{
    GroupObject *object;
    VecFx32 corners[4];
    u32 *areaData;
    u32 *file;
    u8 *archive;
    u32 *steps;
    u32 *recordTable;
    u32 *data;
    int maxGroups;
    int i;

    FreeSceneRecords();
    ResetCameraDefault();
    if (GetCtxModeByte() == 6) {
        gOv031SceneWorkStorage->field_b8 = 30 << 12;
    } else {
        gOv031SceneWorkStorage->field_b8 = 15 << 12;
    }

    archive = GetSessionResourceArchive();
    areaData = LoadFileAllocFromHeapTail(ARCHIVE_FILE_KEY(archive, findSharedResourceByName(GetSessionResourceArchive(), areaFile)), 2);
    gOv031SceneWorkStorage->areaCount = areaData[0];
    gOv031SceneWorkStorage->areas = NNSi_FndAllocFromDefaultHeap(gOv031SceneWorkStorage->areaCount * sizeof(SceneArea));
    MIi_CpuCopy32(areaData + 1, gOv031SceneWorkStorage->areas, gOv031SceneWorkStorage->areaCount * sizeof(SceneArea));
    NNSi_FndFreeFromDefaultHeap(areaData);

    archive = GetSessionResourceArchive();
    file = LoadFileAllocFromHeapTail(ARCHIVE_FILE_KEY(archive, findSharedResourceByName(GetSessionResourceArchive(), recordFile)), 2);
    steps = file + 1;
    recordTable = steps + file[0];
    data = recordTable + 1;
    maxGroups = 0;
    gOv031SceneWorkStorage->stepCount = file[0];
    gOv031SceneWorkStorage->stepCodes = NNSi_FndAllocFromDefaultHeap(gOv031SceneWorkStorage->stepCount * sizeof(u32));
    MIi_CpuCopy32(steps, gOv031SceneWorkStorage->stepCodes, gOv031SceneWorkStorage->stepCount * sizeof(u32));
    gOv031SceneWorkStorage->recordCount = recordTable[0];
    gOv031SceneWorkStorage->records = NNSi_FndAllocFromDefaultHeap(gOv031SceneWorkStorage->recordCount * sizeof(SceneRecord));
    for (i = 0; i < gOv031SceneWorkStorage->recordCount; i++) {
        gOv031SceneWorkStorage->records[i].header = *(SceneRecordHeader *)(data + 1);
        gOv031SceneWorkStorage->records[i].groupDescCount = data[11];
        gOv031SceneWorkStorage->records[i].groupDescs =
            NNSi_FndAllocFromDefaultHeap(gOv031SceneWorkStorage->records[i].groupDescCount * sizeof(GroupDesc));
        data += 12;
        MIi_CpuCopy32(data, gOv031SceneWorkStorage->records[i].groupDescs,
                      gOv031SceneWorkStorage->records[i].groupDescCount * sizeof(GroupDesc));
        data += gOv031SceneWorkStorage->records[i].groupDescCount * (sizeof(GroupDesc) / 4);
        gOv031SceneWorkStorage->records[i].spawnCount = data[0];
        gOv031SceneWorkStorage->records[i].spawns =
            NNSi_FndAllocFromDefaultHeap(gOv031SceneWorkStorage->records[i].spawnCount * sizeof(ActorSpawn));
        data++;
        MIi_CpuCopy32(data, gOv031SceneWorkStorage->records[i].spawns,
                      gOv031SceneWorkStorage->records[i].spawnCount * sizeof(ActorSpawn));
        data += gOv031SceneWorkStorage->records[i].spawnCount * (sizeof(ActorSpawn) / 4);
        gOv031SceneWorkStorage->records[i].itemCount = data[0];
        gOv031SceneWorkStorage->records[i].items =
            NNSi_FndAllocFromDefaultHeap(gOv031SceneWorkStorage->records[i].itemCount * sizeof(RecordItem));
        data++;
        MIi_CpuCopy32(data, gOv031SceneWorkStorage->records[i].items,
                      gOv031SceneWorkStorage->records[i].itemCount * sizeof(RecordItem));
        data += gOv031SceneWorkStorage->records[i].itemCount * (sizeof(RecordItem) / 4);
        gOv031SceneWorkStorage->records[i].panelCount = data[0];
        gOv031SceneWorkStorage->records[i].panelSpawns =
            NNSi_FndAllocFromDefaultHeap(gOv031SceneWorkStorage->records[i].panelCount * sizeof(PanelSpawn));
        data++;
        MIi_CpuCopy32(data, gOv031SceneWorkStorage->records[i].panelSpawns,
                      gOv031SceneWorkStorage->records[i].panelCount * sizeof(PanelSpawn));
        data += gOv031SceneWorkStorage->records[i].panelCount * (sizeof(PanelSpawn) / 4);
        if (maxGroups < gOv031SceneWorkStorage->records[i].groupDescCount) {
            maxGroups = gOv031SceneWorkStorage->records[i].groupDescCount;
        }
    }
    gOv031SceneWorkStorage->groupCount = maxGroups * 3 + 1;
    gOv031SceneWorkStorage->groups = NNSi_FndAllocFromDefaultHeap(gOv031SceneWorkStorage->groupCount * sizeof(ObjectGroup));
    NNSi_FndFreeFromDefaultHeap(file);

    Obj_InitLinkState(&gOv031SceneWorkStorage->links[0]);
    Obj_InitLinkState(&gOv031SceneWorkStorage->links[1]);
    gOv031SceneWorkStorage->links[0].kind = 2;
    gOv031SceneWorkStorage->links[1].kind = 6;
    gOv031SceneWorkStorage->activeGroupCount = 1;
    gOv031SceneWorkStorage->groups[0].hidden = 0;
    gOv031SceneWorkStorage->groups[0].slot = 1;
    gOv031SceneWorkStorage->groups[0].position = MakeVec(0, 0, 0x5000);
    gOv031SceneWorkStorage->groups[0].mode = 0;
    gOv031SceneWorkStorage->groups[0].objectCount = 1;
    gOv031SceneWorkStorage->groups[0].polygons = NNSi_FndAllocFromDefaultHeap(sizeof(CollisionPolygon));
    gOv031SceneWorkStorage->groups[0].objects = NNSi_FndAllocFromDefaultHeap(sizeof(GroupObject));
    object = Group_GetObjects(&gOv031SceneWorkStorage->groups[0]);
    InitCollisionObject(object, 0, &gOv031SceneWorkStorage->links[0]);
    corners[0] = MakeVec(-0xa000, 0, -0x64000);
    corners[1] = MakeVec(0xa000, 0, -0x64000);
    corners[2] = MakeVec(0xa000, 0, 0x64000);
    corners[3] = MakeVec(-0xa000, 0, 0x64000);
    object->shape = MakePolygonShape(gOv031SceneWorkStorage->groups[0].polygons, 4, corners);
    object->enabled = 0;
    object->info = MakeCollisionInfo(0, 10);
    gOv031SceneWorkStorage->field_5b = 0;
    for (i = 1; i < gOv031SceneWorkStorage->groupCount; i++) {
        gOv031SceneWorkStorage->groups[i].polygons = NNSi_FndAllocFromDefaultHeap(0x410);
        gOv031SceneWorkStorage->groups[i].objects = NNSi_FndAllocFromDefaultHeap(0x2a8);
    }

    gOv031SceneWorkStorage->field_40 = -1;
    gOv031SceneWorkStorage->recordIndex = -1;
    gOv031SceneWorkStorage->field_b0 = 0;
    gOv031SceneWorkStorage->field_c0 = -1;
    gOv031SceneWorkStorage->field_cc = 0;
    gOv031SceneWorkStorage->field_58 = 0;
    gOv031SceneWorkStorage->field_b4 = 0;
    gOv031SceneWorkStorage->nearestEvent = 0xffff;
    gOv031SceneWorkStorage->filledStepCount = 0;
    for (i = 0; i < gOv031SceneWorkStorage->stepCount - 1; i++) {
        SceneRecord *record = &gOv031SceneWorkStorage->records[gOv031SceneWorkStorage->stepCodes[i]];

        if (record->groupDescCount != 0 || record->spawnCount != 0 || record->itemCount != 0) {
            gOv031SceneWorkStorage->filledStepCount++;
        }
    }
}
