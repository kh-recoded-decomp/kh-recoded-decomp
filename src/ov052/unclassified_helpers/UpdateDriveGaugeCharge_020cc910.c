#include "nitro/types.h"

typedef struct {
    u8 id;
    u8 pad_01[0x11];
    u16 angle;
    u8 pad_14[0x10];
    s8 level;
    u8 visible;
    s16 count;
    u8 pad_28[4];
} MarkerRequest;

typedef struct {
    int rates[4];
} GaugeRates;

typedef struct {
    u8 pad_00[6];
    u16 triggered;
} StepTimer;

typedef struct {
    u8 pad_00[2];
    u16 gauge;
} ActorInfo;

typedef struct {
    u8 pad_0000[0x1d4];
    ActorInfo *info;
    u8 pad_01d8[0x9b4 - 0x1d8];
    u8 player;
    u8 pad_09b5[3];
    int kind;
    u8 pad_09bc[4];
    int stageType;
    u8 pad_09c4[0x9ec - 0x9c4];
    int frameStep;
    u8 pad_09f0[0x1037 - 0x9f0];
    s8 palette;
    u8 pad_1038[0x10d4 - 0x1038];
    StepTimer gaugeTimer;
    StepTimer healTimer;
} Actor;

extern const GaugeRates data_ov052_020d20ec;
extern s32 func_ov001_02063a38(void);
extern int func_ov001_02064784(void);
extern u32 func_ov001_02064490(void);
extern s32 GetClampedPaletteSlot_02073598(void);
extern int func_02023dbc(int value, int scale);
extern int AdvanceTimerWithCarry_020cca9c(StepTimer *timer, int step, int amount);
extern int AdvanceStepTimer_020ccac8(StepTimer *timer, int step, int value);
extern void AddGaugePoints_02073074(int delta, BOOL loadNow);
extern void ClearHandleActiveFlags_0204ffd0(void);
extern u32 func_ov001_0207b560(s32 index);
extern void MarkTaggedEntry_0204ff7c(u32 id);
extern BOOL IsFieldFlag16Set_020735b8(void);
extern void func_ov021_020a8ab4(MarkerRequest *request);
extern int func_ov021_020a8ca0(MarkerRequest *request, int groupId);
extern int func_ov001_0206db8c(int index);
extern u16 GetLinkedAngleOffset_020ceb7c(Actor *actor);
extern void PlaySoundChecked_0204d8d0(void *ptr, int arg);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern void ApplyScaledHealthDelta_020a7620(Actor *actor, s32 amount, BOOL force);

void UpdateDriveGaugeCharge_020cc910(Actor *actor)
{
    BOOL charging = TRUE;
    int i;
    int level;
    int heal;
    GaugeRates rates;
    MarkerRequest request;

    if (actor->kind != 0 || actor->info->gauge == 0 || func_ov001_02063a38() == 6) {
        return;
    }
    if (actor->stageType == 0x18) {
        charging = FALSE;
    }
    if (func_ov001_02064784() == 5 && actor->stageType == 0x1f) {
        charging = FALSE;
    }
    if (charging) {
        StepTimer *timer = &actor->gaugeTimer;
        int rate;
        int amount;
        rates = data_ov052_020d20ec;
        rate = func_02023dbc(rates.rates[GetClampedPaletteSlot_02073598()], 100);
        amount = (int)(((s64)rate * 0x400 + 0x800) >> 12);
        if (!func_ov001_02064490()) {
            int gain = AdvanceTimerWithCarry_020cca9c(timer, actor->frameStep, amount);
            if (gain > 0) {
                AddGaugePoints_02073074(-gain, FALSE);
                timer->triggered = 1;
            }
        }
    }
    level = GetClampedPaletteSlot_02073598();
    ClearHandleActiveFlags_0204ffd0();
    for (i = 0; i < 4; i++) {
        u32 entry = func_ov001_0207b560(i);
        if (i > level) {
            break;
        }
        MarkTaggedEntry_0204ff7c(entry);
    }
    if (IsFieldFlag16Set_020735b8()) {
        level = 4;
    }
    if (actor->palette < level && level > 0) {
        func_ov021_020a8ab4(&request);
        request.id = actor->player;
        request.visible = 1;
        request.count = 1;
        request.angle = GetLinkedAngleOffset_020ceb7c(actor) + 0x8000;
        request.level = level - 1;
        if (level != 4) {
            PlaySoundChecked_0204d8d0(NULL, 0x43);
        } else {
            PlaySoundChecked_0204d8d0(NULL, 0x44);
        }
        func_ov021_020a8ca0(&request, func_ov001_0206db8c(6));
    }
    actor->palette = level;
    if (IsPlayerEntryFlagSet_02050014(actor->player, 0x44)) {
        heal = AdvanceStepTimer_020ccac8(&actor->healTimer, actor->frameStep, 0x6400);
        if (heal > 0) {
            if (heal < 0x1000) {
                heal = 0x1000;
            }
            ApplyScaledHealthDelta_020a7620(actor, heal, FALSE);
        }
    }
}
