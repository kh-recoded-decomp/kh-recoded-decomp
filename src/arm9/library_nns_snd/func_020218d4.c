/* Sets a fader’s origin to its current value, stores a target and duration, and resets its progress counter.
 * Uncertainty: The duration scale is determined by callers. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nns/snd/calls/func_0201e144.c.
 * Original routine: func_0201e144. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000




typedef struct NNSSndFader {
    int origin;
    int target;
    int counter;
    int frame;
} NNSSndFader;
int func_020218fc(const NNSSndFader * fader);
extern int func_020218fc (const NNSSndFader * fader);

/* func_020218d4 -- NitroSystem fader.c: NNSi_SndFaderSet. */
void func_020218d4 (NNSSndFader * fader, int target, int frame)
{

    fader->origin = func_020218fc(fader);
    fader->target = target;
    fader->frame = frame;
    fader->counter = 0;

}
