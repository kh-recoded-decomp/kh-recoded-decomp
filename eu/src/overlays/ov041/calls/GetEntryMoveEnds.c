#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole count as fx32, rounded the way the converter of the original tools did. */
#define INT_TO_FX32(x) ((x) > 0 ? (fx32)((f32)((x) << FX32_SHIFT) + 0.5f) : (fx32)((f32)((x) << FX32_SHIFT) - 0.5f))

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern void GetEntryOverheadPosition(VecFx32 *out, StageEntry *entry);
extern void GetStageGridPosition(VecFx32 *position, u8 row, u8 column);

static inline VecFx32 PositionOf(StageEntry *entry)
{
    VecFx32 position;

    GetEntryPosition(&position, entry);
    return position;
}

static inline VecFx32 AboveGroundOf(StageEntry *entry)
{
    VecFx32 position;

    GetPositionAboveGround(&position, entry);
    return position;
}

static inline fx32 OverheadY(StageEntry *entry)
{
    VecFx32 position;

    GetEntryOverheadPosition(&position, entry);
    return position.y;
}

static inline VecFx32 GridOf(u8 row, u8 column)
{
    VecFx32 position;

    GetStageGridPosition(&position, row, column);
    return position;
}

/*
 * Where an entry's move starts and ends: it starts where the entry stands; going to its main target it ends
 * above the target's ground, its radius plus the target's in front of it (kinds 1 and 6: the target's radius plus
 * the action's extra reach), with kind 0x10 attackers aiming at twice or half the target's overhead height and
 * kind 0x12 staying one unit above the start; going back it ends on its grid place at its ground height.
 */
void GetEntryMoveEnds(StageEntry *entry, VecFx32 *start, VecFx32 *end, BOOL toTarget)
{
    StageEntry *target = &gMovieContextState->stageWork->entries[entry->mainTarget];
    StageEntryAction *action = GetEntryAction(entry);
    fx32 reach = entry->radius + target->radius;

    if (action->kind == 1 || action->kind == 6) {
        reach = target->radius + FX_Mul(INT_TO_FX32(action->extraReach), 0x19a);
    }
    *start = PositionOf(entry);
    if (toTarget) {
        *end = AboveGroundOf(target);
        if (entry->flags & STAGE_ENTRY_ENEMY) {
            reach = FX_Mul(reach, -FX32_ONE);
        }
        end->x += reach;
        switch (entry->kind) {
        case 0x12:
            end->y = start->y + FX32_ONE;
            break;
        case 0x10:
            if (action->attackStyle == 0) {
                end->y = FX_Mul(OverheadY(target), 2 * FX32_ONE);
            } else {
                end->y = FX_Div(OverheadY(target), 2 * FX32_ONE);
            }
            break;
        }
    } else {
        *end = GridOf(entry->row, entry->column);
        end->y += entry->groundHeight;
    }
}
