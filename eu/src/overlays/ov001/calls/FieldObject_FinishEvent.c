#include "nitro/types.h"

typedef struct SessionFlags {
    u32 unk_0 : 12;
    u32 eventActive : 1;
    u32 unk_13 : 19;
} SessionFlags;

typedef struct Session {
    u8 pad_000[0x214];
    SessionFlags flags;
} Session;

typedef struct FieldObject {
    u8 pad_00[0x4e];
    u16 stateFlags;
    u8 pad_50[8];
    u8 eventState;
    s8 configFlags;
} FieldObject;

extern Session *data_ov001_020a0480;
extern void SetFieldEntriesPaused(BOOL paused);
extern void FieldObject_SetSavedValue(FieldObject *object, u32 value);

void FieldObject_FinishEvent(FieldObject *object)
{
    object->eventState = 0;
    if (!data_ov001_020a0480->flags.eventActive) {
        SetFieldEntriesPaused(FALSE);
    }
    FieldObject_SetSavedValue(object, 1);
    if (!(object->configFlags & 0x80)) {
        object->stateFlags &= ~0x10;
    }
}
