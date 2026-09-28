typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef unsigned short vu16;
typedef unsigned int vu32;
typedef unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

typedef struct SNDCommand {
    struct SNDCommand *next;
    u32 id;
    u32 arg[4];
} SNDCommand;

enum {
    SND_COMMAND_START_SEQ = 0,
    SND_COMMAND_STOP_SEQ = 1,
    SND_COMMAND_PREPARE_SEQ = 2,
    SND_COMMAND_START_PREPARED_SEQ = 3,
    SND_COMMAND_PAUSE_SEQ = 4,
    SND_COMMAND_CHANNEL_PAN = 0x15,
    SND_COMMAND_LOCK_CHANNEL = 0x1a,
    SND_COMMAND_UNLOCK_CHANNEL = 0x1b
};
#define SND_COMMAND_NOBLOCK 0
#define SND_COMMAND_BLOCK 1

extern void PushCommand_impl(int command, u32 arg0, u32 arg1, u32 arg2, u32 arg3);
#define PushCommand(c, a0, a1, a2, a3) PushCommand_impl((c), (u32)(a0), (u32)(a1), (u32)(a2), (u32)(a3))

typedef struct SNDBinaryFileHeader {
    char signature[4];
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} SNDBinaryFileHeader;

typedef struct SNDBinaryBlockHeader {
    u32 kind;
    u32 size;
} SNDBinaryBlockHeader;

typedef struct SNDWaveArcLink {
    struct SNDWaveArc *waveArc;
    struct SNDWaveArcLink *next;
} SNDWaveArcLink;

typedef struct SNDWaveArc {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    SNDWaveArcLink *topLink;
    u32 reserved[7];
    u32 waveCount;
    u32 waveOffset[0];
} SNDWaveArc;

typedef struct SNDWaveData SNDWaveData;

#define SND_BANK_TO_WAVEARC_MAX 4
typedef struct SNDBankData {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    SNDWaveArcLink waveArcLink[SND_BANK_TO_WAVEARC_MAX];
    u32 instCount;
    u32 instOffset[0];
} SNDBankData;

extern void func_0200edc8(void);
extern void func_0200eddc(void);
#define SNDi_LockMutex func_0200edc8
#define SNDi_UnlockMutex func_0200eddc
extern void DC_StoreRange(void *addr, u32 size);

const SNDWaveData *func_0200fad0(const SNDWaveArc *waveArc, int index)
{
    const SNDWaveData *wave;
    u32 offset;

    SNDi_LockMutex();

    offset = waveArc->waveOffset[index];

    if (offset != 0) {
        if (offset < HW_MAIN_MEM)
            wave = (const SNDWaveData *)((u8 *)waveArc + offset);
        else
            wave = (const SNDWaveData *)offset;
    } else {
        wave = NULL;
    }

    SNDi_UnlockMutex();

    return wave;
}
