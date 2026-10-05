#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageEvent {
    u16 entryId;
    u16 state;
    u16 spawnArg;
    u16 activeCount;
    s8 lives;
    u8 spawnOnTimer : 1;
    u8 resetOnTimer : 1;
    u8 flags_2 : 2;
    u8 enabled : 1;
    u8 ignoreGate : 1;
    u8 spawned : 1;
    u8 flags_7 : 1;
    s16 firstEvent;
    s16 lastEvent;
    u8 resetPending;
    u8 pad_0f[5];
    s32 timer;
    s32 cooldown;
    VecFx32 origin;
} StageEvent;

typedef struct StageEventParams {
    u8 pad_00[4];
    u32 active;
    u8 pad_08[0x10];
    VecFx32 position;
    fx32 spawnRadius;
    fx32 resetRadius;
} StageEventParams;

typedef struct StageEventRecord {
    s32 mode;
    u16 active : 1;
    u16 flags4_1 : 2;
    u16 disabled : 1;
    u16 flags4_4 : 9;
    u16 alwaysCounted : 1;
    u16 flags4_14 : 2;
    u16 flags6_0 : 7;
    u16 hidden : 1;
    u16 flags6_8 : 8;
    u8 pad_08;
    u8 kind;
    u8 pad_0a[4];
    u16 type;
    u16 actorId;
    u8 pad_12[0x5e];
    s32 remaining;
    u8 pad_74[0x1c8 - 0x74];
} StageEventRecord;

typedef struct StageState {
    u32 flags;
    u8 pad_004[0x204];
    StageEvent *events;
    u8 pad_20c[4];
    StageEventRecord *records;
    u8 pad_214[0x18de8 - 0x214];
    u16 eventCount;
    u8 pad_18dea[0x18e5c - 0x18dea];
    fx32 minPlayerHeight;
    u8 pad_18e60[0x18f2d - 0x18e60];
    s8 cutscenePending;
    u8 pad_18f2e[6];
    u32 cutsceneActive;
    u8 pad_18f38[8];
    s32 delay;
} StageState;

extern StageState *data_ov001_020a0508;
extern int Session_Exists_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern BOOL func_ov001_020645c8(u32 value);
extern u32 GetGlobalScaleValue_0209c3cc(void);
extern StageEventParams *GetLargeTableEntry_0209c30c(u32 index);
extern void ResetGroupRows_0209ca00(u32 index);
extern u32 func_ov001_0209c584(u32 mask);
extern void SyncStageEntryPosition_02098fbc(u32 id, VecFx32 *outPosition);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern int ProjectWorldPositionToScreen_02019f84(const VecFx32 *pWorld, int *px, int *py);
extern void SpawnStageEventGroups_0209895c(StageEvent *event);
extern StageState *func_ov001_0209c3c0(void);
extern void ResetGroupCommandState_02095880(StageEventRecord *record);
extern int func_ov001_020644b0(void);
extern unsigned int random_next_scaled_0202aa04(unsigned int upperBound);

