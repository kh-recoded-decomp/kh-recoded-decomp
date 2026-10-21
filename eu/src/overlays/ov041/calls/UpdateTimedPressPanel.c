#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

#define PAD_BUTTON_A 0x0001
#define PAD_BUTTON_Y 0x0800

extern u16 data_02060500;
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void PlaceSlotPanelAtWorldPosition(int panel, const VecFx32 *position, BOOL lit);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);

/* The press panel (3) goes above the other entry's edge when the player attacks, the player's own (2) at the
 * panel offset when it defends. */
static inline void PlacePressPanel(StageEntry *player, StageEntry *other, BOOL playerFirst, BOOL lit)
{
    VecFx32 position;
    int panel;

    if (playerFirst) {
        panel = 3;
        GetPositionAboveGround(&position, other);
        position.x += other->radius;
        position.y += 0x1ccd;
    } else {
        panel = 2;
        GetPositionAboveGround(&position, player);
        VEC_Add(&position, &data_ov041_020cff48.panelOffset, &position);
    }
    PlaceSlotPanelAtWorldPosition(panel, &position, lit);
}

/*
 * The timed press of a player entry against another: sets where its defending panel shows, then (unless the
 * player is at 0 hp or timed input is off) checks A when attacking or Y when defending; a press in time marks
 * the player and plays the press sound. The panel is drawn lit once pressed.
 */
void UpdateTimedPressPanel(StageEntry *player, StageEntry *other, BOOL playerFirst)
{
    StageWork *work = gMovieContextState->stageWork;
    BOOL pressed = FALSE;

    data_ov041_020cff48.panelOffset.x = -FX_Mul(player->radius, 0x68f);
    data_ov041_020cff48.panelOffset.y = FX_Mul(player->radius, 0x2548);
    data_ov041_020cff48.panelOffset.z = 0;
    if (player->hp == 0) {
        return;
    }
    if (work->flags & STAGE_WORK_NO_TIMED_INPUT) {
        return;
    }
    if (player->flags & STAGE_ENTRY_TIMED_PRESS) {
        if (player->flags & STAGE_ENTRY_PRESS_PANEL) {
            PlacePressPanel(player, other, playerFirst, TRUE);
        }
        return;
    }
    if (!playerFirst && player->statuses[STAGE_ENTRY_STATUS_9] > 0) {
        player->flags |= STAGE_ENTRY_PRESS_PANEL | STAGE_ENTRY_PRESSED_GUARD;
        player->flags |= STAGE_ENTRY_TIMED_PRESS;
        return;
    }
    if (playerFirst) {
        if (data_02060500 & PAD_BUTTON_A) {
            pressed = TRUE;
        }
    } else if (data_02060500 & PAD_BUTTON_Y) {
        pressed = TRUE;
    }
    if (pressed) {
        if (playerFirst) {
            player->flags |= STAGE_ENTRY_PRESS_PANEL | STAGE_ENTRY_PRESSED_ATTACK;
        } else {
            player->flags |= STAGE_ENTRY_PRESS_PANEL | STAGE_ENTRY_PRESSED_GUARD;
        }
        player->flags |= STAGE_ENTRY_TIMED_PRESS;
        PlayStageSound(0x1a0, 0x2c, TRUE);
    }
    PlacePressPanel(player, other, playerFirst, pressed);
}
