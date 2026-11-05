#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x218];
    u32 pendingValue;
} Session;

extern Session *data_ov001_020a0480;
extern void ConfigureFieldTracks(int x, int y, int mode, int param);
extern u32 GetManagedActorPosition(int index);
extern u32 GetBiasAdjustedField(int index);
extern void StorePackedSessionPlacement(u32 values, u32 extra);
extern void SetGlobalStateValue(u32 value);

void QueueStage900AndSaveLeaderPlacement(u32 value)
{
    u32 values;

    ConfigureFieldTracks(900, -4, 1, -1);
    data_ov001_020a0480->pendingValue = value;
    values = GetManagedActorPosition(0);
    StorePackedSessionPlacement(values, GetBiasAdjustedField(0));
    SetGlobalStateValue(-1);
}