static inline s32 GetSessionMode(void)
{
    if (Session_Exists_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}

static inline BOOL ShouldSpawnEvent(StageEvent *event)
{
    StageEventParams *params = GetLargeTableEntry_0209c30c(event->entryId);
    s32 mode;
    VecFx32 pos;
    VecFx32 delta;
    int screenX;
    int screenY;
    BOOL result;

    if (func_ov001_0209c584(2) != 0 && (event->spawnArg == 0 || event->spawnArg == 0xffff) && !event->ignoreGate) {
        result = FALSE;
    } else {
        if (event->spawnOnTimer && event->timer <= 0) {
            result = TRUE;
        } else {
            mode = GetSessionMode();
            if (mode == 0 || mode != 4) {
                fx32 dist;
                BOOL inRange;

                SyncStageEntryPosition_02098fbc(1, &pos);
                VEC_Subtract_01ff9e3c(&pos, &params->position, &delta);
                dist = VEC_Mag_01ff9f28(&delta);
                inRange = FALSE;
                if (params->spawnRadius != 0 && dist < params->spawnRadius) {
                    inRange = TRUE;
                }
                result = TRUE;
                if (!inRange) {
                    result = FALSE;
                }
            } else {
                pos = params->position;
                if (params->spawnRadius > 0xa000) {
                    params->spawnRadius = 0x3000;
                }
                pos.x -= params->spawnRadius;
                ProjectWorldPositionToScreen_02019f84(&pos, &screenX, &screenY);
                if (screenX > 0 && screenX < 0x100) {
                    result = TRUE;
                } else {
                    pos = params->position;
                    ProjectWorldPositionToScreen_02019f84(&pos, &screenX, &screenY);
                    if (screenX > 0 && screenX < 0x100) {
                        result = TRUE;
                    } else {
                        result = FALSE;
                    }
                }
            }
        }
    }
    return result;
}

static inline BOOL ShouldResetEvent(StageEvent *event)
{
    StageEventParams *params = GetLargeTableEntry_0209c30c(event->entryId);
    s32 mode;
    VecFx32 pos;
    VecFx32 delta;
    int screenX;
    int screenY;
    BOOL result;

    if (func_ov001_0209c584(2) != 0 && (event->spawnArg == 0 || event->spawnArg == 0xffff) && !event->ignoreGate) {
        result = TRUE;
    } else {
        if (event->resetOnTimer && event->timer <= 0) {
            result = TRUE;
        } else {
            mode = GetSessionMode();
            if (mode == 0 || mode != 4) {
                StageState *manager;
                fx32 dist;
                BOOL outOfRange;

                result = TRUE;
                SyncStageEntryPosition_02098fbc(1, &pos);
                manager = func_ov001_0209c3c0();
                if (manager == NULL || manager->minPlayerHeight == 0 || manager->minPlayerHeight <= pos.y) {
                    VEC_Subtract_01ff9e3c(&pos, &params->position, &delta);
                    dist = VEC_Mag_01ff9f28(&delta);
                    outOfRange = FALSE;
                    if (params->resetRadius != 0 && dist > params->resetRadius) {
                        outOfRange = TRUE;
                    }
                    result = TRUE;
                    if (!outOfRange) {
                        result = FALSE;
                    }
                }
            } else {
                if (params->resetRadius != 0) {
                    BOOL visible;

                    pos = params->position;
                    pos.x += params->resetRadius;
                    visible = ProjectWorldPositionToScreen_02019f84(&pos, &screenX, &screenY);
                    if (screenX < 0x80) {
                        result = TRUE;
                        if (!visible) {
                            result = FALSE;
                        }
                        goto done;
                    }
                }
                result = FALSE;
            }
        }
    }
done:
    return result;
}

int UpdateStageEventSpawns_02099c28(void)
{
    StageState *state = data_ov001_020a0508;
    int i;

    if (state->delay != 0) {
        if (state->delay < 0) {
            return 0;
        }
        if (state->flags & 1) {
            return 0;
        }
        if (GetSessionMode() == 10 && func_ov001_020645c8(0x380c)) {
            data_ov001_020a0508->delay = 0;
        }
        data_ov001_020a0508->delay -= GetGlobalScaleValue_0209c3cc();
        if (data_ov001_020a0508->delay > 0) {
            return 0;
        }
        data_ov001_020a0508->delay = 0;
    }
    for (i = 0; i < data_ov001_020a0508->eventCount; i++) {
        StageEvent *event = &data_ov001_020a0508->events[i];
        StageEventParams *params = GetLargeTableEntry_0209c30c(event->entryId);

        if (!event->enabled) {
            continue;
        }
        if (event->cooldown > 0) {
            event->cooldown -= GetGlobalScaleValue_0209c3cc();
            if (event->cooldown < 0) {
                event->cooldown = 0;
            }
        }
        if (Session_Exists_02063a24() && func_ov001_020645c8(0x3630) && event->lives < 0) {
            event->lives = 0;
        }
        if (params->active == 0 || event->state != 2) {
            continue;
        }
        if (event->timer != 0) {
            event->timer -= GetGlobalScaleValue_0209c3cc();
            if (event->timer <= 0) {
                event->timer = 0;
                ResetGroupRows_0209ca00(event->entryId);
            }
        } else {
            int index;
            int slot;
            u16 alive;
            BOOL respawn;

            if (ShouldSpawnEvent(event)) {
                SpawnStageEventGroups_0209895c(event);
            } else if (ShouldResetEvent(event)) {
                StageState *manager = func_ov001_0209c3c0();

                for (index = event->firstEvent; index <= event->lastEvent; index++) {
                    ResetGroupCommandState_02095880(&manager->records[index]);
                }
                event->resetPending = 0;
            }
            event->activeCount = 0;
            for (slot = event->firstEvent; slot <= event->lastEvent; slot++) {
                if (state->records[slot].actorId != 0) {
                    event->activeCount++;
                }
                if (state->records[slot].type == 99 && state->records[slot].remaining != 0 && state->records[slot].active) {
                    event->activeCount++;
                }
            }
            alive = 0;
            for (index = event->firstEvent; index <= event->lastEvent; index++) {
                StageEventRecord *record = &state->records[index];

                if (!record->disabled && !record->hidden) {
                    if (record->alwaysCounted) {
                        alive++;
                    } else if (record->remaining > 0) {
                        alive++;
                    }
                    if (record->kind != 4) {
                        if (record->mode != 1) {
                            alive++;
                        }
                    } else if (state->cutsceneActive != 0 || state->cutscenePending != 0) {
                        alive++;
                    }
                }
            }
            if (alive == 0) {
                s8 lives = event->lives;

                respawn = FALSE;
                if (lives < 0) {
                    respawn = TRUE;
                } else if (lives > 0) {
                    respawn = TRUE;
                    event->lives = lives - 1;
                }
                event->resetPending = 0;
                if (respawn) {
                    event->timer = 0x1e000;
                    if (func_ov001_020644b0() == 700 && event->lives < 0) {
                        event->timer = (random_next_scaled_0202aa04(10) + 20) * 0x1e000;
                    }
                } else {
                    event->state = 7;
                }
            }
        }
    }
    return 0;
}
