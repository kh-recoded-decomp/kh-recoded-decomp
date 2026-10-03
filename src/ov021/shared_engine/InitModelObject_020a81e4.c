#include "nitro/types.h"

typedef struct {
    u16 unk_00;
    u16 loaded;
} SharedRecord;

typedef struct {
    u8 state;
    s8 slot;
    u8 pad_002[6];
    u8 body[0x108];
    u16 mask;
    u8 pad_112[0xa];
    u32 unk_11c;
} ModelObject;

extern SharedRecord *RetainOrInitializeSharedRecord_0202c80c(int a, int b);
extern void *func_0202c48c(u32 fileId, u32 mode);
extern void func_0202ed9c(void *object, SharedRecord *record, void *data, int kind);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void InitModelObject_020a81e4(ModelObject *model, int recordId, u32 fileId)
{
    void *data;
    SharedRecord *record;

    model->slot = -1;
    data = NULL;
    model->state = 0;
    model->mask = 0x1f;
    model->unk_11c = 0;
    record = RetainOrInitializeSharedRecord_0202c80c(recordId, 6);
    if (record->loaded == 0) {
        data = func_0202c48c(fileId, 0x11);
    }
    func_0202ed9c(model->body, record, data, 6);
    if (data != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(data);
    }
}
