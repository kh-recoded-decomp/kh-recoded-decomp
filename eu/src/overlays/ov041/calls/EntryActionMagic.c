#pragma opt_propagation off
#pragma opt_common_subs off
#pragma opt_rotateloops off
#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole frame count as fx32, rounded half away from zero (converted once, after the rounding). */
#define FRAME_TO_FX32(x) ((fx32)((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f))

#define YAW_TURNED 0x3ffc /* facing across the field */
#define SHOT_HEIGHT 0x19a

/* StageEntryAction.castStyle */
#define CAST_SHOT 0 /* a shot flies from the caster to the target */
#define CAST_LOB 1 /* a shot rises over the caster, then drops on the target */
#define CAST_AT_TARGET 2 /* the effect appears on the target */
#define CAST_ON_SELF 3 /* the effect appears on the caster */
#define CAST_AT_PRIMARIES 4 /* a shot flies to every standing primary entry */
#define CAST_FROM_HAND 5 /* a shot held in the caster's hand is thrown at the target */
#define CAST_NONE 0x32

#define SPELL_SHOT 10
#define SPELL_LOB 20
#define SPELL_AT_TARGET 30
#define SPELL_ON_SELF 40
#define SPELL_AT_PRIMARIES 50
#define SPELL_FROM_HAND 60
#define SPELL_PLAIN 90
#define SPELL_HIT 100

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern void PlayEntryActionSound(StageEntry *entry, fx32 frame);
extern void HandleTimedPressWindow(StageEntry *entry, int animation, fx32 hitFrame);
extern int func_0202a9e4(u16 range);
extern void ChooseEntryMainTarget(StageEntry *entry);
extern void FinishEntryAction(StageEntry *entry);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern void GetEntryOverheadPosition(VecFx32 *out, StageEntry *entry);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern int NNS_G3dGetResDictIdxByName(const void *dict, const char *name);
extern void MI_Copy48B(const void *src, void *dest);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern void StartStageMotion(VecFx32 *position, StageMotion *motion, const VecFx32 *start, const VecFx32 *end,
                             fx32 duration, int profile);
extern BOOL StepStageMotion(VecFx32 *position, StageMotion *motion, fx32 step);
extern void SpawnPanelDriftPreset(int preset);
extern void ReleaseStageItem(StageResourceItem *item);
extern void ComputeEntryHit(StageEntry *entry, StageEntryHit *hit);
extern void ApplyActionToTargets(StageEntry *entry);
extern const MtxFx43 *NNS_G3dGlbGetInvV(void);
extern void MTX_Concat43(const MtxFx43 *a, const MtxFx43 *b, MtxFx43 *ab);
extern BOOL IsStageEntryFrozen(StageEntry *entry);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void ClearEntryActionState(StageEntry *entry);
extern BOOL MatchesEitherSlotId(StageEntry *entry, int animation);
extern const char sOv041_Bip01RHand_020cf780[];

static inline void TurnItemModel(StageItemModel *model, u16 yaw)
{
    model->yaw = yaw;
    model->flags |= STAGE_MODEL_USE_YAW;
}

/*
 * Action handler for magic (kind 2): the caster plays its animation and its effect item appears at the cast frame,
 * then an aim effect shows over it and the spell reaches the main target in one of six styles: a shot flying from
 * the caster, a lob that rises over the caster and drops on the target, an effect on the target, an effect on the
 * caster (with a panel drift), shots flying to every standing primary entry, or a shot held in the caster's right
 * hand and thrown at the target (sound 0x44/2 plays early in its first throw). After the hit, once the entry is no
 * longer frozen, the cast starts over while the attack flag is set (the hand-thrown shot keeps it set until
 * castCount casts are done); otherwise the action finishes.
 */
