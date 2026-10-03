#include "nitro/types.h"

typedef struct {
    s32 mode;
    u32 flags;
    s32 action;
    s32 savedValue;
    u8 pad_10[0x1c];
    s32 soundEmitter;
} AiState;

typedef struct {
    u8 pad_00[2];
    u16 locked;
} EnemyStats;

typedef struct {
    u8 pad_000[0x1d4];
    EnemyStats *stats;
    u8 pad_1d8[0x9ac - 0x1d8];
    u64 stateFlags;
    u8 pad_9b4[0x1258 - 0x9b4];
    AiState ai;
} Enemy;

extern void InitRecordEntry_020d4500(AiState *ai);
extern int func_ov001_0206db8c(int index);
extern void StopAndClearSoundEmitter_020a8e14(s32 groupId, s32 emitterIndex);
extern void FinishEnemyRecovery_020d6c78(Enemy *enemy);
extern void SetEntityModeEnabled_020ce7a0(Enemy *enemy, int mode, int enabled);

void SetEnemyModeEnabled_020d6958(Enemy *enemy, int mode, int enabled)
{
    AiState *ai = &enemy->ai;
    s32 saved;
    s32 emitter;

    switch (mode) {
    case 0:
        if (enabled != 0) {
            saved = ai->savedValue;
            InitRecordEntry_020d4500(ai);
            ai->savedValue = saved;
        }
        break;
    case 2:
        if (enabled != 0) {
            if (enemy->stats->locked != 0) {
                break;
            }
            if ((enemy->stateFlags & 0x800000) == 0) {
                enemy->stateFlags |= 0x40000000;
                break;
            }
            FinishEnemyRecovery_020d6c78(enemy);
        } else {
            emitter = ai->soundEmitter;
            if (emitter >= 0) {
                StopAndClearSoundEmitter_020a8e14(func_ov001_0206db8c(8), emitter);
                ai->soundEmitter = -1;
            }
            if ((enemy->stateFlags & 0x80000000) == 0) {
                break;
            }
            if (enemy->stats->locked != 0) {
                break;
            }
            if ((enemy->stateFlags & 0x800000) == 0) {
                break;
            }
            FinishEnemyRecovery_020d6c78(enemy);
        }
        break;
    }
    SetEntityModeEnabled_020ce7a0(enemy, mode, enabled);
}
