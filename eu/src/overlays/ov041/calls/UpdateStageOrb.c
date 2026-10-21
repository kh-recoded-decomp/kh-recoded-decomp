#include "nitro/types.h"
#include "src/overlays/ov041/StageOrbs.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void TurnVecTowardVecLimited(VecFx32 *vec, const VecFx32 *target, fx32 maxAngle);
extern void SetStageOrbPhase(StageOrb *orb, int phase);
extern int GetScaleLevel(fx32 value);
extern fx32 GetScaleLevelFactor(int level);
extern void func_020367d4(void *manager, void *node);
extern BOOL PlaySoundChecked(int seqArcNo, int index);

/*
 * Moves an orb for one frame: it falls while bursting and steers toward the collector while homing. Once it
 * touches the collector it is freed and the collector gets its hp back (up to its maximum).
 */
void UpdateStageOrb(StageOrb *orb, StageOrbPool *pool, StageEntry *collector, const VecFx32 *target)
{
    VecFx32 offset;
    VecFx32 toTarget;
    fx32 distance;

    VEC_Subtract(target, &orb->position, &toTarget);
    offset = toTarget;
    switch (orb->phase) {
    case STAGE_ORB_BURST:
        orb->velocity.y -= 0x52;
        break;
    case STAGE_ORB_HOMING:
        TurnVecTowardVecLimited(&orb->velocity, &offset, 0x430);
        break;
    }
    distance = VEC_Mag(&offset);
    if (distance <= collector->radius + GetScaleLevelFactor(GetScaleLevel(orb->value))) {
        SetStageOrbPhase(orb, STAGE_ORB_FREE);
        orb->position = *target;
        func_020367d4(pool->drawList, orb->link);
        collector->hp += (s16)(orb->value >> FX32_SHIFT);
        if (collector->hp > collector->maxHp) {
            collector->hp = collector->maxHp;
        }
        PlaySoundChecked(0, 15);
        return;
    }
    VEC_Add(&orb->position, &orb->velocity, &orb->position);
}
