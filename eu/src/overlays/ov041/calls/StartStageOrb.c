#include "nitro/types.h"
#include "src/overlays/ov041/StageOrbs.h"

extern void SetStageOrbPhase(StageOrb *orb, int phase);
extern int GetScaleLevel(fx32 value);
extern fx32 GetScaleLevelFactor(int level);
extern void func_020367c4(void *manager, void *node);

/* Starts an orb worth value at a position, sized by its value, and puts it on the draw list. */
void StartStageOrb(StageOrb *orb, StageOrbPool *pool, const VecFx32 *position, fx32 value)
{
    SetStageOrbPhase(orb, STAGE_ORB_BURST);
    orb->sprite = pool->sprite;
    orb->value = value;
    orb->position = *position;
    orb->baseScale = GetScaleLevelFactor(GetScaleLevel(value)) * 2;
    orb->scale = orb->baseScale;
    orb->frameTimer = 0;
    orb->frame = orb->frameTimer;
    orb->width = 0x20;
    orb->height = 0x20;
    orb->alpha = 0x1f;
    orb->rotation = 0;
    func_020367c4(pool->drawList, orb->link);
}
