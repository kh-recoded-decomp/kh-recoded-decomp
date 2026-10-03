#include "nitro/types.h"

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

extern ModelManager *data_ov001_020a0508;
extern char data_ov001_020a0414[];
extern char data_ov001_020a0418[];
extern char data_ov001_020a041c[];
extern char data_ov001_020a0420[];
extern char data_ov001_020a0428[];

extern void func_01ff8830(void *dst, int value, u32 size);
extern int func_0202b788(void);
extern int OS_SNPrintf_02002468(char *dst, u32 size, const char *fmt, ...);
extern int findSharedResourceByName_0202cd8c(u8 *table, void *name);
extern ModelHeader *func_ov001_020993d0(u32 fileId, u32 mode, BOOL allocFromEnd);
extern ModelHeader *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void *func_0202c48c(u32 fileId, u32 mode);
extern void func_0202ed3c(void *dst, u32 fileId, void *buffer, u32 mode);
extern void LoadActorAnimationSet_0209bfd0(void *animSet, void *model, u32 fileId);
extern u32 func_0202c478(u32 fileId, u32 mode);
extern u32 func_0202cb7c(u32 fileId);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern u8 GetModelMaterialPolygonID_0208f59c(void *model, u8 index);

#define ARCHIVE_FILE_ID(base) (((((u32)(base) + 0x8000) & 0xfffffc) << 7) | 0x80000000)

s16 LoadStageModelEntry_0209a8ac(u16 id, int variant, int type)
{
    ModelManager *manager = data_ov001_020a0508;
    void *buffer = NULL;
    ModelEntry *entry = &manager->entries[manager->count];
    ModelHeader *header;
    ModelHeader *loaded;
    char *prefix;
    u8 *archive;
    char name[64];
    u16 i;
    int index;

    func_01ff8830(entry, 0, sizeof(ModelEntry));
    for (i = 0; i < manager->count; i++) {
        if (manager->entries[i].key != 0 && type == manager->entries[i].type && id + 1 == manager->entries[i].key) {
            return i + 1;
        }
    }
    entry->type = type;
    entry->key = id + 1;
    archive = NULL;
    prefix = NULL;
    loaded = NULL;
    if (type == 0) {
        prefix = data_ov001_020a0414;
        archive = data_ov001_020a0508->archives[0];
    }
    if (type == 1) {
        prefix = data_ov001_020a0418;
        archive = data_ov001_020a0508->archives[1];
    }
    if (type == 2) {
        prefix = data_ov001_020a041c;
        archive = NULL;
    }
    if (type == 1) {
        if (id == 0x17) {
            int state = func_0202b788();
            if (state != 0 && state == 5) {
                id = 0x1e;
            }
        } else if (id == 0x1a) {
            int state = func_0202b788();
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
        OS_SNPrintf_02002468(name, sizeof(name), data_ov001_020a0420, id);
        index = findSharedResourceByName_0202cd8c(archive, name);
        if (index >= 0) {
            loaded = func_ov001_020993d0(ARCHIVE_FILE_ID(archive) | (index & 0x1ff), 0xb, FALSE);
        }
        if (loaded == NULL) {
            header = NULL;
            goto store;
        }
    } else {
        OS_SNPrintf_02002468(name, sizeof(name), data_ov001_020a0428, prefix, id);
        loaded = Msg_OpenContainerAndReadHeader_0202cc6c(name, 0xb, FALSE);
        header = NULL;
        if (loaded == NULL) {
            goto store;
        }
    }
    header = loaded;
store:
    entry->header = header;
    if (header->kind <= 3) {
        if (header->kind > 2) {
            buffer = func_0202c48c(ARCHIVE_FILE_ID(header) | 2, 0xb);
        }
        func_0202ed3c(entry->model, ARCHIVE_FILE_ID(entry->header) | 1, buffer, 0xb);
    } else {
        buffer = func_0202c48c(ARCHIVE_FILE_ID(header) | ((variant * 2 + 2) & 0x1ff), 0xb);
        func_0202ed3c(entry->model, ARCHIVE_FILE_ID(entry->header) | ((variant * 2 + 1) & 0x1ff), buffer, 0xb);
        LoadActorAnimationSet_0209bfd0(entry->animSet, entry->model, ARCHIVE_FILE_ID(entry->header) | 9);
    }
    entry->resource = func_0202c478(ARCHIVE_FILE_ID(entry->header), 0xb);
    entry->resourceSize = func_0202cb7c(ARCHIVE_FILE_ID(entry->header));
    if (buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(buffer);
    }
    if (entry != NULL) {
        for (i = 0; i < 11; i++) {
            u8 polygonId = GetModelMaterialPolygonID_0208f59c(entry->model, i);
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
