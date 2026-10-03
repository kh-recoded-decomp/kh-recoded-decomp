#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[6];
    u16 strength;
    u16 magic;
} PlayerStats;

typedef struct {
    fx32 power;
    u8 pad_04[0xc];
    u8 attackType;
    u8 element;
} AttackDesc;

extern void *GetBoundedEntryField_0206db5c(int player);
extern BOOL func_ov001_02075248(int player);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern int GetPlayerEntryCount_02050050(int player, u32 id);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);

fx32 ComputeAttackDamage_020ac6cc(int player, AttackDesc *attack)
{
    BOOL physical;
    BOOL magical;
    PlayerStats *stats;
    fx32 damage;
    BOOL boosted;
    stats = *(PlayerStats **)((u8 *)GetBoundedEntryField_0206db5c(player) + 0x1d4);
    damage = 0;
    physical = FALSE;
    magical = FALSE;
    boosted = FALSE;
    if (func_ov001_02075248(player)) {
        boosted = TRUE;
    }
    switch (attack->attackType) {
    case 0:
        damage = stats->strength << 12;
        if (boosted && IsPlayerEntryFlagSet_02050014(player, 0x1b)) {
            damage += FixedPointMultiply12(damage, 0x280);
        }
        physical = TRUE;
        break;
    case 1:
        damage = stats->magic << 12;
        if (boosted && IsPlayerEntryFlagSet_02050014(player, 0x1c)) {
            damage += FixedPointMultiply12(damage, 0x280);
        }
        magical = TRUE;
        break;
    }
    damage = FixedPointMultiply12(attack->power, damage);
    switch (attack->element) {
    case 1:
    case 2:
    case 3:
    case 4: {
        u32 id = attack->element - 1;
        if (IsPlayerEntryFlagSet_02050014(player, id)) {
            damage += damage * GetPlayerEntryCount_02050050(player, id) / 100;
        }
        break;
    }
    }
    if (physical) {
        if (IsPlayerEntryFlagSet_02050014(player, 0x48)) {
            damage += FixedPointMultiply12(damage, 0x480);
        }
        if (IsPlayerEntryFlagSet_02050014(player, 0x4f)) {
            damage += FixedPointMultiply12(damage, 0x800);
        }
    }
    if (magical && IsPlayerEntryFlagSet_02050014(player, 0x49)) {
        damage += FixedPointMultiply12(damage, 0x480);
    }
    return damage;
}
