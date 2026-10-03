#include "nitro/types.h"

typedef struct HitOwner HitOwner;
typedef void (*HitCallback)(HitOwner *owner);

struct HitOwner {
    u8 pad_000[0x1d8];
    u8 playerId;
    u8 pad_1d9[0x53];
    HitCallback onHit;
};

typedef struct {
    u8 pad_00[0x24];
    u32 flags;
    u8 pad_28[8];
    s32 chance;
    s32 kind;
} HitInfo;

extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern int nextRandom12_0202aa58(void);

void RollHitEffect_020a78b0(HitOwner *owner, HitInfo *hit)
{
    s32 chance;

    if (owner->onHit != NULL) {
        owner->onHit(owner);
    }
    chance = 0;
    if (hit->kind != 0 && !IsPlayerEntryFlagSet_02050014(owner->playerId, 0x53)) {
        if (hit->kind == 12) {
            chance = hit->chance;
        }
        if (chance > 0 && nextRandom12_0202aa58() * 100 <= chance) {
            hit->flags |= 2;
        }
    }
}
