#include "nitro/types.h"

typedef struct EventTargetConfig {
    u8 pad_00[0x4c];
    s32 distanceLimit;
} EventTargetConfig;

typedef struct EventTargetWork {
    u8 pad_00[8];
    EventTargetConfig *config;
    u8 pad_0c[0xa0];
    s16 layerId;
    u8 channel;
} EventTargetWork;

extern int VEC_Distance(const void *a, const void *b);
extern int ScriptCmd_ResetScreenLayer(unsigned int value, int layerId, int channel);
extern void ConfigureChannelSlot(int channel, int mode, int value);
extern int func_ov001_0206dc38(void);
extern unsigned int GetBoundedEntryField(int index);
extern void *func_ov001_0206dc4c(int index);
extern void *GetRaisedOwnerPosition(EventTargetWork *work);

void UpdateEventTargetMode(EventTargetWork *work)
{
    int result;
    void *targetPosition;
    void *playerPosition;

    result = func_ov001_0206dc38();
    if (result <= 0) {
        return;
    }
    targetPosition = GetRaisedOwnerPosition(work);
    playerPosition = func_ov001_0206dc4c(0);
    result = VEC_Distance(targetPosition, playerPosition);
    if (work->config->distanceLimit < result) {
        return;
    }
    result = ScriptCmd_ResetScreenLayer(GetBoundedEntryField(0), work->layerId, work->channel);
    if (result != 0) {
        ConfigureChannelSlot(0, 2, 0);
        return;
    }
    ConfigureChannelSlot(0, 1, 0);
}
