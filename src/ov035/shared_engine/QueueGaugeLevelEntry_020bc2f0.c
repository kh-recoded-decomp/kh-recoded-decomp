#include "nitro/types.h"

typedef struct LevelEntry {
    u8 header[0x0c];
    s16 levelA;
    s16 levelB;
    s16 scale;
    u8 unknown_12[2];
} LevelEntry;

typedef struct LevelQueue {
    u8 unknown_00[0x3c];
    LevelEntry entries[12];
    int count;
} LevelQueue;

typedef struct SoundWork {
    void *unknown_00;
    LevelQueue *queue;
} SoundWork;

extern SoundWork data_ov035_020bc4e8;
extern int _s32_div_f(int numerator, int denominator);
extern void func_01ff89a8(const void *src, void *dest, u32 size);

void QueueGaugeLevelEntry_020bc2f0(const void *header, u16 valueA, u16 valueB, u16 limit, BOOL wide)
{
    LevelQueue *queue = data_ov035_020bc4e8.queue;
    int levelA;
    int levelB;
    int slot;
    u32 clampedA;
    u16 scale;

    if (queue->count < 12) {
        scale = wide ? 0x30 : 0x18;
        clampedA = valueA <= limit ? valueA : limit;
        if (valueB > limit) {
            valueB = limit;
        }
        levelA = _s32_div_f(clampedA * scale, limit);
        levelB = _s32_div_f(valueB * scale, limit);
        if (valueA != 0 && levelA == 0) {
            levelA = 1;
        }
        slot = queue->count;
        queue->entries[slot].levelA = levelA;
        queue->entries[slot].levelB = levelB;
        queue->entries[slot].scale = scale;
        func_01ff89a8(header, queue->entries[slot].header, 0xc);
        queue->count++;
    }
}
