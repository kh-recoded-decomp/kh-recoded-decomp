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

#define SND_COMMAND_NOBLOCK 0

typedef enum SNDCommandID {
    SND_COMMAND_START_SEQ,
    SND_COMMAND_STOP_SEQ,
    SND_COMMAND_PREPARE_SEQ,
    SND_COMMAND_START_PREPARED_SEQ,
    SND_COMMAND_PAUSE_SEQ,
    SND_COMMAND_SKIP_SEQ,
    SND_COMMAND_PLAYER_PARAM,
    SND_COMMAND_TRACK_PARAM,
    SND_COMMAND_MUTE_TRACK,
    SND_COMMAND_ALLOCATABLE_CHANNEL,
    SND_COMMAND_PLAYER_LOCAL_VAR,
    SND_COMMAND_PLAYER_GLOBAL_VAR,
    SND_COMMAND_START_TIMER,
    SND_COMMAND_STOP_TIMER,
    SND_COMMAND_SETUP_CHANNEL_PCM,
    SND_COMMAND_SETUP_CHANNEL_PSG,
    SND_COMMAND_SETUP_CHANNEL_NOISE,
    SND_COMMAND_SETUP_CAPTURE,
    SND_COMMAND_SETUP_ALARM,
    SND_COMMAND_CHANNEL_TIMER,
    SND_COMMAND_CHANNEL_VOLUME,
    SND_COMMAND_CHANNEL_PAN,
    SND_COMMAND_SURROUND_DECAY,
    SND_COMMAND_MASTER_VOLUME,
    SND_COMMAND_MASTER_PAN,
    SND_COMMAND_OUTPUT_SELECTOR,
    SND_COMMAND_LOCK_CHANNEL,
    SND_COMMAND_UNLOCK_CHANNEL,
    SND_COMMAND_STOP_UNLOCKED_CHANNEL,
    SND_COMMAND_SHARED_WORK,
    SND_COMMAND_INVALIDATE_SEQ,
    SND_COMMAND_INVALIDATE_BANK,
    SND_COMMAND_INVALIDATE_WAVE,
    SND_COMMAND_READ_DRIVER_INFO
} SNDCommandID;
typedef struct SNDCommand {
    struct SNDCommand * next;
    SNDCommandID id;
    u32 arg[4];
} SNDCommand;
const SNDCommand * func_0200eec0(u32 flags);
BOOL func_0200f080(u32 flags);
void func_0201e544(void);
void func_0201d974(void);
void func_02020388(void);

void func_0201d290 (void)
{
    while (func_0200eec0(SND_COMMAND_NOBLOCK) != NULL) {
    }

    func_0201d974();
    func_0201e544();
#ifndef SDK_SMALL_BUILD
    func_02020388();
#endif

    (void)func_0200f080(SND_COMMAND_NOBLOCK);
}
