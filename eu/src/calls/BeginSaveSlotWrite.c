#include "src/SaveIoState.h"

enum {
    SAVE_CLOCK_HZ = 33514000,
    SAVE_TICKS_PER_SECOND = 523656,
    SAVE_MAX_PLAY_TIME_SECONDS = 3599999,
    SAVE_AREA_OFFSET = 0x20
};

#define SAVE_SLOT_SIGNATURE 0xc3f793a3U

extern void CARD_LockBackup(u16 lockId);
extern void CARD_UnlockBackup(u16 lockId);
extern void IncrementBusyCounter(void);
extern void DecrementBusyCounterIfPositive(void);
extern int ReadCardBackupSync(u32 source, void *destination, u32 size);
extern u64 OS_GetTick(void);
extern void ComputeHash(void *digest, const void *data, u32 size);
extern void EmitCommandVariantA(u32 destination, const void *source, u32 size);

/* Start writing the current save, updating play time and its digest first. */
int BeginSaveSlotWrite(int slot)
{
    u8 probe;

    CARD_LockBackup(data_0205fe00.lockId);
    IncrementBusyCounter();
    if (ReadCardBackupSync(0, &probe, 1) != 0) {
        CARD_UnlockBackup(data_0205fe00.lockId);
        DecrementBusyCounterIfPositive();
        return 0;
    }

    u64 elapsed = OS_GetTick() - data_0205fe00.startTick;
    data_0205fe00.save->playTimeSeconds += (elapsed * 64) / SAVE_CLOCK_HZ;
    if (data_0205fe00.save->playTimeSeconds > SAVE_MAX_PLAY_TIME_SECONDS) {
        data_0205fe00.save->playTimeSeconds = SAVE_MAX_PLAY_TIME_SECONDS;
    }
    data_0205fe00.startTick += elapsed - elapsed % SAVE_TICKS_PER_SECOND;

    ComputeHash(data_0205fe00.buffer->digest, &data_0205fe00.buffer->data,
                sizeof(data_0205fe00.buffer->data));
    data_0205fe00.buffer->signature = SAVE_SLOT_SIGNATURE;
    data_0205fe00.blockCounter = 0;
    data_0205fe00.slot = slot;
    EmitCommandVariantA((data_0205fe00.slot * 2) * sizeof(SaveSlotBuffer) + SAVE_AREA_OFFSET,
                        data_0205fe00.buffer, sizeof(SaveSlotBuffer));
    return 1;
}
