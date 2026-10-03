#include "nitro/types.h"

typedef struct {
    s16 id;
    u8 instanceIndices[10];
} AreaRecord;

typedef struct {
    u8 pad_00;
    u8 tier : 7;
    u8 tierFlag : 1;
    u8 pad_02[0x1a];
} AreaGroup;

typedef struct {
    u8 instanceCount;
    u8 recordCount;
    u8 pad_02[2];
    u8 *instances;
    AreaRecord *records;
} AreaObjects;

typedef struct {
    u8 pad_00[0x1d];
    u8 sceneReady;
    u8 pad_1e[8];
    s16 recordId;
    u8 pad_28[0x28];
    AreaGroup *groups;
    u8 pad_54[0x68];
    AreaObjects objects;
    u8 soundState;
} AreaManager;

typedef struct {
    u8 sceneReady;
    u8 tier;
    u8 instanceCount;
    u8 pad_03;
    u8 *soundState;
    u8 *instances[9];
} AreaSceneInfo;

extern AreaManager *data_ov035_020bc4e0;
extern int func_ov035_020bae64(void);
extern u8 func_ov035_020bb0f0(void);
extern void func_ov041_020bc500(AreaSceneInfo *info);

void BuildAreaSceneInfo_020bc504(AreaSceneInfo *info) {
    AreaManager *manager = data_ov035_020bc4e0;
    AreaObjects *objects = &manager->objects;
    int found = -1;
    AreaRecord *record;
    int i;

    info->sceneReady = manager->sceneReady;
    if (func_ov035_020bae64() >= 0) {
        info->tier = manager->groups[func_ov035_020bae64()].tier;
    } else {
        info->tier = 0;
    }
    for (i = 0; i < objects->recordCount; i++) {
        if (manager->recordId == objects->records[i].id) {
            found = i;
            break;
        }
    }
    record = &objects->records[found];
    info->instanceCount = 0;
    for (i = 0; i < 9; i++) {
        u8 index = record->instanceIndices[i];
        if (index == 0xff) {
            info->instances[i] = NULL;
        } else {
            info->instances[i] = objects->instances + index * 0x48;
            info->instanceCount++;
        }
    }
    info->soundState = &manager->soundState;
    *info->soundState = func_ov035_020bb0f0();
    func_ov041_020bc500(info);
}
