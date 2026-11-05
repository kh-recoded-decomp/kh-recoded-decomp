#include "nitro/types.h"

typedef struct {
    s32 mode;
    u32 flags;
    s32 request;
    u8 pad_0c[0x04];
    s32 pendingAction;
} AiState;

typedef struct {
    u8 pad_0000[0x9ac];
    u64 statusFlags;
    u8 pad_09b4[0x1034 - 0x9b4];
    u8 action;
    u8 pad_1035[0x1258 - 0x1035];
    AiState ai;
} Enemy;

extern void StartEnemyLaunch(Enemy *enemy);
extern BOOL AcquireEnemyTargetWithFallback(Enemy *enemy);

void ProcessEnemyAiRequest(Enemy *enemy)
{
    AiState *ai = &enemy->ai;

    switch (ai->request) {
    case 3:
        ai->flags |= 0x100000;
        StartEnemyLaunch(enemy);
        break;
    case 2:
        if ((enemy->statusFlags & 0x20820) == 0 && !(ai->flags & 0x100000)) {
            ai->flags = (ai->flags & ~0x4000) | 0x80000;
            AcquireEnemyTargetWithFallback(enemy);
            enemy->action = ai->pendingAction;
        }
        break;
    }
    ai->request = 0;
}
