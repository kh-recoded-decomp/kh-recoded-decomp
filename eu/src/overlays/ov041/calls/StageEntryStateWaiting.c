#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

#define YAW_TURNED 0x3ffc /* facing across, while the menu is held */
#define YAW_FORWARD 0xc004

extern u32 IsEntryFlag2Set(StageEntry *entry);
extern BOOL MatchesEitherSlotId(StageEntry *entry, int animation);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern BOOL UpdateStageEntryMove(StageEntry *entry, fx32 step);
extern void SetEntryState(StageEntry *entry, int state);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern void MoveStageEntryTo(StageEntry *entry, const VecFx32 *destination, fx32 duration, fx32 pause);

static inline VecFx32 PositionOf(StageEntry *entry)
{
    VecFx32 position;

    GetEntryPosition(&position, entry);
    return position;
}

/*
 * Entry states 1 and 2 (waiting, active): keeps the idle animation going and the entry moving; while the
 * command menu is held a player entry turns to face across (and back after); once hit, dodged or guarding it
 * plays the guard or hurt animation with one of its two hurt voices in turn (or steps back a unit when it
 * dodged), then clears those flags.
 */
void StageEntryStateWaiting(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];

    switch (entry->stateStep) {
    case 0:
        if (!IsEntryFlag2Set(entry) && !MatchesEitherSlotId(entry, entry->idleAnimation) &&
            !(entry->flags & STAGE_ENTRY_TURNED)) {
            if (entry->flags & STAGE_ENTRY_ENEMY) {
                SetSceneEntryAnimation(entry, entry->idleAnimation, 0, 0);
            } else if (!(work->flags & 0x100)) {
                SetSceneEntryAnimation(entry, entry->idleAnimation, 0, 0);
            }
        }
        if (!UpdateStageEntryMove(entry, work->frameStep)) {
            break;
        }
        if ((entry->flags & STAGE_ENTRY_FLAG_800) && MatchesEitherSlotId(entry, entry->idleAnimation)) {
            entry->flags &= ~STAGE_ENTRY_FLAG_800;
            SetEntryState(entry, 3);
            return;
        }
        if (!(entry->flags & STAGE_ENTRY_ENEMY)) {
            if (work->flags & STAGE_WORK_NO_TIMED_INPUT) {
                if (!(work->flags & STAGE_WORK_SKIP_CHANCE_B)) {
                    if (entry->slot.node.yaw != YAW_TURNED && !(entry->slot.flags & STAGE_SLOT_FACING_LOCKED)) {
                        entry->slot.node.yaw = YAW_TURNED;
                        entry->slot.node.flags |= STAGE_MODEL_USE_YAW;
                    }
                    if (MatchesEitherSlotId(entry, entry->idleAnimation) || !IsEntryFlag2Set(entry)) {
                        SetSceneEntryAnimation(entry, entry->stepAnimation, 0, 0);
                    }
                    entry->flags |= STAGE_ENTRY_TURNED;
                } else {
                    if (!(entry->slot.flags & STAGE_SLOT_FACING_LOCKED)) {
                        entry->slot.node.yaw = YAW_FORWARD;
                        entry->slot.node.flags |= STAGE_MODEL_USE_YAW;
                    }
                    if (MatchesEitherSlotId(entry, entry->stepAnimation) || !IsEntryFlag2Set(entry)) {
                        SetSceneEntryAnimation(entry, entry->idleAnimation, 0, 0);
                    }
                    entry->flags &= ~STAGE_ENTRY_TURNED;
                }
            } else if (work->flags & 0x100) {
                if (entry->slot.node.yaw != YAW_TURNED && !(entry->slot.flags & STAGE_SLOT_FACING_LOCKED)) {
                    entry->slot.node.yaw = YAW_TURNED;
                    entry->slot.node.flags |= STAGE_MODEL_USE_YAW;
                }
                if (MatchesEitherSlotId(entry, entry->idleAnimation) || !IsEntryFlag2Set(entry)) {
                    SetSceneEntryAnimation(entry, entry->stepAnimation, 0, 0);
                }
                entry->flags |= STAGE_ENTRY_TURNED;
            } else if (entry->flags & STAGE_ENTRY_TURNED) {
                if (!(entry->slot.flags & STAGE_SLOT_FACING_LOCKED)) {
                    entry->slot.node.yaw = YAW_FORWARD;
                    entry->slot.node.flags |= STAGE_MODEL_USE_YAW;
                }
                SetSceneEntryAnimation(entry, entry->idleAnimation, 0, 0);
                entry->flags &= ~STAGE_ENTRY_TURNED;
            }
        }
        if (!(entry->flags & STAGE_ENTRY_GUARDING) && !(entry->flags & STAGE_ENTRY_HURT) &&
            !(entry->flags & STAGE_ENTRY_DODGED)) {
            break;
        }
        if ((entry->flags & STAGE_ENTRY_GUARDING) && (entry->flags & STAGE_ENTRY_PRESS_PANEL)) {
            SetSceneEntryAnimation(entry, entry->guardAnimation, 0, 0);
        }
        entry->stateStep++;
    case 1:
        entry->stateStep++;
    case 2:
        if (entry->flags & STAGE_ENTRY_GUARDING) {
            if (!(entry->flags & STAGE_ENTRY_HURT) && !(entry->flags & STAGE_ENTRY_DODGED) && IsEntryFlag2Set(entry)) {
                break;
            }
            if (!IsEntryFlag2Set(entry)) {
                SetSceneEntryAnimation(entry, entry->idleAnimation, 0, 0);
            }
        }
        entry->stateStep++;
    case 3:
        if (!(entry->flags & STAGE_ENTRY_HURT) && !(entry->flags & STAGE_ENTRY_DODGED)) {
            break;
        }
        entry->stateStep++;
    case 4:
        if (!(entry->flags & STAGE_ENTRY_GUARDED)) {
            if (entry->flags & STAGE_ENTRY_HURT) {
                SetSceneEntryAnimation(entry, entry->hurtAnimation, 0, 1);
                if (entry->flags & STAGE_ENTRY_ENEMY) {
                    if (entry->kind == 0x17) {
                        if (entry->flags & STAGE_ENTRY_VOICE_TOGGLE) {
                            PlayStageSound(0x44, 0, TRUE);
                            entry->flags &= ~STAGE_ENTRY_VOICE_TOGGLE;
                        } else {
                            PlayStageSound(0x44, 5, TRUE);
                            entry->flags |= STAGE_ENTRY_VOICE_TOGGLE;
                        }
                    } else if (entry->flags & STAGE_ENTRY_ALT_VOICES) {
                        if (entry->flags & STAGE_ENTRY_VOICE_TOGGLE) {
                            PlayStageSound(entry->voiceSeqArc, entry->altHurtVoices[1], TRUE);
                            entry->flags &= ~STAGE_ENTRY_VOICE_TOGGLE;
                        } else {
                            PlayStageSound(entry->voiceSeqArc, entry->altHurtVoices[0], TRUE);
                            entry->flags |= STAGE_ENTRY_VOICE_TOGGLE;
                        }
                    } else if (entry->flags & STAGE_ENTRY_VOICE_TOGGLE) {
                        PlayStageSound(entry->voiceSeqArc, entry->hurtVoices[1], TRUE);
                        entry->flags &= ~STAGE_ENTRY_VOICE_TOGGLE;
                    } else {
                        PlayStageSound(entry->voiceSeqArc, entry->hurtVoices[0], TRUE);
                        entry->flags |= STAGE_ENTRY_VOICE_TOGGLE;
                    }
                } else if (entry->flags & STAGE_ENTRY_VOICE_TOGGLE) {
                    PlayStageSound(entry->voiceSeqArc, entry->hurtVoices[1], TRUE);
                    entry->flags &= ~STAGE_ENTRY_VOICE_TOGGLE;
                } else {
                    PlayStageSound(entry->voiceSeqArc, entry->hurtVoices[0], TRUE);
                    entry->flags |= STAGE_ENTRY_VOICE_TOGGLE;
                }
            } else if (!(entry->flags & STAGE_ENTRY_ENEMY)) {
                VecFx32 position = PositionOf(entry);

                position.x += FX32_ONE;
                MoveStageEntryTo(entry, &position, 2 * FX32_ONE, 15 * FX32_ONE);
            }
        } else if (entry->flags & STAGE_ENTRY_HURT) {
            if (!MatchesEitherSlotId(entry, entry->guardAnimation)) {
                SetSceneEntryAnimation(entry, entry->guardAnimation, 0, 0);
            }
        } else if (!(entry->flags & STAGE_ENTRY_ENEMY)) {
            VecFx32 position = PositionOf(entry);

            position.x += FX32_ONE;
            MoveStageEntryTo(entry, &position, 2 * FX32_ONE, 15 * FX32_ONE);
        }
        entry->stateStep++;
    case 5:
        entry->stateStep = 0;
        entry->flags &= ~STAGE_ENTRY_GUARDING;
        entry->flags &= ~STAGE_ENTRY_HURT;
        entry->flags &= ~STAGE_ENTRY_DODGED;
        entry->flags &= ~STAGE_ENTRY_GUARDED;
        break;
    }
}
