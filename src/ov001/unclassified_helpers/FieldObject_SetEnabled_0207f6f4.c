#include "nitro/types.h"

typedef struct ObjectWork {
    u8 pad_00[0x8];
    u16 flags;
} ObjectWork;

struct FieldObject;

typedef struct FieldObjectClass {
    u8 pad_00[0x20];
    void (*onEnabledChanged)(struct FieldObject *object, BOOL enabled);
    u8 pad_24[0x40];
    s16 workIndex;
} FieldObjectClass;

typedef struct FieldObject {
    u8 pad_00[0x8];
    FieldObjectClass *objectClass;
    ObjectWork *work;
    u8 pad_10[0x3e];
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
} FieldObject;

extern BOOL func_ov001_0207f7a4(FieldObject *object);
extern u32 func_ov001_02064574(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);
extern void func_02036140(ObjectWork *work, BOOL enabled);
extern BOOL func_02035b38(ObjectWork *work);
extern void func_02035a18(ObjectWork *work, int a, int b);
extern void func_02036944(ObjectWork *work);
extern void func_02036994(ObjectWork *work);

void FieldObject_SetEnabled_0207f6f4(FieldObject *object, BOOL enabled)
{
    BOOL wasEnabled;
    u16 saved;
    void (*hook)(FieldObject *object, BOOL enabled);

    wasEnabled = func_ov001_0207f7a4(object);
    if (wasEnabled == enabled) {
        return;
    }
    saved = func_ov001_02064574(object->saveBitOffset, object->saveBitCount) & 0xfffe;
    if (!enabled) {
        saved |= 1;
    }
    WriteSessionPackedBits_0206459c(object->saveBitOffset, object->saveBitCount, saved);
    if ((object->flags & 4) && object->objectClass->workIndex >= 0) {
        if (enabled) {
            func_02036140(object->work, TRUE);
            if (!func_02035b38(object->work)) {
                func_02035a18(object->work, 0, 0);
            }
            if (!(object->work->flags & 0x100)) {
                func_02036944(object->work);
            }
        } else {
            func_02036140(object->work, FALSE);
            if (object->work->flags & 0x100) {
                func_02036994(object->work);
            }
        }
    }
    hook = object->objectClass->onEnabledChanged;
    if (hook != NULL) {
        hook(object, enabled);
    }
}