void EntryActionMagic(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    StageEntryAction *action = GetEntryAction(entry);
    int frame;
    BOOL again = FALSE;
    BOOL arrived;
    int i;
    VecFx32 shotStart;
    VecFx32 shotEnd;
    VecFx32 lobStart;
    VecFx32 lobEnd;
    VecFx32 dropStart;
    VecFx32 dropEnd;
    VecFx32 primaryStart;
    VecFx32 primaryEnd;
    MtxFx43 hand;
    VecFx32 handStart;
    VecFx32 handEnd;

    frame = GetEntryAnimationFrame(entry);
    PlayEntryActionSound(entry, frame);
    HandleTimedPressWindow(entry, action->animation, FRAME_TO_FX32(action->effectLength));
    switch (entry->stateStep) {
    case 0:
        data_ov041_020cff48.castsDone = 0;
        data_ov041_020cff48.castCount =
            func_0202a9e4((action->maxRepeats + 1 - action->minRepeats) * 1000) / 1000 + action->minRepeats;
        entry->stateStep++;
    case 1:
        ChooseEntryMainTarget(entry);
        if (entry->mainTarget == entry->index) {
            FinishEntryAction(entry);
            return;
        }
        if (action->castStyle == CAST_NONE) {
            entry->stateStep = SPELL_PLAIN;
            again = TRUE;
            break;
        }
        SetSceneEntryAnimation(entry, action->animation, 1, 1);
        frame = GetEntryAnimationFrame(entry);
        PlayEntryActionSound(entry, frame);
        entry->stateStep++;
    case 2:
        if (frame < FRAME_TO_FX32(action->castFrame)) {
            break;
        }
        if (action->castStyle == CAST_FROM_HAND) {
            VecFx32 position;
            void *dict;

            GetEntryPosition(&position, entry);
            entry->effects[0] =
                SpawnStageItem(entry, action->shotCategory, action->shotIndex, action->shotAnimation, &position, TRUE);
            if (entry->slot.node.modelResource != NULL) {
                dict = (u8 *)entry->slot.node.modelResource + 0x40;
            } else {
                dict = NULL;
            }
            entry->effects[0]->variant =
                dict != NULL ? NNS_G3dGetResDictIdxByName(dict, sOv041_Bip01RHand_020cf780) : -1;
            entry->effects[0]->flags |= 0x10;
        } else {
            VecFx32 position;
            StageResourceItem *item;

            GetEntryPosition(&position, entry);
            item = SpawnStageItem(entry, action->effectCategory, action->effectIndex, action->effectAnimation, &position,
                                  FALSE);
            if (item != NULL) {
                MI_Copy48B(&entry->slot.node.rotation, &item->model.rotation);
                if (entry->kind == 5) {
                    item->model.position.x += FX32_ONE;
                    item->model.position.y += 0x333;
                }
            }
        }
        entry->stateStep++;
    case 3:
        if (frame < FRAME_TO_FX32(action->effectFrame)) {
            break;
        }
        if (action->castStyle != CAST_FROM_HAND) {
            VecFx32 position;
            StageResourceItem *item;

            GetEntryOverheadPosition(&position, entry);
            item = SpawnStageItem(entry, action->aimEffectCategory, action->aimEffectIndex, action->aimEffectAnimation,
                                  &position, FALSE);
            if (item != NULL) {
                MI_Copy48B(&entry->slot.node.rotation, &item->model.rotation);
                if (entry->kind != 6) {
                    if (entry->kind == 0xc && action->castStyle == CAST_SHOT) {
                        item->model.position.y += 2 * FX32_ONE;
                    }
                } else {
                    item->model.position.x += FX32_ONE;
                    item->model.position.y += FX32_ONE / 2;
                }
            }
        }
        switch (action->castStyle) {
        case CAST_SHOT:
            entry->stateStep = SPELL_SHOT;
            break;
        case CAST_LOB:
            entry->stateStep = SPELL_LOB;
            break;
        case CAST_AT_TARGET:
            entry->stateStep = SPELL_AT_TARGET;
            break;
        case CAST_ON_SELF:
            entry->stateStep = SPELL_ON_SELF;
            break;
        case CAST_AT_PRIMARIES:
            entry->stateStep = SPELL_AT_PRIMARIES;
            break;
        case CAST_FROM_HAND:
            entry->stateStep = SPELL_FROM_HAND;
            break;
        }
        again = TRUE;
        break;
    case SPELL_SHOT: {
        VecFx32 position;

        GetEntryOverheadPosition(&position, entry);
        entry->effects[0] =
            SpawnStageItem(entry, action->shotCategory, action->shotIndex, action->shotAnimation, &position, TRUE);
        TurnItemModel(&entry->effects[0]->model, YAW_TURNED);
        if (entry->kind == 0xc) {
            PlayStageSound(action->soundSeqArc, 7, FALSE);
        }
        {
            VecFx32 position;

            GetPositionAboveGround(&position, entry);
            shotStart = position;
        }
        {
            VecFx32 position;

            GetEntryOverheadPosition(&position, &work->entries[entry->mainTarget]);
            shotEnd = position;
        }
        switch (entry->kind) {
        case 0xf:
            shotStart.x += 6 << 10;
            shotStart.y += 2 << 10;
            break;
        case 0x18:
            shotStart.x += 0x299a;
            shotStart.z += 0x333;
            shotStart.y = SHOT_HEIGHT;
            shotEnd.y = SHOT_HEIGHT;
            break;
        case 0xe:
            GetEntryPosition(&shotStart, entry);
            shotStart.x += 0xb33;
            break;
        case 5:
            GetEntryPosition(&shotStart, entry);
            shotStart.y += 2 * FX32_ONE;
            break;
        case 0x12:
            GetEntryPosition(&shotStart, entry);
            shotStart.y += FX32_ONE;
            break;
        case 0xc:
            GetEntryPosition(&shotStart, entry);
            shotStart.y += 2 * FX32_ONE;
            break;
        default:
            shotStart.x += 1 << 10;
            break;
        }
        StartStageMotion(&entry->effects[0]->model.position, &entry->effects[0]->model.motion, &shotStart, &shotEnd,
                         FRAME_TO_FX32(action->effectLength) - FRAME_TO_FX32(action->effectFrame), STAGE_MOTION_STEADY);
        entry->stateStep++;
    }
    case SPELL_SHOT + 1:
        if (!StepStageMotion(&entry->effects[0]->model.position, &entry->effects[0]->model.motion, work->frameStep)) {
            break;
        }
        entry->stateStep = SPELL_HIT;
        again = TRUE;
        break;
    case SPELL_LOB: {
        VecFx32 position;

        GetEntryOverheadPosition(&position, entry);
        entry->effects[0] =
            SpawnStageItem(entry, action->shotCategory, action->shotIndex, action->shotAnimation, &position, TRUE);
        {
            VecFx32 position;

            GetEntryOverheadPosition(&position, entry);
            lobStart = position;
        }
        switch (entry->kind) {
        case 0xf:
            lobStart.x += 0x1b33;
            lobStart.y += 1 << 11;
            break;
        case 0xe:
            lobStart.x += 0x1333;
            break;
        case 6:
            lobStart.y += 1 << 11;
            break;
        default:
            lobStart.x += 1 << 11;
            break;
        }
        lobEnd.x = FX32_ONE;
        lobEnd.y = 4 * FX32_ONE;
        lobEnd.z = 0;
        StartStageMotion(&entry->effects[0]->model.position, &entry->effects[0]->model.motion, &lobStart, &lobEnd,
                         FRAME_TO_FX32(action->returnFrame) - FRAME_TO_FX32(action->effectFrame),
                         STAGE_MOTION_EASE_OUT);
        entry->stateStep++;
    }
    case SPELL_LOB + 1:
        if (StepStageMotion(&entry->effects[0]->model.position, &entry->effects[0]->model.motion, work->frameStep)) {
            entry->stateStep++;
        }
        break;
    case SPELL_LOB + 2:
        if (frame < FRAME_TO_FX32(action->returnFrame)) {
            break;
        }
        dropStart = entry->effects[0]->model.position;
        {
            VecFx32 position;

            GetEntryOverheadPosition(&position, &work->entries[entry->mainTarget]);
            dropEnd = position;
        }
        StartStageMotion(&entry->effects[0]->model.position, &entry->effects[0]->model.motion, &dropStart, &dropEnd,
                         FRAME_TO_FX32(action->effectLength) - FRAME_TO_FX32(action->returnFrame),
                         STAGE_MOTION_EASE_IN);
        entry->stateStep++;
    case SPELL_LOB + 3:
        if (!StepStageMotion(&entry->effects[0]->model.position, &entry->effects[0]->model.motion, work->frameStep)) {
            break;
        }
        entry->stateStep = SPELL_HIT;
        again = TRUE;
        break;
    case SPELL_AT_TARGET: {
        VecFx32 position;

        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        GetPositionAboveGround(&position, &work->entries[entry->mainTarget]);
        SpawnStageItem(entry, action->shotCategory, action->shotIndex, action->shotAnimation, &position, FALSE);
        entry->stateStep = SPELL_HIT;
        again = TRUE;
        break;
    }
    case SPELL_ON_SELF: {
        VecFx32 position;
        StageResourceItem *item;

        GetEntryPosition(&position, entry);
        item = SpawnStageItem(entry, action->shotCategory, action->shotIndex, action->shotAnimation, &position, FALSE);
        if ((entry->kind == 0x18 || entry->kind == 0x19) && item != NULL) {
            MI_Copy48B(&entry->slot.node.rotation, &item->model.rotation);
        }
        SpawnPanelDriftPreset(2);
        entry->stateStep++;
    }
    case SPELL_ON_SELF + 1:
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = SPELL_HIT;
        again = TRUE;
        break;
    case SPELL_AT_PRIMARIES:
        for (i = 0; i < work->primaryCount; i++) {
            if (!(work->entries[i].flags & STAGE_ENTRY_ENEMY) && work->entries[i].state != STAGE_ENTRY_OUT) {
                VecFx32 position;

                GetEntryPosition(&position, entry);
                entry->effects[i] = SpawnStageItem(entry, action->shotCategory, action->shotIndex, action->shotAnimation,
                                                   &position, TRUE);
                {
                    VecFx32 position;

                    GetEntryPosition(&position, entry);
                    primaryStart = position;
                }
                {
                    VecFx32 position;

                    GetEntryOverheadPosition(&position, &work->entries[i]);
                    primaryEnd = position;
                }
                primaryStart.x += 0x11 << 10;
                primaryStart.y += 0xa << 10;
                StartStageMotion(&entry->effects[i]->model.position, &entry->effects[i]->model.motion, &primaryStart,
                                 &primaryEnd,
                                 FRAME_TO_FX32(action->effectLength) - FRAME_TO_FX32(action->effectFrame),
                                 STAGE_MOTION_STEADY);
            }
        }
        entry->stateStep++;
    case SPELL_AT_PRIMARIES + 1:
        arrived = TRUE;
        for (i = 0; i < work->primaryCount; i++) {
            StageResourceItem *shot = entry->effects[i];

            if (shot != NULL && !StepStageMotion(&shot->model.position, &shot->model.motion, work->frameStep)) {
                arrived = FALSE;
            }
        }
        if (!arrived) {
            break;
        }
        for (i = 0; i < work->primaryCount; i++) {
            ReleaseStageItem(entry->effects[i]);
            entry->effects[i] = NULL;
        }
        ComputeEntryHit(entry, &entry->hit);
        ApplyActionToTargets(entry);
        entry->stateStep = SPELL_HIT + 1;
        again = TRUE;
        break;
    case SPELL_FROM_HAND:
        entry->effects[0]->flags &= (u8)~0x10;
        {
            VecFx32 position;

            GetEntryOverheadPosition(&position, &work->entries[entry->mainTarget]);
            handEnd = position;
        }
        handEnd.y += 1 << 10;
        MTX_Concat43((const MtxFx43 *)&entry->effects[0]->model.rotation, NNS_G3dGlbGetInvV(), &hand);
        {
            /* the hand's translation, read z first */
            fx32 z = hand._32;
            fx32 y = hand._31;
            fx32 x = hand._30;

            handStart.x = x;
            handStart.y = y;
            handStart.z = z;
        }
        StartStageMotion(&entry->effects[0]->model.position, &entry->effects[0]->model.motion, &handStart, &handEnd,
                         FRAME_TO_FX32(action->effectLength) - FRAME_TO_FX32(action->effectFrame), STAGE_MOTION_STEADY);
        SpawnStageItem(entry, action->aimEffectCategory, action->aimEffectIndex, action->aimEffectAnimation, &handStart,
                       FALSE);
        entry->stateStep++;
    case SPELL_FROM_HAND + 1:
        if (!StepStageMotion(&entry->effects[0]->model.position, &entry->effects[0]->model.motion, work->frameStep)) {
            break;
        }
        if (data_ov041_020cff48.castsDone < data_ov041_020cff48.castCount - 1) {
            entry->flags |= STAGE_ENTRY_PRESSED_ATTACK;
        } else {
            entry->flags &= ~STAGE_ENTRY_PRESSED_ATTACK;
        }
        entry->stateStep = SPELL_HIT;
        again = TRUE;
        break;
    case SPELL_PLAIN:
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        entry->stateStep++;
    case SPELL_PLAIN + 1:
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = SPELL_HIT;
        again = TRUE;
        break;
    case SPELL_HIT:
        ReleaseStageItem(entry->effects[0]);
        entry->effects[0] = NULL;
        ComputeEntryHit(entry, &entry->hit);
        ApplyActionToTargets(entry);
        entry->stateStep++;
    case SPELL_HIT + 1:
        if (IsStageEntryFrozen(entry)) {
            break;
        }
        entry->stateStep++;
    case SPELL_HIT + 2:
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        if (entry->flags & STAGE_ENTRY_PRESSED_ATTACK) {
            entry->flags &= ~STAGE_ENTRY_PRESSED_ATTACK;
            data_ov041_020cff48.castsDone++;
            entry->stateStep = 1;
            ClearEntryActionState(entry);
            break;
        }
        entry->stateStep++;
    case SPELL_HIT + 3:
        FinishEntryAction(entry);
        break;
    }
    if (action->castStyle == CAST_FROM_HAND && data_ov041_020cff48.castsDone == 0 &&
        MatchesEitherSlotId(entry, action->animation) && frame >= FX32_ONE && frame < 2 * FX32_ONE) {
        PlayStageSound(0x44, 2, TRUE);
    }
    if (again) {
        EntryActionMagic(entryIndex);
    }
}
