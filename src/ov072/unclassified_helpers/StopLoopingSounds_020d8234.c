#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x40];
    s16 soundGroups[5];
    u8 pad_4A[0x84 - 0x4A];
    s32 loopEmitter0 : 8;
    s32 loopEmitter1 : 8;
    s32 loopEmitter2 : 6;
} SoundObject;

extern void StopAndClearSoundEmitter_020a8e14(s32 groupId, s32 emitterIndex);
extern void func_ov001_020734f8(void);
extern void SetManagerEnabled_0206e160(u32 enabled);

void StopLoopingSounds_020d8234(void *list, SoundObject *object)
{
    if (object->loopEmitter0 != -1) {
        StopAndClearSoundEmitter_020a8e14(object->soundGroups[4], object->loopEmitter0);
        object->loopEmitter0 = -1;
    }
    if (object->loopEmitter1 != -1) {
        StopAndClearSoundEmitter_020a8e14(object->soundGroups[0], object->loopEmitter1);
        object->loopEmitter1 = -1;
    }
    if (object->loopEmitter2 != -1) {
        StopAndClearSoundEmitter_020a8e14(object->soundGroups[1], object->loopEmitter2);
        object->loopEmitter2 = -1;
    }
    func_ov001_020734f8();
    SetManagerEnabled_0206e160(0);
}
