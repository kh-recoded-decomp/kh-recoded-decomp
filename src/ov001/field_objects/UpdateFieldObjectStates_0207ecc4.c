#include "nitro/types.h"

typedef struct FieldObject FieldObject;
typedef void *(*FieldObjectState)(FieldObject *object);

struct FieldObject {
    u32 unk0;
    FieldObject *next;
    u8 pad8[0xc];
    FieldObjectState state;
};

typedef struct FieldObjectList {
    u32 unk0;
    u32 unk4;
    FieldObject *head;
} FieldObjectList;

typedef struct FieldFlags {
    u32 unk0 : 6;
    u32 suppressed : 1;
    u32 unk7 : 25;
} FieldFlags;

typedef struct FieldStatus {
    u8 unk0 : 1;
    u8 phase : 3;
    u8 unk4 : 4;
} FieldStatus;

typedef struct FieldContext {
    u8 pad[0x214];
    FieldFlags flags;
    u8 pad218[0x25d9];
    FieldStatus status;
} FieldContext;

extern FieldObjectList *data_ov001_020a04d8;
extern FieldContext *data_ov001_020a0460;
extern int func_ov001_02067ed4(void);
extern BOOL IsObjectFlagClear_0207f7a4(FieldObject *object);
extern void func_ov001_02086c60(int arg);

void UpdateFieldObjectStates_0207ecc4(int arg) {
    FieldObjectList *list = data_ov001_020a04d8;
    FieldContext *context = data_ov001_020a0460;
    FieldObject *object;
    FieldObject *next;
    FieldObjectState state;

    if (!context->flags.suppressed) {
        context->status.phase = 2;
    }
    if (func_ov001_02067ed4() >= 0) {
        for (object = list->head; object != NULL; object = next) {
            next = object->next;
            if (IsObjectFlagClear_0207f7a4(object)) {
                state = object->state(object);
                if (state != NULL) {
                    object->state = state;
                }
            }
        }
    }
    func_ov001_02086c60(arg);
}
