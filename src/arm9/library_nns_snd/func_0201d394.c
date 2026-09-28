/* Adapted from CC0 khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e. */
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


#define SND_ALARM_NUM 8



typedef struct NNSCaptureLockState {
    u32 captureLock;
    u32 alarmLock;
    u32 channelLock;
} NNSCaptureLockState;
extern NNSCaptureLockState data_0205d894;
#define sAlarmLock data_0205d894.alarmLock
#define sChannelLock data_0205d894.channelLock

/* func_0201d394 -- NitroSystem resource_mgr.c: NNS_SndAllocAlarm. */
int func_0201d394 (void)
{
    int alarmNo;
    u32 mask = 1;

    for (alarmNo = 0; alarmNo < SND_ALARM_NUM; alarmNo++, mask <<= 1) {
        if ((sAlarmLock & mask) == 0) {
            sAlarmLock |= mask;
            return alarmNo;
        }
    }

    return -1;
}
