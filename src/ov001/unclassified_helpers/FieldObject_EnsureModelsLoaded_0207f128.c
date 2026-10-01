#include "nitro/types.h"

typedef struct ModelResource {
    u8 pad_00[0xc];
    int recordId;
} ModelResource;

typedef struct FieldObjectClass {
    u8 pad_00[0x54];
    ModelResource *model;
    int animRecord;
    ModelResource *subModel;
    int subAnimRecord;
    s16 modelId;
    s16 subModelId;
} FieldObjectClass;

typedef struct FieldObject {
    u8 pad_00[8];
    FieldObjectClass *objectClass;
} FieldObject;

extern void func_ov001_0207f0b8(int id, ModelResource **out, int heap);
extern int func_ov001_0207f0a8(int id, int heap);
extern BOOL IsRecordIdFree_0202c38c(int id);

BOOL FieldObject_EnsureModelsLoaded_0207f128(FieldObject *object)
{
    FieldObjectClass *objectClass = object->objectClass;

    if (objectClass->modelId < 0) {
        return TRUE;
    }
    if (objectClass->model == NULL) {
        func_ov001_0207f0b8(objectClass->modelId, &objectClass->model, 3);
        if (objectClass->model == NULL) {
            return FALSE;
        }
    }
    if (objectClass->animRecord == 0) {
        objectClass->animRecord = func_ov001_0207f0a8(objectClass->modelId, 3);
        if (objectClass->animRecord == 0) {
            return FALSE;
        }
    }
    if (objectClass->subModelId >= 0) {
        if (objectClass->subModel == NULL) {
            func_ov001_0207f0b8(objectClass->subModelId, &objectClass->subModel, 3);
            if (objectClass->subModel == NULL) {
                return FALSE;
            }
        }
        if (objectClass->subAnimRecord == 0) {
            objectClass->subAnimRecord = func_ov001_0207f0a8(objectClass->subModelId, 3);
            if (objectClass->subAnimRecord == 0) {
                return FALSE;
            }
        }
    }
    if (IsRecordIdFree_0202c38c(objectClass->animRecord) && IsRecordIdFree_0202c38c(objectClass->model->recordId)) {
        if (objectClass->subModelId >= 0) {
            if (IsRecordIdFree_0202c38c(objectClass->subAnimRecord) && IsRecordIdFree_0202c38c(objectClass->subModel->recordId)) {
                return TRUE;
            }
        } else {
            return TRUE;
        }
    }
    return FALSE;
}
