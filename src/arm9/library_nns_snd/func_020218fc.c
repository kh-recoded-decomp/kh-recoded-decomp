/* Computes the current fader value by linear interpolation, returning the target once the counter reaches the frame limit.
 * Uncertainty: The integer scale and external interpretation are caller-defined. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nns/snd/calls/func_0201e16c.c.
 * Original routine: func_0201e16c. External references are
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

/* func_020218fc -- NitroSystem fader.c: NNSi_SndFaderGet. */
int func_020218fc (const NNSSndFader * fader)
{
    s64 value;


    if (fader->counter >= fader->frame) {
        return fader->target;
    }

    value = (fader->target - fader->origin)
            * fader->counter / fader->frame
            + fader->origin;

    return (int)value;
}
