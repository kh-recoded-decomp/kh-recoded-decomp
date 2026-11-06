#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[8];
    u32 result;
} State_020baac0;

extern State_020baac0 *gResumeModeWorkStorage;

void CompleteResumeModeWithResult(u32 value)
{
    gResumeModeWorkStorage->result = value;
    gResumeModeWorkStorage->flags |= 0x4000;
}
