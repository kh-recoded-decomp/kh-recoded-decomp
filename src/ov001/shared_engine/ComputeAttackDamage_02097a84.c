#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[0xa];
    u8 rank;
    u8 pad_0b;
    u8 element;
    u8 pad_0d;
    u16 kind;
    u8 pad_10[0x44];
    s8 resist[8];
    u8 pad_5c[6];
    u8 invincible;
    u8 pad_63[0x15];
    fx32 defense[8];
    fx32 minimum;
} DamageTarget;

typedef struct {
    u8 pad_00[0xc];
    fx32 power;
    u8 pad_10[8];
    fx32 bonus;
    u8 pad_1c[8];
    u8 element;
    u8 pad_25[3];
    u16 unk0 : 1;
    u16 elementBoost : 1;
    u16 unk2 : 3;
    u16 fixedDamage : 1;
} DamageAttack;

extern fx32 FX_Div_01ff9c84(fx32 numerator, fx32 denominator);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);

static inline fx32 ApplyResist(fx32 damage, int percent)
{
    return damage - FX_Div_01ff9c84(FixedPointMultiply12(damage, percent * FX32_ONE), 0x64000);
}

fx32 ComputeAttackDamage_02097a84(DamageTarget *target, DamageAttack *attack, int index) {
    fx32 value = attack->power;
    int element;

    if (value == 0) {
        return 0;
    }
    if (target->invincible == 1) {
        return FX32_ONE;
    }
    if (attack->fixedDamage) {
        if (target->kind != 0x3e) {
            return value;
        }
        return FixedPointMultiply12(value, 0x200);
    }
    value = target->defense[index];
    if (target->rank == 3) {
        value = FixedPointMultiply12(value, 0x1400);
    }
    switch (target->element) {
    case 4:
        if (attack->element != 4) {
            value = FixedPointMultiply12(value, 0xb00);
        }
        break;
    case 2:
        if (attack->element != 2 && attack->elementBoost) {
            value = FixedPointMultiply12(value, 0x800);
        }
        break;
    }
    if (value == 0) {
        value = 1;
    }
    if (attack->power > value) {
        value = FX_Div_01ff9c84(attack->power, value) - FX32_ONE;
        value = FixedPointMultiply12(0x100, value) + 0x280;
        value = FixedPointMultiply12(value, attack->power);
    } else {
        value = FX_Div_01ff9c84(attack->power, value) - FX32_ONE;
        value = FixedPointMultiply12(0x280, value) + 0x280;
        value = FixedPointMultiply12(value, attack->power);
    }
    element = attack->element;
    if (element != 0) {
        value = ApplyResist(value, target->resist[element - 1]);
    }
    if (attack->bonus != 0) {
        value += attack->bonus;
    }
    if (value < target->minimum) {
        return target->minimum;
    }
    return value;
}
