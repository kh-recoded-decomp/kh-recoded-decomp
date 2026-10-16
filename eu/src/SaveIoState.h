#ifndef RECODED_SAVE_IO_STATE_H
#define RECODED_SAVE_IO_STATE_H

#include "nitro/types.h"

typedef struct CardTransferThreadBlock CardTransferThreadBlock;
typedef int (*SaveIoCallback)(int slot);

typedef struct SaveGameData {
    u8 unknown0000[0x28c8];
    u32 playTimeSeconds;
    u8 unknown28cc[0x3760 - 0x28cc];
} SaveGameData;

typedef struct SaveSlotBuffer {
    u32 signature;
    u8 digest[20];
    SaveGameData data;
    u8 padding3778[0x3c18 - 0x3778];
} SaveSlotBuffer;

typedef struct SaveIoState {
    u8 blockCounter;
    u8 slot;
    u16 lockId;
    CardTransferThreadBlock *thread;
    SaveSlotBuffer *buffer;
    SaveGameData *save;
    SaveIoCallback doneCallback;
    s32 result;
    u64 startTick;
} SaveIoState;

typedef char SaveSlotOffset[(u32)&((SaveIoState *)0)->slot == 1 ? 1 : -1];
typedef char SaveLockIdOffset[(u32)&((SaveIoState *)0)->lockId == 2 ? 1 : -1];
typedef char SaveThreadOffset[(u32)&((SaveIoState *)0)->thread == 4 ? 1 : -1];
typedef char SaveBufferOffset[(u32)&((SaveIoState *)0)->buffer == 8 ? 1 : -1];
typedef char ActiveSaveOffset[(u32)&((SaveIoState *)0)->save == 0xc ? 1 : -1];
typedef char SaveCallbackOffset[(u32)&((SaveIoState *)0)->doneCallback == 0x10 ? 1 : -1];
typedef char SaveResultOffset[(u32)&((SaveIoState *)0)->result == 0x14 ? 1 : -1];
typedef char SaveStartTickOffset[(u32)&((SaveIoState *)0)->startTick == 0x18 ? 1 : -1];
typedef char SaveIoStateSize[sizeof(SaveIoState) == 0x20 ? 1 : -1];
typedef char PlayTimeOffset[(u32)&((SaveGameData *)0)->playTimeSeconds == 0x28c8 ? 1 : -1];
typedef char SaveDataSize[sizeof(SaveGameData) == 0x3760 ? 1 : -1];
typedef char SaveDigestOffset[(u32)&((SaveSlotBuffer *)0)->digest == 4 ? 1 : -1];
typedef char SavePayloadOffset[(u32)&((SaveSlotBuffer *)0)->data == 0x18 ? 1 : -1];
typedef char SaveSlotBufferSize[sizeof(SaveSlotBuffer) == 0x3c18 ? 1 : -1];

extern SaveIoState data_0205fe00;
int BeginSaveSlotWrite(int slot);

#endif
