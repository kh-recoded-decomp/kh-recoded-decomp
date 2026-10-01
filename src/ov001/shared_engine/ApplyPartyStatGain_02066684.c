#include "nitro/types.h"

typedef struct StatDelta {
    u16 kind;
    u16 amount;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0a;
} StatDelta;

typedef struct StatEntry {
    u8 pad_00[8];
    u16 bonusA;
    u16 bonusB;
    u8 pad_0c[0x10];
} StatEntry;

typedef struct StatTable {
    u32 count;
    StatEntry entries[1];
} StatTable;

typedef struct SessionData {
    u8 pad_000[0x210];
    StatTable *statTable;
} SessionData;

extern SessionData *data_ov001_020a0464;
extern BOOL func_ov001_020645c8(u32 bitOffset);
extern void func_ov001_02066514(StatDelta *delta, void *target, int mode);
extern void func_ov001_020665bc(int index, void *target);

static inline void ClearStatDelta(StatDelta *delta)
{
    u16 *fields = (u16 *)delta;

    fields[0] = 0;
    fields[1] = 0;
    fields[2] = 0;
    fields[3] = 0;
    fields[4] = 0;
    fields[5] = 0;
}

void ApplyPartyStatGain_02066684(int index, void *target, int amount, BOOL scaled)
{
    SessionData *session = data_ov001_020a0464;
    StatEntry *entry;
    StatDelta delta;
    u16 savedA;
    u16 savedB;

    if (index < 0) {
        return;
    }
    if (func_ov001_020645c8(0x3631)) {
        amount = 0;
    }
    entry = &session->statTable->entries[index];
    if (amount > 0) {
        ClearStatDelta(&delta);
        delta.amount = amount;
        if (scaled) {
            delta.amount /= 10;
            if (delta.amount == 0) {
                delta.amount = 1;
            }
        }
        func_ov001_02066514(&delta, target, 0);
    }
    if (!scaled) {
        savedA = entry->bonusA;
        savedB = entry->bonusB;
        entry->bonusA = 0;
        entry->bonusB = 0;
        func_ov001_020665bc(index, target);
        entry->bonusA = savedA;
        entry->bonusB = savedB;
    }
}
