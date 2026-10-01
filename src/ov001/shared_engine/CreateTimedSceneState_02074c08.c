#include "nitro/types.h"

typedef struct IdList5 {
    u32 ids[5];
} IdList5;

typedef struct TimerSlot {
    s32 duration;
    s32 elapsed;
    u8 pad_08[0x14];
} TimerSlot;

typedef struct BattleHudState {
    u8 pad_000[0x30];
    s32 active;
    u8 pad_034[0x10];
    s32 unk_44;
    u8 pad_048[4];
    s32 speed;
    u8 pad_050[0x8c];
    TimerSlot timers[3];
    s32 lastDuration;
    s32 lastElapsed;
    u8 pad_138[0xc];
    void *records[5];
} BattleHudState;

extern const IdList5 data_ov001_0209de74;
extern BattleHudState *data_ov001_020a04ac;
extern void *GetSceneTagTracker_020711b0(void);
extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_01ff8830(void *dst, int value, u32 size);
extern void func_ov001_020743c0(int arg);
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void func_ov001_02074d14();

void *CreateTimedSceneState_02074c08(int arg)
{
    void *pool;
    IdList5 list;
    int i;
    BattleHudState *state;

    pool = GetSceneTagTracker_020711b0();
    list = data_ov001_0209de74;
    state = NNSi_FndGetCurrentRootHeap_0202a764();
    data_ov001_020a04ac = state;
    func_01ff8830(state, 0, sizeof(BattleHudState));
    state->active = 1;
    func_ov001_020743c0(arg);
    state->timers[0].duration = 0x3d5d;
    state->timers[0].elapsed = 0;
    state->timers[1].duration = 0x28e9;
    state->timers[1].elapsed = 0;
    state->timers[2].duration = 0x3d5d;
    state->timers[2].elapsed = 0;
    state->lastDuration = 0x3d5d;
    state->lastElapsed = 0;
    if (state->speed < 1) {
        state->speed = 1;
    }
    state->unk_44 = 0;
    for (i = 0; i < 5; i++) {
        state->records[i] = FindActiveRecordById_020b8184(pool, list.ids[i]);
    }
    return func_ov001_02074d14;
}
