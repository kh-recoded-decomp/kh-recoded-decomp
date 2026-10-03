#include "nitro/types.h"

typedef struct {
    s32 kind;
} SoundRequest;

extern u32 SpawnSoundSlot_0204da8c(u32 owner, u32 kind, void *position, u32 flags);

void SoundRequest_Play_020cd9c0(SoundRequest *request, void *position)
{
    switch (request->kind) {
    case 1:
        SpawnSoundSlot_0204da8c(0x19d, 2, position, 0);
        break;
    case 2:
        SpawnSoundSlot_0204da8c(0x19d, 3, position, 0);
        break;
    case 3:
        SpawnSoundSlot_0204da8c(0xca, 1, position, 0);
        break;
    case 4:
        SpawnSoundSlot_0204da8c(0xcb, 1, position, 0);
        break;
    }
}
