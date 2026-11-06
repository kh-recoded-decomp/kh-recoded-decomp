#include "nitro/types.h"

typedef struct FieldTimer {
    s32 timeLimit;
    u8 visible : 1;
    u8 running : 1;
    u8 countUp : 1;
    u8 restBits : 5;
} FieldTimer;

typedef struct FieldContext {
    u8 pad_00[0x29b0];
    FieldTimer timer;
} FieldContext;

extern FieldContext *gFieldSessionWork;
extern BOOL IsSessionFlagSet(int bit);
extern u32 ReadSessionPackedBits(int bit, int count);
extern void SetFieldTimerCounterMilliseconds(u32 value, s32 index);
extern BOOL StartCountdownTimer(int seconds, s32 userData);
extern void StartPanelScrollOut(int seconds);
extern void SetCounterHudEnabledIfActive(BOOL enable);
extern void ClearSessionFlagBit(int index);
extern void SetSessionFlagBit(int index);

/* The timer UI encodes count-up as 0 and count-down as 1 in userData. */
static inline s32 TimerDirectionUserData(BOOL countUp)
{
    return (s32)(countUp ? NULL : (void *)1);
}

void RestoreFieldTimer(void)
{
    FieldContext *context = gFieldSessionWork;
    FieldTimer *timer = &context->timer;
    u32 mode;
    s32 timeLimit;
    BOOL visible;
    BOOL running;
    BOOL countUp;

    if (context->timer.visible || !IsSessionFlagSet(0x35f0)) {
        return;
    }
    mode = ReadSessionPackedBits(0x35f1, 2);
    timeLimit = ReadSessionPackedBits(0x35e6, 10) * 1000;
    visible = IsSessionFlagSet(0x35f3);
    running = IsSessionFlagSet(0x35f4);
    countUp = TRUE;
    if (mode & 1) {
        countUp = FALSE;
    }
    timer->countUp = (u8)countUp;
    if (context->timer.countUp) {
        timer->timeLimit = timeLimit;
        SetFieldTimerCounterMilliseconds(0, 0);
    } else {
        SetFieldTimerCounterMilliseconds(timeLimit, 0);
    }
    if (!(mode & 2)) {
        StartCountdownTimer((u16)timeLimit, TimerDirectionUserData(context->timer.countUp));
    } else {
        StartPanelScrollOut((u16)timeLimit);
    }
    if (visible) {
        SetCounterHudEnabledIfActive(visible);
    }
    if (running) {
        ClearSessionFlagBit(0);
    } else {
        SetSessionFlagBit(0);
    }
}
