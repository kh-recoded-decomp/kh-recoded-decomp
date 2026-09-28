#include "nitro/types.h"

typedef struct SessionFlags {
    u32 unk_0 : 12;
    u32 bit12 : 1;
    u32 unk_13 : 19;
} SessionFlags;

typedef struct Session {
    u8 pad_000[0x214];
    SessionFlags flags;
} Session;

typedef struct FieldObject {
    u8 pad_00[0x4E];
    u16 stateFlags;
    u8 pad_50[0x8];
    u8 unk_58;
    s8 configFlags;
} FieldObject;

extern Session *data_ov001_020a0460;
extern void SetActorsEnabled_0206e444(BOOL enabled);
extern void FieldObject_SetSavedValue_0207f9c8(FieldObject *object, u32 value);

void func_ov001_02080e5c(FieldObject *object)
{
    object->unk_58 = 0;
    if (!data_ov001_020a0460->flags.bit12) {
        SetActorsEnabled_0206e444(FALSE);
    }
    FieldObject_SetSavedValue_0207f9c8(object, 1);
    if (!(object->configFlags & 0x80)) {
        object->stateFlags &= ~0x10;
    }
}
