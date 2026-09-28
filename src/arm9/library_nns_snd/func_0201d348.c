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

void func_0200ebc0(u32 chBitMask, u32 flags);

typedef struct NNSCaptureLockState {
    u32 captureLock;
    u32 alarmLock;
    u32 channelLock;
} NNSCaptureLockState;
extern NNSCaptureLockState data_0205d894;
#define sAlarmLock data_0205d894.alarmLock
#define sChannelLock data_0205d894.channelLock

void func_0201d348 (u32 chBitFlag)
{

    if (chBitFlag == 0) return;

    func_0200ebc0(chBitFlag, 0);

    sChannelLock &= ~chBitFlag;
}
