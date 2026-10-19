#include "nitro/types.h"

typedef struct HandlePool HandlePool;
typedef struct StageEventRecord StageEventRecord;

typedef struct ResourceSection {
    u32 kind;
    u32 count;
    u32 stride;
    u8 *data;
} ResourceSection;

typedef struct ResourceHeader {
    u32 kind;
    u32 sectionCount;
    ResourceSection *sections;
} ResourceHeader;

typedef struct StageResource {
    u16 id;
    u16 reserved02;
    ResourceHeader *header;
} StageResource;

typedef struct StageHeapScope {
    u8 reserved00[0x18];
    void *objectHeap;
    u8 reserved1c[0x18];
    void *heap;
    void *savedHeap;
} StageHeapScope;

/* Resource-cache and event-allocation fields of the shared stage manager. */
typedef struct StageResourceManager {
    u8 reserved00000[8];
    StageResource resources[64];
    u8 reserved00208[0x18d7c - 0x208];
    HandlePool *eventPool;
    u8 reserved18d80[0x18dec - 0x18d80];
    u16 resourceCount;
    u16 eventCount;
    u8 reserved18df0[0x10];
    s32 archiveBase;
    u8 reserved18e04[0x10];
    StageHeapScope heapScope;
} StageResourceManager;

typedef struct DependencyRecord {
    u16 type;
} DependencyRecord;

extern StageResourceManager *gStageManager;
extern u16 FindStageLinkIndex(u32 id);
extern u32 OpenAndClassifyFile(u32 id);
extern void *Heap_GetCurrent(void);
extern void *SetDefaultHeap(void *heap);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int alignment);
extern u32 LoadFileIntoBuffer(u32 id, void *buffer, u32 size);
extern void RelocateResourceTable(void *table);
extern StageResource *GetStageEntry(int index);
extern StageResource *LoadStageResource(u32 id);
extern u16 HandlePool_ClaimHandle(HandlePool *pool, int handle);
extern StageEventRecord *GetStageEventRecord(u32 id);
extern void InitializeActorStats(StageEventRecord *record, u16 type,
    u16 stageIndex, u16 recordIndex, BOOL active, BOOL selectionEnabled);
extern u16 FindSmallRecordIndex(u32 id);
extern void *GetResourceSectionElement(StageResource *resource, int section, u32 element);

static inline u32 StageArchiveFileId(u32 index)
{
    return 0x80000000 |
        (((gStageManager->archiveBase + 0x8000) & 0xfffffc) << 7) | index;
}

/* Resource section 5 contains the dependency records. */
static inline u32 DependencyCount(StageResource *resource)
{
    if (resource == NULL) {
        return 0;
    }
    if (resource->header == NULL) {
        return 0;
    }
    return resource->header->sections[5].count;
}

static inline DependencyRecord *DependencyAt(StageResource *resource, u32 element)
{
    ResourceHeader *header;
    ResourceSection *section;
    u32 count;
    u8 *data;

    if (resource == NULL) {
        return NULL;
    }
    header = resource->header;
    if (header == NULL) {
        return NULL;
    }
    count = DependencyCount(resource);
    section = header->sections;
    data = section[5].data;
    if (count == 0) {
        return NULL;
    }
    if (element >= count) {
        return NULL;
    }
    return (DependencyRecord *)(data + element * section[5].stride);
}

/* Cache the resource, create its event, then expand its dependency records.
 * stopType prevents a resource from expanding its own dependency list again.
 * An activation selector of 0xffff enables the root event's active flag. */
u32 SpawnStageResourceTree_0209a4bc(u16 type, u16 stageIndex, u16 recordIndex,
    u16 activationSelector, u16 stopType, BOOL selectionEnabled)
{
    StageEventRecord *record;
    u16 i;
    u16 dependencyCount;
    u32 handle;
    u16 j;
    StageResource *resource;

    u16 slot = FindStageLinkIndex(type);
    StageResourceManager *manager;
    u32 index;
    u32 size;
    void *buffer;

    /* Same checked heap-scope path used by LoadStageResource. */
    if (slot == 0) {
        index = type & 0x1ff;
        size = OpenAndClassifyFile(StageArchiveFileId(index));
        if (size == 0) {
            resource = NULL;
            goto resourceLoaded;
        }
        manager = gStageManager;
        if (manager != NULL && &manager->heapScope != NULL &&
                manager->heapScope.savedHeap == NULL) {
            manager->heapScope.savedHeap = Heap_GetCurrent();
            SetDefaultHeap(manager->heapScope.objectHeap);
        }
        buffer = NNS_FndAllocFromDefaultExpHeapEx(size, 0x20);
        if (buffer == NULL) {
            resource = NULL;
            goto resourceLoaded;
        }
        manager = gStageManager;
        if (manager != NULL && &manager->heapScope != NULL &&
                manager->heapScope.savedHeap != NULL) {
            SetDefaultHeap(manager->heapScope.savedHeap);
            manager->heapScope.savedHeap = NULL;
        }
        if ((u16)LoadFileIntoBuffer(StageArchiveFileId(index), buffer, size) == 0) {
            resource = NULL;
            goto resourceLoaded;
        }
        gStageManager->resources[gStageManager->resourceCount].id = type;
        gStageManager->resources[gStageManager->resourceCount].header = buffer;
        gStageManager->resourceCount++;
        RelocateResourceTable(buffer);
        slot = gStageManager->resourceCount;
    }
    resource = GetStageEntry((s16)slot);

resourceLoaded:
    if (resource != NULL) {
        handle = HandlePool_ClaimHandle(gStageManager->eventPool,
            (u16)(gStageManager->eventCount + 1));
        record = GetStageEventRecord(handle);
        if (record != NULL) {
            BOOL allowSelection = TRUE;
            if (selectionEnabled == FALSE) {
                allowSelection = FALSE;
            }
            InitializeActorStats(record, type, stageIndex, recordIndex,
                activationSelector == 0xffff, allowSelection);
            gStageManager->eventCount++;
        }
        if (stopType == type) {
            return handle;
        }
        dependencyCount = DependencyCount(resource);
        for (i = 0; i < dependencyCount; ++i) {
            DependencyRecord *dependency = DependencyAt(resource, i);
            u16 dependencyIndex = FindSmallRecordIndex(dependency->type);
            u16 dependencyType = dependency->type;
            StageResource *child = LoadStageResource(dependencyType);

            if (child != NULL) {
                u16 childCount;
                record = GetStageEventRecord(HandlePool_ClaimHandle(gStageManager->eventPool,
                    (u16)(gStageManager->eventCount + 1)));
                if (record != NULL) {
                    InitializeActorStats(record, dependencyType, stageIndex, dependencyIndex,
                        TRUE, selectionEnabled != 0);
                    gStageManager->eventCount++;
                }
                if (type != dependencyType) {
                    childCount = DependencyCount(child);
                    for (j = 0; j < childCount; ++j) {
                        DependencyRecord *next = GetResourceSectionElement(child, 5, j);
                        u16 nextIndex = FindSmallRecordIndex(next->type);
                        SpawnStageResourceTree_0209a4bc(next->type, stageIndex, nextIndex, 0xffff,
                            dependencyType, selectionEnabled);
                    }
                }
            }
        }
        return handle;
    }
    return 0;
}
