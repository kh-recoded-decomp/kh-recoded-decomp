#include "nitro/types.h"

typedef struct {
    u32 words[3];
} Block3;

extern u8 *data_0206084c;
extern int RecentRing_Record_0204cb9c(u32 id, u32 kind);
extern int func_0204cc5c(void);
extern void func_0201fdfc(int *player, int seqArc, int index, int priority, u32 owner, u32 kind);
extern void func_0204cd64(int slot);

u32 SpawnSoundSlot_0204da8c(u32 owner, u32 kind, u32 *position, u32 flags)
{
    u8 *base = data_0206084c;
    int slot;
    int index;

    if (base[0xb47d5] == 0)
        return 0;
    if (owner == 0)
        owner = *(u32 *)(base + 0xa4);
    if ((flags & 2) == 0 && RecentRing_Record_0204cb9c(owner, kind) == 0)
        return 0;
    slot = func_0204cc5c();
    if (slot == 0)
        return 0;
    *(Block3 *)(slot + 8) = *(Block3 *)position;
    *(u16 *)(slot + 0x14) &= ~2;
    if (flags & 4)
        *(u16 *)(slot + 0x14) |= 8;
    else
        *(u16 *)(slot + 0x14) &= ~8;
    func_0201fdfc((int *)(slot + 0x1c), *(s16 *)(slot + 0x16), -1, -1, owner, kind);
    func_0204cd64(slot);
    index = slot - (int)(data_0206084c + 0xb4518);
    return ((index / 32) << 24) | *(u32 *)(slot + 0x18);
}
