#include "nitro/types.h"

typedef struct {
    u8 state;
    u8 pad_01[3];
    u16 flags;
    u8 pad_06[0x10E];
    u32 soundHandle;
    u8 pad_118[0x20];
} SoundEmitter;

typedef struct {
    SoundEmitter *emitters;
    s32 emitterCount;
    s16 groupId;
} SoundEmitterGroup;

extern s32 data_ov021_020b5608;
extern void StopSoundSeqHandle_0204dbe4(u32 handle);
extern SoundEmitterGroup *func_ov021_020a8810(s32 groupId);

void StopAndClearSoundEmitter_020a8e14(s32 groupId, s32 emitterIndex)
{
    SoundEmitterGroup *group;
    SoundEmitter *emitter;

    func_ov021_020a8810(groupId);
    if (data_ov021_020b5608 != 0 && (group = func_ov021_020a8810(groupId)) != NULL) {
        emitter = &group->emitters[emitterIndex];
        if (emitter->soundHandle != 0) {
            if ((emitter->flags & 0x80) == 0) {
                StopSoundSeqHandle_0204dbe4(emitter->soundHandle);
            }
            emitter->soundHandle = 0;
        }
        emitter->state = 0;
    }
}
