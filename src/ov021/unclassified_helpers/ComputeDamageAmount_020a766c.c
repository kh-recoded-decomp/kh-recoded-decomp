#include "nitro/types.h"

#pragma opt_lifetimes off

typedef struct UnitStats {
    u8 pad_00[0x2];
    u16 maxValue;
    u8 pad_04[0x6];
    u16 baseValue;
} UnitStats;

typedef struct Unit Unit;
typedef int (*UnitTypeFunc)(Unit *unit);

struct Unit {
    u8 pad_000[0x1d4];
    UnitStats *stats;
    u8 handle;
    u8 pad_1d9[0x3];
    int type;
    u8 pad_1e0[0x4c];
    UnitTypeFunc getType;
};

typedef struct HitInfo {
    u32 flags;
    u8 pad_04[0x4];
    int airborneTime;
    u8 pad_0c[0x10];
    int amount;
    u8 pad_20[0xc];
    int element;
} HitInfo;

typedef struct ScaleEntry {
    int offset;
    int aboveScale;
    int belowScale;
    int elementScale;
} ScaleEntry;

typedef struct ScaleTable {
    ScaleEntry entries[4];
} ScaleTable;

extern ScaleTable data_ov021_020b4de4;

extern u32 func_ov001_02075248(u32 handle);
extern s32 func_02050014(u32 handle, s32 flag);
extern s32 func_02050050(u32 handle, s32 flag);
extern s32 func_02023dbc(s32 numerator, s32 denominator);
extern int func_020511c4(void);
extern int FixedPointMultiply12(int left, int right);
extern int FX_Div_01ff9c84(int numer, int denom);
extern u32 GetSessionStateFlags2Bit_020649b8(void);
extern void AddSessionCounter_02063a80(int index, int amount);

static inline int GetUnitType(Unit *unit) {
    if (unit->getType != NULL) {
        return unit->getType(unit);
    }
    return unit->type;
}

static inline BOOL IsHitAirborne(HitInfo *hit) {
    BOOL airborne = FALSE;
    if (hit->flags & 0x80) {
        airborne = TRUE;
    }
    if (hit->airborneTime > 0) {
        airborne = TRUE;
    }
    return airborne;
}

int ComputeDamageAmount_020a766c(Unit *unit, HitInfo *hit, int capToMax) {
    int maxValue;
    int value;
    int result;
    BOOL hasBoost = FALSE;

    value = hit->amount;
    result = unit->stats->baseValue << 12;

    if (hit->flags & 0x40) {
        if (hit->flags & 2) {
            result = value >> 12;
            goto done;
        }
    } else {
        ScaleTable table;
        u32 tableIndex;
        int element;

        if (func_ov001_02075248(unit->handle)) {
            hasBoost = TRUE;
        }
        if (GetUnitType(unit) == 9) {
            result >>= 1;
        }
        if (hasBoost && func_02050014(unit->handle, 0x1d)) {
            result += FixedPointMultiply12(result, 0x500);
        }
        if (result <= 0) {
            result = 0x1000;
        }
        table = data_ov021_020b4de4;
        tableIndex = GetSessionStateFlags2Bit_020649b8();
        if (value > result) {
            value = FixedPointMultiply12(table.entries[tableIndex].offset + FixedPointMultiply12(table.entries[tableIndex].aboveScale, FX_Div_01ff9c84(value, result) - 0x1000), value);
        } else {
            value = FixedPointMultiply12(table.entries[tableIndex].offset + FixedPointMultiply12(table.entries[tableIndex].belowScale, FX_Div_01ff9c84(value, result) - 0x1000), value);
        }
        element = hit->element;
        switch (element) {
        case 1:
        case 2:
        case 3:
        case 4:
            if (func_02050014(unit->handle, element + 4)) {
                value -= func_02023dbc(value * func_02050050(unit->handle, element + 4), 100);
            }
            value = FixedPointMultiply12(value, table.entries[tableIndex].elementScale);
            break;
        }
        if (GetUnitType(unit) == 2 && IsHitAirborne(hit)) {
            value = FixedPointMultiply12(value, 0x2000);
        }
        if (!(hit->flags & 0x80)) {
            if (func_02050014(unit->handle, 0x51)) {
                value -= FixedPointMultiply12(value, 0x400);
            }
        } else if (func_02050014(unit->handle, 0x52)) {
            value -= FixedPointMultiply12(value, 0x400);
        }
        if (hasBoost && func_02050014(unit->handle, 0x1e)) {
            value /= 2;
        }
    }

    if (hit->flags & 1) {
        value = FixedPointMultiply12(value, func_020511c4());
    }
    if (hit->amount > 0 && value < 0x1000) {
        value = 0x1000;
    }
    result = value >> 12;
    maxValue = unit->stats->maxValue;
    if (func_02050014(unit->handle, 0x22) && capToMax && result >= maxValue) {
        result = maxValue - 1;
    }
    if (func_02050014(unit->handle, 0x23) && maxValue > 1 && result >= maxValue) {
        result = maxValue - 1;
    }
done:
    if (result > 0 && !(hit->flags & 0x200) && !(hit->flags & 2)) {
        AddSessionCounter_02063a80(0xb, 1);
    }
    return result;
}
