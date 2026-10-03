#include "nitro/types.h"

typedef struct {
    u32 file;
    u32 palette;
    u32 pad_08;
    u32 userValue;
    s32 partMask;
    u32 hasExtra;
} ModelSetupDesc;

typedef struct {
    u8 data[0x2c];
} ModelPart;

typedef struct {
    u32 flags;
    u32 pad_04;
    u8 model[0x78];
    void *modelData;
    u8 pad_84[0x8c];
    u32 userValue;
    ModelPart parts[6];
    u8 pad_21c[0xc];
    void *extra;
    s8 heapId;
} ModelObject;

extern u32 MakeVramUploadParams_020a95c8(u32 file, u32 palette);
extern u32 func_ov021_020a95ec(u32 file, u32 palette);
extern s32 func_ov021_020a9614(s32 part, u32 palette);
extern void *RetainOrInitializeSharedRecord_0202c80c(s32 key, s32 context);
extern void *func_0202c48c(u32 id, s32 mode);
extern void func_0202ed9c(void *model, void *record, void *block, s32 context);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void Model_SetAllPolygonIds_0201a8c0(void *model, s32 id);
extern void func_0202f590(void *model, s32 value);
extern void func_0202f5b4(void *model, s32 value);
extern void AcquireSharedRecordState_020a9054(void *state, s32 key, void *model, s32 context);
extern void func_ov021_020a9794(ModelObject *obj, ModelSetupDesc *desc);
extern void func_ov021_020a9814(void *extra, ModelSetupDesc *desc, s32 heapId);

void LoadModelObject_020a998c(ModelObject *obj, ModelSetupDesc *desc)
{
    s32 context = obj->heapId + 8;
    if (!(obj->flags & 1)) {
        void *record;
        void *block;
        obj->flags |= 1;
        obj->userValue = desc->userValue;
        record = RetainOrInitializeSharedRecord_0202c80c(MakeVramUploadParams_020a95c8(desc->file, desc->palette), context);
        block = func_0202c48c(func_ov021_020a95ec(desc->file, desc->palette), 0x11);
        func_0202ed9c(obj->model, record, block, context);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
        Model_SetAllPolygonIds_0201a8c0(obj->modelData, 0x3f);
        func_0202f590(obj->model, 1);
        func_0202f5b4(obj->model, 0x7fff);
        if (desc->partMask > 0) {
            BOOL any = FALSE;
            int i;
            for (i = 0; i < 6; i++) {
                if ((1 << i) & desc->partMask) {
                    s32 part = i;
                    if (i == 5 && (desc->partMask & 0x80)) {
                        part = i + 1;
                    }
                    AcquireSharedRecordState_020a9054(&obj->parts[i], func_ov021_020a9614(part, desc->palette), obj->model, context);
                    any = TRUE;
                }
            }
            if (any) {
                obj->flags |= 4;
            }
        }
        if (!(desc->partMask & 0x100)) {
            func_ov021_020a9794(obj, desc);
        }
        if (desc->hasExtra) {
            obj->extra = NNSi_FndAllocFromDefaultHeap_0202a178(0x114);
            func_ov021_020a9814(obj->extra, desc, obj->heapId);
        }
    }
}
