#include "nitro/types.h"

extern "C" {

typedef struct ResourceSection {
    u32 unk_00;
    u32 count;
    u32 stride;
    u8 *data;
} ResourceSection;

typedef struct ResourceHeader {
    u32 unk_00;
    u32 unk_04;
    ResourceSection *sections;
} ResourceHeader;

typedef struct Resource {
    u32 unk_00;
    ResourceHeader *header;
} Resource;

typedef struct ModelHeader {
    u16 unk_00;
    u16 kind;
} ModelHeader;

typedef struct ModelEntry {
    ModelHeader *header;
    u32 resource;
    u32 resourceSize;
    u8 model[0xd8];
    u8 animSet[0x2c];
    s32 type;
    u16 key;
    u8 polygonIds[12];
} ModelEntry;

typedef struct ModelManager {
    u8 pad_00000[0x214];
    ModelEntry entries[347];
    u8 pad_18de0[0xa];
    u16 count;
    u8 pad_18dec[0x20];
    u8 *archives[2];
} ModelManager;

extern ModelManager *data_ov001_020a0528;
extern char sOv001_Ch_020a0434[];
extern char sOv001_Ef_020a0438[];
extern char sOv001_Pt_020a043c[];
extern char sOv001_Format04dP2_020a0440[];
extern char sOv001_EnFormatSFormat04dP2_020a0448[];

extern void MI_CpuFill8(void *dst, int value, u32 size);
extern int GetLanguageIndex(void);
extern int OS_SNPrintf(char *dst, u32 size, const char *fmt, ...);
extern int findSharedResourceByName(u8 *table, void *name);
extern ModelHeader *func_ov001_020993f8(u32 fileId, u32 mode, BOOL allocFromEnd);
extern ModelHeader *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void *func_0202c4a0(u32 fileId, u32 mode);
extern void InitSharedRecordAndDispatchAlt(void *dst, u32 fileId, void *buffer, u32 mode);
extern void LoadActorAnimationSet(void *animSet, void *model, u32 fileId);
extern u32 Archive_LoadFile(u32 fileId, u32 mode);
extern u32 OpenAndClassifyFile(u32 fileId);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern u8 GetModelMaterialPolygonID(void *model, u8 index);
extern Resource *FindStageLink(u32 id);

#define SECTION_COUNT(resource, index) ({ u32 n_; if ((resource) == NULL) { n_ = 0; } else if ((resource)->header == NULL) { n_ = 0; } else { n_ = (resource)->header->sections[index].count; } n_; })

#define ARCHIVE_FILE_ID(base) (((((u32)(base) + 0x8000) & 0xfffffc) << 7) | 0x80000000)

static inline u32 GetSectionCount(Resource *resource, int index)
{
    if (resource == NULL) {
        return 0;
    }
    if (resource->header == NULL) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    if (index >= 19) {
        return 0;
    }
    return resource->header->sections[index].count;
}

inline void *GetResourceSectionElement(Resource *resource, int index, u32 element) __attribute__((weak))
{
    ResourceHeader *header;
    u32 count;
    u8 *data;

    if (resource == NULL) {
        return NULL;
    }
    header = resource->header;
    if (header == NULL) {
        return NULL;
    }
    if (index < 0) {
        return NULL;
    }
    if (index >= 19) {
        return NULL;
    }
    count = GetSectionCount(resource, index);
    data = header->sections[index].data;
    if (count == 0) {
        return NULL;
    }
    if (element >= count) {
        return NULL;
    }
    return data + element * header->sections[index].stride;
}

inline s16 LoadStageModelEntry(u16 id, int variant, int type) __attribute__((weak))
{
    ModelManager *manager = data_ov001_020a0528;
    void *buffer = NULL;
    ModelEntry *entry = &manager->entries[manager->count];
    ModelHeader *header;
    ModelHeader *loaded;
    char *prefix;
    u8 *archive;
    char name[64];
    u16 i;
    int index;

    MI_CpuFill8(entry, 0, sizeof(ModelEntry));
    for (i = 0; i < manager->count; i++) {
        if (manager->entries[i].key != 0 && type == manager->entries[i].type && id + 1 == manager->entries[i].key) {
            return i + 1;
        }
    }
    entry->type = type;
    entry->key = id + 1;
    archive = (u8 *)NULL;
    prefix = (char *)NULL;
    loaded = (ModelHeader *)NULL;
    if (type == 0) {
        prefix = sOv001_Ch_020a0434;
        archive = data_ov001_020a0528->archives[0];
    }
    if (type == 1) {
        prefix = sOv001_Ef_020a0438;
        archive = data_ov001_020a0528->archives[1];
    }
    if (type == 2) {
        prefix = sOv001_Pt_020a043c;
        archive = (u8 *)NULL;
    }
    if (type == 1) {
        if (id == 0x17) {
            int state = GetLanguageIndex();
            if (state != 0 && state == 5) {
                id = 0x1e;
            }
        } else if (id == 0x1a) {
            int state = GetLanguageIndex();
            if (state != 0) {
                if (state == 5) {
                    id = 0x20;
                } else {
                    id = 0x1f;
                }
            }
        }
    }
    if (archive != NULL) {
        OS_SNPrintf(name, sizeof(name), sOv001_Format04dP2_020a0440, id);
        index = findSharedResourceByName(archive, name);
        if (index >= 0) {
            loaded = func_ov001_020993f8(ARCHIVE_FILE_ID(archive) | (index & 0x1ff), 0xb, FALSE);
        }
        if (loaded == NULL) {
            header = (ModelHeader *)NULL;
            goto store;
        }
    } else {
        OS_SNPrintf(name, sizeof(name), sOv001_EnFormatSFormat04dP2_020a0448, prefix, id);
        loaded = Msg_OpenContainerAndReadHeader(name, 0xb, FALSE);
        header = (ModelHeader *)NULL;
        if (loaded == NULL) {
            goto store;
        }
    }
    header = loaded;
store:
    entry->header = header;
    if (header->kind <= 3) {
        if (header->kind > 2) {
            buffer = func_0202c4a0(ARCHIVE_FILE_ID(header) | 2, 0xb);
        }
        InitSharedRecordAndDispatchAlt(entry->model, ARCHIVE_FILE_ID(entry->header) | 1, buffer, 0xb);
    } else {
        buffer = func_0202c4a0(ARCHIVE_FILE_ID(header) | ((variant * 2 + 2) & 0x1ff), 0xb);
        InitSharedRecordAndDispatchAlt(entry->model, ARCHIVE_FILE_ID(entry->header) | ((variant * 2 + 1) & 0x1ff), buffer, 0xb);
        LoadActorAnimationSet(entry->animSet, entry->model, ARCHIVE_FILE_ID(entry->header) | 9);
    }
    entry->resource = Archive_LoadFile(ARCHIVE_FILE_ID(entry->header), 0xb);
    entry->resourceSize = OpenAndClassifyFile(ARCHIVE_FILE_ID(entry->header));
    if (buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(buffer);
    }
    if (entry != NULL) {
        for (i = 0; i < 11; i++) {
            u8 polygonId = GetModelMaterialPolygonID(entry->model, i);
            if (polygonId == 0xff) {
                break;
            }
            entry->polygonIds[i] = polygonId;
        }
        entry->polygonIds[i] = 0xff;
    }
    manager->count++;
    return manager->count;
}



extern void LoadStageModels(u16 stageId, int variant, u16 parentId);

inline void LoadStageModels(u16 stageId, int variant, u16 parentId)
{
    Resource *stage = FindStageLink(stageId);
    u8 *element;
    u16 count;
    u16 i;

    count = SECTION_COUNT(stage, 4);
    for (i = 0; i < count; i++) {
        element = (u8 *)GetResourceSectionElement(stage, 4, i);
        LoadStageModelEntry(i + stageId * 100, variant, 0);
    }
    count = SECTION_COUNT(stage, 6);
    for (i = 0; i < count; i++) {
        LoadStageModelEntry(*(u32 *)GetResourceSectionElement(stage, 6, i), 0, 1);
    }
    element = (u8 *)GetResourceSectionElement(stage, 0, 0);
    if (element != NULL && element[0x18] == 4) {
        LoadStageModelEntry(6, 0, 1);
    }
    if (parentId == stageId) {
        return;
    }
    count = SECTION_COUNT(stage, 5);
    for (i = 0; i < count; i++) {
        LoadStageModels(*(u16 *)GetResourceSectionElement(stage, 5, i), 0, stageId);
    }
}
void (*const sLoadStageModelsRef)(u16, int, u16) = LoadStageModels;

}
