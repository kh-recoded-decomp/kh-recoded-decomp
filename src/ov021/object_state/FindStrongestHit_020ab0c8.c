#include "nitro/types.h"

typedef struct {
    s32 target;
    s32 side;
    s32 strength;
    u8 pad_0c[0xc8];
} HitResult;

typedef struct {
    HitResult result;
    u32 active;
    u32 pad_d8;
} HitScan;

typedef struct {
    u8 data[0x60];
} HitQuery;

typedef struct {
    u8 data[0x28];
} HitFilter;

typedef struct {
    u32 flags;
} UnitType;

typedef struct {
    u8 pad_00[0x138];
    UnitType *type;
} Unit;

typedef struct Attacker Attacker;
typedef void (*HitCallback)(Attacker *attacker, Unit *unit, HitScan *scan);

struct Attacker {
    s32 player;
    u8 pad_04[0x30];
    HitCallback onHit;
    HitCallback onScan;
};

extern void func_ov021_020ac148(HitResult *result);
extern void func_ov021_020aaad4(Unit *unit, HitQuery *query, u32 arg0, u32 arg1);
extern s32 func_ov021_020ac0d4(HitQuery *query);
extern void func_ov021_020aacb8(Unit *unit, s32 player, HitFilter *filter);
extern void ZeroAndSetField0xd4_020ac150(HitScan *scan);
extern BOOL func_ov021_020ac164(s32 player, HitQuery *query, HitFilter *filter, HitScan *scan);
extern void AdvanceToSecondPhase_020ab5f0(Unit *unit);

HitResult FindStrongestHit_020ab0c8(Attacker *attacker, Unit *unit, u32 arg0, u32 arg1)
{
    UnitType *type = unit->type;
    BOOL advance;
    HitQuery query;
    HitScan scan;
    HitResult best;
    HitFilter filter;
    HitScan *cur = &scan;

    func_ov021_020ac148(&best);
    func_ov021_020aaad4(unit, &query, arg0, arg1);
    if (func_ov021_020ac0d4(&query) <= 0) {
        return best;
    }
    func_ov021_020aacb8(unit, attacker->player, &filter);
    advance = FALSE;
    ZeroAndSetField0xd4_020ac150(&scan);
    while (func_ov021_020ac164(attacker->player, &query, &filter, &scan)) {
        if (cur->result.strength != 0) {
            if (cur->result.strength == 1) {
                if (!(type->flags & 4)) {
                    advance = TRUE;
                }
                if ((type->flags & 0x2000) && cur->result.side == 2) {
                    advance = FALSE;
                }
            } else if (!(type->flags & 2)) {
                advance = TRUE;
            }
            if (attacker->onScan != NULL) {
                attacker->onScan(attacker, unit, &scan);
            }
            if (cur->result.strength != 0 && best.strength <= cur->result.strength) {
                best = scan.result;
            }
            if (!(type->flags & 0x10) && attacker->onHit != NULL) {
                attacker->onHit(attacker, unit, &scan);
            }
        }
    }
    if (advance) {
        AdvanceToSecondPhase_020ab5f0(unit);
    }
    return best;
}
