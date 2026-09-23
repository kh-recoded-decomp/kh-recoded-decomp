/* Services one movie frame alarm, advances consumed-frame state, chooses or releases a decode buffer, and schedules the next frame deadline.
 * Evidence: MobiClip frame timer fields, front-buffer callback, frame counters, time base, and OS alarm calls in source.
 * Uncertainty: Decoder callback argument meanings are inferred from surrounding MobiClip code; preserve opaque callees.
 * Source: src/overlays/ov024/calls/func_ov024_0208421c.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long s64;

#define TICKS_PER_FRAME_NUMERATOR 0x000007fd88400000ULL

struct MobiClipFrameTimer {
    void *pDecoder;
    u8 alarm[0x2c];
    s64 nStartTick;
    u8 nState;
    u8 nFrontBuffer;
    u8 bPrimed;
    u8 pad003b;
    u32 pad003c;
    int nDecoded;
    u32 nConsumed;
    int nPresented;
    u64 nTimeBase;
    int (*pfnBufferForIndex)(int nIndex);
};

extern void func_020a935c(void *pDecoder);
extern void func_020a9338(void *pDecoder, int nValue, int nCount, int nFlags);
extern void movie_frame_alarm_callback_020a7f3c(struct MobiClipFrameTimer *frameTimer);
extern s64 func_02003fd4(void);
extern void OS_SetAlarm(void *pAlarm, u64 nTick, void *pfnHandler, void *pArg);

void movie_frame_alarm_callback_020a7f3c(struct MobiClipFrameTimer *frameTimer)
{
    int decodedAhead = frameTimer->nDecoded - (int)frameTimer->nConsumed;
    s64 elapsedTicks;
    u64 nextDeadline;

    if (decodedAhead > 0) {
        if (decodedAhead <= 3 && frameTimer->nState < 4) {
            func_020a935c(frameTimer->pDecoder);
        } else if (frameTimer->bPrimed == 0) {
            OS_SetAlarm(frameTimer->alarm, 1, (void *)&movie_frame_alarm_callback_020a7f3c, frameTimer);
            return;
        } else {
            func_020a9338(frameTimer->pDecoder,
                                frameTimer->pfnBufferForIndex((signed char)frameTimer->nFrontBuffer),
                                0x100, 0);
            frameTimer->bPrimed = 0;
        }
    } else if (frameTimer->bPrimed == 0) {
        OS_SetAlarm(frameTimer->alarm, 1, (void *)&movie_frame_alarm_callback_020a7f3c, frameTimer);
        return;
    } else {
        frameTimer->bPrimed = 0;
    }

    frameTimer->nConsumed++;
    elapsedTicks = func_02003fd4() - frameTimer->nStartTick;
    nextDeadline = (frameTimer->nConsumed + 1) * TICKS_PER_FRAME_NUMERATOR / frameTimer->nTimeBase;
    OS_SetAlarm(frameTimer->alarm, nextDeadline - elapsedTicks,
                (void *)&movie_frame_alarm_callback_020a7f3c, frameTimer);
}
